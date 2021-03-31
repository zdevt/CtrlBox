/*
 * =====================================================================================
 *
 *       Filename:  DebugFpgaGet.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2015 10:45:00 AM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "DebugFpgaGet.h"
#include "FpgaTestPic.h"
#include "LogPrint.h"
#include "MainboardInterface.h"

DebugFpgaGet::DebugFpgaGet()
{
}

DebugFpgaGet::~DebugFpgaGet()
{
}

bool DebugFpgaGet::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  int addr = 0;
  int val = 0;
  std::stringstream ss ( funarg );
  ss >> std::hex >> addr;

  val = FpgaGetReg ( addr );
  PRINT_LOG2 ( "FpgaGet %0x %04x\n", addr, val );

  return true;
}

void DebugFpgaGet::Help ( )
{
  PRINT_LOG2 ( "FpgaGet addr\n" );
}

std::shared_ptr<DebugFun> DebugFpgaGet::GetObj ( )
{
  return std::make_shared<DebugFpgaGet> ( );
}

