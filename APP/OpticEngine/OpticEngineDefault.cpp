/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineDefault.cpp
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

#include "OpticEngineDefault.h"
#include "FpgaDev.h"
#include "MainboardInterface.h"

uint8_t OpticEngineDefaultEDID[] =
{
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x22, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x24, 0x1A, 0x01, 0x03, 0x80, 0x00, 0x00, 0x78, 0x0A, 0x32, 0xEC, 0xA0, 0x55, 0x4A, 0x9B, 0x26,
  0x10, 0x48, 0x4F, 0xFF, 0xFF, 0x80, 0x90, 0x40, 0x81, 0x80, 0x61, 0x40, 0x61, 0x4F, 0x61, 0x59,
  0xA9, 0x40, 0x45, 0x40, 0x31, 0x59, 0x30, 0x2A, 0x78, 0x20, 0x51, 0x1A, 0x10, 0x40, 0x30, 0x70,
  0x13, 0x00, 0x7C, 0x22, 0x11, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x32, 0x30, 0x31,
  0x36, 0x30, 0x39, 0x30, 0x33, 0x30, 0x30, 0x30, 0x30, 0x31, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x44,
  0x4C, 0x50, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x10,
  0x00, 0x1A, 0x10, 0x40, 0x30, 0x70, 0x13, 0x00, 0x7C, 0x22, 0x11, 0x00, 0x00, 0x18, 0x00, 0x3E,
};

std::shared_ptr<OpticEngine> OpticEngineDefault::GetObj ( std::string engineName )
{
  return std::make_shared<OpticEngineDefault> ( engineName );
}

OpticEngineDefault::OpticEngineDefault ( std::string engineName )
  : OpticEngine ( engineName )
{
}

OpticEngineDefault::~OpticEngineDefault()
{
}

uint32_t OpticEngineDefault::GetEngineRes ( int& width, int& height )
{
  width = 1400;
  height = 1050;
  return OPTIC_ENGINE_RES_SXGA;
}

uint32_t OpticEngineDefault::GetEngineType()
{
  return OPTIC_ENGINE_TYPE_LED;
}

uint32_t OpticEngineDefault::GetEnginePlatform()
{
  return OPTIC_ENGINE_PLATFORM_DDP3021;
}

uint32_t OpticEngineDefault::GetEngine2Dor3D()
{
  return OPTIC_ENGINE_2D;
}

int OpticEngineDefault::WriteLogoAndTestPic()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_SXGAP.bmp", FPGA_PIC_SXGA );
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_SXGAP.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineDefault::WriteLogo()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_SXGAP.bmp", FPGA_PIC_SXGA );
  return 0;
}

int OpticEngineDefault::WriteTestPic()
{
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_SXGAP.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineDefault::SetPowerState ( uint8_t state )
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
    #if 0
    GetLedDacRedBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacRed ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );

    GetLedDacGreenBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacGreen ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );

    GetLedDacBlueBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacBlue ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );
    #else
    GetLedDacGreenBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacGreen ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );

    GetLedDacRedBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacRed ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );

    GetLedDacBlueBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacBlue ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 100 * 1000 );
    #endif

    FpgaImageSwitch::SetDeskTopIndex ( FpgaImageSwitch::GetDeskTopIndex() );

    uint8_t mode = 0;
    GetProjMode ( mode );
    SetProjMode ( mode );
  }

  int istate = state;
  XmlConfig::SetParam ( "OpticEngine", "PowerState", istate );

  return 0;
}

int OpticEngineDefault::GetPowerState ( uint8_t& state )
{
  int istate = 0;
  XmlConfig::GetParam ( "OpticEngine", "PowerState", istate, 0 );
  state = istate;

  return 0;
}

int OpticEngineDefault::SetFpgaPixel( )
{
  int w = 0;
  int h = 0;
  GetEngineRes ( w, h );

  GET_MBPTR->SetDisplayTimming ( w, h, NULL );

  return 0;
}

int OpticEngineDefault::SetBcMode ( uint8_t mode )
{
  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "SysTemMode", imode );
  return DmdDdp3021Interface::SetBcMode ( mode );
}

int OpticEngineDefault::GetBcMode ( uint8_t& mode )
{
  int imode = 0;
  XmlConfig::GetParam ( "OpticEngine", "SysTemMode", imode, 0 );
  mode = imode;
  return 0;
}

int OpticEngineDefault::SetDmdGamma ( uint8_t gammaType )
{
  int igammaType = gammaType ;
  XmlConfig::SetParam ( "OpticEngine", "DmdGamma", igammaType );
  return DmdDdp3021Interface::SetDmdGamma ( gammaType );
}

int OpticEngineDefault::GetDmdGamma ( uint8_t& gammaType )
{
  int igammaType = 0;
  XmlConfig::GetParam ( "OpticEngine", "DmdGamma", igammaType, 0 );
  gammaType = igammaType;
  return 0;
}

int OpticEngineDefault::SetProjMode ( uint8_t mode )
{
  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "ProjMode", imode );
  return DmdDdp3021Interface::SetProjMode ( mode );
}

int OpticEngineDefault::GetProjMode ( uint8_t& mode )
{
  int imode = 0;
  XmlConfig::GetParam ( "OpticEngine", "ProjMode", imode, 0 );
  mode = imode;
  return 0;
}

int OpticEngineDefault::SetColorOffset ( uint16_t r, uint16_t g, uint16_t b )
{
  DmdDdp3021Interface::SetColorOffset ( r, g, b );

  XmlConfig::SetParam ( "OpticEngine", "ColorOffsetR", r );
  XmlConfig::SetParam ( "OpticEngine", "ColorOffsetG", g );
  XmlConfig::SetParam ( "OpticEngine", "ColorOffsetB", b );

  return 0;
}

int OpticEngineDefault::GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetB", b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineDefault::SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b )
{
  DmdDdp3021Interface::SetColorBrightness ( r, g, b );

  XmlConfig::SetParam ( "OpticEngine", "ColorBrightnessR", r );
  XmlConfig::SetParam ( "OpticEngine", "ColorBrightnessG", g );
  XmlConfig::SetParam ( "OpticEngine", "ColorBrightnessB", b );

  return 0;
}

int OpticEngineDefault::GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessB", b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineDefault::SetColorContrast ( uint16_t r, uint16_t g, uint16_t b )
{
  DmdDdp3021Interface::SetColorContrast ( r, g, b );

  XmlConfig::SetParam ( "OpticEngine", "ColorContrastR", r );
  XmlConfig::SetParam ( "OpticEngine", "ColorContrastG", g );
  XmlConfig::SetParam ( "OpticEngine", "ColorContrastB", b );

  return 0;
}

int OpticEngineDefault::GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastB", b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineDefault::SetDutycycle ( uint8_t dc )
{
  int idc = dc;
  XmlConfig::SetParam ( "OpticEngine", "Dutycycle", idc );
  return DmdDdp3021Interface::SetDutycycle ( dc );
}

int OpticEngineDefault::GetDutycycle ( uint8_t* dc )
{
  int idc;
  XmlConfig::GetParam ( "OpticEngine", "Dutycycle", idc, ( int32_t ) 0 );
  *dc = idc;
  return 0;
}

int OpticEngineDefault::GetDutycycleValue ( void* p )
{
  /* 暂未实现 需查资料 */
  return 0;
}

int OpticEngineDefault::SetHsgAdjustment ( void* hsg )
{
  uint8_t* pTemp = reinterpret_cast<uint8_t*> ( hsg );
  XmlConfig::SetParamArray ( "OpticEngine", "HsgAdjustment", pTemp, 42 );
  return DmdDdp3021Interface::SetHsg ( hsg );
}

int OpticEngineDefault::GetHsgAdjustment ( void* hsg )
{
  uint8_t* pTemp = reinterpret_cast<uint8_t*> ( hsg );
  XmlConfig::GetParamArray ( "OpticEngine", "HsgAdjustment", pTemp, NULL, 42 );
  return 0;
}

int OpticEngineDefault::SetLedDacRed ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  DmdDdp3021Interface::SetRedDac ( dac->r, dac->g, dac->b );
  usleep ( 10 * 1000 );
  return 0;
}

int OpticEngineDefault::SetLedDacRedBasic ( void* p )
{
  SetLedDacRed ( p );
  dac_t* dac = reinterpret_cast<dac_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacRedR", dac->r );
  XmlConfig::SetParam ( "OpticEngine", "LedDacRedG", dac->g );
  XmlConfig::SetParam ( "OpticEngine", "LedDacRedB", dac->b );

  return 0;
}

int OpticEngineDefault::GetLedDacRedBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedR", dac->r, ( uint16_t ) 1023 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedG", dac->g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedB", dac->b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineDefault::GetLedDacRed ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  DmdDdp3021Interface::GetRedDac ( dac->r, dac->g, dac->b );
  return 0;
}

int OpticEngineDefault::SetLedDacGreen ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  DmdDdp3021Interface::SetGreenDac ( dac->r, dac->g, dac->b );
  usleep ( 10 * 1000 );
  return 0;
}

int OpticEngineDefault::SetLedDacGreenBasic ( void* p )
{
  SetLedDacGreen ( p );
  dac_t* dac = reinterpret_cast<dac_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenR", dac->r );
  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenG", dac->g );
  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenB", dac->b );

  return 0;
}

int OpticEngineDefault::GetLedDacGreenBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenR", dac->r, ( uint16_t ) 1023 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenG", dac->g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenB", dac->b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineDefault::GetLedDacGreen ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  DmdDdp3021Interface::GetGreenDac ( dac->r, dac->g, dac->b );
  return 0;
}

int OpticEngineDefault::SetLedDacBlue ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  DmdDdp3021Interface::SetBlueDac ( dac->r, dac->g, dac->b );
  usleep ( 10 * 1000 );
  return 0;
}

int OpticEngineDefault::SetLedDacBlueBasic ( void* p )
{
  SetLedDacBlue ( p );
  dac_t* dac = reinterpret_cast<dac_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueR", dac->r );
  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueG", dac->g );
  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueB", dac->b );

  return 0;
}

int OpticEngineDefault::GetLedDacBlueBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueR", dac->r, ( uint16_t ) 1023 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueG", dac->g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueB", dac->b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineDefault::GetLedDacBlue ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  DmdDdp3021Interface::GetBlueDac ( dac->r, dac->g, dac->b );
  return 0;
}

int OpticEngineDefault::LumCompStart()
{
  return 0;
}

int OpticEngineDefault::SetDspEffect ( uint32_t dspEffect )
{
  uint16_t val = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
  fpga_reg_pic_pro_ctl_t* pval = reinterpret_cast<fpga_reg_pic_pro_ctl_t*> ( &val );

  if ( 1 == dspEffect )
    pval->frc_en = 0;
  else
    pval->frc_en = 1;

  FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, val );

  return 0;
}


int OpticEngineDefault::GetMaxDac ( void* p )
{
  uint16_t* pdac = reinterpret_cast<uint16_t* > ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedR", 		pdac[0], ( uint16_t ) 1023 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenG", 	pdac[1], ( uint16_t ) 1023 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueB", 	pdac[2], ( uint16_t ) 1023 );
  return 1023;
}

int OpticEngineDefault::GetDmdTemp ( int& temp )
{
  return 0;
}

int OpticEngineDefault::GetLedTemp ( int* ptemp )
{
  return 0;
}

int OpticEngineDefault::GetLedStatus ( void* p )
{
  return 0;
}

int OpticEngineDefault::SetWpcMode ( uint8_t mode )
{
  return 0;
}

int OpticEngineDefault::GetWpcMode ( uint8_t& mode )
{
  return 0;
}

int OpticEngineDefault::SetWpcTarget ( uint8_t* pTarget )
{
  return 0;
}

int OpticEngineDefault::GetWpcTarget ( uint8_t* pTarget )
{
  return 0;
}

int OpticEngineDefault::SetAlgorithmEnable ( uint8_t value )
{
  return 0;
}

int OpticEngineDefault::GetAlgorithmEnable ( uint8_t& value )
{
  return 0;
}

int OpticEngineDefault::SetCCATarget ( uint8_t* pTarget )
{
  return 0;
}

int OpticEngineDefault::GetCCATarget ( uint8_t* pTarget )
{
  return 0;
}

int OpticEngineDefault::SetDmdRegVal ( uint8_t subaddr, uint32_t datalen, uint8_t* data )
{
  return 0;
}

int OpticEngineDefault::GetDmdRegVal ( uint8_t subaddr, uint32_t paramlen, uint8_t* param, uint32_t datalen, uint8_t* data )
{
  return 0;
}

bool OpticEngineDefault::SetFanPwm ( uint8_t fanid, uint8_t pwm )
{
  return false;
}

bool OpticEngineDefault::GetFanPwm ( uint8_t fanid, uint8_t& pwm )
{
  return false;
}

bool OpticEngineDefault::SetFanSpeed ( uint8_t fanid, uint16_t speed )
{
  return false;
}

bool OpticEngineDefault::GetFanSpeed ( uint8_t fanid, uint16_t& speed )
{
  return false;
}

uint8_t* OpticEngineDefault::GetEdid ( )
{
  return OpticEngineDefaultEDID;
}

int OpticEngineDefault::SetOverLap ( uint16_t overlap )
{
  return 0;
}

int OpticEngineDefault::GetOverLap ( uint16_t& overlap )
{
  return 0;
}

int OpticEngineDefault::GetFirmwareVersion ( uint32_t& version )
{
  return 0;
}
