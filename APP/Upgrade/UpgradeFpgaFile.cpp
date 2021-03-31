/*
 * =====================================================================================
 *
 *       Filename:  UpgradeFpgaFile.cpp
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

#include "UpgradeFpgaFile.h"


UpgradeFpgaFile::UpgradeFpgaFile ( std::string infilename )
  : UpgradeFile ( infilename )
{
}


UpgradeFpgaFile::~UpgradeFpgaFile()
{
}


int UpgradeFpgaFile::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  WriteFile ( FPGA_SOFT_NAME, vecout );
  return 0;
}


std::shared_ptr<UpgradeFile> UpgradeFpgaFile::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeFpgaFile> ( infilename );
}


