/*
 * =====================================================================================
 *
 *       Filename:  Interrupt.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/16/2015 01:21:53 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  INTERRUPT_INC
#define  INTERRUPT_INC

#define NETLINK_ZT              (22)

enum
{
  MSG_TYPE_ENABLE  = 1,  /*  USER->KERNEL */
  MSG_TYPE_INTERRUPT,    /*  KERNEL->USER */

  MSG_TYPE_MAX,
};

enum
{
  INTERRUPT_INFO_TYPE_FPGA = 1,

  INTERRUPT_INFO_TYPE_MAX,
};

#pragma pack(push)
#pragma pack(1)
/* For MSG_TYPE_ENABLE */
typedef struct
{
  unsigned int irqNo;  /* irq No */
  unsigned int status; /* 0: disable 1: enable */
} irq_opt_t;

/* For MSG_TYPE_INTERRUPT */
typedef struct
{
  unsigned long type;
  unsigned long val;
} interrupt_info_t;

//中断结构定义
typedef struct
{
  unsigned int  irq;                //中断号
  irq_handler_t handle;             //中断处理函数
  unsigned long flags;              //中断触发类型
  unsigned int  enabled;            //是否已经打开
  char*         name;               //中断名字
} irq_def_t;
#pragma pack(pop)

#define INT_FPGA_PIN      AT91_PIN_PC25


#endif   /* ----- #ifndef INTERRUPT_INC  ----- */


