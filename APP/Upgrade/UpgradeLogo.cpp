/*
 * =====================================================================================
 *
 *       Filename:  UpgradeLogo.cpp
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

#include "UpgradeLogo.h"
#include "FpgaTestPic.h"


UpgradeLogo::UpgradeLogo ( std::string infilename )
  : UpgradeFile ( infilename )
{
}

UpgradeLogo::~UpgradeLogo()
{
}

int UpgradeLogo::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  int fileno = GetFileNo();
  std::stringstream ss;

  if ( fileno == 0 )
  {
    ss << "1080P";
  }
  else if ( fileno == 1 )
  {
    ss << "SXGAP";
  }
  else if ( fileno == 2 )
  {
    ss << "XGA";
  }

  /*  TODO 改为按照分辨率自动改名 */
  std::string outfilename = FPGA_LOGO_NAME;
  outfilename.replace ( outfilename.find ( "FILENO" ), strlen ( "FILENO" ), ss.str() );

  WriteFile ( outfilename, vecout );
  FpgaTestPic::WriteBmpLogo ( outfilename, FPGA_PIC_SXGA );

  return 0;
}

std::shared_ptr<UpgradeFile> UpgradeLogo::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeLogo> ( infilename );
}

