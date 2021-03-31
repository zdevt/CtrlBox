/*
 * =====================================================================================
 *
 *       Filename:  UpgradeFile.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/29/2014 09:42:11 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */
#ifndef  UPGRADEFILE_INC
#define  UPGRADEFILE_INC

#include <vector>
#include <string>
#include <memory>

#include "Common.h"
#include "LogPrint.h"

#define MAX_UPGRADE_FILE            (10*1024*1024)      /* 升级文件最大限制 */


enum UPGRADEFILE_ERR
{
  ERROR_UPGRADEFILE_NOEXIST     = 0x0001,
  ERROR_UPGRADEFILE_TOOLARGE,
  ERROR_UPGRADEFILE_ERROR,
  ERROR_UPGRADEFILE_HEADER,
  ERROR_UPGRADEFILE_CRC,
  ERROR_UPGRADEFILE_UNCOMPRESS,
  ERROR_UPGRADEFILE_MAGICNUM,
  ERROR_UPGRADEFILE_SAVE,
};

typedef void ( *pUpgradeCbk ) ( int, int ); /* currentPercent, totalPercent */

class UpgradeFile
{
  public:
    explicit UpgradeFile ( std::string infilename );
    virtual ~UpgradeFile();

    virtual int HandleFile ( pUpgradeCbk cbk ) = 0;

    int UnCompress ( std::vector<char>& vecharOut ); /*  解压到内存 */
    int WriteFile ( std::string filename ); /*  内部解压写文件 */
    int WriteFile ( std::string filename, std::vector<char>& vecharFileData ); /*  内存buffer写到文件 */

    int GetFileNo();

  private:
    void ReadFileHeader();
    int ReadFile ( std::vector<char>& vecharFile );

  private:
    std::string m_infilename;
    upgrade_file_header_t m_fileHeader;
};


#endif   /* ----- #ifndef UPGRADE_INC  ----- */


