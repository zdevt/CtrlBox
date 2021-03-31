/*
 * =====================================================================================
 *
 *       Filename:  UpgradeMainApp.h
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

#ifndef  UPGRADEMAINAPP_INC
#define  UPGRADEMAINAPP_INC

#include <string>

#include "UpgradeFile.h"

#define APP_SOFT_NAME  "/app/MAINAPP"

class UpgradeMainApp : public UpgradeFile
{
  public:
    explicit UpgradeMainApp ( std::string infilename );
    virtual ~UpgradeMainApp();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};


#endif   /* ----- #ifndef UPGRADEMAINAPP_INC  ----- */

