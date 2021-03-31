/*
 * =====================================================================================
 *
 *       Filename:  UpgradeEngineId.cpp
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

#include "UpgradeEngineId.h"
#include "I2cEeprom24cXX.h"

UpgradeEngineId::UpgradeEngineId ( std::string infilename )
  : UpgradeFile ( infilename )
{
}

UpgradeEngineId::~UpgradeEngineId()
{
}

int UpgradeEngineId::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  return I2cEeprom24cXX::Write ( I2cBusInterface::GetBusName ( 1 ), 0xa0, 0x0,
                                 reinterpret_cast<uint8_t*> ( &vecout[0] ), vecout.size(), "24c64" );
}

std::shared_ptr<UpgradeFile> UpgradeEngineId::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeEngineId> ( infilename );
}

