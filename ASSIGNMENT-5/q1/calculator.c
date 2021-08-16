#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>          
#include<linux/uaccess.h>       
#include<linux/ioctl.h>


#define W_VALUE _IOW('a','a',int32_t*)
#define R_VALUE _IOR('a','b',int32_t*)


int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);


int32_t v1 = 0 ;
int32_t v2 = 0 ;
int32_t res = 0 ;
int32_t opn = 0 ;
dev_t dev=0;
static struct class *dev_class;
static struct cdev my_cdev ;

static int __init my_driver_init(void);
static void __exit my_driver_exit(void);


static long my_ioctl(struct file *file,unsigned int cmd,unsigned long arg);





static struct file_operations fops = 
{
    .owner      = THIS_MODULE,
     .open	= NAME_open,
     .release= NAME_release,
    .unlocked_ioctl = my_ioctl,

};


int NAME_open(struct inode *inode,struct file *filp)
{
	printk("open call...\n");
	return 0;
}



int NAME_release(struct inode *inode,struct file *filp)
{
	printk("close call...\n");
	return 0;
} 



static long my_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
{
    static int c = 0;
	long retn;
    switch(cmd) 
	{
	case W_VALUE:
		{
            if(c == 0)
                {
                retn = copy_from_user(&opn,(int32_t*)arg,sizeof(opn));
                printk(KERN_INFO "numop = %d\n",opn);
		c+=1;
                 }
            else if(c == 1)
		{
                retn = copy_from_user(&v1,(int32_t*)arg,sizeof(v1));
                printk(KERN_INFO "num1 = %d\n",v1);
		c+=1;
               	 }
            else if(c == 2)
		{
                retn = copy_from_user(&v2,(int32_t*)arg,sizeof(v2));
                printk(KERN_INFO "num2 = %d\n",v2);
		c+=1;
                 }
		break;
		}
        case R_VALUE:
		{
		if(opn == 1)
                res = v1 + v2 ;
		
            else if(opn == 2)
                res = v1 - v2;
		
            else if(opn == 3)
                res = v1 * v2;
		
            else if(opn == 4)
                res = v1 / v2;
		}
		break;
            }
 retn = copy_to_user((int32_t*) arg, &res,sizeof(res));
		
            if(c == 3)
               c = 0 ;

return 0;
}

static int __init my_driver_init(void)
{
    if((alloc_chrdev_region(&dev,0,1,"my_dev")) <0)
	{
        printk("major number allocation failed\n");
        return -1;
        }
    printk(" MAJOR = %d Minor = %d\n",MAJOR(dev),MINOR(dev));


    cdev_init(&my_cdev,&fops);


    if((cdev_add(&my_cdev,dev,1)) < 0)
	{
        printk("device add failed\n");
        unregister_chrdev_region(dev,1);
        return -1;
        }

     
        if((dev_class = class_create(THIS_MODULE,"my_class")) == NULL)
	{
            printk("class not created\n");
           unregister_chrdev_region(dev,1);
        return -1;
        }


        if((device_create(dev_class,NULL,dev,NULL,"cal_device")) == NULL)
	{
            printk("device failed\n");
            
		class_destroy(dev_class);
        }
        printk("In init module...\n");
    return 0;


        

        
}

void __exit my_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev, 1);
    printk("In exit module...\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavya");
