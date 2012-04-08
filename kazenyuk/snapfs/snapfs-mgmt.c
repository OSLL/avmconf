#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/fs.h>		// fs_kobj
#include <linux/kobject.h>
#include <linux/dcache.h>
#include <linux/slab.h>

#include "snapfs-mgmt.h"

static char mnt_point_path[256];

static ssize_t mnt_point_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	if (kobj) {
		printk(KERN_INFO "mnt_point_show for '%s' kobject\n", kobject_name(kobj));
	} else {
		printk(KERN_INFO "mnt_point_show for unknown kobject\n");
	}

	return sprintf(buf, "%s\n", mnt_point_path);
}

static ssize_t mnt_point_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	if (kobj) {
		printk(KERN_INFO "mnt_point_show for '%s' kobject\n", kobject_name(kobj));
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

#define max_snapfs_mnt_attr_grp 5
static int snapfs_mnt_point_number = 0;
static struct attribute_group snapfs_mnt_attr_grp[max_snapfs_mnt_attr_grp];
#undef max_snapfs_mnt_attr_grp

int setup_snapfs_mount_point_mgmt(struct dentry *mnt_point)
{
	int result;
	/*struct kobject *snapfs_mnt_point_kobj = kobject_create();
	kobject_set_name(snapfs_mnt_point_kobj, "%d", number_of_mnt_points++);
	kobject_init(snapfs_mnt_point_kojb, snapfs_mnt_point_ktype);
	kobject_add(snapfs_mnt_point_kojb, fs_kobj, "%d", number_of_mnt_points - 1);*/
	
	memset(&snapfs_mnt_attr_grp[snapfs_mnt_point_number], 0, 
	       sizeof(*snapfs_mnt_attr_grp));
	
	snapfs_mnt_attr_grp[snapfs_mnt_point_number].name = kmalloc(30, GFP_KERNEL);	//maybe GFP_NOFS?
	if (!snapfs_mnt_attr_grp[snapfs_mnt_point_number].name) {
		printk(KERN_ERR "Can't do kmalloc\n");
		return -ENOMEM;
	}
	snapfs_mnt_attr_grp[snapfs_mnt_point_number].attrs = snapfs_mnt_attrs;
	snprintf((char*)snapfs_mnt_attr_grp[snapfs_mnt_point_number].name, 30,
		 "mnt_point_%d", 
		 snapfs_mnt_point_number);
	
	result = sysfs_create_group(snapfs_kobj, &snapfs_mnt_attr_grp[snapfs_mnt_point_number]);
	if (result) {
		printk(KERN_ERR "Can't create sysfs group");
		kobject_put(snapfs_kobj);
	}
	++snapfs_mnt_point_number;
	return result;
}

void cleanup_snapfs_mgmt()
{
	kobject_put(snapfs_kobj);
}

void cleanup_snapfs_mount_point_mgmt()
{
	//delete corresponding sysfs group
}

