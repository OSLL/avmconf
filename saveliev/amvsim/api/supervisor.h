#ifndef _ANDCONT_SUPERVISOR_H
#define _ANDCONT_SUPERVISOR_H

// The Netlink interface

#define NETLINK_SUPERVISOR 17             // The AndCont supervisor protocol number

#define NL_MC_GROUP_MASK(group) (1 << (group-1))

#define ANDCONT_SUPERVISOR_KERNEL_EVENT_MC_GROUP 1 // The phone event subscriber multicast group


#define ANDCONT_NL_MK_TYPE(subsys, msg) (((subsys) << 8) | msg)
#define ANDCONT_NL_SUBSYS(type) ((type) >> 8)

#define ANDCONT_SUBSYS_KERNEL 1       // The message destined to/originated from the kernel supervisor
#define ANDCONT_SUBSYS_ROUTER 2       // The message destined to the ICC router

// AndCont supervisor messages

#define ANDCONT_SUPERVISOR_MSG_EVENT     ANDCONT_NL_MK_TYPE(ANDCONT_SUBSYS_KERNEL, 1)
#define ANDCONT_SUPERVISOR_MSG_EVENT_ACK ANDCONT_NL_MK_TYPE(ANDCONT_SUBSYS_KERNEL, 2)
#define ANDCONT_SUPERVISOR_MSG_ACCESS    ANDCONT_NL_MK_TYPE(ANDCONT_SUBSYS_KERNEL, 3)

// AndCont virtual container state change events

enum andcont_supervisor_event_t {
  ANDCONT_SUPERV_EVENT_PHONE_ADDED,	// The argument is ignored when received by the kernel
  					// The argument is the container init PID when broadcast by the kernel

  ANDCONT_SUPERV_EVENT_PHONE_REMOVED,   // The message is never to be sent to the kernel
  					// The argmunet is the container init PID when broadcast by the kernel

  ANDCONT_SUPERV_EVENT_FOREGROUND_CHANGED, // The argument is the init PID of the foreground container
                                           // The argument is the same when broadcast by the kernel

  ANDCONT_DRIVER_MSG                       // ???
};

typedef struct {
  enum andcont_supervisor_event_t event;
  void* arg;
} andcont_msg_event_t;


// Device access control

#define DCP_TYPE_CHAR 1
#define DCP_TYPE_BLK  2

typedef struct {
  int type;
  dev_t dev;
} andcont_msg_access_t;


// ----------------------------------------------------------------------------
// Router messages

// Destination types

#define DEST_KERNEL  0
#define DEST_ROOT_NS 1
#define DEST_CURRENT 2

// The router message

typedef struct {
  pid_t dest;     // The destination container init PID
  pid_t src_pid;  // The source PID (filled by the kernel)
  //void* src_vc;
  uint32_t dst_groups;
  uint32_t type;  // The message type
} andcont_router_msg_t;


#ifdef __KERNEL__

#include <linux/types.h>
#include <linux/list.h>
#include <linux/semaphore.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include <net/net_namespace.h>

#include <linux/andcont/common.h>

/*============= DATA STRUCTURES ========== */

struct andcont_driver_list_entry {
  struct list_head list_entry;
  struct andcont_driver *driver;
};

/* supervisor subsystem stores data about 
 * all the drivers here */
struct andcont_driver_list {
  spinlock_t lock; /* lock for the overall list */
  struct andcont_driver_list_entry head;
};
typedef struct andcont_driver_list driver_list_t;

struct andcont_supervisor {
  struct semaphore lock;
  struct andcont_driver_list drivers;
  struct andcont_virt_phone_list vphones;
  struct sock *supervisor_sock;
  struct mutex sock_lock;
  vcid_t fg_vc;
  unsigned int ignore_pm; //ignore power management
};

/*=========== INITIALIZERS ========== */
/* call them before any work with datastructure */
struct andcont_driver_list_entry* add_new_driver_list_entry(
                                  struct andcont_supervisor *supervisor); 

int andcont_init_supervisor(void);

/* NO DESTRUCTORS: FOR NOW WE THINK THAT 
 * ALL DRIVERS EXIST ALL KERNEL LIFETIME */

/*============= FUNCTIONS =========== */
unsigned int andcont_supervisor_created(void);
struct andcont_supervisor* andcont_get_supervisor(void);

#endif /* ifdef __KERNEL__ */

#endif /* _ANDCONT_SUPERVISOR_H */
