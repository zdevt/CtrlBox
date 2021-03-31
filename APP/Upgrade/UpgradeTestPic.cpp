/*
 * =====================================================================================
 *
 *       Filename:  UpgradeTestPic.cpp
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

#include "UpgradeTestPic.h"
#include "FpgaTestPic.h"


UpgradeTestPic::UpgradeTestPic ( std::string infilename )
  : UpgradeFile ( infilename )
{
}

UpgradeTestPic::~UpgradeTestPic()
{
}

int UpgradeTestPic::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  int fileno = GetFileNo();
  std::stringstream ss;
  ss << fileno;

  /*  按照分辨率改名字 */
  std::string outfilename = FPGA_TEST_PIC_NAME;
  outfilename.replace ( outfilename.find ( "FILENO" ), strlen ( "FILENO" ), ss.str() );

  WriteFile ( outfilename, vecout );
  FpgaTestPic::WriteBmpTestPic ( outfilename, FPGA_TEST_PIC );

  return 0;
}

std::shared_ptr<UpgradeFile> UpgradeTestPic::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeTestPic> ( infilename );
}

