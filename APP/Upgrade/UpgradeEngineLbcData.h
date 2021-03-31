/*
 * =====================================================================================
 *
 *       Filename:  UpgradeEngineLbcData.h
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

#ifndef  UPGRADEENGINELBCDATA_INC
#define  UPGRADEENGINELBCDATA_INC

#include <string>

#include "UpgradeFile.h"

#define LBCDATA_SOFT_NAME  "/app/lbcdata.bin"

class UpgradeEngineLbcData : public UpgradeFile
{
  public:
    explicit UpgradeEngineLbcData ( std::string infilename );
    virtual ~UpgradeEngineLbcData();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};

#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */

