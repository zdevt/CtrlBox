/*
 * =====================================================================================
 *
 *       Filename:  UpgradeKernel.cpp
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

#include "UpgradeKernel.h"
#include "RootfsAdmin.h"


UpgradeKernel::UpgradeKernel ( std::string infilename )
  : UpgradeFile ( infilename )
{
}


UpgradeKernel::~UpgradeKernel()
{
}


int UpgradeKernel::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  WriteFile ( KERNEL_SOFT_NAME, vecout );
  RootfsAdmin::UpgradeKernel ( KERNEL_SOFT_NAME );
  return 0;
}


std::shared_ptr<UpgradeFile> UpgradeKernel::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeKernel> ( infilename );
}


