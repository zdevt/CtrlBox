/*
 * =====================================================================================
 *
 *       Filename:  DebugSetMainboard.cpp
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

#include "DebugSetMainboard.h"
#include "LogPrint.h"
#include "XmlConfig.h"

DebugSetMainboard::DebugSetMainboard()
{
}

DebugSetMainboard::~DebugSetMainboard()
{
}

bool DebugSetMainboard::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  std::string model;
  std::stringstream ss ( funarg );
  ss >> model;
  XmlConfig::SetParam ( "Mainboard", "Model", model );
  return true;
}

void DebugSetMainboard::Help ( )
{
  PRINT_LOG2 ( "SetMainboard\n" );
}

std::shared_ptr<DebugFun> DebugSetMainboard::GetObj ( )
{
  return std::make_shared<DebugSetMainboard> ( );
}


