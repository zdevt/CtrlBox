/*
 * =====================================================================================
 *
 *       Filename:  UpgradeFileInterface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/03/2015 09:49:20 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <fstream>
#include <zlib.h>

#include "UpgradeFileInterface.h"
#include "Locker.h"

#include "UpgradeFile.h"
#include "UpgradeNull.h"

#include "UpgradeBootloader.h"
#include "UpgradeFpgaFile.h"
#include "UpgradeMainApp.h"
#include "UpgradeRootfs.h"
#include "UpgradeKernel.h"
#include "UpgradeLogo.h"
#include "UpgradeTestPic.h"
#include "UpgradeUserDefDesk.h"
#include "UpgradeEngineId.h"
#include "UpgradeEngineLbcData.h"

bool UpgradeFileInterface::m_upgradeFlag = false;

void UpgradeFileInterface::SetUpgradeFlag ( bool flag )
{
  m_upgradeFlag = flag;
}

bool UpgradeFileInterface::GetUpgradeFlag( )
{
  return m_upgradeFlag;
}

pthread_mutex_t g_UpgradeFileMutex = PTHREAD_MUTEX_INITIALIZER;

mapGetUpgradeFileObj_t UpgradeFileInterface::m_mapGetUpgradeFileObj =
{
  { UPG_FILE_BOOTLOADER,  UpgradeBootloader::GetObj },
  { UPG_FILE_MAINAPP,     UpgradeMainApp::GetObj },
  { UPG_FILE_FPGA,        UpgradeFpgaFile::GetObj },
  { UPG_FILE_ROOTFS,      UpgradeRootfs::GetObj },
  { UPG_FILE_KERNEL,      UpgradeKernel::GetObj },
  { UPG_FILE_LOGO,        UpgradeLogo::GetObj },
  { UPG_FILE_TEST_PIC,    UpgradeTestPic::GetObj },
  { UPG_FILE_USERDEFDESK, UpgradeUserDefDesk::GetObj },
  { UPG_FILE_ENGINEID,    UpgradeEngineId::GetObj },
  { UPG_FILE_ENGINELBC,   UpgradeEngineLbcData::GetObj },
};

std::shared_ptr<UpgradeFileInterface> UpgradeFileInterface::m_UpgradeFileInterface = NULL;

UpgradeFileInterface::UpgradeFileInterface()
{
}

UpgradeFileInterface::~UpgradeFileInterface()
{
}

std::shared_ptr<UpgradeFileInterface> UpgradeFileInterface::GetInstance()
{
  if ( !m_UpgradeFileInterface )
    m_UpgradeFileInterface = std::make_shared<UpgradeFileInterface>();

  return m_UpgradeFileInterface;
}

std::shared_ptr<UpgradeFile> UpgradeFileInterface::GetObj ( std::string infilename )
{
  upgrade_file_header_t upgrade_file_header;

  if ( 0 != GetFile ( infilename, upgrade_file_header ) )
    return  std::make_shared<UpgradeNull> ( infilename );

  auto iter = m_mapGetUpgradeFileObj.find ( upgrade_file_header.fileType );

  if ( iter != m_mapGetUpgradeFileObj.end() )
    return ( iter->second ) ( infilename );

  return std::make_shared<UpgradeNull> ( infilename );
}

int UpgradeFileInterface::GetFile ( std::string infilename, upgrade_file_header_t& upgrade_file_header )
{
  std::ifstream ifs ( infilename, std::ifstream::binary );

  if ( !ifs )
    return ERROR_UPGRADEFILE_NOEXIST;

  ifs.read ( reinterpret_cast<char*> ( &upgrade_file_header ), sizeof ( upgrade_file_header_t ) );

  if ( ( sizeof ( upgrade_file_header_t ) != ifs.gcount() )
       && ( !CheckFileHeader ( upgrade_file_header ) ) )
  {
    return ERROR_UPGRADEFILE_HEADER;
  }

  if ( UPGRADE_FILE_MAGIC_NUM != upgrade_file_header.magicNum )
    return ERROR_UPGRADEFILE_MAGICNUM;

  system ( "sync;echo 3 > /proc/sys/vm/drop_caches;" );

  std::vector<char> vechar;
  vechar.resize ( upgrade_file_header.fileCompressSize, 0 );

  ifs.read ( &vechar[0], vechar.size() );

  if ( upgrade_file_header.fileCrc != crc32 ( 0, reinterpret_cast<unsigned char*> ( &vechar[0] ), vechar.size() ) )
  {
    fprintf ( stderr, "fileCrc Error!\n" );
    return ERROR_UPGRADEFILE_CRC;
  }

  return 0;
}

bool UpgradeFileInterface::CheckFileHeader ( upgrade_file_header_t& upgrade_file_header )
{
  unsigned int* p = reinterpret_cast<unsigned int*> ( &upgrade_file_header );
  unsigned int chksum = 0;

  for ( unsigned int i = 1; i < sizeof ( upgrade_file_header_t ) / sizeof ( int ); ++i )
    chksum += p[i];

  if ( upgrade_file_header.hearderChksum == chksum )
    return true;

  return false;
}

int UpgradeFileInterface::HandleUpgradeFile ( std::string infilename, pUpgradeCbk cbk )
{
  int ret = 0;
  Locker locker ( & g_UpgradeFileMutex );

  SetUpgradeFlag ( true );
  ret = GetInstance()->GetObj ( infilename )->HandleFile ( cbk );
  SetUpgradeFlag ( false );

  system ( "sync;" );

  return ret;
}

