/*
 * =====================================================================================
 *
 *       Filename:  UpgradeBootloader.cpp
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

#include "UpgradeBootloader.h"
#include "RootfsAdmin.h"


UpgradeBootloader::UpgradeBootloader ( std::string infilename )
  : UpgradeFile ( infilename )
{
}


UpgradeBootloader::~UpgradeBootloader()
{
}


int UpgradeBootloader::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  WriteFile ( BOOTLOADER_SOFT_NAME, vecout );
  RootfsAdmin::UpgradeBootloader ( BOOTLOADER_SOFT_NAME );
  return 0;
}


std::shared_ptr<UpgradeFile> UpgradeBootloader::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeBootloader> ( infilename );
}


