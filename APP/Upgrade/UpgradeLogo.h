/*
 * =====================================================================================
 *
 *       Filename:  UpgradeLogo.h
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

#ifndef  UPGRADELOGO_INC
#define  UPGRADELOGO_INC

#include <string>

#include "UpgradeFile.h"

class UpgradeLogo : public UpgradeFile
{
  public:
    explicit UpgradeLogo ( std::string infilename );
    virtual ~UpgradeLogo();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};

#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */

