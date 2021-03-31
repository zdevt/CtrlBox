/*
 * =====================================================================================
 *
 *       Filename:  UpgradeUserDefDesk.h
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

#ifndef  UPGRADEUSERDEFDESK_INC
#define  UPGRADEUSERDEFDESK_INC

#include <string>

#include "UpgradeFile.h"

class UpgradeUserDefDesk : public UpgradeFile
{
  public:
    explicit UpgradeUserDefDesk ( std::string infilename );
    virtual ~UpgradeUserDefDesk();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};

#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */

