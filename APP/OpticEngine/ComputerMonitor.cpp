/*
 * =====================================================================================
 *
 *       Filename:  ComputerMonitor.cpp
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

#include "ComputerMonitor.h"
#include "FpgaDev.h"
#include "MainboardInterface.h"

std::shared_ptr<OpticEngine> ComputerMonitor::GetObj ( std::string engineName )
{
  return std::make_shared<ComputerMonitor> ( engineName );
}

ComputerMonitor::ComputerMonitor ( std::string engineName )
  : OpticEngine ( engineName )
{
}

ComputerMonitor::~ComputerMonitor()
{
}

uint32_t ComputerMonitor::GetEngineRes ( int& width, int& height )
{
  width = 1920;
  height = 1080;
  return OPTIC_ENGINE_RES_1080P;
}

uint32_t ComputerMonitor::GetEngineType()
{
  return 0;
}

uint32_t ComputerMonitor::GetEnginePlatform()
{
  return 0;
}

uint32_t ComputerMonitor::GetEngine2Dor3D()
{
  return 0;
}

int ComputerMonitor::WriteLogoAndTestPic()
{
  GET_MBPTR->WriteBmpFileToFpga ( "/app/logo_1080P.bmp", FPGA_PIC_SXGA );
  GET_MBPTR->WriteBmpFileToFpga ( "/app/test_pic_1080P.bmp", FPGA_TEST_PIC );
  return 0;
}

int ComputerMonitor::WriteLogo()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_1080P.bmp", FPGA_PIC_SXGA );
  return 0;
}

int ComputerMonitor::WriteTestPic()
{
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_1080P.bmp", FPGA_TEST_PIC );
  return 0;
}

int ComputerMonitor::SetPowerState ( uint8_t state )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "%d\n", state );

  if ( state )
  {
    SetFpgaPixel();
    WriteLogoAndTestPic();
    FpgaImageSwitch::SetDeskTopIndex ( FpgaImageSwitch::GetDeskTopIndex() );
  }

  int istate = state;
  XmlConfig::SetParam ( "OpticEngine", "PowerState", istate );

  return 0;
}

int ComputerMonitor::GetPowerState ( uint8_t& state )
{
  int istate = 0;
  XmlConfig::GetParam ( "OpticEngine", "PowerState", istate, 0 );
  state = istate;

  return 0;
}

int ComputerMonitor::SetFpgaPixel( )
{
  int w = 0;
  int h = 0;
  GetEngineRes ( w, h );

  GET_MBPTR->SetDisplayTimming ( w, h, NULL );

  return 0;
}

int ComputerMonitor::SetBcMode ( uint8_t mode )
{
  return 0;
}

int ComputerMonitor::GetBcMode ( uint8_t& mode )
{
  return 0;
}

int ComputerMonitor::SetDmdGamma ( uint8_t gammaType )
{
  return 0;
}

int ComputerMonitor::GetDmdGamma ( uint8_t& gammaType )
{
  return 0;
}

int ComputerMonitor::SetProjMode ( uint8_t mode )
{
  return 0;
}

int ComputerMonitor::GetProjMode ( uint8_t& mode )
{
  return 0;
}

int ComputerMonitor::SetColorOffset ( uint16_t r, uint16_t g, uint16_t b )
{
  return 0;
}

int ComputerMonitor::GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  return 0;
}

int ComputerMonitor::SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b )
{
  return 0;
}

int ComputerMonitor::GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  return 0;
}

int ComputerMonitor::SetColorContrast ( uint16_t r, uint16_t g, uint16_t b )
{
  return 0;
}

int ComputerMonitor::GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  return 0;
}

int ComputerMonitor::SetDutycycle ( uint8_t dc )
{
  return 0;
}

int ComputerMonitor::GetDutycycle ( uint8_t* dc )
{
  return 0;
}

int ComputerMonitor::GetDutycycleValue ( void* p )
{
  return 0;
}

int ComputerMonitor::SetHsgAdjustment ( void* hsg )
{
  return 0;
}

int ComputerMonitor::GetHsgAdjustment ( void* hsg )
{
  return 0;
}

int ComputerMonitor::SetLedDacRed ( void* p )
{
  return 0;
}

int ComputerMonitor::SetLedDacRedBasic ( void* p )
{
  return 0;
}

int ComputerMonitor::GetLedDacRedBasic ( void* p )
{
  return 0;
}

int ComputerMonitor::GetLedDacRed ( void* p )
{
  return 0;
}

int ComputerMonitor::SetLedDacGreen ( void* p )
{
  return 0;
}

int ComputerMonitor::SetLedDacGreenBasic ( void* p )
{
  return 0;
}

int ComputerMonitor::GetLedDacGreenBasic ( void* p )
{
  return 0;
}

int ComputerMonitor::GetLedDacGreen ( void* p )
{
  return 0;
}

int ComputerMonitor::SetLedDacBlue ( void* p )
{
  return 0;
}

int ComputerMonitor::SetLedDacBlueBasic ( void* p )
{
  return 0;
}

int ComputerMonitor::GetLedDacBlueBasic ( void* p )
{
  return 0;
}

int ComputerMonitor::GetLedDacBlue ( void* p )
{
  return 0;
}

int ComputerMonitor::LumCompStart()
{
  return 0;
}

int ComputerMonitor::SetDspEffect ( uint32_t dspEffect )
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

int ComputerMonitor::GetMaxDac ( void* p )
{
  return 1023;
}

int ComputerMonitor::GetDmdTemp ( int& temp )
{
  return 0;
}

int ComputerMonitor::GetLedTemp ( int* ptemp )
{
  return 0;
}

int ComputerMonitor::GetLedStatus ( void* p )
{
  return 0;
}

int ComputerMonitor::SetWpcMode ( uint8_t mode )
{
  return 0;
}

int ComputerMonitor::GetWpcMode ( uint8_t& mode )
{
  return 0;
}

int ComputerMonitor::SetWpcTarget ( uint8_t* pTarget )
{
  return 0;
}

int ComputerMonitor::GetWpcTarget ( uint8_t* pTarget )
{
  return 0;
}

int ComputerMonitor::SetAlgorithmEnable ( uint8_t value )
{
  return 0;
}

int ComputerMonitor::GetAlgorithmEnable ( uint8_t& value )
{
  return 0;
}

int ComputerMonitor::SetCCATarget ( uint8_t* pTarget )
{
  return 0;
}

int ComputerMonitor::GetCCATarget ( uint8_t* pTarget )
{
  return 0;
}

int ComputerMonitor::SetDmdRegVal ( uint8_t subaddr, uint32_t datalen, uint8_t* data )
{
  return 0;
}

int ComputerMonitor::GetDmdRegVal ( uint8_t subaddr, uint32_t paramlen, uint8_t* param, uint32_t datalen, uint8_t* data )
{
  return 0;
}

bool ComputerMonitor::SetFanPwm ( uint8_t fanid, uint8_t pwm )
{
  return false;
}

bool ComputerMonitor::GetFanPwm ( uint8_t fanid, uint8_t& pwm )
{
  return false;
}

bool ComputerMonitor::SetFanSpeed ( uint8_t fanid, uint16_t speed )
{
  return false;
}

bool ComputerMonitor::GetFanSpeed ( uint8_t fanid, uint16_t& speed )
{
  return false;
}

uint8_t* ComputerMonitor::GetEdid ( )
{
  return NULL;
}

int ComputerMonitor::SetOverLap ( uint16_t overlap )
{
  return 0;
}

int ComputerMonitor::GetOverLap ( uint16_t& overlap )
{
  return 0;
}

int ComputerMonitor::GetFirmwareVersion ( uint32_t& version )
{
  version = 10000;
  return 0;
}

