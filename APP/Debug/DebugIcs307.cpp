/*
 * =====================================================================================
 *
 *       Filename:  DebugIcs307.cpp
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

#include "DebugIcs307.h"
#include "Ics307.h"
#include "LogPrint.h"


DebugIcs307::DebugIcs307()
{
}

DebugIcs307::~DebugIcs307()
{
}

bool DebugIcs307::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  uint32_t val = 0;
  std::stringstream ss ( funarg );
  ss >> std::hex >> val;
  Ics307::SetFrequency ( val );
  return true;
}

void DebugIcs307::Help ( )
{
  PRINT_LOG2 ( "Ics307 val\n" );
  PRINT_LOG2 ( "val : 1 32500kHZ\n" );
  PRINT_LOG2 ( "val : 2 54000kHZ\n" );
  PRINT_LOG2 ( "val : 3 81000KHZ\n" );
  PRINT_LOG2 ( "val : 4 42500kHZ\n" );
  PRINT_LOG2 ( "val : 5 74250kHZ\n" );
  PRINT_LOG2 ( "val : other direct write reg\n" );
}

std::shared_ptr<DebugFun> DebugIcs307::GetObj ( )
{
  return std::make_shared<DebugIcs307> ( );
}


