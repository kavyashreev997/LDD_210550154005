/*Character driver with open and close functionality*/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define NAME MyCharDevice

/*fuction prototype*/

int NAME_open(struct inode *inode,struct file *flip);
int NAME_release(struct inode *inode,struct file *flip);

struct file_operations fops=
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.release = NAME_release,
};

struct cdev *my_cdev;

/*init module*/
static int chardevice_init(void)
{

    int output;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev=MKDEV(255,0); //create a device number
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\n The major number is %d The minor number is %d\n",MAJOR,MINOR);
	output=register_chrdev_region(Mydev,1,"MyCharDevice");    //register device region
	if(output<0)
	{
		printk("The region is not obtained\n");
		return(-1);
	}

my_cdev=cdev_alloc(); //memory allocation to char device structures
my_cdev->ops=&fops;


output=cdev_add(my_cdev,Mydev,1);
if(output<0)
{
	printk("\n The character device has not created\n");
	unregister_chrdev_region(Mydev,1);
		return(-1);
}
return 0;
}


//clean up module
static void chardevice_exit(void)
{
	dev_t Mydev;
	int MAJOR,MINOR;
	Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\n The major number is %d The minor number is %d\n",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,1);
	cdev_del(my_cdev);
	printk("\n good bye\n");
	return ;
}

/*Open functionality*/

int NAME_open(struct inode *inode,struct file *filp)
{
	printk("\n open call\n");
	return 0;
}


/*close functionality*/

int NAME_release(struct inode *inode,struct file *filp)
{
	printk("\n close call\n");
	return 0;
}

module_init(chardevice_init);
module_exit(chardevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KAVYA");
MODULE_DESCRIPTION("open and close functionality");
