/*
 * =====================================================================================
 *
 *       Filename:  DebugSetOpticEngine.cpp
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

#include "DebugSetOpticEngine.h"
#include "LogPrint.h"
#include "XmlConfig.h"

DebugSetOpticEngine::DebugSetOpticEngine()
{
}

DebugSetOpticEngine::~DebugSetOpticEngine()
{
}

bool DebugSetOpticEngine::Fun ( std::string funarg )
{
  if ( GetArgNum ( funarg ) != 1 )
  {
    Help();
    return false;
  }

  std::string model;
  std::stringstream ss ( funarg );
  ss >> model;
  XmlConfig::SetParam ( "OpticEngine", "EngineType", model );
  return true;
}

void DebugSetOpticEngine::Help ( )
{
  PRINT_LOG2 ( "SetOpticEngine\n" );
}

std::shared_ptr<DebugFun> DebugSetOpticEngine::GetObj ( )
{
  return std::make_shared<DebugSetOpticEngine> ( );
}


