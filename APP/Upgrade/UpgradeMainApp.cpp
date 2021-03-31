/*
 * =====================================================================================
 *
 *       Filename:  UpgradeMainApp.cpp
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

#include "UpgradeMainApp.h"
#include "MainApp.h"


UpgradeMainApp::UpgradeMainApp ( std::string infilename )
  : UpgradeFile ( infilename )
{
}

UpgradeMainApp::~UpgradeMainApp()
{
}

int UpgradeMainApp::HandleFile ( pUpgradeCbk cbk )
{
  std::vector<char> vecout;

  if ( 0 != UnCompress ( vecout ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  unlink ( APP_SOFT_NAME );
  system ( "sync;" );

  WriteFile ( APP_SOFT_NAME, vecout );
  chmod ( APP_SOFT_NAME, 0777 );
  system ( "sync;md5sum /app/MAINAPP >/app/cksum;" );
  system ( "sync;sleep 1;reboot;" );
  //MainApp::SetRunFlag ( false );
  return 0;
}


std::shared_ptr<UpgradeFile> UpgradeMainApp::GetObj ( std::string infilename )
{
  return std::make_shared<UpgradeMainApp> ( infilename );
}


