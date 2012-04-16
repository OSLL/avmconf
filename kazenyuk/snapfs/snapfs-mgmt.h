#ifndef _SNAPFS_MGMT_H
#define _SNAPFS_MGMT_H

struct kobject;
struct attribute_group;
struct dentry;

struct snapfs_mnt_point {
	char *name;
	struct kobject *kobj;
	struct attribute_group *attrs;
	struct dentry *dentry;
	int state;
	int next_state;
};

int setup_snapfs_mgmt(void);
int setup_snapfs_mount_point_mgmt(struct dentry *mnt_point);
void cleanup_snapfs_mgmt(void);
void cleanup_snapfs_mount_point_mgmt(void);

#endif

