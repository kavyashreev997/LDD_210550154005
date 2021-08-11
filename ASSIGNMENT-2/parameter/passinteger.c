#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
 
static int data = 20;
static char *str = "passinteger";

module_param(data, int, S_IRUSR|S_IWUSR);                     
module_param(str, charp, S_IRUSR|S_IWUSR);                     



static int __init hello_world_init(void)
{
        printk("DATA = %d  \n",data);
        printk("STRING= %s \n", str);
        printk("Kernel Module Inserted Successfully...\n");
    return 0;
}

static void __exit hello_world_exit(void)
{
    printk("Kernel Module Removed Successfully...\n");
}
 
module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavya");
