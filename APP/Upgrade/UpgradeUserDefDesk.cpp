/*
 * =====================================================================================
 *
 *       Filename:  UpgradeUserDefDesk.cpp
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

#include "UpgradeUserDefDesk.h"
#include "FpgaTestPic.h"


UpgradeUserDefDesk::UpgradeUserDefDesk ( std::string infilename )
  : UpgradeFile ( infilename )
{
}

UpgradeUserDefDesk::~UpgradeUserDefDesk()
{
}

int UpgradeUserDefDesk::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  int fileno = GetFileNo();
  std::stringstream ss;
  ss << fileno;

  std::string outfilename = FPGA_USER_DEF_DSK_NAME;
  outfilename.replace ( outfilename.find ( "FILENO" ), strlen ( "FILENO" ), ss.str() );

  WriteFile ( outfilename, vecout );
  FpgaTestPic::WriteBmpUserDef ( outfilename, fileno );

  return 0;
}

std::shared_ptr<UpgradeFile> UpgradeUserDefDesk::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeUserDefDesk> ( infilename );
}

