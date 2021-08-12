#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

int Helloworld_type=1;
static int helloworld_add(int a,int b);

static int hello_init(void)
{
	printk("In init module...the module parameter is %d\n",Helloworld_type);
	printk("Helloworld\n");
	return 0;
}

static int helloworld_add(int a,int b)
{
	printk("Addition function\n");
	return(a+b);

}

EXPORT_SYMBOL_GPL(helloworld_add);


static void hello_exit(void)
{
	printk("In cleanup Module... the module parameter is %d\n",Helloworld_type);
	printk("goodbye,world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavya");
