// Simple test hello world
// module
#include <linux/module.h> // needed by all modules
#include <linux/kernel.h> // needed for KERN_INFO
MODULE_LICENSE("GPLv2");
int hello_init(void) {
  printk(KERN_INFO "Hello World 1.\n");
  // non 0 return means init_module failed and module can't be loaded.
  return 0;
}

void hello_exit(void) {
  printk(KERN_INFO "Goodbye World 1.\n");
}
module_init(hello_init);
module_exit(hello_exit);
