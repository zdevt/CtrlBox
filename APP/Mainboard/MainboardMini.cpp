/*
 * =====================================================================================
 *
 *       Filename:  MainboardMini.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/10/2015 10:33:01 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <unistd.h>

#include "MainboardMini.h"
#include "At91GpioDev.h"
#include "FpgaDev.h"
#include "FpgaTestPic.h"
#include "PowerSupplyDefault.h"
#include "XmlConfig.h"
#include "Idt5V49EE902.h"
#include "OpticEngineInterface.h"
#include "Warping787.h"
#include "GpioPwm.h"
#include "Led74Hc595D.h"
#include "RootfsAdmin.h"
#include "GpioDefine.h"

std::shared_ptr<Mainboard> MainboardMini::GetObj ( std::string mainboardName )
{
  return std::make_shared<MainboardMini> ( mainboardName );
}

MainboardMini::MainboardMini ( std::string mainboardName )
  : MainboardDefault ( mainboardName )
{

}

MainboardMini::~MainboardMini()
{
  DeInit();
}

bool MainboardMini::Open()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );

  Idt5V49EE902::SetPll ( NULL );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "SetPll\n" );

  Warping787::SetRes();

  sleep ( 2 );
  fpga_reg_interrupt_sta_t  fpga_reg_interrupt_sta;
  uint16_t ddr_resp_cnt = 0;
  uint32_t loadcnt = 1;
  uint32_t ddrcnt = 1;

  Led74Hc595D::Disp ( "3" );

  do
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "FpgaLoad cnt=%d\n", loadcnt );

    if ( -10 == FpgaLoad ( ) )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "FpgaLoad File not exist\n" );
      Led74Hc595D::Disp ( "3." );
      return false; // Fpga文件不存在直接返回失败，只有在fpag文件存在且加载失败的情况下才切换系统
    }

    if ( !FpgaIsLoad() )
      loadcnt++;
    else
    {
      /*  Get ddr status */
      usleep ( 100 * 1000 );
      fpga_reg_interrupt_sta.data = FpgaGetReg ( FPGA_REG_INTERRUPT_STA );

      PRINT_LOG ( LOG_LEVEL_NORMAL, "FpgaSta = 0x%04x\n", fpga_reg_interrupt_sta.data );

      Led74Hc595D::Disp ( "4" );

      while ( ( 0 == fpga_reg_interrupt_sta.init_done ) && ( ddrcnt++ < 10 ) )
      {
        PRINT_LOG ( LOG_LEVEL_NORMAL, "WAITTING DDR cnt=%d ...\n", ddrcnt );
        usleep ( 100 * 1000 );
      }

      if ( ddrcnt > 10 )
      {
        PRINT_LOG ( LOG_LEVEL_NORMAL, "DDR ERROR\n" );
        Led74Hc595D::Disp ( "4." );
        return false;
      }

      PRINT_LOG ( LOG_LEVEL_NORMAL, "Set Fpga Black \n" );
      FpgaSetReg ( FPGA_DESKTOP_REG, 0x6 ); /*  black  */

      /*  reset cnt */
      fpga_reg_interrupt_sta.reset_cnt = 1;
      FpgaSetReg ( FPGA_REG_INTERRUPT_STA, fpga_reg_interrupt_sta.data );
      fpga_reg_interrupt_sta.reset_cnt = 0;
      FpgaSetReg ( FPGA_REG_INTERRUPT_STA, fpga_reg_interrupt_sta.data );

      /*  write logo for test */
      GET_ENGPTR->WriteLogo();

      /*  reset cnt twice */
      fpga_reg_interrupt_sta.reset_cnt = 1;
      FpgaSetReg ( FPGA_REG_INTERRUPT_STA, fpga_reg_interrupt_sta.data );
      fpga_reg_interrupt_sta.reset_cnt = 0;
      FpgaSetReg ( FPGA_REG_INTERRUPT_STA, fpga_reg_interrupt_sta.data );

      /*  write logo for test */
      GET_ENGPTR->WriteLogo();

      /*  check ddr resp cnt */
      fpga_reg_interrupt_sta.data = FpgaGetReg ( FPGA_REG_INTERRUPT_STA );
      ddr_resp_cnt = fpga_reg_interrupt_sta.cnt_l4 + ( fpga_reg_interrupt_sta.cnt_h8 << 4 );

      PRINT_LOG ( LOG_LEVEL_NORMAL, "ddr_resp_cnt=%d\n", ddr_resp_cnt );
    }
  }
  while ( ( 0 == ddr_resp_cnt ) && ( loadcnt < 5 ) );

  if ( loadcnt == 5 )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "FpgaLoad ERROR\n" );
    Led74Hc595D::Disp ( "3." );
    RootfsAdmin::SwitchSysTem();
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Now Reboot .......!\n" );
    system ( "reboot;" );
    return false;
  }

  PRINT_LOG ( LOG_LEVEL_NORMAL, "FpgaLoad OK\n" );
  sleep ( 1 );

  //FpgaSetReg ( FPGA_DESKTOP_REG, 0x6 ); /*  black  */

  //sleep ( 1 );

  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_0.bmp", 0 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_1.bmp", 1 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_2.bmp", 2 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_3.bmp", 3 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_4.bmp", 4 );
  FpgaTestPic::WriteBmpUserDef ( "/app/user_def_5.bmp", 5 );

  GpioSetValue ( MAINBOARDDEFAULT_SYNC_ON_OFF, 1 );


  #if 1

  if ( GetCutWinFlag() )
  {
    uint32_t vd_hres, vd_vres;

    if ( 0 == GetInputSignalResol ( vd_hres, vd_vres ) )
    {
      int x, y, w, h;
      GetInputSignalRect ( x, y, w, h );

      SetInputSignalRectAndShow ( x, y, w, h, vd_hres, vd_vres );
    }
  }

  #endif

  return true;
}

bool MainboardMini::Close()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
  FpgaRegSet ( FPGA_DESKTOP_REG, 0x6 ); /*  black  */
  //FpgaUnLoad ( );

  GpioSetValue ( MAINBOARDDEFAULT_SYNC_ON_OFF, 0 );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "SetDmdReSetPin 0\n" );
  GpioSetValue ( MAINBOARDDEFAULT_DMD_RESET, 0 );
  usleep ( 15 * 1000 * 1000 );
  FpgaUnLoad ( );

  /* 关机引脚拉低 */
  //GpioSetOutput ( AT91_PIN_PC21, 0 );
  //GpioSetOutput ( FPGA_ECP3_RESET_PIN, 0 ); //PC26
  //GpioSetOutput ( AT91_PIN_PC27, 0 );
  //GpioSetOutput ( MAINBOARDDEFAULT_I2CBUS_ON_OFF, 0 ); //PC28

  //GpioSetOutput ( AT91_PIN_PA20, 0 );
  //GpioSetOutput ( AT91_PIN_PA21, 0 );

  //GpioSetOutput ( AT91_PIN_PB14, 0 );
  //GpioSetOutput ( AT91_PIN_PB15, 0 );
  //GpioSetOutput ( AT91_PIN_PB16, 0 );
  //GpioSetOutput ( AT91_PIN_PB17, 0 );
  //GpioSetOutput ( AT91_PIN_PB18, 0 );
  //GpioSetOutput ( AT91_PIN_PB19, 0 );

  return true;
}

bool MainboardMini::Init()
{
  std::string cmd;
  cmd += "modprobe GpioMod;";
  //cmd += "modprobe Interrupt;";
  cmd += "sleep 1;";
  PRINT_LOG ( LOG_LEVEL_NORMAL, "Mod %s\n", cmd.c_str() );

  system ( cmd.c_str() );

  PRINT_LOG ( LOG_LEVEL_NORMAL, " FPGA_ECP3 Init\n" );
  FpgaInitGpioPin ( );

  GpioSetOutput ( MAINBOARDDEFAULT_SYNC_ON_OFF, 1 );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "SetDmdReSetPin 0\n" );
  GpioSetOutput ( MAINBOARDDEFAULT_DMD_RESET, 0 );

  GpioSetInput ( MAINBOARDDEFAULT_ON_OFF, 1 );

  return false;
}

bool MainboardMini::DeInit()
{
  FpgaUnLoad ( );
  return true;
}

int MainboardMini::FpgaLoad ( )
{
  return FpgaECP3::Load ( FPGA_ECP3_BIT_FILE_NAME, FPGA_ECP3_CONFIG_NAME );
}

int MainboardMini::FpgaIsLoad ( )
{
  return FpgaECP3::IsLoad( );
}

int MainboardMini::FpgaUnLoad ( )
{
  return FpgaECP3::UnLoad ( FPGA_ECP3_CONFIG_NAME );
}

int MainboardMini::FpgaInitGpioPin ( )
{
  FpgaECP3::InitPin ( NULL, FPGA_ECP3_CONFIG_NAME );
  return 0;
}

int MainboardMini::FpgaRegGet ( int addr )
{
  return FpgaECP3::GetReg ( addr, FPGA_ECP3_NAME );
}

int MainboardMini::FpgaRegSet ( int addr, int val )
{
  return FpgaECP3::SetReg ( addr, val, FPGA_ECP3_NAME );
}

int MainboardMini::FpgaDdrGetReg ( int addr )
{
  return FpgaECP3::DdrGetReg ( addr, FPGA_ECP3_NAME );
}

int MainboardMini::FpgaDdrSetReg ( int addr, int val )
{
  return FpgaECP3::DdrSetReg ( addr, val, FPGA_ECP3_NAME );
}

int MainboardMini::FpgaSetRegN ( void* p )
{
  return FpgaECP3::SetRegN ( p, FPGA_ECP3_NAME );
}

int MainboardMini::FpgaDdrSetRegN ( void* p )
{
  return FpgaECP3::DdrSetRegN ( p, FPGA_ECP3_NAME );
}

int MainboardMini::SetDisplayTimming ( uint32_t w, uint32_t h, void* p )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "w=%d h=%d\n", w, h );

  if ( ( 1400 == w ) && ( 1050 == h ) )
  {
    FpgaRegSet ( FPGA_REG_HS_POL_CNT_REG,         0x8070 );
    FpgaRegSet ( FPGA_REG_VS_POL_CNT_REG,         0x8003 );
    FpgaRegSet ( FPGA_REG_HS_TOTAL_DOTCNT_REG,    0x0698 );
    FpgaRegSet ( FPGA_REG_VS_TOTAL_LINECNT_REG,   0x042a );
    FpgaRegSet ( FPGA_REG_HS2DE_STCNT_REG,        0x00f0 );
    FpgaRegSet ( FPGA_REG_HS2DE_ENDCNT_REG,       0x0668 );
    FpgaRegSet ( FPGA_REG_VS2DE_STCNT_REG,        0x000e );
    FpgaRegSet ( FPGA_REG_VS2DE_ENDCNT_REG,       0x0428 );

    /*  SET 4:3  */
    FpgaRegSet ( FPGA_REG_P3L_FLAG,               0x0000 );
  }

  #if 1
  else if ( ( 1920 == w ) && ( 1080 == h ) &&
            ( NULL != p ) && ( 0x3a == * ( int* ) p ) ) /* P3A */
  {
    FpgaRegSet ( FPGA_REG_HS_POL_CNT_REG,         0x802c );
    FpgaRegSet ( FPGA_REG_VS_POL_CNT_REG,         0x8005 );
    FpgaRegSet ( FPGA_REG_HS_TOTAL_DOTCNT_REG,    0x0898 );
    FpgaRegSet ( FPGA_REG_VS_TOTAL_LINECNT_REG,   0x0465 );
    FpgaRegSet ( FPGA_REG_HS2DE_STCNT_REG,        0x00c0 );
    FpgaRegSet ( FPGA_REG_HS2DE_ENDCNT_REG,       0x0840 );
    FpgaRegSet ( FPGA_REG_VS2DE_STCNT_REG,        0x0029 );
    FpgaRegSet ( FPGA_REG_VS2DE_ENDCNT_REG,       0x0461 );

    /*  SET 16:9  */
    FpgaRegSet ( FPGA_REG_P3L_FLAG,               0x0001 );
  }

  #endif
  else if ( ( 1920 == w ) && ( 1080 == h ) )
  {
    FpgaRegSet ( FPGA_REG_HS_POL_CNT_REG,         0x8014 );
    FpgaRegSet ( FPGA_REG_VS_POL_CNT_REG,         0x8005 );
    FpgaRegSet ( FPGA_REG_HS_TOTAL_DOTCNT_REG,    0x0898 );
    FpgaRegSet ( FPGA_REG_VS_TOTAL_LINECNT_REG,   0x0465 );
    FpgaRegSet ( FPGA_REG_HS2DE_STCNT_REG,        0x00a0 );
    FpgaRegSet ( FPGA_REG_HS2DE_ENDCNT_REG,       0x0820 );
    FpgaRegSet ( FPGA_REG_VS2DE_STCNT_REG,        0x0019 );
    FpgaRegSet ( FPGA_REG_VS2DE_ENDCNT_REG,       0x0451 );

    /*  SET 16:9  */
    FpgaRegSet ( FPGA_REG_P3L_FLAG,               0x0001 );
  }

  /*  show desktop */
  FpgaRegSet ( FPGA_REG_PIC_PRO_CTL,            0x4400 );

  /*  初始完fpga输出后 再启动dmd */
  PRINT_LOG ( LOG_LEVEL_NORMAL, "Wait 5S\n" );
  sleep ( 5 );

  FpgaRegSet ( FPGA_REG_DE_WIDTH,               w );
  FpgaRegSet ( FPGA_REG_DE_HEIGHT,              h );

  /*  初始完fpga输出后 再启动dmd */
  PRINT_LOG ( LOG_LEVEL_NORMAL, "SetDmdReSetPin\n" );
  SetDmdReSetPin ( false );

  return 0;
}

int MainboardMini::SetI2cPower ( std::string busname, bool onoff )
{

  return 0;
}

std::string MainboardMini::GetDmdI2cBus()
{
  return I2C_BUS_0_NAME;
}

bool MainboardMini::WriteBmpFileToFpga ( std::string filename, int addr )
{
  SemLocker semLocker ( GetFpgaSem() );
  return FpgaTestPic::WriteBmpFileToFpgaEcp3 ( filename, addr );
}

int MainboardMini::SetInputSignalRectAndShow ( int x, int y, int w, int h, uint32_t vd_hres, uint32_t vd_vres )
{
  #if 0
  PRINT_LOG ( LOG_LEVEL_NORMAL, "x=%d y=%d w=%d h=%d vd_vres=%d vd_vres=%d\n",
              x, y, w, h,	vd_hres, vd_vres );
  #endif

  if ( ( x > ( int ) vd_hres ) ||
       ( y > ( int ) vd_vres ) ||
       ( ( x + w ) > ( int ) vd_hres ) ||
       ( ( y + h ) > ( int ) vd_vres ) )
  {
    x = 0;
    y = 0;
    w = vd_hres;
    h = vd_vres;
  }

  SetInputSignalRect ( x, y, w, h );

  int width, height;
  GET_ENGPTR->GetEngineRes ( width, height );

  SetOuputSignalRect ( 0, 0, width, height );
  SetVsHsFactorAndShow ( x, y, w, h, 0, 0, width, height );

  return 0;
}

bool MainboardMini::CheckSignalChange ( uint32_t& w, uint32_t& h )
{
  static uint32_t s_hres = 0;
  static uint32_t s_vres = 0;

  if ( 0 != GetInputSignalResol ( w, h ) )
  {
    s_hres = 0;
    s_vres = 0;
    return false;
  }

  if ( ( s_hres == w ) && ( s_vres == h ) )
    return false;

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Resolution of input signal is changed: last resolution is %d x %d, and current resolution is %d x %d\n",
              s_hres, s_vres, w, h );

  s_hres = w;
  s_vres = h;

  return true;
}

int MainboardMini::CheckSignalAndShow( )
{
  uint32_t vd_hres = 0;
  uint32_t vd_vres = 0;

  if ( !CheckSignalChange ( vd_hres, vd_vres ) )
    return 0;

  #if 1

  if ( GetCutWinFlag() ) /* 按照裁剪方案处理 */
  {
    int x, y, w, h;
    GetInputSignalRect ( x, y, w, h );
    SetInputSignalRectAndShow ( x, y, w, h, vd_hres, vd_vres );
    return 0;
  }

  #endif

  SetInputSignalRect ( 0, 0, vd_hres, vd_vres );

  int width, height;
  GET_ENGPTR->GetEngineRes ( width, height );

  SetOuputSignalRect ( 0, 0, width, height );
  SetVsHsFactorAndShow ( 0, 0, vd_hres, vd_vres, 0, 0, width, height );

  return 0;
}

int MainboardMini::WriteEdid( )
{
  return 0;
}

int MainboardMini::GetInputSignalResol ( uint32_t& w, uint32_t& h )
{
  SemLocker semLocker ( GetFpgaSem() );

  fpga_reg_v_active_t fpga_reg_v_active;
  fpga_reg_v_active.data = FpgaGetReg ( FPGA_REG_V_ACTIVE );

  if ( 0 == fpga_reg_v_active.img_valid )
  {
    w = 0;
    h = 0;
    return -1;
  }

  w = FpgaGetReg ( FPGA_REG_VD_HRES );
  h = FpgaGetReg ( FPGA_REG_VD_VRES );

  return 0;
}

int MainboardMini::SetInputSignalRect ( int x, int y, int w, int h )
{
  SemLocker semLocker ( GetFpgaSem() );

  FpgaSetReg ( FPGA_REG_CLP_ST_X, x );
  FpgaSetReg ( FPGA_REG_CLP_ST_Y, y );
  FpgaSetReg ( FPGA_REG_CLP_ED_X, x + w );
  FpgaSetReg ( FPGA_REG_CLP_ED_Y, y + h );

  return 0;
}

int MainboardMini::GetInputSignalRect ( int& x, int& y, int& w, int& h )
{
  #if 0
  x = FpgaGetReg ( FPGA_REG_CLP_ST_X );
  y = FpgaGetReg ( FPGA_REG_CLP_ST_Y );
  w = FpgaGetReg ( FPGA_REG_CLP_ED_X );
  w = w - x;
  h = FpgaGetReg ( FPGA_REG_CLP_ED_Y );
  h = h - y;
  #endif

  int temp = 0;
  XmlConfig::GetParam ( "SignalRect", "x", x, temp );
  XmlConfig::GetParam ( "SignalRect", "y", y, temp );
  XmlConfig::GetParam ( "SignalRect", "w", w, temp );
  XmlConfig::GetParam ( "SignalRect", "h", h, temp );
  return 0;
}

int MainboardMini::SetOuputSignalRect ( int x, int y, int w, int h )
{
  //PRINT_LOG ( LOG_LEVEL_NORMAL, "x=%d y=%d w=%d h=%d \n", x, y, w, h );
  SemLocker semLocker ( GetFpgaSem() );

  FpgaSetReg ( FPGA_REG_WIN_ST_X, x );
  FpgaSetReg ( FPGA_REG_WIN_ST_Y, y );
  FpgaSetReg ( FPGA_REG_WIN_ED_X, x + w );
  FpgaSetReg ( FPGA_REG_WIN_ED_Y, y + h );

  return 0;
}

int MainboardMini::GetOuputSignalRect ( int& x, int& y, int& w, int& h )
{
  SemLocker semLocker ( GetFpgaSem() );

  x = FpgaGetReg ( FPGA_REG_WIN_ST_X );
  y = FpgaGetReg ( FPGA_REG_WIN_ST_Y );
  w = FpgaGetReg ( FPGA_REG_WIN_ED_X );
  w = w - x;
  h = FpgaGetReg ( FPGA_REG_WIN_ED_Y );
  h = h - y;
  return 0;
}

int MainboardMini::SetVsHsFactorAndShow ( int ix, int iy, int iw, int ih,
    int ox, int oy, int ow, int oh )
{
  SemLocker semLocker ( GetFpgaSem() );

  fpga_reg_pic_pro_ctl_t fpga_reg_pic_pro_ctl;

  uint16_t hsfactor = ( uint16_t ) ( iw * 2048.0 / ow );
  uint16_t vsfactor = ( uint16_t ) ( ih * 2048.0 / oh );
  //PRINT_LOG ( LOG_LEVEL_NORMAL, "vsfactor=%d hsfactor=%d\n", vsfactor, hsfactor );

  FpgaSetReg ( FPGA_REG_VSFACTOR, vsfactor );
  FpgaSetReg ( FPGA_REG_HSFACTOR, hsfactor );

  fpga_reg_win_flush_t fpga_reg_win_flush;

  for ( int i = 0; i < 3; ++i )
  {
    usleep ( 1000 );
    fpga_reg_win_flush.data = FpgaGetReg ( FPGA_REG_WIN_FLUSH );
    fpga_reg_win_flush.update_cube_win = 0;
    FpgaSetReg ( FPGA_REG_WIN_FLUSH, fpga_reg_win_flush.data );
    usleep ( 1000 );
    fpga_reg_win_flush.update_cube_win = 1;
    FpgaSetReg ( FPGA_REG_WIN_FLUSH, fpga_reg_win_flush.data );
    usleep ( 1000 );
    fpga_reg_win_flush.update_cube_win = 0;
    FpgaSetReg ( FPGA_REG_WIN_FLUSH, fpga_reg_win_flush.data );
  }

  fpga_reg_pic_pro_ctl.data = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
  fpga_reg_pic_pro_ctl.scaler = 0;
  FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, fpga_reg_pic_pro_ctl.data );


  return 0;
}

