/*
 * =====================================================================================
 *
 *       Filename:  UpgradeEngineId.h
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

#ifndef  UPGRADEENGINEID_INC
#define  UPGRADEENGINEID_INC

#include <string>

#include "UpgradeFile.h"

class UpgradeEngineId : public UpgradeFile
{
  public:
    explicit UpgradeEngineId ( std::string infilename );
    virtual ~UpgradeEngineId();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};

#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */

