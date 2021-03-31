/*
 * =====================================================================================
 *
 *       Filename:  UpgradeFileInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/03/2015 09:49:28 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  UPGRADEFILEINTERFACE_INC
#define  UPGRADEFILEINTERFACE_INC

#include <memory>
#include <map>

#include "UpgradeFile.h"
#include "Common.h"
#include "UpgradeFileInterface.h"


typedef std::shared_ptr<UpgradeFile> ( *pGetUpgradeFileObj ) ( std::string );
typedef std::map<int, pGetUpgradeFileObj> mapGetUpgradeFileObj_t;

enum UPG_FILE_TYPE_E
{
  UPG_FILE_BOOTLOADER     = 0x00,
  UPG_FILE_MAINAPP        = 0x01,
  UPG_FILE_FPGA           = 0x02,
  UPG_FILE_ROOTFS         = 0x03,
  UPG_FILE_KERNEL         = 0x04,
  UPG_FILE_LOGO           = 0x05,
  UPG_FILE_TEST_PIC       = 0x06,
  UPG_FILE_USERDEFDESK    = 0x07, /* 文件编号只允许0-5 */
  UPG_FILE_ENGINEID       = 0x08,
  UPG_FILE_ENGINELBC      = 0x09,

  UPG_FILE_MAX,
};

class UpgradeFileInterface
{
  public:
    UpgradeFileInterface();
    ~UpgradeFileInterface();

  public:
    static int HandleUpgradeFile ( std::string infilename, pUpgradeCbk cbk = NULL );
    static bool GetUpgradeFlag( );

  private:
    static std::shared_ptr<UpgradeFileInterface> GetInstance();
    static void SetUpgradeFlag ( bool flag );

    std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
    int GetFile ( std::string infilename, upgrade_file_header_t& upgread_file_header );
    bool CheckFileHeader ( upgrade_file_header_t& upgrade_file_header );

  private:
    static mapGetUpgradeFileObj_t m_mapGetUpgradeFileObj;
    static std::shared_ptr<UpgradeFileInterface> m_UpgradeFileInterface;
    static bool m_upgradeFlag;
};

#endif   /* ----- #ifndef UPGRADEFILEINTERFACE_INC  ----- */

