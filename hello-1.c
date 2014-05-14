// Simple test hello world
// module
#include <linux/module.h> // needed by all modules
#include <linux/kernel.h> // needed for KERN_INFO
#include <linux/init.h> // needed for __init and __exit macros

MODULE_LICENSE("GPLv2");
static int __init hello_init(void) {
  printk(KERN_INFO "Hello World 1.\n");
  // non 0 return means init_module failed and module can't be loaded.
  return 0;
}

static void __exit hello_exit(void) {
  printk(KERN_INFO "Goodbye World 1.\n");
}
module_init(hello_init);
module_exit(hello_exit);
