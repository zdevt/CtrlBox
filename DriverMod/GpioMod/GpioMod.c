/*
 * =====================================================================================
 *
 *       Filename:  GpioMod.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/13/2015 05:59:09 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  __KERNEL__
  #define  __KERNEL__
#endif

#ifndef MODULE
  #define MODULE
#endif

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <mach/gpio.h>
#include <mach/at91_pio.h>

#include "GpioMod.h"


#define DEV_NAME_GPIO "GpioMod"

static DECLARE_MUTEX ( mutex_gpio );

static int32_t gpio_major = 0;
static int32_t gpio_minor = 0;

static dev_t dev_t_gpio = 0;
static struct cdev cdev_gpio;
struct class* class_gpio = NULL;


/* IOCTL CMD */
/*  CMD_GPIO_TEST     */
static int cmd_gpio_test ( void* pvoid )
{
  return 0;
}

/* CMD_SET_GPIO_PERIPH * mux the pin to the "GPIO" peripheral role. */
static int cmd_set_gpio_periph ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_GPIO_periph ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，是否上拉 */
}

/* CMD_SET_A_PERIPH,   mux the pin to the "A" internal peripheral role. */
static int cmd_set_a_periph ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_A_periph ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，是否上拉 */
}

/* CMD_SET_B_PERIPH,   mux the pin to the "B" internal peripheral role. */
static int cmd_set_b_periph ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_B_periph ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，是否上拉 */
}

/* CMD_SET_GPIO_INPUT, mux the pin to the gpio controller , and configure it for an input. */
static int cmd_set_gpio_input ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_gpio_input ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，是否上拉 */
}

/* CMD_SET_GPIO_OUTPUT, output */
static int cmd_set_gpio_output ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_gpio_output ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，值 */
}

/* CMD_SET_DEGLITCH, enable/disable the glitch filter; mostly used with IRQ handling */
static int cmd_set_deglitch ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_deglitch ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，是否打开 */
}

/* CMD_SET_MULTI_DRIVER, enable/disable the multi-driver output pin to run as an open collector output*/
static int cmd_set_multi_driver ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_multi_drive ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，是否打开 */
}

/* CMD_SET_GPIO_VALUE, assuming the pin is muxed as a gpio output, set its value. */
static int cmd_set_gpio_value ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  return at91_set_gpio_value ( pgpio_data->addr, pgpio_data->val ); /* 参数，管脚，值 */
}

/* CMD_GET_GPIO_VALUE, read the pin's value (works even if it's not muxed as a gpio). */
static int cmd_get_gpio_value ( void* pvoid )
{
  gpio_data_t* pgpio_data = pvoid;

  if ( ! pgpio_data )
    return -EFAULT;

  pgpio_data->val = at91_get_gpio_value ( pgpio_data->addr ); /* 参数，管脚*/

  return 0;
}


static int cmd_max ( void* pvoid )
{
  return 0;
}


/* 函数顺序须与 enum CMD_GPIO 一致 */
PFUNC PFUNC_ARRAY[] =
{
  cmd_gpio_test,
  cmd_set_gpio_periph,
  cmd_set_a_periph,
  cmd_set_b_periph,
  cmd_set_gpio_input,
  cmd_set_gpio_output,
  cmd_set_deglitch,
  cmd_set_multi_driver,
  cmd_set_gpio_value,
  cmd_get_gpio_value,

  cmd_max,
};

static long gpio_ioctl ( struct file* file, unsigned int cmd, unsigned long val )
{
  int iRet = 0 ;

  if ( cmd >= ARRAY_SIZE ( PFUNC_ARRAY ) ) /* 传入cmd超出数组范围返回失败 */
  {
    printk ( "cmd > gpio_ioctl ARRAY_SIZE! cmd=%d\n", cmd );
    return -EFAULT;
  }

  if ( down_interruptible ( &mutex_gpio ) )
    return -ERESTARTSYS;

  iRet = ( int ) ( PFUNC_ARRAY[cmd] ( ( void* ) val ) );

  up ( &mutex_gpio );
  return iRet;
}


static int gpio_open ( struct inode* pinode, struct file* pfile )
{
  try_module_get ( THIS_MODULE );
  return 0;
}

static int gpio_release ( struct inode* pinode, struct file* pfile )
{
  module_put ( THIS_MODULE );
  return 0;
}

static ssize_t gpio_write ( struct file* file,
                            const char __user* buffer,
                            size_t len,
                            loff_t* offset )
{
  printk ( "enter gpio_write\n" );
  return len;
}

static ssize_t gpio_read ( struct file* file,
                           char __user* buffer,
                           size_t len,
                           loff_t* offset )
{
  printk ( "enter gpio_read\n" );
  return len;
}



static struct file_operations fops_gpio =
{
  .owner = THIS_MODULE,
  .unlocked_ioctl = gpio_ioctl,
  .open     = gpio_open,
  .release  = gpio_release,
  .write    = gpio_write,
  .read     = gpio_read,
};


static int __init GpioModInit ( void )
{
  int result = 0;

  result = alloc_chrdev_region ( &dev_t_gpio, 0, 1, DEV_NAME_GPIO );

  if ( result < 0 )
  {
    printk ( "alloc_chrdev_region %d \n", result );
    return result;
  }

  gpio_major = MAJOR ( dev_t_gpio );

  sema_init ( &mutex_gpio, 1 );

  cdev_init ( &cdev_gpio, &fops_gpio );
  cdev_gpio.owner = THIS_MODULE;
  cdev_gpio.ops = &fops_gpio;

  result = cdev_add ( &cdev_gpio, MKDEV ( gpio_major, gpio_minor ), 1 );

  if ( result )
  {
    printk ( KERN_NOTICE "Error %d adding cdev!\n", result );
    goto MOD_ERROR;
  }

  /* 创建 /sys/class 信息 */
  class_gpio = class_create ( THIS_MODULE, DEV_NAME_GPIO );

  if ( NULL == class_gpio )
  {
    printk ( KERN_NOTICE "class_create error !\n" );
    goto MOD_ERROR;
  }

  /* 创建 /dev  信息 */
  device_create ( class_gpio, NULL, dev_t_gpio, NULL, DEV_NAME_GPIO );

  return 0;

MOD_ERROR:

  cdev_del ( &cdev_gpio );
  unregister_chrdev_region ( dev_t_gpio, 1 );

  if ( class_gpio )
  {
    device_destroy ( class_gpio, dev_t_gpio );
    class_destroy ( class_gpio );
    class_gpio = NULL;
  }

  return -1;
}

static void __exit GpioModExit ( void )
{
  cdev_del ( &cdev_gpio );
  unregister_chrdev_region ( MKDEV ( gpio_major, 0 ), 1 );

  if ( class_gpio )
  {
    device_destroy ( class_gpio, dev_t_gpio );
    class_destroy ( class_gpio );
    class_gpio = NULL;
  }
}


module_init ( GpioModInit );
module_exit ( GpioModExit );


MODULE_AUTHOR ( "zt" );
MODULE_LICENSE ( "GPL" );


