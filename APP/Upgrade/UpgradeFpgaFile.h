/*
 * =====================================================================================
 *
 *       Filename:  UpgradeFpgaFile.h
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

#ifndef  UPGRADEFPGAFILE_INC
#define  UPGRADEFPGAFILE_INC

#include <string>

#include "UpgradeFile.h"

#define FPGA_SOFT_NAME  "/app/fpga_ecp3.bit"

class UpgradeFpgaFile : public UpgradeFile
{
  public:
    explicit UpgradeFpgaFile ( std::string infilename );
    virtual ~UpgradeFpgaFile();

    virtual int HandleFile ( pUpgradeCbk cbk );

    static std::shared_ptr<UpgradeFile> GetObj ( std::string infilename );
};


#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */


