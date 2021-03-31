/*
 * =====================================================================================
 *
 *       Filename:  DebugLightBrightnessCompensation.cpp
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

#include "DebugLightBrightnessCompensation.h"
#include "LogPrint.h"
#include "LightBrightnessCompensation.h"
#include "FileHandle.h"


DebugLightBrightnessCompensation::DebugLightBrightnessCompensation()
{
}

DebugLightBrightnessCompensation::~DebugLightBrightnessCompensation()
{
}

bool DebugLightBrightnessCompensation::Fun ( std::string funarg )
{
  uint32_t argNum = GetArgNum ( funarg );

  if ( argNum < 1 )
  {
    Help();
    return false;
  }

  std::string filename;
  std::stringstream ss ( funarg );
  ss >> filename ;

  std::vector<char> vechar;

  if ( !FileHandle::Read ( filename, vechar ) )
    return false;

  int ret = LightBrightnessCompensation:: WriteDataToFPGA ( vechar );
  PRINT_LOG2 ( "LightBrightnessCompensation ret = %d\n", ret );

  return true;
}

void DebugLightBrightnessCompensation::Help ( )
{
  PRINT_LOG2 ( "DebugLightBrightnessCompensation filename \n" );
}

std::shared_ptr<DebugFun> DebugLightBrightnessCompensation::GetObj ( )
{
  return std::make_shared<DebugLightBrightnessCompensation> ( );
}

