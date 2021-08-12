#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include "Header.h" 


int a_test=30,b_test=20;

static int hello_init(void)
{
	int average;
	printk("In init module...the module parameter is %d\n",a_test);
	printk("Helloworld\n");
	average = helloworld_add(a_test,b_test)/2;
	printk("\n The Average is %d\n",average);
	return 0;	
}

static void hello_exit(void)
{
	printk("In cleanup module...the module parameter is %d\n",a_test);
	printk("goodbye,world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavya");