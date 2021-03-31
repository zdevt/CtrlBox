/*
 * =====================================================================================
 *
 *       Filename:  FpgaReg.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月02日 20时41分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  FPGAREG_INC
#define  FPGAREG_INC

#include <stdint.h>


/* FPGA_REG_INTERRUPT_STA  0x05 */
typedef union
{
  struct
  {
    uint8_t : 2;
    uint8_t init_done: 1; /*  R; 0:失败，再复位fpga，1：成功 */
    uint8_t reset_cnt: 1; /*  RW : 1->0 清除寄存器*/
    uint8_t cnt_l4: 4; /*  R */
    uint8_t cnt_h8: 8; /*  R */
  };
  uint16_t data;
} fpga_reg_interrupt_sta_t;

/*  FPGA_REG_PIC_PRO_CTL  0x08 */
typedef union
{
  struct
  {
    uint8_t auto_desk: 1;
    uint8_t scaler: 1;
    uint8_t blc: 1;
    uint8_t gamma: 1;
    uint8_t ide: 1;
    uint8_t lbc: 1;
    uint8_t osd: 1;
    uint8_t res: 1;

    uint8_t testpic: 1;
    uint8_t pic_add: 1;
    uint8_t frc_en: 1;
    uint8_t logo_en: 1;
    uint8_t colorkey: 1;
    uint8_t awb: 1;
    uint8_t sig_loss_mode : 1;
    uint8_t res2: 1;
  };
  uint16_t data;
} fpga_reg_pic_pro_ctl_t;

/*  FPGA_DESKTOP_SEL 0x7a        */
typedef union
{
  struct
  {
    uint8_t dvi_sel: 2;
    uint8_t dvi1: 1;
    uint8_t dvi2: 1;
    uint8_t res: 4;
  };
  uint16_t data;
} fpga_reg_desktop_sel_t;

/* FPGA_REG_WIN_FLUSH  */
typedef union
{
  struct
  {
    uint8_t update_all_cube_win : 1;
    uint8_t update_cube_win : 1;
    uint8_t update_user_def : 1;
  };
  uint16_t data;
} fpga_reg_win_flush_t;

/*  FPGA_REG_V_ACTIVE */
typedef union
{
  struct
  {
    uint8_t img_valid : 1;
    uint8_t hs : 1;
    uint8_t vs : 1;
  };
  uint16_t data;
} fpga_reg_v_active_t;

/*  FPGA_REG_PIC_TYPE */
typedef union
{
  struct
  {
    /* 00:24  01:1 */
    uint8_t logo : 2;
    uint8_t test : 2;
  };
  uint16_t data;
} fpga_reg_pic_type_t;

enum FPGAREG_E
{
  FPGA_FAN1_RATE          = 0x0003,   /* 背板风扇转速       R   16  0   */
  FPGA_FAN2_RATE          = 0x0004,   /* 背板风扇转速       R   16  0   */

  FPGA_REG_INTERRUPT_STA  = 0x0005,   /* 中断状态寄存器    R/W 1   0   */
  /* [0]---行场同步正在改变中断     */
  /* [1]---DVI信号无效(需优先响应)   */
  /* [2]---行同步在改变（1:改变）   */
  /* [3]---场同步在改变（1:改变）   */

  FPGA_REG_PIC_PRO_CTL    = 0x0008,   /*  图像和处理功能和旁路选择 R/W 16 0x00ff */
  /* auto/manul desk  [0]---1/0 0:自动 1: 手动  */
  /* CTC—色温补偿     [1]---1/0 允许CTC/旁路    */
  /* BLC—黑电平调整   [2]---1/0 允许BLC/旁路  */
  /* Gamma—Gamma修正  [3]---1/0 允许Gamma/旁路 */
  /* IDE—图像抖动处理 [4]---1/0 允许IDE /旁路 */
  /* LBC—局部亮度补偿 [5]---1/0 允许LBC/旁路 */
  /* OSD-菜单         [6]---1/0 OSD显示/关闭 */
  /*                  [7] */
  /*                  [8]---1/0 测试图允许/关闭 */
  /*                  [9]---1/0 叠加允许/关闭 */
  /* FRC_in--桌面输入 [10]---FRC in桌面输入/停止 */
  /* LOGO--LOGO图输出 [11]---LOGO图输出 */
  /* colorkey--窗口叠加colorkey [12]---colorkey允许/关闭 */
  /* AWB--自动白平衡调节 [13]---AWB调整允许关闭 */

  FPGA_REG_P3L_FLAG       = 0x0009,   /* 全局控制寄存器  R/W 3  0 */
  /*                  [0]---0:为棋盘格测试图按4:3输出;  1:还是16:9输出 */

  FPGA_REG_RED_COEF       = 0x0010,   /* 测试图红色调整  R/W 8 255 */
  FPGA_REG_GRN_COEF       = 0x0011,   /* 测试图绿色调整  R/W 8 255 */
  FPGA_REG_BLU_COEF       = 0x0012,   /* 测试图蓝色调整  R/W 8 255 */

  FPGA_REG_DDR2_EX_ADDR   = 0x0030,   /* DDR2地址扩展寄存器 R/W 16 0 */
  /* {[5:4],[1:0]}位。DDR Bank地址选择。 */
  /* 0000：作为DDR地址扩展(Bank0) */
  /* 0001：作为DDR地址扩展(Bank1) */
  /* ..................           */
  /* 1111：作为DDR地址扩展(Bank15) */
  /* [3]---ARM写DDR标志。高有效。 */
  /* [2]---ARM读DDR标志。高有效   */

  FPGA_REG_K24_H          = 0x0033,  /* LBC像素修正系数 R/W 8 0 */
  /* [7:0]为LBC像素修正系数高8位。其他位保留。*/
  FPGA_REG_K24_L          = 0x0034,  /* LBC像素修正系数 R/W 16 0 */
  /* [15:0]为LBC像素修正系数低16位。 */

  FPGA_REG_CIRCLE_COLOR0__H = 0x0035,  /* 1位测试圆的0值代表颜色 */
  /*  1位测试圆的0值代表颜色高8位 */
  FPGA_REG_CIRCLE_COLOR0__L = 0x0036,  /* 1位测试圆的0值代表颜色 */
  /*  1位测试圆的0值代表颜色低16位 */
  FPGA_REG_CIRCLE_COLOR1__H = 0x0037,  /* 1位测试圆的0值代表颜色 */
  /*  1位测试圆的1值代表颜色高8位 */
  FPGA_REG_CIRCLE_COLOR1__L = 0x0038,  /* 1位测试圆的0值代表颜色 */
  /*  1位测试圆的1值代表颜色低16位 */

  FPGA_REG_PIC_TYPE       = 0x0039, /*  ARM当前输出图像数据类型 R/W 4 0 */
  /*  [1:0]代表LOGO图像数据类型。 */
  /*  [3:2]代表测试圆图像数据类型 */
  /*  00---24位图像类型； */
  /*  10代表8位调色板图像类型 */
  /*  11表8位灰度图像类型 */
  /*  01代表1位图像类型。 */

  FPGA_REG_FIFI_FLAG            = 0x003E, /*  ARM读写fifo标志 R/W 0xb110 */
  /*  [0]--ARM写DDR2 fifo满标志。 */
  /*  [1]--ARM写DDR2 fifo空标志。 */
  /*  [2]--ARM读DDR2 fifo空标志 */

  FPGA_REG_V_ACTIVE             = 0x0043,
  /*  [0] 图像有效 */
  /*  [1] 行同步 机型 */
  /*  [2] 场同步 */

  FPGA_REG_VD_HRES              = 0x0045, /*  FPGA检测出来的分辨率 */
  FPGA_REG_VD_VRES              = 0x0046,

  FPGA_REG_DE_WIDTH             = 0x0047,
  FPGA_REG_DE_HEIGHT            = 0x0048,

  FPGA_REG_CLP_ST_X             = 0x0050,
  FPGA_REG_CLP_ST_Y             = 0x0051,
  FPGA_REG_CLP_ED_X             = 0x0052,
  FPGA_REG_CLP_ED_Y             = 0x0053,

  FPGA_REG_WIN_ST_X             = 0x0054,
  FPGA_REG_WIN_ST_Y             = 0x0055,
  FPGA_REG_WIN_ED_X             = 0x0056,
  FPGA_REG_WIN_ED_Y             = 0x0057,

  FPGA_REG_VSFACTOR             = 0x0058,
  FPGA_REG_HSFACTOR             = 0x0059,

  FPGA_REG_WIN_FLUSH            = 0x006a,
  /*  [0]--同时更新所有窗口  */
  /*  [1]--更新本单元 */
  /*  [2]--自定义桌面 */

  FPGA_REG_ARMWR_BE             = 0x0070,
  FPGA_DDR_LOCKE                = 0x0071,
  FPGA_DESKTOP_REG              = 0x0074,

  FPGA_USERDEF_SEL              = 0x0079,

  /*  主控板DVI口选择  读回来4位  [3]     1代表第二路DVI有 */
  /*                              [2]     1代表第一路DVI有 */
  /*                              [1:0]   10 表示选择DVI1 */
  /*                              [1:0]   00 表示选择DVI2 */
  FPGA_DESKTOP_SEL              = 0x007a,

  FPGA_REG_HS_POL_CNT_REG       = 0x0080, /*HS的极性宽度寄存器*/
  FPGA_REG_VS_POL_CNT_REG       = 0x0081, /*VS的极性宽度寄存器*/
  FPGA_REG_HS_TOTAL_DOTCNT_REG  = 0x0082, /*每行的点数//含消隐区/寄存器*/
  FPGA_REG_VS_TOTAL_LINECNT_REG = 0x0083,  /*每场的行数//含消隐区/寄存器*/
  FPGA_REG_HS2DE_STCNT_REG      = 0x0084, /*行前沿到DE开始//像素点/寄存器*/
  FPGA_REG_HS2DE_ENDCNT_REG     = 0x0085, /*行前沿到DE开始+行中DE宽度//像素点/寄存器*/
  FPGA_REG_VS2DE_STCNT_REG      = 0x0086,  /*场前沿到DE开始行寄存器*/
  FPGA_REG_VS2DE_ENDCNT_REG     = 0x0087,  /*场前沿到DE开始行+场中DE宽度寄存器*/

  FPGA_REG_TEST                 = 0x00ff,

};

#define     DISABLE                     0
#define     ENABLE                      1

void FPGAConfigDdrLockReg ( unsigned short val );
void FPGAArmWriteContol ( unsigned char Enable );
void FPGASetDDR2WriteOnOff ( unsigned short onOff );
void FPGASetDDR2ExtendAddress ( unsigned short exAddr );
void FPGASetColorTypeRegister ( unsigned short val );
void FPGADisableLBCControl();

#define LBCFPGA_REG_EXADDR  0x02
void LBCFPGASetDDR2ExtendAddress ( uint16_t exAddr );
void FPGAEnablePictureProcessControl ( uint16_t val );

#endif   /* ----- #ifndef FpgaReg.h ----- */

