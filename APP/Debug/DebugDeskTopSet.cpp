/*
 * =====================================================================================
 *
 *       Filename:  DebugDeskTopSet.cpp
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

#include "DebugDeskTopSet.h"
#include "LogPrint.h"
#include "FpgaImageSwitch.h"


DebugDeskTopSet::DebugDeskTopSet()
{
}

DebugDeskTopSet::~DebugDeskTopSet()
{
}

bool DebugDeskTopSet::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  uint32_t val = 0;
  std::stringstream ss ( funarg );
  ss >> std::hex >> val;
  FpgaImageSwitch::SetDeskTopIndex ( val );
  return true;
}

void DebugDeskTopSet::Help ( )
{
  PRINT_LOG2 ( "DebugDeskTopSet xx\n" );
}

std::shared_ptr<DebugFun> DebugDeskTopSet::GetObj ( )
{
  return std::make_shared<DebugDeskTopSet> ( );
}


