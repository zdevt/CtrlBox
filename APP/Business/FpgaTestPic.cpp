/*
 * =====================================================================================
 *
 *       Filename:  FpgaTestPic.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月05日 20时39分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <string.h>
#include <fstream>

#include "FpgaTestPic.h"
#include "FpgaDev.h"
#include "FpgaReg.h"
#include "LogPrint.h"
#include "FileHandle.h"
#include "BmpHandle.h"

mapiDispDdrAddr_t FpgaTestPic::m_mapiDispDdrAddr =
{
  { 0,                {"FPGABase",        0x00000000, 0x00000000, 0x00} },
  { 1,                {"GammaTable0",     0x00600000, 0x00300000, 0x00} },
  { 2,                {"GammaTable1",     0x00601000, 0x00300800, 0x00} },
  { 3,                {"GammaTable2",     0x00602000, 0x00301000, 0x00} },
  { 4,                {"GammaTable3",     0x00603000, 0x00301800, 0x00} },
  { 5,                {"GammaTable4",     0x00604000, 0x00302000, 0x00} },
  { 6,                {"GammaTable5",     0x00605000, 0x00302800, 0x00} },
  { 7,                {"DDR2Base",        0x00000000, 0x00000000, 0x00} },
  { FPGA_PIC_SXGA,    {"LogoSxgaPlus",    0x00100000, 0x00c00000, 0x00} },
  { FPGA_PIC_XGA,     {"LogoXga",         0x00100000, 0x01800000, 0x00} },
  { 10,               {"OSDBackground",   0x00000000, 0x00000000, 0x00} },
  { 11,               {"OSDContrl",       0x00200000, 0x00100000, 0x00} },
  { 12,               {"OSDForeground",   0x00400000, 0x00200000, 0x00} },
  { FPGA_LBC,         {"BrightnessComp",  0x00697800, 0x00380000, 0x00} },
  { FPGA_TEST_PIC,    {"TestPicture",     0x00800000, 0x00800000, 0x00} },
  { USER_DEF_DSK0,    {"UserDefDesktop",  0x00000000, 0x00800000, 0x03} },
  { USER_DEF_DSK1,    {"UserDefDesktop1", 0x00800000, 0x00800000, 0x03} },
  { USER_DEF_DSK2,    {"UserDefDesktop2", 0x00000000, 0x00800000, 0x10} },
  { USER_DEF_DSK3,    {"UserDefDesktop3", 0x00800000, 0x00800000, 0x10} },
  { USER_DEF_DSK4,    {"UserDefDesktop4", 0x00000000, 0x00800000, 0x11} },
  { USER_DEF_DSK5,    {"UserDefDesktop5", 0x00800000, 0x00800000, 0x11} },
};

mapFpgaEcp3DdrAddr_t FpgaTestPic::m_mapFpgaEcp3DdrAddr =
{
  { FPGA_PIC_SXGA, 0x1  },
  { FPGA_PIC_XGA,  0x1  },
  { FPGA_LBC,  	   0x0  },
  { FPGA_TEST_PIC, 0x08 },
  { USER_DEF_DSK0, 0x30 },
  { USER_DEF_DSK1, 0x38 },
  { USER_DEF_DSK2, 0x40 },
  { USER_DEF_DSK3, 0x48 },
  { USER_DEF_DSK4, 0x50 },
  { USER_DEF_DSK5, 0x58 },

};

#if 0
{ 0, 0 },   /*  DRGB */
{ 1, 2 },   /*  测试园 */
{ 2, 3 },   /*  棋盘格 */
{ 3, 4 },   /*  256灰阶 */
{ 4, 5 },   /*  彩条 */
{ 5, 6 },   /*  黑色 */
{ 6, 7 },   /*  白色 */
{ 7, 8 },   /*  红 */
{ 8, 9 },   /*  绿 */
{ 9, 10 },  /*  蓝 */
{ 10, 11 }, /*  青 */
{ 11, 12 }, /*  紫 */
{ 12, 13 }, /*  黄 */
{ 13, 14 }, /*  纵向八级灰阶 */
{ 14, 15 }, /*  横向八级灰阶 */
{ 15, 16 }, /*   */
#endif

FpgaTestPic::FpgaTestPic()
{

}

FpgaTestPic::~FpgaTestPic()
{

}

bool FpgaTestPic::WriteBmpFileToFpgaEcp3 ( std::string filename, int addr )
{
  auto iter = m_mapFpgaEcp3DdrAddr.find ( addr );

  if ( iter == m_mapFpgaEcp3DdrAddr.end() )
    return false;

  BmpFileHeader  	fileHeader;
  BmpInfo        	infoHeader;
  std::ifstream ifs ( filename.c_str(), std::ifstream::binary );

  vechar_t vecharData;
  BmpHandle::GetBmp ( filename, fileHeader, infoHeader,	vecharData );

  int bmpBit = infoHeader.bBitCount;

  fpga_reg_pic_type_t fpga_reg_pic_type;
  fpga_reg_pic_type.data = FpgaGetReg ( FPGA_REG_PIC_TYPE );

  if ( FPGA_TEST_PIC == addr ) /*  test pic  */
  {
    if ( 1 == bmpBit )
      fpga_reg_pic_type.test = 1;
    else
      fpga_reg_pic_type.test = 0;
  }
  else
  {
    if ( 1 == bmpBit )
      fpga_reg_pic_type.logo = 1;
    else
      fpga_reg_pic_type.logo = 0;
  }

  FpgaSetReg ( FPGA_REG_PIC_TYPE, fpga_reg_pic_type.data );

  #if 0

  if ( 1 == bmpBit )
    FPGASetColorTypeRegister ( 5 ); /* 1bit bmp */
  else
    FPGASetColorTypeRegister ( 0 ); /* 24bit bmp */

  #endif

  FpgaSetReg ( FPGA_REG_DDR2_EX_ADDR, iter->second );

  uint32_t writeByte = vecharData.size();

  if ( writeByte % 0x10 )
  {
    writeByte = ( writeByte / 0x10 + 1 ) * 0x10;
    vecharData.resize ( writeByte, 0 );
  }

  fpga_datan_t fpga_datan;
  fpga_datan.offset = 0;
  fpga_datan.cnt = writeByte;

  vecharData.insert ( vecharData.begin(),
                      reinterpret_cast<char*> ( &fpga_datan ),
                      reinterpret_cast<char*> ( &fpga_datan ) + sizeof ( fpga_datan ) );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Bmp %s a=%d b=%d n=%d!\n",
              filename.c_str(), addr, bmpBit, writeByte );

  FPGA_DDR_SET_REGN ( &vecharData[0] );

  #if 0
  FPGASetDDR2WriteOnOff ( DISABLE );
  usleep ( 11 * 1000 );
  FPGAArmWriteContol ( DISABLE );
  FPGAConfigDdrLockReg ( ENABLE );
  usleep ( 50 * 1000 );
  #endif

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Bmp %d Done!\n", addr );

  system ( "sync;echo 3 > /proc/sys/vm/drop_caches;" );
  return false;
}

bool FpgaTestPic::WriteBmpFileToFpga ( std::string filename, int addr )
{
  auto iter = m_mapiDispDdrAddr.find ( addr );

  if ( iter == m_mapiDispDdrAddr.end() )
    return false;

  BmpFileHeader  	fileHeader;
  BmpInfo        	infoHeader;
  uint32_t        imgDataOffset = 0;

  std::ifstream ifs ( filename.c_str(), std::ifstream::binary );

  if ( !ifs )
    return false;

  ifs.read ( reinterpret_cast<char*> ( &fileHeader ), sizeof ( fileHeader ) );

  if ( fileHeader.bType != 0x4d42 )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Error Bmp Type = 0x%04x\n", fileHeader.bType );
    return false;
  }

  ifs.read ( reinterpret_cast<char*> ( &infoHeader ), sizeof ( infoHeader ) );

  int bmpBit = infoHeader.bBitCount;

  fpga_reg_pic_type_t fpga_reg_pic_type;
  fpga_reg_pic_type.data = FpgaGetReg ( FPGA_REG_PIC_TYPE );

  if ( FPGA_TEST_PIC == addr ) /*  test pic  */
  {
    if ( 1 == bmpBit )
      fpga_reg_pic_type.test = 1;
    else
      fpga_reg_pic_type.test = 0;

    PRINT_LOG ( LOG_LEVEL_NORMAL, "TestPic Bit=%d\n", bmpBit );
  }
  else
  {
    if ( 1 == bmpBit )
      fpga_reg_pic_type.logo = 1;
    else
      fpga_reg_pic_type.logo = 0;

    PRINT_LOG ( LOG_LEVEL_NORMAL, "Logo Bit=%d\n", bmpBit );
  }

  FpgaSetReg ( FPGA_REG_PIC_TYPE, fpga_reg_pic_type.data );

  #if 0

  if ( 1 == bmpBit )
    FPGASetColorTypeRegister ( 5 ); /* 1bit bmp */
  else
    FPGASetColorTypeRegister ( 0 ); /* 24bit bmp */

  #endif

  uint32_t bytesPerLine =   ( infoHeader.bWidth * bmpBit ) / 8  ;
  uint32_t totalBytesPerLine = ( ( bytesPerLine + 3 ) / 4 ) * 4;
  uint32_t totalLine = infoHeader.bHeight;
  imgDataOffset = fileHeader.bOffset;

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Start Write Bmp %d bit=%d offset=%d!\n", addr, bmpBit, fileHeader.bOffset );

  FPGAConfigDdrLockReg ( DISABLE );
  FPGAArmWriteContol ( ENABLE );
  FPGASetDDR2WriteOnOff ( ENABLE );
  FPGASetDDR2ExtendAddress ( iter->second.ExAddr );

  /*  一次写几行的数据 必须为偶数*/
  const int oneTimeWriteLine = 2;

  vechar_t vechar;
  vechar.resize ( oneTimeWriteLine * bytesPerLine + sizeof ( fpga_datan_t ), 0 );

  fpga_datan_t* pfpga_datan = reinterpret_cast<fpga_datan_t*> ( &vechar[0] );
  pfpga_datan->offset = iter->second.CpuAddr;

  /* cnt datan的个数，datan为short */
  pfpga_datan->cnt = ( bytesPerLine * oneTimeWriteLine ) / 2;

  int totalWriteCnt = totalLine / oneTimeWriteLine;

  PRINT_LOG ( LOG_LEVEL_NORMAL, "totalLine = %d cnt=%d\n", totalLine, pfpga_datan->cnt );

  for ( int32_t i = 0; i < totalWriteCnt; ++i )
  {
    //ifs.seekg ( imgDataOffset + oneTimeWriteLine * totalBytesPerLine * i, ifs.beg ); /*  反 */
    ifs.seekg ( imgDataOffset + oneTimeWriteLine * totalBytesPerLine * ( totalWriteCnt - 1 - i ),
                ifs.beg ); /*  正 */

    for ( uint32_t j = 0; j < oneTimeWriteLine; ++j )
      ifs.read ( reinterpret_cast<char*> ( &vechar[0] + sizeof ( fpga_datan_t ) + bytesPerLine * ( oneTimeWriteLine - 1 - j ) ),
                 bytesPerLine );

    FPGA_DDR_SET_REGN ( pfpga_datan );
    pfpga_datan->offset += oneTimeWriteLine * bytesPerLine;
  }

  ifs.close();

  FPGASetDDR2WriteOnOff ( DISABLE );
  usleep ( 11 * 1000 );
  FPGAArmWriteContol ( DISABLE );
  FPGAConfigDdrLockReg ( ENABLE );
  usleep ( 50 * 1000 );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Write Bmp %d Done!\n", addr );

  system ( "sync;echo 3 > /proc/sys/vm/drop_caches;" );
  return false;
}

bool FpgaTestPic::WriteBmpLogo ( std::string filename, int addr )
{
  return GET_MBPTR->WriteBmpFileToFpga ( filename, addr );
}

bool FpgaTestPic::WriteBmpTestPic ( std::string filename, int addr )
{
  FpgaSetReg ( FPGA_REG_CIRCLE_COLOR1__H, ( FPGA_TEST_PIC_0_COLOR & 0xff0000 ) >> 16 );
  FpgaSetReg ( FPGA_REG_CIRCLE_COLOR1__L, ( FPGA_TEST_PIC_0_COLOR & 0xffff ) );
  FpgaSetReg ( FPGA_REG_CIRCLE_COLOR0__H, ( FPGA_TEST_PIC_1_COLOR & 0xff0000 ) >> 16 );
  FpgaSetReg ( FPGA_REG_CIRCLE_COLOR0__L, ( FPGA_TEST_PIC_1_COLOR & 0xffff ) );

  return GET_MBPTR->WriteBmpFileToFpga ( filename, addr );
}

bool FpgaTestPic::WriteBmpUserDef ( std::string filename, int picNo )
{
  if ( ( picNo < 0 ) || ( picNo > 5 ) )
    return false;

  return GET_MBPTR->WriteBmpFileToFpga ( filename, USER_DEF_DSK0 + picNo );
}

