#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
 
static int d1=5;
static int d2=10;
static char *opr = "add";

module_param(data, int, S_IRUSR|S_IWUSR);                     
module_param(str, charp, S_IRUSR|S_IWUSR);                     



static int __init hello_world_init(void)
{
        int i;
        printk("DATA = %d  \n",data);
        printk("oprerand %s \n",opr);
        switch(opr)
        {
            case "add":
                     printk("ADD=%d",(d1+d2));
                     break;
            case "sub":
                     printk("SUB=%d",(d1-d2));
                     break;
            case "mul":
                     printk("MUL=%d",(d1*d2));
                     break;
            case "div":
                     printk("DIV=%d",(d1/d2));
                     break;
           default:
                     printk("ADD= %d",(d1+d2));
                     break;
                     
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
