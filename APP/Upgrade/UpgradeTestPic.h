/*
 * =====================================================================================
 *
 *       Filename:  UpgradeTestPic.h
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

#ifndef  UPGRADETESTPIC_INC
#define  UPGRADETESTPIC_INC

#include <string>

#include "UpgradeFile.h"

class UpgradeTestPic : public UpgradeFile
{
  public:
    explicit UpgradeTestPic ( std::string infilename );
    virtual ~UpgradeTestPic();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};


#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */


