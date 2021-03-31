/*
 * =====================================================================================
 *
 *       Filename:  UpgradeRootfs.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/2015 05:57:45 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <sys/stat.h>

#include "UpgradeRootfs.h"
#include "RootfsAdmin.h"


UpgradeRootfs::UpgradeRootfs ( std::string infilename )
  : UpgradeFile ( infilename )
{
}

UpgradeRootfs::~UpgradeRootfs()
{
}

int UpgradeRootfs::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  WriteFile ( ROOTFS_SOFT_NAME, vecout );
  RootfsAdmin::UpgradeRootfsAndWriteInfo ( ROOTFS_SOFT_NAME );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "UpgradeRootfs Done!\n" );
  return 0;
}

std::shared_ptr<UpgradeFile> UpgradeRootfs::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeRootfs> ( infilename );
}

