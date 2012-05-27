#include <QThread>

#include <cstdio>
#include <cerrno>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>


#include <api/supervisor.h>

// ================================================================================

#define __LOGE(x...) printf(x)

static int init_transport(int *sock) {
    struct sockaddr_nl nladdr;
    int ret = 0;

    *sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_SUPERVISOR);
    if (*sock < 0) {
	__LOGE("Failed to create NETLINK socket: %s\n", strerror(errno));
	return *sock;
    }

    /* source address */
    nladdr.nl_family = AF_NETLINK;
    nladdr.nl_pad = 0;
    nladdr.nl_pid = 0;
    nladdr.nl_groups = ANDCONT_SUPERVISOR_KERNEL_EVENT_MC_GROUP;
    ret = bind(*sock, (struct sockaddr*)&nladdr, sizeof(nladdr));
    if (ret) {
	__LOGE("Failed to bind to the Netlink address: %s\n", strerror(errno));
    }
    return ret;
}

static andcont_msg_event_t* recv_sup_msg(int sock) {
    static char buf[NLMSG_LENGTH(sizeof(andcont_msg_event_t))];

    struct nlmsghdr* h = (struct nlmsghdr*)buf;

    for (;;) {
	int res = recv(sock, buf, sizeof(buf), 0);

	if (res > 0) {
	    break;
	} else if (res < 0 && errno != EINTR) {
	    __LOGE("Failed to receive a supervisor message: %s\n", strerror(errno));
	    return NULL;
	}
    }

    if (h->nlmsg_type != ANDCONT_SUPERVISOR_MSG_EVENT) {
	return NULL;
    }

    return (andcont_msg_event_t*)NLMSG_DATA(h);
}


class SupervisorListener : public QThread {
    Q_OBJECT

public:
    SupervisorListener() : QThread(NULL) { }

protected:
    void run() {
	int sk;

	if (init_transport(&sk) < 0) {
	    return;
	}

	for (;;) {
	    __LOGE("Waiting for the supervisor\n");

	    andcont_msg_event_t* ev = recv_sup_msg(sk);

	    __LOGE("Received a message from the supervisor\n");

	    if (!ev) {
		return;
	    }

	    if (ev->event == ANDCONT_SUPERV_EVENT_FOREGROUND_CHANGED && (size_t)ev->arg == 1) {
		__LOGE("Switched to root\n");

 		emit switchedToRoot();
	    }

	    if (ev->event == ANDCONT_SUPERV_EVENT_PHONE_ADDED) {
		__LOGE("Phone added\n");

		emit phoneAdded();
	    }
	}
    }

signals:
    void switchedToRoot();
    void phoneAdded();
};
