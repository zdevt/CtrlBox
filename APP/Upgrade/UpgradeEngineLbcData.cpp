/*
 * =====================================================================================
 *
 *       Filename:  UpgradeEngineLbcData.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/30/2014 02:43:28 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <sstream>
#include <string.h>

#include "UpgradeEngineLbcData.h"

UpgradeEngineLbcData::UpgradeEngineLbcData ( std::string infilename )
  : UpgradeFile ( infilename )
{
}

UpgradeEngineLbcData::~UpgradeEngineLbcData()
{
}

int UpgradeEngineLbcData::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  WriteFile ( LBCDATA_SOFT_NAME, vecout );

  return 0;
}

std::shared_ptr<UpgradeFile> UpgradeEngineLbcData::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeEngineLbcData> ( infilename );
}

