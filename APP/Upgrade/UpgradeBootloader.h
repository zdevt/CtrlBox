/*
 * =====================================================================================
 *
 *       Filename:  UpgradeBootloader.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/30/2014 02:43:34 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  UPGRADEBOOTLOADER_INC
#define  UPGRADEBOOTLOADER_INC

#include <string>

#include "UpgradeFile.h"

#define BOOTLOADER_SOFT_NAME  "/app/bootloader.bin"

class UpgradeBootloader : public UpgradeFile
{
  public:
    explicit UpgradeBootloader ( std::string infilename );
    virtual ~UpgradeBootloader();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};


#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */


