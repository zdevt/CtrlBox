/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageFpga.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月21日 14时36分05秒
 *  Last Modified:  2015年09月21日 14时36分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "FpgaImageFpga.h"

std::shared_ptr<FpgaImageHandle> FpgaImageFpga::GetObj ( )
{
  return std::make_shared<FpgaImageFpga> ( );
}

FpgaImageFpga::FpgaImageFpga()
{

}

FpgaImageFpga::~FpgaImageFpga()
{

}

bool FpgaImageFpga::Handle ( int index )
{
  FpgaSetReg ( FPGA_DESKTOP_REG, index + 1 );
  return true;
}

