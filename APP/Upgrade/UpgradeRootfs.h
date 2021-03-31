/*
 * =====================================================================================
 *
 *       Filename:  UpgradeRootfs.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/2015 05:57:52 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  UPGRADEROOTFS_INC
#define  UPGRADEROOTFS_INC

#include <string>

#include "UpgradeFile.h"

#define ROOTFS_SOFT_NAME  "/app/fs.tlz"

class UpgradeRootfs : public UpgradeFile
{
  public:
    explicit UpgradeRootfs ( std::string infilename );
    virtual ~UpgradeRootfs();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};


#endif   /* ----- #ifndef UPGRADEMAINAPP_INC  ----- */

