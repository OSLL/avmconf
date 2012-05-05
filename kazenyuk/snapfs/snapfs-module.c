#include <linux/module.h>
#include <linux/init.h>

#include <linux/kernel.h>       /* KERN_INFO */
#include <linux/fs.h>		/* inode, new_inode, super_block, super_operationsi, page_symlink_inode_operations, file_operations, simple_dir_operations, inc_nlink */

#include <linux/dcache.h>	/* d_entry, d_alloc_root */
#include <linux/stat.h>		/* S_IFDIR */
#include <linux/time.h>		/* CURRENT_TIME */
#include <linux/pagemap.h>	/* PAGE_CACHE_SIZE, PAGE_CACHE_SHIFT */
#include <linux/list.h>

#include "snapfs-mgmt.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sergey Kazenyuk");
MODULE_DESCRIPTION("Snapshotting filesystem skeleton");


static int snapfs_mknod(struct inode *dir, struct dentry *dentry,
		    umode_t mode, dev_t dev);
static int snapfs_create(struct inode *dir, struct dentry *dentry,
		     umode_t mode, struct nameidata *nd);
struct inode *snapfs_get_inode(struct super_block *sb, struct inode *node,
		               umode_t mode, dev_t dev);
int snapfs_fill_super(struct super_block *sb, void *data, int silent);
struct dentry *snapfs_mount(struct file_system_type *fs_type,
                            int flags, const char *dev_name, void *data);
void snapfs_kill_sb(struct super_block *sb);
/*static int snapfs_mkdir(struct inode *dir, struct dentry *dentry,
		                        umode_t mode);*/
struct dentry *snapfs_inode_lookup(struct inode *inode, struct dentry *dentry, 
				   struct nameidata *nd);


static struct file_system_type snapfs_fs_type = {
	.name    = "snapfs",
	.mount   = snapfs_mount,
	.kill_sb = snapfs_kill_sb,
	.owner   = THIS_MODULE,
};

static struct super_operations snapfs_super_ops = {
	.drop_inode   = generic_delete_inode,
	.statfs       = simple_statfs,
	.show_options = generic_show_options,
};

static struct inode_operations snapfs_file_inode_ops = {
	.setattr = simple_setattr,
	.getattr = simple_getattr,
};

static struct inode_operations snapfs_dir_inode_ops = {
	.lookup  = snapfs_inode_lookup,
	//.lookup  = simple_lookup,
	.create  = snapfs_create,
	//.link    = simple_link,
	//.unlink  = simple_unlink,
	//.symlink = snapfs_symlink,
	//.mkdir   = snapfs_mkdir,
	//.rmdir   = simple_rmdir,
	.mknod   = snapfs_mknod,
	//.rename  = simple_rename,
};

static struct file_operations snapfs_file_ops = {
	.read         = do_sync_read,
	.aio_read     = generic_file_aio_read,
	.write        = do_sync_write,
	.aio_write    = generic_file_aio_write,
	.mmap         = generic_file_mmap,
	.fsync        = noop_fsync,
	.splice_read  = generic_file_splice_read,
	.splice_write = generic_file_splice_write,
	.llseek       = generic_file_llseek,
};


struct dentry *snapfs_inode_lookup(struct inode *inode, struct dentry *dentry,
				   struct nameidata *nd)
{
	struct inode *wrapped_node = NULL;
	struct super_block *wrapped_sb = NULL;
	struct super_block *snapfs_sb = NULL;

	printk(KERN_INFO "snapfs_inode_lookup\n");

	snapfs_sb = inode->i_sb;
	printk(KERN_INFO "SnapFS super block FS name: \"%s\"\n", snapfs_sb->s_type->name);

	// find super_block of the corresponding wrapped file system
	wrapped_sb = list_entry(&snapfs_sb->s_list, struct super_block, s_list);
	do {
		printk(KERN_INFO "wrapped_sb = %p", wrapped_sb);
		if (wrapped_sb) {
			printk(KERN_INFO "wrapped_sb->s_magic = %lx", wrapped_sb->s_magic);
			printk(KERN_INFO "wrapped_sb->s_type = %p", wrapped_sb->s_type);
			if (wrapped_sb->s_type) {
				printk(KERN_INFO "wrapped_sb->s_type->name = %p", wrapped_sb->s_type->name);
				if (wrapped_sb->s_type->name) {
					printk(KERN_INFO "super block FS name: \"%s\"\n", wrapped_sb->s_type->name);
				}
			}
		}
		wrapped_sb = list_entry(wrapped_sb->s_list.next, struct super_block, s_list);
	} while (wrapped_sb != snapfs_sb);

	return simple_lookup(inode, dentry, nd);
}

static int snapfs_mknod(struct inode *dir, struct dentry *dentry,
		    umode_t mode, dev_t dev)
{
	struct inode *node;
	int error;

	printk(KERN_INFO "snapfs_mknod\n");
	node = snapfs_get_inode(dir->i_sb, dir, mode, dev);
	error = -ENOSPC;
	if (node) {
		d_instantiate(dentry, node);
		dget(dentry);
		error = 0;
		dir->i_mtime = CURRENT_TIME;
	}
	return error;
}

/*static int snapfs_mkdir(struct inode *dir, struct dentry *dentry,
			umode_t mode)
{
	int result;

	printk(KERN_INFO "snapfs_mkdir\n");
	result = snapfs_mknod(dir, dentry, mode | S_IFDIR, 0);
	if (!result) {
		inc_nlink(dir);
	}
	return result;
}*/

static int snapfs_create(struct inode *dir, struct dentry *entry, 
		     umode_t mode, struct nameidata *nd)
{
	printk(KERN_INFO "snapfs_create\n");
	return snapfs_mknod(dir, entry, mode | S_IFREG, 0);
}

struct inode *snapfs_get_inode(struct super_block *sb, struct inode *dir, 
			       umode_t mode, dev_t dev)
{
	struct inode *node;	// allocate a new inode for superblock
	printk(KERN_INFO "snapfs_get_inode\n");
	node = new_inode(sb);
	
	if (node) {
		inode_init_owner(node, dir, mode);// set inode uid,gid,mode according to posix standards 
		node->i_ino = get_next_ino();	// set inode number

		// set inode and file methods depending on the mode
		switch (mode & S_IFMT) {
		case S_IFREG:
			node->i_op = &snapfs_file_inode_ops;
			node->i_fop = &snapfs_file_ops;
			break;
		case S_IFDIR:
			node->i_op = &snapfs_dir_inode_ops;
			node->i_fop = &simple_dir_operations;

			inc_nlink(node);	// directory inodes start off 
						// with i_nlink == 2 (for "." entry) (WHY?!)
			break;
		//case S_IFLNK:
		//	node->i_op = &page_symlink_inode_operations;
		//	break;
		default:
			//init character, block device; fifo, socket inode
			init_special_inode(node, mode, dev);
			break;
		};
		// set c/m/a time
		node->i_ctime = node->i_mtime = node->i_atime = CURRENT_TIME;
	}
	return node;
}

int snapfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *root_inode;
	struct dentry *root_dentry;
	int error;
	root_inode = NULL;
	root_dentry = NULL;
	error = 0;

	printk(KERN_INFO "snapfs_fill_super\n");
	sb->s_blocksize_bits = PAGE_CACHE_SHIFT;	// block size in bits
	sb->s_blocksize = PAGE_CACHE_SIZE;		// block size in bytes
	sb->s_maxbytes  = MAX_LFS_FILESIZE;		// max file size
	sb->s_op      = &snapfs_super_ops;		// superblock methods
	sb->s_magic   = 0x858458ff;	// filesystem's magic - random number here, 
					// should be defined in linux/magic.h

	root_inode = snapfs_get_inode(sb, NULL, S_IFDIR, 0);
	if (!root_inode) {
		error = -ENOMEM;
		goto snapfs_fill_super_fail;
	}

	root_dentry = d_alloc_root(root_inode);	// allocate a root dentry for root inode. 
						// consider using d_make_root here instead 
						// (it puts root_inode if something is wrong)
	if (!root_dentry) {
		// NULL is returned if there is insufficient memory 
		// or the inode is NULL
		error = -ENOMEM;
		goto snapfs_fill_super_fail;
	}
	sb->s_root = root_dentry;	// directory mount point
	
	sb->s_fs_info = NULL;	// filesystem private info - can save parsed mount options here
	sb->s_time_gran = 1;	// granularity of c/m/atime in ns; can't be worse than a second
	save_mount_options(sb, data);	// saved mount options for
					// lazy filesystems to sb->s_options
							// using generic_show_options()

	return 0;

snapfs_fill_super_fail:
	sb->s_fs_info = NULL;
	iput(root_inode);

	return error;
}

struct dentry *snapfs_mount(struct file_system_type *fs_type, 
			    int flags, const char *dev_name, void *data)
{
	int result;
	struct dentry *mnt_point;
	printk(KERN_INFO "snapfs_mount\n");

	mnt_point = mount_nodev(fs_type, flags, data, snapfs_fill_super);
	if (!mnt_point) {
		printk(KERN_ERR "Can't do mount_nodev\n");
		return NULL;
	}

	result = setup_snapfs_mount_point_mgmt(mnt_point);
	if (result) {
		printk(KERN_ERR "Can't setup SnapFS mount point management interface\n");
		return NULL;
	}

	return mnt_point;
}

void snapfs_kill_sb(struct super_block *sb)
{
	printk(KERN_INFO "snapfs_kill_sb\n");
	cleanup_snapfs_mount_point_mgmt();
	kill_litter_super(sb);
}

static int __init init_mod(void)
{
	int result;
	printk(KERN_INFO "FS INIT\n");

	result = setup_snapfs_mgmt();
	if (result) {
		printk(KERN_ERR "Can't setup SnapFS management interface\n");
		return result;
	}

	return register_filesystem(&snapfs_fs_type);
}

static void __exit cleanup_mod(void)
{
	printk(KERN_INFO "FS CLEANUP\n");
	cleanup_snapfs_mgmt();
	unregister_filesystem(&snapfs_fs_type);
}

static int mod_int_param1 = 4242;
static bool mod_bool_param1 = true;

module_init(init_mod);
module_exit(cleanup_mod);

module_param(mod_int_param1, int, 0644);
module_param(mod_bool_param1, bool, 0644);
MODULE_PARM_DESC(mod_int_param1, "Test Parameter 1 of type int");

