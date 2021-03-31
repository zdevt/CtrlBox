/*
 * =====================================================================================
 *
 *       Filename:  UpgradeNull.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/2015 06:04:01 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "UpgradeNull.h"


UpgradeNull::UpgradeNull ( std::string infilename )
  : UpgradeFile ( infilename )
{
}


UpgradeNull::~UpgradeNull()
{
}


int UpgradeNull::HandleFile ( pUpgradeCbk cbk )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "UpgradeNull::HandleFile\n" );
  return 0;
}


std::shared_ptr<UpgradeFile> UpgradeNull::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeNull> ( infilename );
}


