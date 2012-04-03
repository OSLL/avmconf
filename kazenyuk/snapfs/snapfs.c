#include <linux/module.h>
#include <linux/init.h>

#include <linux/kernel.h>       /* KERN_INFO */
#include <linux/fs.h>		/* inode, new_inode, super_block, super_operationsi, page_symlink_inode_operations, file_operations, simple_dir_operations, inc_nlink */

#include <linux/dcache.h>	/* d_entry, d_alloc_root */
#include <linux/stat.h>		/* S_IFDIR */
#include <linux/time.h>		/* CURRENT_TIME */
#include <linux/pagemap.h>	/* PAGE_CACHE_SIZE, PAGE_CACHE_SHIFT */

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
	.lookup  = simple_lookup,
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

//static struct address_space_operations snapfs_a

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
	printk(KERN_INFO "snapfs_mount\n");
	return mount_nodev(fs_type, flags, data, snapfs_fill_super);
}

void snapfs_kill_sb(struct super_block *sb)
{
	printk(KERN_INFO "snapfs_kill_sb\n");
	kill_litter_super(sb);
}

static int __init init_mod(void)
{
	printk(KERN_INFO "FS INIT\n");
	return register_filesystem(&snapfs_fs_type);
}

static void __exit cleanup_mod(void)
{
	printk(KERN_INFO "FS CLEANUP\n");
	unregister_filesystem(&snapfs_fs_type);
}

module_init(init_mod);
module_exit(cleanup_mod);

