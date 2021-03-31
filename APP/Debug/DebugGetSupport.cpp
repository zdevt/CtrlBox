/*
 * =====================================================================================
 *
 *       Filename:  DebugGetSupport.cpp
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

#include "DebugGetSupport.h"
#include "FpgaTestPic.h"
#include "LogPrint.h"
#include "MainboardInterface.h"
#include "OpticEngineInterface.h"

DebugGetSupport::DebugGetSupport()
{
}

DebugGetSupport::~DebugGetSupport()
{
}

bool DebugGetSupport::Fun ( std::string funarg )
{
  PRINT_LOG2 ( "\nMainboardSupport:\n" );
  MainboardInterface::GetSupport ( );
  PRINT_LOG2 ( "\nOptieEngineSupport:\n" );
  OpticEngineInterface::GetSupport ( );
  return true;
}

void DebugGetSupport::Help ( )
{
  PRINT_LOG2 ( "GetSupport\n" );
}

std::shared_ptr<DebugFun> DebugGetSupport::GetObj ( )
{
  return std::make_shared<DebugGetSupport> ( );
}

