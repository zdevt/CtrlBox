/*
 * =====================================================================================
 *
 *       Filename:  UpgradeNull.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/2015 06:04:11 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  UPGRADENULL_INC
#define  UPGRADENULL_INC

#include <string>

#include "UpgradeFile.h"


class UpgradeNull : public UpgradeFile
{
  public:
    explicit UpgradeNull ( std::string infilename );
    virtual ~UpgradeNull();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );

};


#endif   /* ----- #ifndef UPGRADENULL_INC  ----- */

