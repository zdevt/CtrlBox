/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageTestPic.cpp
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

#include "FpgaImageTestPic.h"
#include "OpticEngineInterface.h"

std::shared_ptr<FpgaImageHandle> FpgaImageTestPic::GetObj ( )
{
  return std::make_shared<FpgaImageTestPic> ( );
}

FpgaImageTestPic::FpgaImageTestPic()
{

}

FpgaImageTestPic::~FpgaImageTestPic()
{

}

bool FpgaImageTestPic::Handle ( int index )
{
  //GET_ENGPTR-> WriteTestPic( );

  FpgaSetReg ( FPGA_DESKTOP_REG, 2 );
  return true;
}

