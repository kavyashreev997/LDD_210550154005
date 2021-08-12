#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
 
static int x=20;
static int y=10;
static char* opr = "add";

 
module_param(x, int, S_IRUSR|S_IWUSR);
module_param(y, int, S_IRUSR|S_IWUSR);
module_param(opr, charp, S_IRUSR|S_IWUSR);                     

 

static int hello_world_init(void)
{
        printk("operator = %s \n",opr);
	if(!strcmp(opr,"add"))
	{
		printk("Add = %d",(x+y));
	}
	else if(!strcmp(opr,"sub"))
	{
		printk("Sub = %d",(x-y));
	}
	else if(!strcmp(opr,"mul"))
	{	
		printk("Mul = %d",(x*y));
	}
	else if(!strcmp(opr,"div"))
	{	
		printk("Div = %d",(x/y));
	}
        printk("In init module...\n");
    return 0;
}

static void hello_world_exit(void)
{
    printk("In exit module...\n");
}
 
module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavya");
