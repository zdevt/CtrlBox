/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineP4A_SXGAP.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/26/2018 03:54:25 PM
 *  Last Modified:  07/26/2018 03:54:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <sstream>
#include <string.h>
#include <string>
#include <map>

#include "OpticEngineP4A_SXGAP.h"
#include "FpgaDev.h"
#include "MainboardInterface.h"

uint8_t OpticEngineP4A_SXGAPEDID[] =
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

std::shared_ptr<OpticEngine> OpticEngineP4A_SXGAP::GetObj ( std::string engineName )
{
  return std::make_shared<OpticEngineP4A_SXGAP> ( engineName );
}

OpticEngineP4A_SXGAP::OpticEngineP4A_SXGAP ( std::string engineName )
  : OpticEngineP4A ( engineName )
{
}

OpticEngineP4A_SXGAP::~OpticEngineP4A_SXGAP()
{
}

uint32_t OpticEngineP4A_SXGAP::GetEngineRes ( int& width, int& height )
{
  width = 1400;
  height = 1050;
  return OPTIC_ENGINE_RES_SXGA;
}

int OpticEngineP4A_SXGAP::WriteLogoAndTestPic()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_SXGAP.bmp", FPGA_PIC_SXGA );
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_SXGAP.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineP4A_SXGAP::WriteLogo()
{
  FpgaTestPic::WriteBmpLogo ( "/app/logo_SXGAP.bmp", FPGA_PIC_SXGA );
  return 0;
}

int OpticEngineP4A_SXGAP::WriteTestPic()
{
  FpgaTestPic::WriteBmpTestPic ( "/app/test_pic_SXGAP.bmp", FPGA_TEST_PIC );
  return 0;
}

int OpticEngineP4A_SXGAP::SetFpgaPixel( )
{
  int w = 0;
  int h = 0;
  GetEngineRes ( w, h );

  GET_MBPTR->SetDisplayTimming ( w, h, NULL );

  return 0;
}

uint8_t* OpticEngineP4A_SXGAP::GetEdid ( )
{
  return OpticEngineP4A_SXGAPEDID;
}

