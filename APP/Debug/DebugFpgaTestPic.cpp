/*
 * =====================================================================================
 *
 *       Filename:  DebugFpgaTestPic.cpp
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

#include "DebugFpgaTestPic.h"
#include "FpgaTestPic.h"
#include "LogPrint.h"
#include "MainboardInterface.h"

DebugFpgaTestPic::DebugFpgaTestPic()
{
}

DebugFpgaTestPic::~DebugFpgaTestPic()
{
}

bool DebugFpgaTestPic::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 2 )
  {
    Help();
    return false;
  }

  std::string filename;
  int addr = 0;
  std::stringstream ss ( funarg );
  ss >> filename >> addr;

  GET_MBPTR->WriteBmpFileToFpga ( filename, addr );

  return true;
}

void DebugFpgaTestPic::Help ( )
{
  PRINT_LOG2 ( "Load Fpga: cat /app/xxx.rbf >/dev/FpgaMod \n" );
  PRINT_LOG2 ( "FpgaTestPic filename addr\n" );
  PRINT_LOG2 ( "FpgaTestPic /app/Logo.bmp 8     | (8<1/24bit>:SXGA+;9<1/24bit>:XGA;14:TestPic<1bit>)\n" );
  PRINT_LOG2 ( "FpgaTestPic /app/UserDef.bmp 15 | (15-20)<24bit>\n" );
}

std::shared_ptr<DebugFun> DebugFpgaTestPic::GetObj ( )
{
  return std::make_shared<DebugFpgaTestPic> ( );
}

