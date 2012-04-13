#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/fs.h>		// fs_kobj
#include <linux/kobject.h>
#include <linux/dcache.h>
#include <linux/slab.h>

#include "snapfs-mgmt.h"

#define max_snapfs_mnt_points 10
static int snapfs_mnt_point_number = -1;
static struct snapfs_mnt_point snapfs_mnt_points[max_snapfs_mnt_points];
#undef max_snapfs_mnt_points

static char mnt_point_path[256];
static struct kobject *snapfs_kobj = NULL;

static ssize_t mnt_point_show(struct kobject *kobj, 
				struct kobj_attribute *attr, char *buf)
{
	if (kobj) {
		printk(KERN_INFO "mnt_point_show for '%s' kobject\n", 
			kobject_name(kobj));
	} else {
		printk(KERN_INFO "mnt_point_show for unknown kobject\n");
	}

	return sprintf(buf, "%s\n", mnt_point_path);
}

static ssize_t mnt_point_store(struct kobject *kobj, 
				struct kobj_attribute *attr, 
				const char *buf, size_t count)
{
	if (kobj) {
		printk(KERN_INFO "mnt_point_show for '%s' kobject\n", 
			kobject_name(kobj));
	} else {
		printk(KERN_INFO "mnt_point_show for unknown kobject\n");
	}

	sscanf(buf, "%s\n", mnt_point_path);
	return count;
}

static struct kobj_attribute mnt_point_attr = __ATTR(mnt_point_path, 0666, mnt_point_show, mnt_point_store);

static struct attribute *snapfs_mnt_attrs[] = {
	&mnt_point_attr.attr,
	NULL,
};

int setup_snapfs_mgmt()
{
	snapfs_kobj = kobject_create_and_add("snapfs", fs_kobj);
	if (!snapfs_kobj) {
		printk(KERN_ERR "Can't create SnapFS KObject\n");
		return -ENOMEM;
	}
	return 0;
}

int setup_snapfs_mount_point_mgmt(struct dentry *dentry)
{
	int result;
	const int mnt_point_name_length = 30;
	struct snapfs_mnt_point *mnt_point;
	
	++snapfs_mnt_point_number;
	mnt_point = &snapfs_mnt_points[snapfs_mnt_point_number];

	mnt_point->name = kmalloc(mnt_point_name_length, GFP_KERNEL);
	if (!mnt_point->name) {
		printk(KERN_ERR "Can't do kmalloc\n");
		return -ENOMEM;
	}
	snprintf(mnt_point->name, mnt_point_name_length, 
			"mnt_point_%d", snapfs_mnt_point_number);
	
	mnt_point->kobj = kobject_create_and_add(mnt_point->name, snapfs_kobj);
        if (!mnt_point->kobj) {
		printk(KERN_ERR "Can't create SnapFS mount point KObject\n");
		return -ENOMEM;
	}
	
	mnt_point->attrs = kmalloc(sizeof(*(mnt_point->attrs)), GFP_KERNEL);
	if (!mnt_point->attrs) {
		printk(KERN_ERR "Can't do kmalloc\n");
		return -ENOMEM;
	}
	memset(mnt_point->attrs, 0, sizeof(*mnt_point->attrs));
	
	mnt_point->attrs->attrs = snapfs_mnt_attrs;
	mnt_point->dentry = dentry;
	
	result = sysfs_create_group(mnt_point->kobj, mnt_point->attrs);
	if (result) {
		printk(KERN_ERR "Can't create sysfs group");
	}
	return result;
}

void cleanup_snapfs_mgmt()
{
	int i;
	kobject_put(snapfs_kobj);
	for (i = 0; i <= snapfs_mnt_point_number; ++i) {
		kobject_put(snapfs_mnt_points[i].kobj);
	}
}

void cleanup_snapfs_mount_point_mgmt()
{
	//delete corresponding sysfs group
}

