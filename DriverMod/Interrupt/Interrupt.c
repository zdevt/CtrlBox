/*
 * =====================================================================================
 *
 *       Filename:  Interrupt.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/16/2015 01:22:33 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <asm/mach/irq.h>
#include <mach/gpio.h>
#include <net/sock.h>
#include <linux/interrupt.h>

#include "Interrupt.h"


static int noused       = 0;
static int userPid      = -1;
struct sock* netlinkFd  = NULL;


irqreturn_t irq_fpga_tophalf ( int irq, void* dev_id );
void fpga_irq_tasklet_bottomhalf ( unsigned long val );


irq_def_t irq_def[] =
{
  {INT_FPGA_PIN,   irq_fpga_tophalf, IRQF_SHARED, 0,  "INT-Fpga"},
};

DECLARE_TASKLET ( fpga_irq_tasklet, fpga_irq_tasklet_bottomhalf, 0 );


static void IrqOpt ( void* buffer, int len )
{
  int i = 0;
  int total = len / sizeof ( irq_opt_t );
  irq_opt_t* p = ( irq_opt_t* ) ( buffer );

  for ( i = 0; i < total; ++i )
  {
    if ( p[i].irqNo < ARRAY_SIZE ( irq_def ) )
    {
      if ( p[i].status != irq_def[p[i].irqNo].enabled )
      {
        irq_def[p[i].irqNo].enabled = p[i].status;

        if ( p[i].status == 0 )
          disable_irq ( irq_def[p[i].irqNo].irq );
        else
          enable_irq ( irq_def[p[i].irqNo].irq );
      }
    }
  }
}

static int KernelSend ( void* buffer, int len, int pid, int type )
{
  struct nlmsghdr* out_nlh = NULL;
  struct sk_buff* out_skb = NULL;

  out_skb = nlmsg_new ( NLMSG_SPACE ( len ), GFP_KERNEL );

  if ( !out_skb )
  {
    printk ( "nlmsg_new error!\n" );
    return -1;
  }

  out_nlh = nlmsg_put ( out_skb, 0, 0, 0, NLMSG_SPACE ( len ), 0 );
  memcpy ( NLMSG_DATA ( out_nlh ), buffer, len );
  out_nlh->nlmsg_len = len + NLMSG_HDRLEN;
  out_nlh->nlmsg_type = type;

  NETLINK_CB ( out_skb ).pid = 0;
  NETLINK_CB ( out_skb ).dst_group = 0;

  netlink_unicast ( netlinkFd, out_skb, pid, MSG_DONTWAIT );

  //nlmsg_free( out_skb );  /* 内核会自己释放，不需要释放也不能释放，释放就会崩溃 */
  return 0;
}

static void KernelRecv ( struct sk_buff* skb )
{
  struct nlmsghdr* nlh = NULL;
  //char sendbuf2[32] = "MSG_TYPE_ENABLE";

  if ( skb->len >= NLMSG_HDRLEN )
  {
    nlh = ( struct nlmsghdr* ) skb->data;

    if ( ( nlh->nlmsg_len >= NLMSG_HDRLEN ) && ( skb->len >= nlh->nlmsg_len ) )
    {
      switch ( nlh->nlmsg_type )
      {
        case MSG_TYPE_ENABLE:
        {
          userPid = nlh->nlmsg_pid;
          IrqOpt ( ( void* ) NLMSG_DATA ( nlh ), ( nlh->nlmsg_len - NLMSG_HDRLEN ) );
          printk ( "User-> %d pid=%d %s\n", nlh->nlmsg_len - NLMSG_HDRLEN , nlh->nlmsg_pid, ( char* ) NLMSG_DATA ( nlh ) );
          //KernelSend ( sendbuf2, strlen ( sendbuf2 ) + 1, nlh->nlmsg_pid, nlh->nlmsg_type );
          break;
        }

        default:
          break;
      }
    }
  }
}

void fpga_irq_tasklet_bottomhalf ( unsigned long val )
{
  interrupt_info_t interrupt_info = {0};
  interrupt_info.type = INTERRUPT_INFO_TYPE_FPGA;
  interrupt_info.val  = val;

  KernelSend ( &interrupt_info, sizeof ( interrupt_info_t ), userPid, MSG_TYPE_INTERRUPT );
}

irqreturn_t irq_fpga_tophalf ( int irq, void* dev_id )
{
  if ( userPid != -1 )
    tasklet_schedule ( &fpga_irq_tasklet );

  return IRQ_HANDLED;
}

void IrqPinInit ( void )
{
  int loop = 0;
  int ret = 0;

  for ( ; loop < ARRAY_SIZE ( irq_def ); ++loop )
  {
    at91_set_gpio_input ( irq_def[loop].irq, 1 );     //设置输入 且上拉
    at91_set_deglitch ( irq_def[loop].irq, 1 );       //滤波
    ret = request_irq ( irq_def[loop].irq, irq_def[loop].handle,
                        irq_def[loop].flags, irq_def[loop].name, &noused );

    if ( ret < 0 )
      printk ( "request_irq error no:%d error:%d\n", loop, ret );

    disable_irq ( irq_def[loop].irq ); //先禁止中断
  }
}

void IrqPinDeinit ( void )
{
  int loop = 0;

  for ( ; loop < ARRAY_SIZE ( irq_def ); ++loop )
    free_irq ( irq_def[loop].irq, &noused );
}

static int __init InterruptInit ( void )
{
  IrqPinInit();

  netlinkFd = netlink_kernel_create ( &init_net, NETLINK_ZT, 0, KernelRecv, NULL, THIS_MODULE );

  if ( !netlinkFd )
    return -1;

  return 0;
}

static void __exit InterruptExit ( void )
{
  IrqPinDeinit();
  sock_release ( netlinkFd->sk_socket );
}

module_init ( InterruptInit );
module_exit ( InterruptExit );

MODULE_AUTHOR ( "zt" );
MODULE_LICENSE ( "GPL" );


