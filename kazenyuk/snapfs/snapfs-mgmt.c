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

static struct kobject *snapfs_kobj = NULL;

/*
static void snapfs_mntpoint_kobj_release(struct kobject *kobj)
{
	return;
}
*/

static struct kobj_type snapfs_mntpoint_ktype = {
	//.release = snapfs_mntpoint_kobj_release,
	.release = NULL,
	//.sysfs_ops = &kobj_sysfs_ops,	// to be set in mntpoint setup function
};

static struct snapfs_mnt_point *snapfs_mnt_point_for_kobj(struct kobject *kobj)
{
	printk(KERN_INFO "snapfs_mnt_point_for_kobj\n");
	return container_of(kobj, struct snapfs_mnt_point, kobj);
}

static ssize_t path_show(struct kobject *kobj, 
				struct kobj_attribute *attr, char *buf)
{
	struct snapfs_mnt_point *mnt_point;
	
	if (kobj) {
		printk(KERN_INFO "mnt_point_show for '%s' kobject\n", 
			kobject_name(kobj));
	} else {
		printk(KERN_WARNING "mnt_point_show for unknown kobject\n");
		return 0;
	}

	mnt_point = snapfs_mnt_point_for_kobj(kobj);
	if (!mnt_point) {
		printk(KERN_ERR "Can't find mount point for kobject\n");
		return 0;
	}

	if (!mnt_point->dentry) {
		printk(KERN_ERR "No dentry in mnt_point structure\n");
		return 0;
	}

	if (!mnt_point->dentry->d_name.name) {
		printk(KERN_ERR "No name specified in mount point dentry\n");
		return 0;
	}

	printk(KERN_ERR "d_name.len = %d\n", mnt_point->dentry->d_name.len);
	printk(KERN_ERR "d_name.name = %s\n", mnt_point->dentry->d_name.name);
	//return snprintf(buf, mnt_point->dentry->d_name.len, 
	//		"%s\n", mnt_point->dentry->d_name.name);
	return sprintf(buf, "%s\n", mnt_point->dentry->d_name.name);
}

static ssize_t state_show(struct kobject *kobj,
			struct kobj_attribute *attr, char *buf)
{
	struct snapfs_mnt_point *mnt_point;

	mnt_point = snapfs_mnt_point_for_kobj(kobj);
	if (!mnt_point) {
		printk(KERN_ERR "Can't find mount point for kobject\n");
		return 0;
	}

	return sprintf(buf, "%d\n", mnt_point->state);
}

static ssize_t state_store(struct kobject *kobj, 
				struct kobj_attribute *attr, 
				const char *buf, size_t count)
{
	struct snapfs_mnt_point *mnt_point;

	if (kobj) {
		printk(KERN_INFO "next_state_store for '%s' kobject\n", 
			kobject_name(kobj));
	} else {
		printk(KERN_WARNING "next_state_store for unknown kobject\n");
		return 0;
	}

	mnt_point = snapfs_mnt_point_for_kobj(kobj);
	if (!mnt_point) {
		printk(KERN_ERR "Can't find mount point for kobject\n");
		return 0;
	}

	sscanf(buf, "%d\n", &mnt_point->state);
	return count;
}

static struct kobj_attribute path_attr = __ATTR(path, 0444, 
						path_show, 
						NULL);
static struct kobj_attribute state_attr = __ATTR(state, 0444,
						state_show,
						state_store);

static struct attribute *snapfs_mnt_attrs[] = {
	&path_attr.attr,
	&state_attr.attr,
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
	int next_snapfs_mnt_point_number;
	const int mnt_point_name_length = 30;
	struct snapfs_mnt_point *mnt_point;
	
	next_snapfs_mnt_point_number = snapfs_mnt_point_number + 1;
	mnt_point = &snapfs_mnt_points[next_snapfs_mnt_point_number];

	mnt_point->name = kmalloc(mnt_point_name_length, GFP_KERNEL);
	if (!mnt_point->name) {
		printk(KERN_ERR "Can't do kmalloc\n");
		return -ENOMEM;
	}
	snprintf(mnt_point->name, mnt_point_name_length, 
			"mnt_point_%d", next_snapfs_mnt_point_number);
	snapfs_mntpoint_ktype.sysfs_ops = snapfs_kobj->ktype->sysfs_ops;
	result = kobject_init_and_add(&mnt_point->kobj, &snapfs_mntpoint_ktype, 
					snapfs_kobj, mnt_point->name);
	if (result) {
		printk(KERN_ERR "Can't init SnapFS mount point KObject\n");
		kobject_put(&mnt_point->kobj);
		return -ENOMEM;
	}
	
	mnt_point->attrs = kmalloc(sizeof(*(mnt_point->attrs)), GFP_KERNEL);
	if (!mnt_point->attrs) {
		printk(KERN_ERR "Can't do kmalloc\n");
		kfree(mnt_point->name);
		kobject_put(&mnt_point->kobj);
		return -ENOMEM;
	}
	memset(mnt_point->attrs, 0, sizeof(*mnt_point->attrs));
	
	mnt_point->attrs->attrs = snapfs_mnt_attrs;
	mnt_point->dentry = dentry;
	
	result = sysfs_create_group(&mnt_point->kobj, mnt_point->attrs);
	if (result) {
		printk(KERN_ERR "Can't create sysfs group");
		kfree(mnt_point->name);
		kobject_put(&mnt_point->kobj);
		kfree(mnt_point->attrs);
		return result;
	}

	snapfs_mnt_point_number = next_snapfs_mnt_point_number;
	return result;
}

void cleanup_snapfs_mgmt()
{
	int i;
	struct snapfs_mnt_point *mnt_point;

	kobject_put(snapfs_kobj);
	for (i = 0; i <= snapfs_mnt_point_number; ++i) {
		mnt_point = &snapfs_mnt_points[i];
		kfree(mnt_point->name);
		kfree(mnt_point->attrs);
		kobject_put(&mnt_point->kobj);	//do we really need to do it here?
	}
}

void cleanup_snapfs_mount_point_mgmt()
{
	//delete corresponding sysfs group
}

