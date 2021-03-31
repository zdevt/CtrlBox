/*
 * =====================================================================================
 *
 *       Filename:  FpgaMod.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/12/2015 10:16:29 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/cdev.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/ioctl.h>
#include <linux/device.h>

#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/gpio.h>

#include "FpgaMod.h"


#define DEV_NAME_MOD "FpgaMod"

static DECLARE_MUTEX ( mutex_mod );

//static int32_t fpga_major = 0;
//static int32_t fpga_minor = 0;

static dev_t dev_t_mod   = 0;
struct class* pclass_mod  = NULL;
static struct cdev cdev_mod;

static unsigned long FPGA_IOREMAP_BASE = 0;
static unsigned long DDR_IOREMAP_BASE  = 0;

static bool g_fpga_start_config = false;

fpga_pin_t g_fpga_pin = { 0 };

#define FPGA_DATA0_PIN      g_fpga_pin.data0
#define FPGA_CLK_PIN        g_fpga_pin.clk
#define FPGA_NCONFIG_PIN    g_fpga_pin.nconfig
#define FPGA_CFG_DONE_PIN   g_fpga_pin.cfg_done
#define FPGA_NSTATUS_PIN    g_fpga_pin.nstatus
#define FPGA_NRESET_EN_PIN  g_fpga_pin.nreset_en
#define FPGA_NRESET_PIN     g_fpga_pin.nreset
#define FPGA_RW_EN_PIN      g_fpga_pin.rw_en

static void FpgaPinDef ( void )
{
  FPGA_DATA0_PIN      = AT91_PIN_PC16;
  FPGA_CLK_PIN        = AT91_PIN_PC18;
  FPGA_NCONFIG_PIN    = AT91_PIN_PC17;
  FPGA_CFG_DONE_PIN   = AT91_PIN_PC19;
  FPGA_NSTATUS_PIN    = AT91_PIN_PC20;
  FPGA_NRESET_EN_PIN  = AT91_PIN_PC27;
  FPGA_NRESET_PIN     = AT91_PIN_PC26;
  FPGA_RW_EN_PIN      = AT91_PIN_PB22;
}

static void DeInitFpgaPin ( void )
{
  PIN_FUNC ( at91_set_gpio_input, FPGA_DATA0_PIN, 0 );
  PIN_FUNC ( at91_set_gpio_input, FPGA_CLK_PIN, 0 );
  PIN_FUNC ( at91_set_gpio_input, FPGA_NCONFIG_PIN, 0 );

  PIN_FUNC ( at91_set_gpio_input, FPGA_NSTATUS_PIN, 0 );
  PIN_FUNC ( at91_set_gpio_input, FPGA_NRESET_PIN, 0 );
}

static void  InitFpgaPin ( void )
{
  PIN_FUNC ( at91_set_gpio_output, FPGA_DATA0_PIN, 0 );
  PIN_FUNC ( at91_set_gpio_output, FPGA_CLK_PIN, 0 );
  PIN_FUNC ( at91_set_gpio_output, FPGA_NCONFIG_PIN, 1 );
  PIN_FUNC ( at91_set_gpio_input,  FPGA_CFG_DONE_PIN, 0 );
  PIN_FUNC ( at91_set_gpio_input,  FPGA_NSTATUS_PIN, 0 );
  PIN_FUNC ( at91_set_gpio_output, FPGA_NRESET_PIN, 1 );
  PIN_FUNC ( at91_set_gpio_output, FPGA_NRESET_EN_PIN, 1 );
  PIN_FUNC ( at91_set_gpio_output, FPGA_RW_EN_PIN, 0 );
}

static  void TriggerFpgaLoad ( void )
{
  PIN_FUNC ( at91_set_gpio_value , FPGA_NCONFIG_PIN, 0 );
  udelay ( 10 );
  PIN_FUNC ( at91_set_gpio_value , FPGA_NCONFIG_PIN, 1 );
}

static unsigned int FpgaIsReady ( void )
{
  if ( FPGA_NSTATUS_PIN )
    return at91_get_gpio_value ( FPGA_NSTATUS_PIN );

  return -6;
}

static void  ResetFpga ( void )
{
  PIN_FUNC ( at91_set_gpio_value , FPGA_NRESET_PIN, 0 );
  udelay ( 100 );
  PIN_FUNC ( at91_set_gpio_value , FPGA_NRESET_PIN, 1 );
}

static  int FpgaLoadByte ( unsigned char data )
{
  unsigned int j = 0;
  static int count = 0;

  for ( j = 0; j < 8; j++ )
  {
    PIN_FUNC ( at91_set_gpio_value , FPGA_CLK_PIN, 0 );
    PIN_FUNC ( at91_set_gpio_value , FPGA_DATA0_PIN, ( data >> j ) & 0x1 );
    PIN_FUNC ( at91_set_gpio_value , FPGA_CLK_PIN, 1 );
  }

  count++;

  if ( 0 == FpgaIsReady() ) //检测是否出错
  {
    //printk ( KERN_ERR"FPGA program Error %d\n", count ) ;
    return -1;
  }

  return 0;
}

static int FgpaLoadData ( unsigned char* data, unsigned int length )
{
  unsigned int i, count = 0;
  unsigned char val;

  for ( i = 0; i < length; i++ )
  {
    val = *data++;

    if ( FpgaLoadByte ( val ) )
      return -6;
  }

  for ( i = 0; i < 100; i++ )
  {
    PIN_FUNC ( at91_set_gpio_value , FPGA_CLK_PIN, 0 );
    ndelay ( 5 );
    PIN_FUNC ( at91_set_gpio_value , FPGA_CLK_PIN, 1 );
  }

  if ( !FPGA_CFG_DONE_PIN )
    return -7;

  while ( 0 == at91_get_gpio_value ( FPGA_CFG_DONE_PIN ) )
  {
    udelay ( 30 ) ;
    count++ ;

    if ( 10 == count )
    {
      printk ( KERN_ERR"FPGA DONE Signal Error \n" ) ;
      return -8;
    }
  }

  PIN_FUNC ( at91_set_gpio_value , FPGA_NRESET_EN_PIN, 0 );
  mdelay ( 50 );
  ResetFpga();
  mdelay ( 50 );
  return 0;
}

static int FpgaProg ( unsigned char* data, unsigned int length )
{
  unsigned int  count = 0;
  InitFpgaPin();
  TriggerFpgaLoad();

  while ( 0 == FpgaIsReady() )
  {
    udelay ( 10 ) ;
    count++ ;

    if ( 10 == count )
    {
      printk ( KERN_NOTICE"FPGA INIT Signal error!!" ) ;
      return -5;
    }
  }

  return FgpaLoadData ( data, length );
}

static int CmdFpgaLoad ( void* p )
{
  fpga_config_data_t* fpga_config_data = ( fpga_config_data_t* ) p;
  return FpgaProg ( fpga_config_data->data, fpga_config_data->cnt );
}

static int CmdFpgaGet ( void* p )
{
  fpga_data_t* pfpga_data = NULL ;

  pfpga_data = ( fpga_data_t* ) p;
  pfpga_data->data = ioread16 ( FPGA_IOREMAP_BASE +  ( pfpga_data->offset ) ) ;
  return 0;
}

static int CmdFpgaSet ( void* p )
{
  fpga_data_t* pfpga_data = NULL ;

  pfpga_data = ( fpga_data_t* ) p;
  iowrite16 ( pfpga_data->data, ( FPGA_IOREMAP_BASE + ( pfpga_data->offset ) ) );
  return 0;
}

static int CmdFpgaRwEn ( void* p )
{
  PIN_FUNC ( at91_set_gpio_output , FPGA_RW_EN_PIN, 1 );
  PIN_FUNC ( at91_set_gpio_value , FPGA_RW_EN_PIN, 0 );
  return 0;
}

static int CmdDdrGet ( void* p )
{
  fpga_data_t* pfpga_data = NULL ;

  pfpga_data = ( fpga_data_t* ) p;
  pfpga_data->data = ioread16 ( ( DDR_IOREMAP_BASE +  ( pfpga_data->offset ) ) );
  return 0;
}

static int CmdDdrSet ( void* p )
{
  fpga_data_t* pfpga_data = NULL ;

  pfpga_data = ( fpga_data_t* ) p;
  iowrite16 ( pfpga_data->data, ( DDR_IOREMAP_BASE + ( pfpga_data->offset ) ) );
  return 0;
}

static int CmdFpgaSetN ( void* p )
{
  unsigned int offset, index;

  fpga_datan_t* fpga_datan = ( fpga_datan_t* ) p;
  offset = fpga_datan->offset;

  for ( index = 0; index < fpga_datan->cnt; ++index, offset += 2 )
    iowrite16 ( fpga_datan->data[index], ( FPGA_IOREMAP_BASE + offset ) );

  return 0;
}

static int CmdDdrSetN ( void* p )
{
  unsigned int offset, index;
  fpga_datan_t* fpga_datan = ( fpga_datan_t* ) p;
  offset = fpga_datan->offset;

  for ( index = 0; index < fpga_datan->cnt; ++index, offset += 2 )
    iowrite16 ( fpga_datan->data[index], ( DDR_IOREMAP_BASE + offset ) );

  return 0;
}

static int CmdFpgaInit ( void* p )
{
  if ( !p )
    return -EFAULT;

  if ( copy_from_user ( &g_fpga_pin, ( fpga_pin_t __user* ) p, sizeof ( fpga_pin_t ) ) )
    return -EFAULT;

  return 0;
}

static int CmdFgpaDeInit ( void* p )
{
  DeInitFpgaPin ( );
  return 0;
}

static int CmdFpgaMax ( void* p )
{
  return 0;
}

PFUNC PFUNCARRAY[] =
{
  CmdFpgaLoad,

  CmdFpgaInit,
  CmdFgpaDeInit,
  CmdFpgaRwEn,

  CmdFpgaGet,
  CmdFpgaSet,

  CmdDdrGet,
  CmdDdrSet,

  CmdFpgaSetN,
  CmdDdrSetN,

  CmdFpgaMax,
};


static void FpgaStartConfig ( void )
{
  unsigned int  count = 0;
  InitFpgaPin();
  TriggerFpgaLoad();

  while ( ( 0 == FpgaIsReady() ) && ( ++count < 10 ) )
    udelay ( 10 ) ;
}

static void FpgaConfigData ( const char* buffer, int len )
{
  unsigned int i = 0;

  for ( i = 0; i < len; i++ )
    FpgaLoadByte ( *buffer++ );

  if ( len == 4096 )
    g_fpga_start_config = true;
  else
  {
    for ( i = 0; i < 100; i++ )
    {
      PIN_FUNC ( at91_set_gpio_value , FPGA_CLK_PIN, 0 );
      ndelay ( 5 );
      PIN_FUNC ( at91_set_gpio_value , FPGA_CLK_PIN, 1 );
    }

    mdelay ( 50 );
    g_fpga_start_config = false;
  }
}

static int FpgaIoctl ( struct inode* inode, struct file* file, unsigned int cmd, unsigned long arg )
{
  int iRet = 0 ;

  if ( cmd >= ARRAY_SIZE ( PFUNCARRAY ) || ( !pclass_mod ) )
  {
    printk ( "cmd > FpgaIoctl ARRAY_SIZE! cmd=%d\n", cmd );
    return -EFAULT;
  }

  if ( down_interruptible ( &mutex_mod ) )
    return -ERESTARTSYS;

  iRet = ( int ) ( PFUNCARRAY[cmd] ( ( void* ) arg ) );

  up ( &mutex_mod );
  return iRet;
}

static int FpgaOpen ( struct inode* pinode, struct file* pfile )
{
  try_module_get ( THIS_MODULE );
  return 0;
}

static int FpgaClose ( struct inode* pinode, struct file* pfile )
{
  module_put ( THIS_MODULE );
  return 0;
}

static ssize_t FpgaWrite ( struct file* file,
                           const char __user* buffer,
                           size_t len,
                           loff_t* offset )
{
  if ( !g_fpga_start_config )
    FpgaStartConfig();

  FpgaConfigData ( buffer, len );

  return len;
}

static ssize_t FpgaRead ( struct file* file,
                          char __user* buffer,
                          size_t len,
                          loff_t* offset )
{
  printk ( "enter FpgaRead\n" );
  return len;
}

static struct file_operations fops_fpga =
{
  .owner    = THIS_MODULE,
  .ioctl    = FpgaIoctl,
  .open     = FpgaOpen,
  .release  = FpgaClose,
  .write    = FpgaWrite,
  .read     = FpgaRead,
};

static int IoRemap ( void )
{
  if ( !request_mem_region ( FPGA_PHY_START, FPGA_REMAP_SIZE, "FPGA_REG" ) )
  {
    printk ( "request_mem_region fpga failed\n" );
    goto MOD_ERROR;
  }

  FPGA_IOREMAP_BASE =  ( unsigned long ) ioremap ( FPGA_PHY_START, FPGA_REMAP_SIZE );

  if ( !FPGA_IOREMAP_BASE )
  {
    printk ( "ioremap fpga failed\n" );
    goto MOD_ERROR;
  }

  if ( !request_mem_region ( DDR_PHY_START, DDR_REMAP_SIZE, "FPGA_DDR" ) )
  {
    printk ( "request_mem_region ddr failed\n" );
    goto MOD_ERROR;
  }

  DDR_IOREMAP_BASE =  ( unsigned long ) ioremap ( DDR_PHY_START, DDR_REMAP_SIZE );

  if ( !DDR_IOREMAP_BASE )
  {
    printk ( "ioremap ddr failed\n" );
    goto MOD_ERROR;
  }

  return 0;

MOD_ERROR:
  return -1;
}

static void IoUnmap ( void )
{
  if ( FPGA_IOREMAP_BASE )
  {
    iounmap ( ( void* ) ( FPGA_IOREMAP_BASE ) );
    release_mem_region ( FPGA_PHY_START, FPGA_REMAP_SIZE );
    FPGA_IOREMAP_BASE = 0;
  }

  if ( DDR_IOREMAP_BASE )
  {
    iounmap ( ( void* ) ( DDR_IOREMAP_BASE ) );
    release_mem_region ( DDR_PHY_START, DDR_REMAP_SIZE );
    DDR_IOREMAP_BASE = 0;
  }
}

static void DelDev ( void )
{
  cdev_del ( &cdev_mod );
  unregister_chrdev_region ( dev_t_mod, 1 );

  if ( pclass_mod )
  {
    device_destroy ( pclass_mod, dev_t_mod );
    class_destroy ( pclass_mod );
    pclass_mod = NULL;
  }
}

static int __init ModInit ( void )
{
  int result = 0;

  result = alloc_chrdev_region ( &dev_t_mod, 0, 1, DEV_NAME_MOD );

  if ( result < 0 )
  {
    printk ( "alloc_chrdev_region %d \n", result );
    return result;
  }

  IoRemap();

  //fpga_major = MAJOR ( dev_t_mod );

  sema_init ( &mutex_mod, 1 );

  cdev_init ( &cdev_mod, &fops_fpga );
  cdev_mod.owner = THIS_MODULE;
  cdev_mod.ops = &fops_fpga;

  //result = cdev_add ( &cdev_mod, MKDEV ( fpga_major, fpga_minor ), 1 );
  result = cdev_add ( &cdev_mod, dev_t_mod, 1 );

  if ( result )
  {
    printk ( KERN_NOTICE "Error %d adding cdev!\n", result );
    goto MOD_ERROR;
  }

  /* 创建 /sys/class 信息 */
  pclass_mod = class_create ( THIS_MODULE, DEV_NAME_MOD );

  if ( NULL == pclass_mod )
  {
    printk ( KERN_NOTICE "class_create error !\n" );
    goto MOD_ERROR;
  }

  /* 创建 /dev  信息 */
  device_create ( pclass_mod, NULL, dev_t_mod, NULL, DEV_NAME_MOD );

  FpgaPinDef();
  InitFpgaPin();

  return 0;

MOD_ERROR:
  IoUnmap();
  DelDev();

  return -1;
}

static void __exit ModExit ( void )
{
  IoUnmap();
  DelDev();
  DeInitFpgaPin();
}

module_init ( ModInit );
module_exit ( ModExit );

MODULE_AUTHOR ( "zt" );
MODULE_LICENSE ( "GPL" );

