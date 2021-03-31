/*
 * =====================================================================================
 *
 *       Filename:  DebugFpgaSet.cpp
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

#include "DebugFpgaSet.h"
#include "FpgaTestPic.h"
#include "LogPrint.h"
#include "MainboardInterface.h"

DebugFpgaSet::DebugFpgaSet()
{
}

DebugFpgaSet::~DebugFpgaSet()
{
}

bool DebugFpgaSet::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 2 )
  {
    Help();
    return false;
  }

  int addr = 0;
  int val = 0;
  std::stringstream ss ( funarg );
  ss >> std::hex >> addr >> std::hex >> val;

  FpgaSetReg ( addr, val );
  return true;
}

void DebugFpgaSet::Help ( )
{
  PRINT_LOG2 ( "FpgaSet addr val\n" );
}

std::shared_ptr<DebugFun> DebugFpgaSet::GetObj ( )
{
  return std::make_shared<DebugFpgaSet> ( );
}

