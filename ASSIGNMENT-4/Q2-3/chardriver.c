/*Open,Read,Write and close functionalities using dynamically allocation of major and minor number pair from the kernel*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>                 
#include<linux/uaccess.h>              
 
#define chardevice        1024           
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev my_cdev;
uint8_t *kernel_buffer;

static int      __init NAME_Chardriver_init(void);
static void     __exit NAME_Chardriver_exit(void);
static int      NAME_open(struct inode *inode, struct file *file);
static int      NAME_release(struct inode *inode, struct file *file);
static ssize_t  NAME_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  NAME_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = NAME_read,
        .write          = NAME_write,
        .open           = NAME_open,
        .release        = NAME_release,
};
 
static int NAME_open(struct inode *inode, struct file *file)
{
        
        if((kernel_buffer = kmalloc(chardevice , GFP_KERNEL)) == 0)
	{
            printk("memory not allocated in kernel\n");
            return -1;
        }
        printk("Device file opened successfully\n");
        return 0;
}

static int NAME_release(struct inode *inode, struct file *file)
{
        kfree(kernel_buffer);
        printk("Device file closed successfully \n");
        return 0;
}

static ssize_t NAME_read(struct file *filp, char __user *buf, size_t count, loff_t *off)
{
        
        if( copy_to_user(buf, kernel_buffer, chardevice))
        {
                printk("Error in writing the data...\n");
        }
        printk("Data written succesfully...\n");
        return chardevice;
}


static ssize_t NAME_write(struct file *filp, const char __user *buf, size_t count, loff_t *off)
{
        
        if( copy_from_user(kernel_buffer, buf, count))
        {
                printk("Error in writing the data...\n");
        }
        printk("Data written succesfully...\n");
        return count;
}


static int __init NAME_Chardriver_init(void)
{
        
        if((alloc_chrdev_region(&dev, 0, 1, "my_Dev")) <0)
	{
                printk("The major number is not allocated \n");
                return -1;
        }
        printk("Major Number = %d Minor Number = %d \n",MAJOR(dev), MINOR(dev));
        cdev_init(&my_cdev,&fops);
        if((cdev_add(&my_cdev,dev,1)) < 0)
	{
            printk("Cannot add the device to the system\n");
	    unregister_chrdev_region(dev,1);
            return -1;
        }
 
        if((dev_class = class_create(THIS_MODULE,"my_class")) == NULL)
	{
            printk("The struct class cant be created...\n");
            unregister_chrdev_region(dev,1);
            return -1;
        }
 
        if((device_create(dev_class,NULL,dev,NULL,"my_device")) == NULL)
	{
            printk("The device can't be created...\n");
	    class_destroy(dev_class);
        }
        printk("The character device driver installed successfully..HELLOWORLD\n");
        return 0;
}

static void __exit NAME_Chardriver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev, 1);
        printk("The character device driver removed successfully...GOODBYE\n");
}
 
module_init(NAME_Chardriver_init);
module_exit(NAME_Chardriver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("kavya");
MODULE_DESCRIPTION("open,read,write and release funtionality dynamically");
