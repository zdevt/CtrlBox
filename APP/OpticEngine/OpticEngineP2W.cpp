
/*
 * ==============================================================================
 *
 *       FileName:  OpticEngineP2W.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017-11-18 09:43:06
 *  Last Modified:  2017-11-22 13:28:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt ()
 *   Organization:
 *
 * ===============================================================================
 */

#include <sstream>
#include <string.h>
#include <string>
#include <map>

#include "OpticEngineP2W.h"
#include "FpgaDev.h"
#include "MainboardInterface.h"

uint8_t OpticEngineP2WEDID[] =
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

std::shared_ptr<OpticEngine> OpticEngineP2W::GetObj ( std::string engineName )
{
  return std::make_shared<OpticEngineP2W> ( engineName );
}

OpticEngineP2W::OpticEngineP2W ( std::string engineName )
  : OpticEngineThin ( engineName )
{
}

OpticEngineP2W::~OpticEngineP2W()
{
}

uint32_t OpticEngineP2W::GetEngineRes ( int& width, int& height )
{
  width = 1920;
  height = 1080;
  return OPTIC_ENGINE_RES_1080P;
}
uint32_t OpticEngineP2W::GetEngineType()
{
  return OPTIC_ENGINE_TYPE_LED;
}

uint32_t OpticEngineP2W::GetEnginePlatform()
{
  return OPTIC_ENGINE_PLATFORM_DDP442X;
}

uint32_t OpticEngineP2W::GetEngine2Dor3D()
{
  return OPTIC_ENGINE_2D;
}

int OpticEngineP2W::WriteLogoAndTestPic()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_1080P.bmp", FPGA_PIC_SXGA );
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_1080P.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineP2W::WriteLogo()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_1080P.bmp", FPGA_PIC_SXGA );
  return 0;
}

int OpticEngineP2W::WriteTestPic()
{
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_1080P.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineP2W::SetPowerState ( uint8_t state )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "%d\n", state );

  if ( state )
  {
    uint8_t val = 0;
    DmdDdp442XInterface::SetSipP2wOpenMethod ( val );
    DmdDdp442XInterface::SetSipP2wOpen ( state );
    /*  1.  */
    SetFpgaPixel();
    /*  set saved dac */
    sleep ( 10 ); /*  wait engine ready */
    WriteLogoAndTestPic();
    sleep ( 5 ); /*  wait engine ready */

    //dac_t dac;
    //GetLedDacRedBasic ( reinterpret_cast<void*> ( &dac ) );
    //SetLedDacRed ( reinterpret_cast<void*> ( &dac ) );
    //usleep ( 100 * 1000 );

    //GetLedDacGreenBasic ( reinterpret_cast<void*> ( &dac ) );
    //SetLedDacGreen ( reinterpret_cast<void*> ( &dac ) );
    //usleep ( 100 * 1000 );

    //GetLedDacBlueBasic ( reinterpret_cast<void*> ( &dac ) );
    //SetLedDacBlue ( reinterpret_cast<void*> ( &dac ) );
    //usleep ( 100 * 1000 );

    //uint8_t value;

    //sleep ( 5 );
    //sleep ( 4 );

    //GetBcMode ( value );
    //SetBcMode ( value );

    //sleep ( 1 );
    //GetDutycycle ( &value );
    //SetDutycycle ( value );

    uint8_t temp[128] = { 0 };
    #if 0
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
    //SetProjMode ( mode );

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

int OpticEngineP2W::GetPowerState ( uint8_t& state )
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

int OpticEngineP2W::SetFpgaPixel( )
{
  int w = 0;
  int h = 0;
  GetEngineRes ( w, h );
  int flag = 0x3a;

  GET_MBPTR->SetDisplayTimming ( w, h, ( void* ) &flag );

  return 0;
}

int OpticEngineP2W::SetBcMode ( uint8_t mode )
{
  DmdDdp442XInterface::SetSystemMode ( mode );

  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "SysTemMode", imode );

  return 0;
}

int OpticEngineP2W::GetBcMode ( uint8_t& mode )
{
  int imode = 0;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "SysTemMode", imode, temp );
  mode = imode;
  return 0;
}

int OpticEngineP2W::SetDmdGamma ( uint8_t gammaType )
{
  DmdDdp442XInterface::SetGammaTable ( gammaType );

  int igammaType = gammaType ;
  XmlConfig::SetParam ( "OpticEngine", "DmdGamma", igammaType );
  return 0;
}

int OpticEngineP2W::GetDmdGamma ( uint8_t& gammaType )
{
  int igammaType = 0;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "DmdGamma", igammaType, temp );
  gammaType = igammaType;
  return 0;
}

int OpticEngineP2W::SetProjMode ( uint8_t mode )
{
  DmdDdp442XInterface::SetImageFlip ( mode );

  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "ProjMode", imode );
  return 0;
}

int OpticEngineP2W::GetProjMode ( uint8_t& mode )
{
  int imode = 0;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "ProjMode", imode, temp );
  mode = imode;
  return 0;
}

int OpticEngineP2W::SetColorOffset ( uint16_t r, uint16_t g, uint16_t b )
{
  color_offset_cfg_t color_offset_cfg;
  color_offset_cfg.r = r;
  color_offset_cfg.g = g;
  color_offset_cfg.b = b;

  DmdDdp442XInterface::SetColorOffset ( reinterpret_cast<uint8_t*> ( &color_offset_cfg ) );

  XmlConfig::SetParam ( "OpticEngine", "ColorOffsetR", r );
  XmlConfig::SetParam ( "OpticEngine", "ColorOffsetG", g );
  XmlConfig::SetParam ( "OpticEngine", "ColorOffsetB", b );

  return 0;
}

int OpticEngineP2W::GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetB", b, ( uint16_t ) 0 );

  return 0;
}

int OpticEngineP2W::SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b )
{
  brightness_cfg_t brightness_cfg;
  brightness_cfg.r = r;
  brightness_cfg.g = g;
  brightness_cfg.b = b;

  DmdDdp442XInterface::SetColorContrast ( reinterpret_cast<uint8_t*> ( &brightness_cfg ) );

  XmlConfig::SetParam ( "OpticEngine", "ColorBrightnessR", r );
  XmlConfig::SetParam ( "OpticEngine", "ColorBrightnessG", g );
  XmlConfig::SetParam ( "OpticEngine", "ColorBrightnessB", b );

  return 0;
}

int OpticEngineP2W::GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessB", b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineP2W::SetColorContrast ( uint16_t r, uint16_t g, uint16_t b )
{
  contrast_cfg_t contrast_cfg;
  contrast_cfg.r = r;
  contrast_cfg.g = g;
  contrast_cfg.b = b;

  DmdDdp442XInterface::SetColorContrast ( reinterpret_cast<uint8_t*> ( &contrast_cfg ) );

  XmlConfig::SetParam ( "OpticEngine", "ColorContrastR", r );
  XmlConfig::SetParam ( "OpticEngine", "ColorContrastG", g );
  XmlConfig::SetParam ( "OpticEngine", "ColorContrastB", b );
  return 0;
}

int OpticEngineP2W::GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastB", b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineP2W::SetDutycycle ( uint8_t dc )
{
  int idc = dc;
  XmlConfig::SetParam ( "OpticEngine", "Dutycycle", idc );
  DmdDdp442XInterface::SetDutycycle ( dc );
  return 0;
}

int OpticEngineP2W::GetDutycycle ( uint8_t* dc )
{
  int idc;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "Dutycycle", idc, temp );
  *dc = ( uint8_t ) idc;
  //DmdDdp442XInterface::GetDutycycle ( dc );
  return 0;
}

int OpticEngineP2W::GetDutycycleValue ( void* p )
{
  DmdDdp442XInterface::GetDutycycleValue ( reinterpret_cast<uint8_t*> ( p ) );
  return 0;
}

int OpticEngineP2W::SetLedDacRed ( void* p )
{
  /*  red yellow */
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac_cfg_t dac_cfg;
  memset ( reinterpret_cast<void*> ( &dac_cfg ), 0, sizeof ( dac_cfg ) );

  dac_cfg.redDac = dac->r;
  dac_cfg.greenDac = dac->g;
  dac_cfg.blueDac = dac->b;

  dac_cfg.yellowDac = dac->r;

  DmdDdp442XInterface::SetRedLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineP2W::SetLedDacRedBasic ( void* p )
{
  SetLedDacRed ( p );
  dac_cfg_t* pdac_cfg = reinterpret_cast<dac_cfg_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacRedR", pdac_cfg->redDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacRedG", pdac_cfg->greenDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacRedB", pdac_cfg->blueDac );

  return 0;
}

int OpticEngineP2W::GetLedDacRedBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedR", dac->r, ( uint16_t ) 4095 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedG", dac->g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedB", dac->b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineP2W::GetLedDacRed ( void* p )
{
  dac_cfg_t dac_cfg;
  DmdDdp442XInterface::GetRedLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac->r = dac_cfg.redDac;
  dac->g = dac_cfg.greenDac;
  dac->b = dac_cfg.blueDac;

  unsigned int times = 3;

  while ( !dac->IsValid() && ( --times ) )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Invalid red DAC value: %d %d %d\n", dac->r, dac->g, dac->b );
    DmdDdp442XInterface::GetRedLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );
    dac->r = dac_cfg.redDac;
    dac->g = dac_cfg.greenDac;
    dac->b = dac_cfg.blueDac;
  }

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineP2W::SetLedDacGreen ( void* p )
{
  /*  green yellow cyan */
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac_cfg_t dac_cfg;
  memset ( reinterpret_cast<void*> ( &dac_cfg ), 0, sizeof ( dac_cfg ) );

  dac_cfg.redDac = dac->r;
  dac_cfg.greenDac = dac->g;
  dac_cfg.blueDac = dac->b;

  dac_cfg.yellowDac = dac->g;
  dac_cfg.cyanDac = dac->g;

  DmdDdp442XInterface::SetGreenLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  usleep ( 30 * 1000 );

  return 0;
}

int OpticEngineP2W::SetLedDacGreenBasic ( void* p )
{
  SetLedDacGreen ( p );

  dac_cfg_t* pdac_cfg = reinterpret_cast<dac_cfg_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenR", pdac_cfg->redDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenG", pdac_cfg->greenDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenB", pdac_cfg->blueDac );

  return 0;
}

int OpticEngineP2W::GetLedDacGreenBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenR", dac->r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenG", dac->g, ( uint16_t ) 4095 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenB", dac->b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineP2W::GetLedDacGreen ( void* p )
{
  dac_cfg_t dac_cfg;
  DmdDdp442XInterface::GetGreenLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac->r = dac_cfg.redDac;
  dac->g = dac_cfg.greenDac;
  dac->b = dac_cfg.blueDac;

  unsigned int times = 3;

  while ( !dac->IsValid() && ( --times ) )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Invalid green DAC value: %d %d %d\n", dac->r, dac->g, dac->b );
    DmdDdp442XInterface::GetGreenLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );
    dac->r = dac_cfg.redDac;
    dac->g = dac_cfg.greenDac;
    dac->b = dac_cfg.blueDac;
  }

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineP2W::SetLedDacBlue ( void* p )
{
  /*  blue cyan */
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac_cfg_t dac_cfg;
  memset ( reinterpret_cast<void*> ( &dac_cfg ), 0, sizeof ( dac_cfg ) );

  dac_cfg.redDac = dac->r;
  dac_cfg.greenDac = dac->g;
  dac_cfg.blueDac = dac->b;

  dac_cfg.cyanDac = dac->b;

  DmdDdp442XInterface::SetBlueLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineP2W::SetLedDacBlueBasic ( void* p )
{
  SetLedDacBlue ( p );
  dac_cfg_t* pdac_cfg = reinterpret_cast<dac_cfg_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueR", pdac_cfg->redDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueG", pdac_cfg->greenDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueB", pdac_cfg->blueDac );

  return 0;
}

int OpticEngineP2W::GetLedDacBlueBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueR", dac->r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueG", dac->g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueB", dac->b, ( uint16_t ) 4095 );
  return 0;
}

int OpticEngineP2W::GetLedDacBlue ( void* p )
{
  dac_cfg_t dac_cfg;
  DmdDdp442XInterface::GetBlueLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac->r = dac_cfg.redDac;
  dac->g = dac_cfg.greenDac;
  dac->b = dac_cfg.blueDac;

  unsigned int times = 3;

  while ( !dac->IsValid() && ( --times ) )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Invalid blue DAC value: %d %d %d\n", dac->r, dac->g, dac->b );
    DmdDdp442XInterface::GetBlueLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );
    dac->r = dac_cfg.redDac;
    dac->g = dac_cfg.greenDac;
    dac->b = dac_cfg.blueDac;
  }

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineP2W::LumCompStart()
{
  return 0;
}

int OpticEngineP2W::SetDspEffect ( uint32_t dspEffect )
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

int OpticEngineP2W::GetMaxDac ( void* p )
{
  uint16_t* pdac = reinterpret_cast<uint16_t* > ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedR", 		pdac[0], ( uint16_t ) 4095 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenG", 	pdac[1], ( uint16_t ) 4095 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueB", 	pdac[2], ( uint16_t ) 4095 );

  return 4095;
}

int OpticEngineP2W::GetDmdTemp ( int& temp )
{
  int16_t t;
  DmdDdp442XInterface::GetDmdTemp ( &t );
  temp = t;
  return 0;
}

int OpticEngineP2W::GetLedTemp ( int* ptemp )
{
  DmdDdp442XInterface::GetLedTempThin ( 0, & ( ptemp[0] ) );
  DmdDdp442XInterface::GetLedTempThin ( 1, & ( ptemp[1] ) );
  DmdDdp442XInterface::GetLedTempThin ( 2, & ( ptemp[2] ) );
  return 0;
}

int OpticEngineP2W::GetLedStatus ( void* p )
{
  DmdDdp442XInterface::GetLedTempVA ( reinterpret_cast<uint8_t*> ( p ) );
  return 0;
}

int OpticEngineP2W::SetDmdRegVal ( uint8_t subaddr, uint32_t datalen, uint8_t* data )
{
  return DmdDdp442XInterface::SetCommand ( subaddr, data, datalen );
}

int OpticEngineP2W::GetDmdRegVal ( uint8_t subaddr, uint32_t paramlen, uint8_t* param, uint32_t datalen, uint8_t* data )
{
  return DmdDdp442XInterface::GetCommand ( subaddr, param, paramlen, data, datalen );
}

int OpticEngineP2W::SetWpcMode ( uint8_t mode )
{
  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "WpcMode", imode );
  return DmdDdp442XInterface::SetWpcMode ( &mode );
}

int OpticEngineP2W::GetWpcMode ( uint8_t& mode )
{
  int imode = 0;
  XmlConfig::GetParam ( "OpticEngine", "WpcMode", imode, 0 );
  mode = imode;
  return 0;
}

int OpticEngineP2W::SetWpcTarget ( uint8_t* pTarget )
{
  XmlConfig::SetParamArray ( "OpticEngine", "WpcTarget", pTarget, 12 );
  return DmdDdp442XInterface::SetWpcTarget ( pTarget );
}

int OpticEngineP2W::GetWpcTarget ( uint8_t* pTarget )
{
  XmlConfig::GetParamArray ( "OpticEngine", "WpcTarget", pTarget, NULL, 12 );
  return 0;
}

int OpticEngineP2W::SetAlgorithmEnable ( uint8_t value )
{
  int imode = value;
  XmlConfig::SetParam ( "OpticEngine", "AlgorithmEnable", imode );

  DmdDdp442XInterface::SetAlgorithmEnable ( value );

  return 0;
}

int OpticEngineP2W::GetAlgorithmEnable ( uint8_t& value )
{
  return DmdDdp442XInterface::GetAlgorithmEnable ( value );
}

static std::map<uint8_t, std::string> map_cca_str =
{
  { 0, "CCATargetRed"},
  { 1, "CCATargetGreen"},
  { 2, "CCATargetBlue"},
  { 3, "CCATargetCyan"},
  { 4, "CCATargetMagenta"},
  { 5, "CCATargetYellow"},
};

int OpticEngineP2W::SetCCATarget ( uint8_t* pTarget )
{
  auto iter = map_cca_str.find ( pTarget[0] );

  if ( iter != map_cca_str.end() )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Set %s\n", iter->second.c_str() );

    uint8_t temp[13];
    temp[0] = pTarget[0];
    memcpy ( &temp[1], & ( pTarget[1 + 12 * pTarget[0] ] ), 12 );

    DmdDdp442XInterface::SetCCATarget ( temp );
    XmlConfig::SetParamArray ( "OpticEngine", iter->second, &temp[1], 12 );
  }

  if ( 0xff == pTarget[0] ) /*  Set All Cca  */
  {
    for ( auto& ele : map_cca_str )
    {
      uint8_t temp[13];
      temp[0] = ele.first;
      memcpy ( &temp[1], & ( pTarget[1 + 12 * temp[0] ] ), 12 );

      if ( ele.first > 2 )
        continue;

      DmdDdp442XInterface::SetCCATarget ( temp );
      XmlConfig::SetParamArray ( "OpticEngine", ele.second, &temp[1], 12 );
    }
  }

  return 0;
}

int OpticEngineP2W::GetCCATarget ( uint8_t* pTarget )
{
  auto iter = map_cca_str.find ( pTarget[0] );

  if ( iter != map_cca_str.end() )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Get %s\n", iter->second.c_str() );
    uint8_t temp[13];
    temp[0] = pTarget[0];

    XmlConfig::GetParamArray ( "OpticEngine", iter->second, &temp[1], NULL, 12 );
    memcpy ( &pTarget[1 + pTarget[0] * 12], &temp[1], 12 );
  }

  if ( 0xff == pTarget[0] )
  {
    for ( auto& ele : map_cca_str )
    {
      uint8_t temp[13];
      temp[0] = ele.first;

      XmlConfig::GetParamArray ( "OpticEngine", ele.second, &temp[1], NULL, 12 );
      memcpy ( &pTarget[1 + temp[0] * 12], &temp[1], 12 );
    }
  }

  return 0;
}

bool OpticEngineP2W::SetFanPwm ( uint8_t fanid, uint8_t pwm ) /*  0:; 1:led driver; 2:led,; 3: */
{
  DmdDdp442XInterface::SetFanPwm ( fanid, pwm );
  return true;
}

bool OpticEngineP2W::GetFanPwm ( uint8_t fanid, uint8_t& pwm )
{
  DmdDdp442XInterface::GetFanPwm ( fanid, pwm );
  return true;
}

bool OpticEngineP2W::SetFanSpeed ( uint8_t fanid, uint16_t speed )
{
  return true;
}

bool OpticEngineP2W::GetFanSpeed ( uint8_t fanid, uint16_t& speed )
{
  int i = 0;

  do
  {
    DmdDdp442XInterface::GetFanSpeed ( fanid, speed );
    usleep ( 50 * 1000 );
  }
  while ( ( ++i < 10 ) && ( speed > 10000 ) );

  if ( speed > 10000 )
    return false;

  return true;
}

uint8_t* OpticEngineP2W::GetEdid ( )
{
  return OpticEngineP2WEDID;
}

int OpticEngineP2W::SetOverLap ( uint16_t overlap )
{
  return 0;
}

int OpticEngineP2W::GetOverLap ( uint16_t& overlap )
{
  return 0;
}

int OpticEngineP2W::GetFirmwareVersion ( uint32_t& version )
{
  uint8_t ver[4] = {0};
  int ret = DmdDdp442XInterface::GetFirmwareVersion ( ver );

  if ( ret == 0 )
  {
    version = ( ( ( uint32_t ) ver[3] ) << 24 ) + ( ( ( uint32_t ) ver[2] ) << 16 ) + ( ( ( uint32_t ) ver[1] ) << 8 ) + ( uint32_t ) ver[0];
  }

  return ret;
}

