/*
 * =====================================================================================
 *
 *       Filename:  NorflashMod.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/20/2015 09:38:48 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/io.h>
#include <linux/slab.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>

#include "NorflashMod.h"

static struct map_info* sam_9g45_nor_map = NULL;
static struct mtd_info* sam_9g45_nor_mtd = NULL;

static struct mtd_partition sam_9g45_nor_partition[] =
{
  {
    .name = "bootloader",
    .offset = 0x0,
    //.mask_flags = MTD_WRITEABLE,
    .size = MTDPART_SIZ_FULL,
  },
};

static int __init init_sam_9g45_nor ( void )
{
  if ( sam_9g45_nor_map != NULL )
  {
    printk ( "sam_9g45_nor_map ok !\n" );
    return 0;
  }

  sam_9g45_nor_map = kzalloc ( sizeof ( struct map_info ), GFP_KERNEL );
  if ( NULL == sam_9g45_nor_map )
  {
    printk ( "sam_9g45_nor_map kzalloc error!\n" );
    return -1;
  }

  sam_9g45_nor_map->name      = "S29GL064N90FFI010";
  sam_9g45_nor_map->phys      = 0x10000000;
  sam_9g45_nor_map->size      = 0x800000;
  sam_9g45_nor_map->bankwidth = 2;

  sam_9g45_nor_map->virt = ioremap ( sam_9g45_nor_map->phys, sam_9g45_nor_map->size );
  if ( NULL == sam_9g45_nor_map->virt )
  {
    kfree ( sam_9g45_nor_map );
    printk ( "NULL == sam_9g45_nor_map->virt!\n" );
    return -1;
  }

  simple_map_init ( sam_9g45_nor_map );

  sam_9g45_nor_mtd = do_map_probe ( "cfi_probe", sam_9g45_nor_map );

  if ( NULL == sam_9g45_nor_mtd )
  {
    iounmap ( sam_9g45_nor_map->virt );
    kfree ( sam_9g45_nor_map );
    printk ( "NULL == sam_9g45_nor_mtd!\n" );
    return -1;
  }
  sam_9g45_nor_mtd->owner = THIS_MODULE;

  add_mtd_partitions ( sam_9g45_nor_mtd, sam_9g45_nor_partition, 1 );

  return 0;
}


static void __exit  exit_sam_9g45_nor ( void )
{
  if ( NULL != sam_9g45_nor_mtd )
  {
    del_mtd_partitions ( sam_9g45_nor_mtd );
    sam_9g45_nor_mtd = NULL;
  }

  if ( NULL != sam_9g45_nor_map->virt )
  {
    iounmap ( sam_9g45_nor_map->virt );
    sam_9g45_nor_map->virt = NULL;
  }

  if ( NULL != sam_9g45_nor_map )
  {
    kfree ( sam_9g45_nor_map );
    sam_9g45_nor_map = NULL;
  }

}

module_init ( init_sam_9g45_nor );
module_exit ( exit_sam_9g45_nor );


MODULE_LICENSE ( "GPL" );
MODULE_AUTHOR ( "zt" );

MODULE_DESCRIPTION ( "Generic configurable MTD map driver" );


