/*
 * =====================================================================================
 *
 *       Filename:  DebugHelp.cpp
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

#include "DebugHelp.h"
#include "LogPrint.h"
#include "DebugAdmin.h"
#include "SystemDefine.h"

DebugHelp::DebugHelp()
{
}

DebugHelp::~DebugHelp()
{
}

bool DebugHelp::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 0 )
  {
    std::string arg;
    std::stringstream ss ( funarg );
    ss >> arg;
    auto iter = DebugAdmin::GetMap().find ( arg );

    if ( iter != DebugAdmin::GetMap().end() )
      ( iter->second ) ()->Help();
  }
  else
  {
    for ( auto iter = DebugAdmin::GetMap().begin();
          iter !=  DebugAdmin::GetMap().end(); ++iter )
      PRINT_LOG2 ( "%s\n", ( iter->first ).c_str() );
  }

  PRINT_LOG2 ( "Maketime    = % s\n", SystemDefine::GetMakeTime().c_str() );
  PRINT_LOG2 ( "Ver         = % s\n", SystemDefine::GetVer().c_str() );

  return true;
}

void DebugHelp::Help ( )
{
  PRINT_LOG2 ( "DebugHelp xxx\n" );
}

std::shared_ptr<DebugFun> DebugHelp::GetObj ( )
{
  return std::make_shared<DebugHelp> ( );
}

