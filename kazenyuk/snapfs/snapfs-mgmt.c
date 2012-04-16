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

static struct snapfs_mnt_point *snapfs_mnt_point_for_kobj(struct kobject *kobj)
{
	int i;
	struct snapfs_mnt_point *mnt_point;

	printk(KERN_DEBUG "snapfs_mnt_point_for_kobj\n");

	i = 0;
	mnt_point = snapfs_mnt_points;
	if (snapfs_mnt_point_number < 0) {
		return NULL;
	}

	while (i <= snapfs_mnt_point_number) {
		if (mnt_point[i].kobj == kobj) {
			return &mnt_point[i];
		}
		++i;
	}

	return NULL;
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

static ssize_t next_state_show(struct kobject *kobj, 
				struct kobj_attribute *attr, char *buf)
{
	struct snapfs_mnt_point *mnt_point;

	mnt_point = snapfs_mnt_point_for_kobj(kobj);
	if (!mnt_point) {
		printk(KERN_ERR "Can't find mount point for kobject\n");
		return 0;
	}

	return sprintf(buf, "%d\n", mnt_point->next_state);
}

static ssize_t next_state_store(struct kobject *kobj, 
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

	sscanf(buf, "%d\n", &mnt_point->next_state);
	return count;
}

static struct kobj_attribute path_attr = __ATTR(path, 0444, 
						path_show, 
						NULL);
static struct kobj_attribute state_attr = __ATTR(state, 0444,
						state_show,
						NULL);
static struct kobj_attribute next_state_attr = __ATTR(next_state, 0666, 
							next_state_show, 
							next_state_store);

static struct attribute *snapfs_mnt_attrs[] = {
	&path_attr.attr,
	&next_state_attr.attr,
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
	
	mnt_point->kobj = kobject_create_and_add(mnt_point->name, snapfs_kobj);
        if (!mnt_point->kobj) {
		printk(KERN_ERR "Can't create SnapFS mount point KObject\n");
		kfree(mnt_point->name);
		return -ENOMEM;
	}
	
	mnt_point->attrs = kmalloc(sizeof(*(mnt_point->attrs)), GFP_KERNEL);
	if (!mnt_point->attrs) {
		printk(KERN_ERR "Can't do kmalloc\n");
		kfree(mnt_point->name);
		kobject_put(mnt_point->kobj);
		return -ENOMEM;
	}
	memset(mnt_point->attrs, 0, sizeof(*mnt_point->attrs));
	
	mnt_point->attrs->attrs = snapfs_mnt_attrs;
	mnt_point->dentry = dentry;
	
	result = sysfs_create_group(mnt_point->kobj, mnt_point->attrs);
	if (result) {
		printk(KERN_ERR "Can't create sysfs group");
		kfree(mnt_point->name);
		kobject_put(mnt_point->kobj);
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
		kobject_put(mnt_point->kobj);	//do we really need to do it here?
	}
}

void cleanup_snapfs_mount_point_mgmt()
{
	//delete corresponding sysfs group
}

