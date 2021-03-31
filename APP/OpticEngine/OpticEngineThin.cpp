/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineThin.cpp
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
#include <iomanip>

#include "OpticEngineThin.h"
#include "FpgaDev.h"
#include "MainboardInterface.h"

uint8_t OpticEngineThinEDID[] =
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

std::shared_ptr<OpticEngine> OpticEngineThin::GetObj ( std::string engineName )
{
  return std::make_shared<OpticEngineThin> ( engineName );
}

OpticEngineThin::OpticEngineThin ( std::string engineName )
  : OpticEngine ( engineName )
{
}

OpticEngineThin::~OpticEngineThin()
{
}

uint32_t OpticEngineThin::GetEngineRes ( int& width, int& height )
{
  width = 1920;
  height = 1080;
  return OPTIC_ENGINE_RES_1080P;
}
uint32_t OpticEngineThin::GetEngineType()
{
  return OPTIC_ENGINE_TYPE_LED;
}

uint32_t OpticEngineThin::GetEnginePlatform()
{
  return OPTIC_ENGINE_PLATFORM_DDP442X;
}

uint32_t OpticEngineThin::GetEngine2Dor3D()
{
  return OPTIC_ENGINE_2D;
}

int OpticEngineThin::WriteLogoAndTestPic()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_1080P.bmp", FPGA_PIC_SXGA );
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_1080P.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineThin::WriteLogo()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_1080P.bmp", FPGA_PIC_SXGA );
  return 0;
}

int OpticEngineThin::WriteTestPic()
{
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_1080P.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineThin::SetPowerState ( uint8_t state )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "%d\n", state );

  if ( state )
  {
    /*  1.  */
    SetFpgaPixel();
    /*  set saved dac */
    sleep ( 10 ); /*  wait engine ready */
    WriteLogoAndTestPic();
    sleep ( 10 ); /*  wait engine ready */

    uint8_t value;
    GetBcMode ( value );
    SetBcMode ( value );

    sleep ( 5 );
    #if 0
    GetDutycycle ( &value );
    SetDutycycle ( value );
    #endif

    sleep ( 5 );
    dac_t dac;
    GetLedDacRedBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacRed ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 200 * 1000 );

    GetLedDacGreenBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacGreen ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 200 * 1000 );

    GetLedDacBlueBasic ( reinterpret_cast<void*> ( &dac ) );
    SetLedDacBlue ( reinterpret_cast<void*> ( &dac ) );
    usleep ( 200 * 1000 );


    uint8_t temp[128] = { 0 };

    #if 1
    /*  Set HSG Enable */
    int imode = 0;
    XmlConfig::GetParam ( "OpticEngine", "CcAEnable", imode, 0 );
    ddp442x_alg_enable_t ddp442x_alg_enable;

    if ( imode )
    {
      sleep ( 3 );
      GetAlgorithmEnable ( ddp442x_alg_enable.data );
      PRINT_LOG ( LOG_LEVEL_NORMAL, "0. Read AlgorithmEnable %d!\n", ddp442x_alg_enable.data );
      ddp442x_alg_enable.degamma = 1;
      ddp442x_alg_enable.cca     = 1;
      ddp442x_alg_enable.stm     = 1;
      PRINT_LOG ( LOG_LEVEL_NORMAL, "1. Write AlgorithmEnable %d!\n", ddp442x_alg_enable.data );
      usleep ( 25 * 1000 );
      SetAlgorithmEnable ( ddp442x_alg_enable.data );
      usleep ( 2000 * 1000 );
    }

    #endif

    /*  Set HSG Value */
    GetHsgAdjustment ( temp );
    SetHsgAdjustment ( temp );
    sleep ( 1 );

    /* check hsg */
    uint8_t pDmdHsg[42] = { 0 };
    std::stringstream sx, sd;

    auto checkXmlDmdHsg  = [] ( uint8_t* p1, uint8_t* p2, int num )
    {
      for ( int i = 1; i < num; i += 2 )
        if ( p1[i] != p2[i] )
          return false;

      return true;
    };

    for ( int i = 0; i < 3; ++i )
    {
      DmdDdp442XInterface::GetHsgAdjustment ( pDmdHsg );

      if ( !checkXmlDmdHsg ( temp, pDmdHsg, 42 ) )
      {
        sleep ( 1 );
        SetHsgAdjustment ( temp );

        for ( int j = 0; j < 42; ++j )
        {
          sx << "0x" << std::hex << std::setw ( 2 ) << std::setfill ( '0' ) << ( int ) temp[j] << " ";
          sd << "0x" << std::hex << std::setw ( 2 ) << std::setfill ( '0' ) << ( int ) pDmdHsg[j] << " ";
        }

        PRINT_LOG ( LOG_LEVEL_FATAL, "xmlhsg =\n: %s\ndmdhsg=\n: %s\n",
                    sx.str().c_str(),
                    sd.str().c_str() );
      }
      else
        break;
    }

    /* check hsg end */

    FpgaImageSwitch::SetDeskTopIndex ( FpgaImageSwitch::GetDeskTopIndex() );

    uint8_t mode = 0;
    GetProjMode ( mode );
    SetProjMode ( mode );

    /*  如果授权使用非法,画面显示不正常*/
    //if ( !CheckUsePeriodValid() )
    //{
    //  PRINT_LOG ( LOG_LEVEL_NORMAL, "UsePeriod Time Out!\n" );
    //  FpgaSetReg ( FPGA_DESKTOP_REG, 6 );//画面打黑
    //  return 1;
    //}
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

int OpticEngineThin::GetPowerState ( uint8_t& state )
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

int OpticEngineThin::SetFpgaPixel( )
{
  int w = 0;
  int h = 0;
  GetEngineRes ( w, h );

  GET_MBPTR->SetDisplayTimming ( w, h, NULL );

  return 0;
}

int OpticEngineThin::SetBcMode ( uint8_t mode )
{
  DmdDdp442XInterface::SetSystemMode ( mode );

  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "SysTemMode", imode );

  return 0;
}

int OpticEngineThin::GetBcMode ( uint8_t& mode )
{
  int imode = 0;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "SysTemMode", imode, temp );
  mode = imode;
  return 0;
}

int OpticEngineThin::SetDmdGamma ( uint8_t gammaType )
{
  DmdDdp442XInterface::SetGammaTable ( gammaType );

  int igammaType = gammaType ;
  XmlConfig::SetParam ( "OpticEngine", "DmdGamma", igammaType );
  return 0;
}

int OpticEngineThin::GetDmdGamma ( uint8_t& gammaType )
{
  int igammaType = 0;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "DmdGamma", igammaType, temp );
  gammaType = igammaType;
  return 0;
}

int OpticEngineThin::SetProjMode ( uint8_t mode )
{
  DmdDdp442XInterface::SetImageFlip ( mode );

  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "ProjMode", imode );
  return 0;
}

int OpticEngineThin::GetProjMode ( uint8_t& mode )
{
  int imode = 0;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "ProjMode", imode, temp );
  mode = imode;
  return 0;
}

int OpticEngineThin::SetColorOffset ( uint16_t r, uint16_t g, uint16_t b )
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

int OpticEngineThin::GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorOffsetB", b, ( uint16_t ) 0 );

  return 0;
}

int OpticEngineThin::SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b )
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

int OpticEngineThin::GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorBrightnessB", b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineThin::SetColorContrast ( uint16_t r, uint16_t g, uint16_t b )
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

int OpticEngineThin::GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastR", r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastG", g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "ColorContrastB", b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineThin::SetDutycycle ( uint8_t dc )
{
  int idc = dc;
  XmlConfig::SetParam ( "OpticEngine", "Dutycycle", idc );
  DmdDdp442XInterface::SetDutycycle ( dc );
  return 0;
}

int OpticEngineThin::GetDutycycle ( uint8_t* dc )
{
  int idc;
  int temp = 0;
  XmlConfig::GetParam ( "OpticEngine", "Dutycycle", idc, temp );
  *dc = ( uint8_t ) idc;
  //DmdDdp442XInterface::GetDutycycle ( dc );
  return 0;
}

int OpticEngineThin::GetDutycycleValue ( void* p )
{
  DmdDdp442XInterface::GetDutycycleValue ( reinterpret_cast<uint8_t*> ( p ) );
  return 0;
}

int OpticEngineThin::SetLedDacRed ( void* p )
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

int OpticEngineThin::SetLedDacRedBasic ( void* p )
{
  SetLedDacRed ( p );
  dac_cfg_t* pdac_cfg = reinterpret_cast<dac_cfg_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacRedR", pdac_cfg->redDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacRedG", pdac_cfg->greenDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacRedB", pdac_cfg->blueDac );

  return 0;
}

int OpticEngineThin::GetLedDacRedBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedR", dac->r, ( uint16_t ) 1023 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedG", dac->g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedB", dac->b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineThin::GetLedDacRed ( void* p )
{
  dac_cfg_t dac_cfg;
  DmdDdp442XInterface::GetRedLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac->r = dac_cfg.redDac;
  dac->g = dac_cfg.greenDac;
  dac->b = dac_cfg.blueDac;

  unsigned int times = 5;

  while ( !dac->IsValid() && ( --times ) )
  {
    usleep ( 30 * 1000 );
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Invalid red DAC value: %d %d %d\n", dac->r, dac->g, dac->b );
    DmdDdp442XInterface::GetRedLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );
    dac->r = dac_cfg.redDac;
    dac->g = dac_cfg.greenDac;
    dac->b = dac_cfg.blueDac;
  }

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineThin::SetLedDacGreen ( void* p )
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

int OpticEngineThin::SetLedDacGreenBasic ( void* p )
{
  SetLedDacGreen ( p );

  dac_cfg_t* pdac_cfg = reinterpret_cast<dac_cfg_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenR", pdac_cfg->redDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenG", pdac_cfg->greenDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacGreenB", pdac_cfg->blueDac );

  return 0;
}

int OpticEngineThin::GetLedDacGreenBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenR", dac->r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenG", dac->g, ( uint16_t ) 1023 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenB", dac->b, ( uint16_t ) 0 );
  return 0;
}

int OpticEngineThin::GetLedDacGreen ( void* p )
{
  dac_cfg_t dac_cfg;
  DmdDdp442XInterface::GetGreenLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac->r = dac_cfg.redDac;
  dac->g = dac_cfg.greenDac;
  dac->b = dac_cfg.blueDac;

  unsigned int times = 5;

  while ( !dac->IsValid() && ( --times ) )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Invalid green DAC value: %d %d %d\n", dac->r, dac->g, dac->b );
    usleep ( 30 * 1000 );
    DmdDdp442XInterface::GetGreenLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );
    dac->r = dac_cfg.redDac;
    dac->g = dac_cfg.greenDac;
    dac->b = dac_cfg.blueDac;
  }

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineThin::SetLedDacBlue ( void* p )
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

int OpticEngineThin::SetLedDacBlueBasic ( void* p )
{
  SetLedDacBlue ( p );
  dac_cfg_t* pdac_cfg = reinterpret_cast<dac_cfg_t*> ( p );

  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueR", pdac_cfg->redDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueG", pdac_cfg->greenDac );
  XmlConfig::SetParam ( "OpticEngine", "LedDacBlueB", pdac_cfg->blueDac );

  return 0;
}

int OpticEngineThin::GetLedDacBlueBasic ( void* p )
{
  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueR", dac->r, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueG", dac->g, ( uint16_t ) 0 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueB", dac->b, ( uint16_t ) 1023 );
  return 0;
}

int OpticEngineThin::GetLedDacBlue ( void* p )
{
  dac_cfg_t dac_cfg;
  DmdDdp442XInterface::GetBlueLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );

  dac_t* dac = reinterpret_cast<dac_t*> ( p );
  dac->r = dac_cfg.redDac;
  dac->g = dac_cfg.greenDac;
  dac->b = dac_cfg.blueDac;

  unsigned int times = 5;

  while ( !dac->IsValid() && ( --times ) )
  {
    usleep ( 30 * 1000 );
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Invalid blue DAC value: %d %d %d\n", dac->r, dac->g, dac->b );
    DmdDdp442XInterface::GetBlueLedDac ( reinterpret_cast<uint8_t*> ( &dac_cfg ) );
    dac->r = dac_cfg.redDac;
    dac->g = dac_cfg.greenDac;
    dac->b = dac_cfg.blueDac;
  }

  usleep ( 30 * 1000 );
  return 0;
}

int OpticEngineThin::LumCompStart()
{
  return 0;
}

int OpticEngineThin::SetDspEffect ( uint32_t dspEffect )
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

int OpticEngineThin::GetMaxDac ( void* p )
{
  uint16_t* pdac = reinterpret_cast<uint16_t* > ( p );
  XmlConfig::GetParam ( "OpticEngine", "LedDacRedR", 		pdac[0], ( uint16_t ) 4095 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacGreenG", 	pdac[1], ( uint16_t ) 4095 );
  XmlConfig::GetParam ( "OpticEngine", "LedDacBlueB", 	pdac[2], ( uint16_t ) 4095 );

  return 4095;
}

int OpticEngineThin::GetDmdTemp ( int& temp )
{
  int16_t t;
  DmdDdp442XInterface::GetDmdTemp ( &t );
  temp = t;
  return 0;
}

int OpticEngineThin::GetLedTemp ( int* ptemp )
{
  DmdDdp442XInterface::GetLedTempThin ( 0, & ( ptemp[0] ) );
  DmdDdp442XInterface::GetLedTempThin ( 1, & ( ptemp[1] ) );
  DmdDdp442XInterface::GetLedTempThin ( 2, & ( ptemp[2] ) );
  return 0;
}

int OpticEngineThin::GetLedStatus ( void* p )
{
  DmdDdp442XInterface::GetLedTempVA ( reinterpret_cast<uint8_t*> ( p ) );
  return 0;
}

int OpticEngineThin::SetDmdRegVal ( uint8_t subaddr, uint32_t datalen, uint8_t* data )
{
  return DmdDdp442XInterface::SetCommand ( subaddr, data, datalen );
}

int OpticEngineThin::GetDmdRegVal ( uint8_t subaddr, uint32_t paramlen, uint8_t* param, uint32_t datalen, uint8_t* data )
{
  return DmdDdp442XInterface::GetCommand ( subaddr, param, paramlen, data, datalen );
}

int OpticEngineThin::SetWpcMode ( uint8_t mode )
{
  int imode = mode;
  XmlConfig::SetParam ( "OpticEngine", "WpcMode", imode );
  return DmdDdp442XInterface::SetWpcMode ( &mode );
}

int OpticEngineThin::GetWpcMode ( uint8_t& mode )
{
  int imode = 0;
  XmlConfig::GetParam ( "OpticEngine", "WpcMode", imode, 0 );
  mode = imode;
  return 0;
}

int OpticEngineThin::SetWpcTarget ( uint8_t* pTarget )
{
  XmlConfig::SetParamArray ( "OpticEngine", "WpcTarget", pTarget, 12 );
  return DmdDdp442XInterface::SetWpcTarget ( pTarget );
}

int OpticEngineThin::GetWpcTarget ( uint8_t* pTarget )
{
  XmlConfig::GetParamArray ( "OpticEngine", "WpcTarget", pTarget, NULL, 12 );
  return 0;
}

int OpticEngineThin::SetAlgorithmEnable ( uint8_t value )
{
  int imode = value;
  XmlConfig::SetParam ( "OpticEngine", "AlgorithmEnable", imode );

  DmdDdp442XInterface::SetAlgorithmEnable ( value );

  return 0;
}

int OpticEngineThin::GetAlgorithmEnable ( uint8_t& value )
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

int OpticEngineThin::SetCCATarget ( uint8_t* pTarget )
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

int OpticEngineThin::GetCCATarget ( uint8_t* pTarget )
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

int OpticEngineThin::SetHsgAdjustment ( void* hsg )
{
  uint8_t* pTemp = reinterpret_cast<uint8_t*> ( hsg );
  DmdDdp442XInterface::SetHsgAdjustment ( reinterpret_cast<uint8_t*> ( hsg ) );
  XmlConfig::SetParamArray ( "OpticEngine", "HsgAdjustment", pTemp, 42 );
  return 0;
}

int OpticEngineThin::GetHsgAdjustment ( void* hsg )
{
  uint8_t* pTemp = reinterpret_cast<uint8_t*> ( hsg );
  XmlConfig::GetParamArray ( "OpticEngine", "HsgAdjustment", pTemp, NULL, 42 );

  return 0;
}

bool OpticEngineThin::SetFanPwm ( uint8_t fanid, uint8_t pwm ) /*  0:; 1:led driver; 2:led,; 3: */
{
  return ( 1 == DmdDdp442XInterface::SetFanPwm ( fanid, pwm ) );
}

bool OpticEngineThin::GetFanPwm ( uint8_t fanid, uint8_t& pwm )
{
  return ( 2 == DmdDdp442XInterface::GetFanPwm ( fanid, pwm ) );
}

bool OpticEngineThin::SetFanSpeed ( uint8_t fanid, uint16_t speed )
{
  return true;
}

bool OpticEngineThin::GetFanSpeed ( uint8_t fanid, uint16_t& speed )
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

uint8_t* OpticEngineThin::GetEdid ( )
{
  return OpticEngineThinEDID;
}

int OpticEngineThin::SetOverLap ( uint16_t overlap )
{
  return 0;
}

int OpticEngineThin::GetOverLap ( uint16_t& overlap )
{
  return 0;
}

int OpticEngineThin::GetFirmwareVersion ( uint32_t& version )
{
  uint8_t ver[4] = {0};
  int ret = DmdDdp442XInterface::GetFirmwareVersion ( ver );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "firmware version %x %x %x %x\n", ver[0], ver[1], ver[2], ver[3] );
  version = ( ( ( uint32_t ) ver[3] ) << 24 ) + ( ( ( uint32_t ) ver[2] ) << 16 ) + ( ( ( uint32_t ) ver[1] ) << 8 ) + ( uint32_t ) ver[0];
  return ret;
}

int OpticEngineThin::SetChannelSource ( uint8_t type )
{
  return DmdDdp442XInterface::SetChannelSource ( type );
}

int OpticEngineThin::GetChannelSource ( uint8_t& type )
{
  return DmdDdp442XInterface::GetChannelSource ( type );
}

int OpticEngineThin::Check()
{
  CheckLedTempAndSetFanPwm();
  return 0;
}

int OpticEngineThin::CheckLedTempAndSetFanPwm()
{
  return 0;
  static int i = 0;
  ++i;

  if ( i % 60 != 0 ) /* 60s call once */
    return 0;

  int temp = 0 ;
  uint8_t mode = 0;
  uint8_t fan1Pwm, fan2Pwm;
  uint8_t fan1PwmNow, fan2PwmNow;

  GetDmdTemp ( temp );
  GetBcMode ( mode );

  if ( mode % 2 == 0 ) /* even 100% ; odd 130% */
  {
    if ( temp < 15 )
    {
      fan1Pwm = 0;
      fan2Pwm = 80;
    }
    else if ( temp >= 15 && temp < 35 )
    {
      fan1Pwm = 80;
      fan2Pwm = 105;
    }
    else if ( temp >= 35 && temp < 40 )
    {
      fan1Pwm = 110;
      fan2Pwm = 140;
    }
    else if ( temp >= 40 && temp < 45 )
    {
      fan1Pwm = 145;
      fan2Pwm = 190;
    }
    else
    {
      fan1Pwm = 255;
      fan2Pwm = 255;
    }
  }
  else
  {
    if ( temp < 30 )
    {
      fan1Pwm = 80;
      fan2Pwm = 105;
    }
    else if ( temp >= 30 && temp < 35 )
    {
      fan1Pwm = 145;
      fan2Pwm = 190;
    }
    else if ( temp >= 35 && temp < 40 )
    {
      fan1Pwm = 205;
      fan2Pwm = 255;
    }
    else
    {
      fan1Pwm = 225;
      fan2Pwm = 255;
    }
  }

  PRINT_LOG ( LOG_LEVEL_NORMAL, "dmd temperature %d, system mode %d, fan1 pwm %d, fan2 pwm %d\n",
              temp, mode, fan1Pwm, fan2Pwm );

  GetFanPwm ( 1, fan1PwmNow );
  GetFanPwm ( 2, fan2PwmNow );

  if ( fan1PwmNow != fan1Pwm )
  {
    int32_t looptimes = 3;

    while ( ! ( SetFanPwm ( 1, fan1Pwm ) ) && ( looptimes-- ) )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "set fan1 pwm failed %d\n", looptimes );
      usleep ( 500 );
    }

    GetFanPwm ( 1, fan1Pwm );
  }

  if ( fan2PwmNow != fan2Pwm )
  {
    int32_t looptimes = 3;

    while ( ! ( SetFanPwm ( 2, fan2Pwm ) ) && ( looptimes-- ) )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "set fan2 pwm failed %d\n", looptimes );
      usleep ( 500 );
    }

    GetFanPwm ( 2, fan2Pwm );
  }

  PRINT_LOG ( LOG_LEVEL_NORMAL, "actually, fan1 pwm %d, fan2 pwm %d\n",
              fan1Pwm, fan2Pwm );

  return 0;
}

