/*
 * =====================================================================================
 *
 *       Filename:  UpgradeKernel.h
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

#ifndef  UPGRADEKERNEL_INC
#define  UPGRADEKERNEL_INC

#include <string>

#include "UpgradeFile.h"

#define KERNEL_SOFT_NAME  "/app/uImage_9G45.bin"

class UpgradeKernel : public UpgradeFile
{
  public:
    explicit UpgradeKernel ( std::string infilename );
    virtual ~UpgradeKernel();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};


#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */


