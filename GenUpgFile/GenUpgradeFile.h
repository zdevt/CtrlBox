/*
 * =====================================================================================
 *
 *       Filename:  GenUpgradeFile.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/2015 12:41:03 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  GENUPGRADEFILE_INC
#define  GENUPGRADEFILE_INC

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <zlib.h>
#include <vector>
#include <string>

typedef struct
{
  char name[256];
} engine_id_t;

enum UPG_FILE_TYPE_E
{
  UPG_FILE_BOOTLOADER     = 0x00,
  UPG_FILE_MAINAPP        = 0x01,
  UPG_FILE_FPGA           = 0x02,
  UPG_FILE_ROOTFS         = 0x03,
  UPG_FILE_KERNEL         = 0x04,
  UPG_FILE_LOGO           = 0x05, /*  文件编号按分辨率区分 1:XGA 2:SXGA+ 3:1080P 4:... */
  UPG_FILE_TEST_PIC       = 0x06, /*  文件编号同上   */
  UPG_FILE_USERDEFDESK    = 0x07, /*  底层只有存6副自定义桌面的空间 */
  UPG_FILE_ENGINEID       = 0x08,

  UPG_FILE_LIGHT_COMPENSATION = 0x09, /*  亮度补偿文件 */

  UPG_FILE_MAX,
};


#define UPGRADE_FILE_MAGIC_NUM  (0xaa550001)

typedef struct
{
  uint32_t hearderChksum;
  uint32_t magicNum;  /* 0xaa550001 */
  uint32_t fileType;  /*  文件类型 */
  uint32_t fileNo;    /*  文件编号 */
  uint8_t verMajor;   /* Major.Sub.Min.Test */
  uint8_t verSub;
  uint8_t verMin;
  uint8_t verTest;
  uint32_t reserved[8];
  uint32_t fileUnCompressSize;
  uint32_t fileCompressSize;
  uint32_t fileCrc;
} upgrade_file_header_t;


class GenUpgradeFile
{
  public:
    GenUpgradeFile();
    ~GenUpgradeFile();

  public:
    int GenFile ( int argc, char* argv[] );

  private:
    int GenFile ( upgrade_file_header_t& upgrade_file_header, std::string infilename, std::string outfilename = "out.hs" );
    int ReadInputFile ( std::string infile );
    uint32_t CalcHeaderChkSum ( upgrade_file_header_t& upgrade_file_header );
    uint32_t CalcFileCrc ( char* buffer, int len );

  private:
    upgrade_file_header_t m_fileHeader;
    std::vector<char> m_vechar;
    std::vector<char> m_vecharCompress;
};


#endif   /* ----- #ifndef GENUPGRADEFILE_INC  ----- */

