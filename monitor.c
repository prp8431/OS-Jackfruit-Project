#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "monitor_ioctl.h"

#define DEVICE_NAME "monitor_dev"

static int major;

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    switch(cmd) {
        case IOCTL_START:
            printk(KERN_INFO "Container START received\n");
            break;
        case IOCTL_STOP:
            printk(KERN_INFO "Container STOP received\n");
            break;
        default:
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .unlocked_ioctl = device_ioctl,
};

static int __init monitor_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "Monitor module loaded. Major: %d\n", major);
    return 0;
}

static void __exit monitor_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Monitor module unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
