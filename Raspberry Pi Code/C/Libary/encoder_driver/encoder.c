#include<linux/init.h>
#include<linux/module.h>
#include<linux/gpio.h>
#include<linux/interrupt.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>


#define ENCODER_MAJOR 200
#define ENCODER_MINOR   0
#define ENCODER_COUNT   1
dev_t dev=0;
uint32_t encoder_major = 0;
uint32_t encoder_minor = 0;
struct tasklet_struct encoder_tasklet;

struct class *dev_class = NULL;

int flag=0;
int encoder_left=0, encoder_right=0,encoder_flag;
struct encoder_cdev{
    struct cdev cdev;
    int buf[2];
};

struct encoder_cdev *encoder_devp = NULL;

void encoder_do_tasklet(unsigned long);
DECLARE_TASKLET(encoder_tasklet,encoder_do_tasklet,0);

void encoder_do_tasklet(unsigned long n)
{
    //printk("get irq %d\n",encoder_flag);
  switch(encoder_flag)
  {
    case 1:
        if(gpio_get_value(12)==0){
            if(gpio_get_value(16)==0)
                encoder_left--;
            else
                encoder_left++;
            }
        else{
            if(gpio_get_value(16)==0)
                encoder_left++;
            else
                encoder_left--;
            }
        break;
    case 2:
        if(gpio_get_value(16)==0){
            if(gpio_get_value(12)==0)
                encoder_left++;
            else
                encoder_left--;
            }
        else{
            if(gpio_get_value(12)==0)
                encoder_left--;
            else
                encoder_left++;
            }
        break;
    case 3:
        if(gpio_get_value(20)==0){
            if(gpio_get_value(21)==0)
                encoder_right--;
            else
                encoder_right++;
            }
        else{
            if(gpio_get_value(21)==0)
                encoder_right++;
            else
                encoder_right--;
            }
        break;
    case 4:
        if(gpio_get_value(21)==0){
            if(gpio_get_value(20)==0)
                encoder_right++;
            else
                encoder_right--;
            }
        else{
            if(gpio_get_value(20)==0)
                encoder_right--;
            else
                encoder_right++;
            }
        break;
    }
    
  //  printk("encoder left %d right %d\n",encoder_left,encoder_right);
}


static irqreturn_t irq_handler1(int irq,void *dev)
{
    encoder_flag=1;
    tasklet_schedule(&encoder_tasklet);
    return IRQ_HANDLED;
}
static irqreturn_t irq_handler2(int irq,void *dev)
{    
    encoder_flag=2;
    tasklet_schedule(&encoder_tasklet);
    return IRQ_HANDLED;
}
static irqreturn_t irq_handler3(int irq,void *dev)
{    
    encoder_flag=3;
    tasklet_schedule(&encoder_tasklet);
    return IRQ_HANDLED;
}
static irqreturn_t irq_handler4(int irq,void *dev)
{    
    encoder_flag=4;
    tasklet_schedule(&encoder_tasklet);
    return IRQ_HANDLED;
}

int encoder_open(struct inode* inode, struct file *filp)
{
            struct encoder_cdev *pcdevp = NULL;
            printk("enter encoder_open!\n");
                    
            pcdevp = container_of(inode->i_cdev, struct encoder_cdev, cdev);
            printk("pcdevp %p %p\n",pcdevp,encoder_devp);                
            filp->private_data = pcdevp;
                                
            return 0;
}
int encoder_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
    int ret = 0;
    struct encoder_cdev *cdevp = filp->private_data;
   // printk("enter encoder_read!\n");
    encoder_devp->buf[0]=encoder_left;
    encoder_devp->buf[1]=encoder_right;
    ret = copy_to_user(buf,cdevp->buf, count);
   // printk("kernel encoder value:%d %d\n", cdevp->buf[0],cdevp->buf[1]);

    encoder_left=0;
    encoder_right=0;

    return ret;
}
int encoder_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
            int ret = 0;
            printk("enter encoder_write!\n");
                            
            return ret;
}
 
long encoder_ioctl(struct file *filp, unsigned int cmd, unsigned long data)
{
        printk("enter encoder_ioctl!\n");
        return 0;
}
 
int encoder_release(struct inode *inode, struct file *filp){
    printk("encoder release\n");
    return 0;
}

struct file_operations encoder_fops = {
        .owner = THIS_MODULE,
        .open = encoder_open,
        .read = encoder_read,
        .write = encoder_write,
        .unlocked_ioctl = encoder_ioctl,
        .release = encoder_release,
};

static int encoder_init(void)
{
    int err;
    int ret;
    cpumask_t cmask;
    printk(KERN_INFO"ENCODER_INIT\n");

    if(encoder_major){
        dev = MKDEV(ENCODER_MAJOR,ENCODER_MINOR);
        ret = register_chrdev_region(dev,ENCODER_COUNT,"encoder");
    }
    else{
        ret = alloc_chrdev_region(&dev,encoder_minor,ENCODER_COUNT, "encoder");
    }

    if(ret < 0 )
    {
        printk("register_chrdev_region failed!\n");
        goto failure_register_chrdev;
    }
    encoder_major = MAJOR(dev);
    printk("encoder_major = %d\n", encoder_major);

    encoder_devp = kzalloc(sizeof(struct encoder_cdev)*ENCODER_COUNT, GFP_KERNEL);
    if(IS_ERR(encoder_devp)){
            printk("kzalloc failed!\n");
            goto failure_kzalloc;
        }
    dev_class = class_create(THIS_MODULE, "encoder_class");
    if(IS_ERR(dev_class)){
            printk("class_create failed!\n");
            goto failure_dev_class;
    }

    cdev_init(&(encoder_devp->cdev), &encoder_fops);
            /*添加cdev到内核*/
    cdev_add(&(encoder_devp->cdev), dev, 1);
                    /* “/dev/xxx” */
    device_create(dev_class, NULL, dev, NULL, "encoder%d", 1);
                            
    


    err = gpio_request_one(12,GPIOF_IN,"encoder1a");
    if(err)
            return err;
    err = gpio_request_one(16,GPIOF_IN,"encoder1b");
    if(err)
            return err;
    err = gpio_request_one(20,GPIOF_IN,"encoder2a");
    if(err)
            return err;
    err = gpio_request_one(21,GPIOF_IN,"encoder2b");
    if(err)
            return err;
    enable_irq(gpio_to_irq(12));
    enable_irq(gpio_to_irq(16));
    enable_irq(gpio_to_irq(20));
    enable_irq(gpio_to_irq(21));


    err = request_irq(gpio_to_irq(12),irq_handler1,IRQ_TYPE_EDGE_BOTH,"encoder1a",NULL);
    if(err<0)
    {
        printk("irq_request failed\n");
        return err;
    }
    err = request_irq(gpio_to_irq(16),irq_handler2,IRQ_TYPE_EDGE_BOTH,"encoder1b",NULL);
    if(err<0)
    {
        printk("irq_request failed\n");
        return err;
    }
    err = request_irq(gpio_to_irq(20),irq_handler3,IRQ_TYPE_EDGE_BOTH,"encoder2a",NULL);
    if(err<0)
    {
        printk("irq_request failed\n");
        return err;
    }
    err = request_irq(gpio_to_irq(21),irq_handler4,IRQ_TYPE_EDGE_BOTH,"encoder2b",NULL);
    if(err<0)
    {
        printk("irq_request failed\n");
        return err;
    }
    flag =1;


    return 0;
failure_dev_class:
    kfree(encoder_devp);
failure_kzalloc:
        unregister_chrdev_region(dev, ENCODER_COUNT);
failure_register_chrdev:
        return ret;
}
static void encoder_exit(void)
{
    printk(KERN_INFO"led_exit\n");

    if(flag){
            free_irq(gpio_to_irq(12),NULL);
            free_irq(gpio_to_irq(16),NULL);
            free_irq(gpio_to_irq(20),NULL);
            free_irq(gpio_to_irq(21),NULL);
            gpio_free(12);
            gpio_free(16);
            gpio_free(20);
            gpio_free(21);
            device_destroy(dev_class, dev);
            cdev_del(&(encoder_devp->cdev));
            printk("destroy class\n");
            class_destroy(dev_class);
            kfree(encoder_devp);
            unregister_chrdev_region(dev,ENCODER_COUNT);
    }
}


module_init(encoder_init);
module_exit(encoder_exit);

MODULE_LICENSE("Dual BSD/GPL");
