#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/fs.h>		// fs_kobj
#include <linux/kobject.h>
#include <linux/dcache.h>
#include <linux/slab.h>

#include "snapfs-mgmt.h"

static char mnt_point_path[256];

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

static struct kobject *snapfs_kobj = NULL;

int setup_snapfs_mgmt()
{
	snapfs_kobj = kobject_create_and_add("snapfs", fs_kobj);
	if (!snapfs_kobj) {
		printk(KERN_ERR "Can't create SnapFS KObject\n");
		return -ENOMEM;
	}
	return 0;
}

struct snapfs_mnt_point {
	char *name;
	struct kobject *kobj;
	struct attribute_group *attrs;
	struct dentry *dentry;
};

#define max_snapfs_mnt_points 5
static int snapfs_mnt_point_number = -1;
//static struct attribute_group snapfs_mnt_attr_grp[max_snapfs_mnt_points];
//static struct kobject snapfs_mnt_point_kobjects[max_snapfs_mnt_points];
static struct snapfs_mnt_point snapfs_mnt_points[max_snapfs_mnt_points];
#undef max_snapfs_mnt_points

int setup_snapfs_mount_point_mgmt(struct dentry *mnt_point_dentry)
{
	int result;
	struct snapfs_mnt_point *mnt_point;
	struct attribute_group *mnt_point_grp;
	struct kobject *mnt_point_kobj;
	/*struct kobject *snapfs_mnt_point_kobj = kobject_create();
	kobject_set_name(snapfs_mnt_point_kobj, "%d", number_of_mnt_points++);
	kobject_init(snapfs_mnt_point_kojb, snapfs_mnt_point_ktype);
	kobject_add(snapfs_mnt_point_kojb, fs_kobj, "%d", number_of_mnt_points - 1);*/
	++snapfs_mnt_point_number;
	mnt_point = &snapfs_mnt_points[snapfs_mnt_point_number];
	//mnt_point_grp = mnt_point->attrs;
	//mnt_point_kobj = mnt_point->kobj;

	mnt_point->attrs = kmalloc(sizeof(*(mnt_point->attrs)), GFP_KERNEL);
	if (!mnt_point->attrs) {
		printk(KERN_ERR "Can't do kmalloc\n");
		return -ENOMEM;
	}

//	memset(mnt_point_grp, 0, sizeof(*mnt_point_grp));
//	memset(mnt_point_kobj, 0, sizeof(*mnt_point_kobj));
	
	/*mnt_point_grp->name = kmalloc(30, GFP_KERNEL); //maybe GFP_NOFS?
	if (!mnt_point_grp->name) {
		printk(KERN_ERR "Can't do kmalloc\n");
		return -ENOMEM;
	}*/
	mnt_point->attrs->attrs = snapfs_mnt_attrs;
	/*snprintf((char*)mnt_point_grp->name, 30, "mnt_point_%d", 
		 snapfs_mnt_point_number);*/
	mnt_point->dentry = mnt_point_dentry;
	mnt_point->name = kmalloc(30, GFP_KERNEL);
	if (!mnt_point->name) {
		printk(KERN_ERR "Can't do kmalloc\n");
		return -ENOMEM;
	}
	snprintf(mnt_point->name, 30, "mnt_point_%d", snapfs_mnt_point_number);

	mnt_point->kobj = kobject_create_and_add(mnt_point->name, snapfs_kobj);
	if (!mnt_point->kobj) {
		printk(KERN_ERR "Can't create SnapFS mount point KObject\n");
		return -ENOMEM;
	}
	result = sysfs_create_group(mnt_point_kobj, mnt_point->attrs);
	if (result) {
		printk(KERN_ERR "Can't create sysfs group");
		//kobject_put(snapfs_kobj);
	}
	//++snapfs_mnt_point_number;
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

