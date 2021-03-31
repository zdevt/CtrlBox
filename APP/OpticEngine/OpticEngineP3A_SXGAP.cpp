/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineP3A_SXGAP.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/30/2014 02:43:28 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <sstream>
#include <string.h>
#include <string>
#include <map>

#include "OpticEngineP3A_SXGAP.h"
#include "FpgaDev.h"
#include "MainboardInterface.h"

uint8_t OpticEngineP3A_SXGAPEDID[] =
{
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x22, 0x6B, 0x00, 0x00, 0xC1, 0x75, 0x1A, 0x78,
  0x20, 0x19, 0x01, 0x03, 0x80, 0x00, 0x00, 0x78, 0x0A, 0x32, 0xEC, 0xA0, 0x55, 0x4A, 0x9B, 0x26,
  0x10, 0x48, 0x4F, 0xFF, 0xFF, 0x00, 0xD1, 0xC0, 0x81, 0x80, 0x61, 0x40, 0x61, 0x4F, 0x61, 0x59,
  0xA9, 0x40, 0x45, 0x40, 0x31, 0x59, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,
  0x45, 0x00, 0x7C, 0x22, 0x11, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x32, 0x30, 0x30,
  0x39, 0x30, 0x39, 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x31, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x44,
  0x4C, 0x50, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x02, 0x3A, 0x80, 0x18,
  0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x7C, 0x22, 0x11, 0x00, 0x00, 0x1E, 0x00, 0x53,
};

std::shared_ptr<OpticEngine> OpticEngineP3A_SXGAP::GetObj ( std::string engineName )
{
  return std::make_shared<OpticEngineP3A_SXGAP> ( engineName );
}

OpticEngineP3A_SXGAP::OpticEngineP3A_SXGAP ( std::string engineName )
  : OpticEngineP3A ( engineName )
{
}

OpticEngineP3A_SXGAP::~OpticEngineP3A_SXGAP()
{
}

uint32_t OpticEngineP3A_SXGAP::GetEngineRes ( int& width, int& height )
{
  width = 1400;
  height = 1050;
  return OPTIC_ENGINE_RES_SXGA;
}

int OpticEngineP3A_SXGAP::WriteLogoAndTestPic()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_SXGAP.bmp", FPGA_PIC_SXGA );
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_SXGAP.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineP3A_SXGAP::WriteLogo()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_SXGAP.bmp", FPGA_PIC_SXGA );
  return 0;
}

int OpticEngineP3A_SXGAP::WriteTestPic()
{
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_SXGAP.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineP3A_SXGAP::SetPowerState ( uint8_t state )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "%d\n", state );

  if ( state )
  {
    /*  1.  */
    SetFpgaPixel();
    /*  set saved dac */
    sleep ( 10 ); /*  wait engine ready */
    WriteLogoAndTestPic();
    sleep ( 5 ); /*  wait engine ready */

    dac_t dac;
    GetLedDacRedBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacRed ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );

    GetLedDacGreenBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacGreen ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );

    GetLedDacBlueBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacBlue ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );

    uint8_t value;

    sleep ( 5 );
    sleep ( 4 );

    GetBcMode ( value );
    SetBcMode ( value );

    sleep ( 1 );
    GetDutycycle ( &value );
    SetDutycycle ( value );

    uint8_t temp[128] = { 0 };
    #if 0
    GetWpcTarget ( temp );  /*  must set wpctarget first */
    SetWpcTarget ( temp );

    GetWpcMode ( value );
    SetWpcMode ( value );

    #if 1
    /*  Set Saved CCA */
    temp[0] = 0xff ;
    GetCCATarget ( temp );
    SetCCATarget ( temp );
    #endif

    int imode = 0;
    XmlConfig::GetParam ( "OpticEngine", "CcAEnable", imode, 0 );
    ddp442x_alg_enable_t ddp442x_alg_enable;

    GetAlgorithmEnable ( ddp442x_alg_enable.data );
    ddp442x_alg_enable.cca = imode ? 1 : 0;
    usleep ( 250 * 1000 );
    SetAlgorithmEnable ( ddp442x_alg_enable.data );

    GetAlgorithmEnable ( ddp442x_alg_enable.data );
    ddp442x_alg_enable.cca = imode ? 1 : 0;
    usleep ( 250 * 1000 );
    SetAlgorithmEnable ( ddp442x_alg_enable.data );
    #endif

    /*  Set HSG */
    GetHsgAdjustment ( temp );
    SetHsgAdjustment ( temp );

    FpgaImageSwitch::SetDeskTopIndex ( FpgaImageSwitch::GetDeskTopIndex() );

    uint8_t mode = 0;
    GetProjMode ( mode );
    SetProjMode ( mode );

    sleep ( 2 );
    uint8_t source = 0;
    SetChannelSource ( source );
    PRINT_LOG ( LOG_LEVEL_NORMAL, "SetChannelSource %d\n", source );
  }
  else
  {
    /*  先打黑 */
    FpgaSetReg ( FPGA_DESKTOP_REG, 6 );
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Set Fpga Black ok!\n" );
  }

  int istate = state;
  XmlConfig::SetParam ( "OpticEngine", "PowerState", istate );
  return 0;
}

int OpticEngineP3A_SXGAP::GetPowerState ( uint8_t& state )
{
  int istate = 0;
  int temp = 1;
  #if defined(__arm__)
  XmlConfig::GetParam ( "OpticEngine", "PowerState", istate, temp );
  #else
  XmlConfig::GetParam ( "OpticEngine", "PowerState", istate, temp );
  #endif
  state = istate;
  return 0;
}

int OpticEngineP3A_SXGAP::SetFpgaPixel( )
{
  int w = 0;
  int h = 0;
  GetEngineRes ( w, h );

  GET_MBPTR->SetDisplayTimming ( w, h, NULL );

  return 0;
}

uint8_t* OpticEngineP3A_SXGAP::GetEdid ( )
{
  return OpticEngineP3A_SXGAPEDID;
}

