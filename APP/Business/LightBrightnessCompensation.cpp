/*
 * =====================================================================================
 *
 *       Filename:  LightBrightnessCompensation.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年05月25日 16时03分22秒
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

#include "LightBrightnessCompensation.h"
#include "LogPrint.h"
#include "I2cBusInterface.h"
#include "FpgaReg.h"
#include "FileHandle.h"


LightBrightnessCompensation::LightBrightnessCompensation()
{

}

LightBrightnessCompensation::~LightBrightnessCompensation()
{

}

int LightBrightnessCompensation::WriteData ( uint32_t pageAddr, uint8_t* fileData, uint32_t filelen )
{
  uint32_t ret;

  if ( ( pageAddr % FLASH_BLOCK_PAGECOUNT ) != 0 )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "page is not block start  %d\n", pageAddr );
    return -1;
  }

  uint8_t flash_block_erase_cmd = FLASH_BLOCK_ERASE;
  uint32_t blockAddr = pageAddr;

  int blockCount = ( filelen / FLASH_BLOCK_SIZE );

  if ( ( filelen % FLASH_BLOCK_SIZE ) != 0 )
    blockCount++;

  for ( int i = 0; i < blockCount; i++ )
  {
    //flash block erase
    ret = I2cBusInterface::Write ( I2cBusInterface::GetBusName ( 1 ),
                                   FlashWriteAddr, ( blockAddr + i * FLASH_BLOCK_PAGECOUNT ),
                                   &flash_block_erase_cmd,
                                   sizeof ( flash_block_erase_cmd ), I2C_SUB_ADDR_16_BIT );
    usleep ( 500 * 1000 );

    if ( ret < 0 )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "flash  block erase failed ret=%d\n", ret );
      return ret;
    }
  }

  uint16_t checkdata = 0;
  uint8_t  dataBuffer[260];
  int integer = filelen / FLASH_PAGE;
  int leve = filelen % FLASH_PAGE;
  uint32_t datalen;

  PRINT_LOG ( LOG_LEVEL_NORMAL, "flash  erase ok ,integer=%d,leve=%d\n", integer, leve );

  usleep ( 50 * 1000 ); /// 延时50ms 以上。

  for ( int ii = 0; ii < integer; ++ii ) ///  整数下载
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "enter page write %d \n", ii );
    memset ( &dataBuffer, 0, FLASH_PAGE + 4 );
    memcpy ( ( void* ) ( dataBuffer + 1 ), ( void* ) ( fileData + ii * FLASH_PAGE ), FLASH_PAGE );

    checkdata = 0;

    for ( int mm = 0; mm < FLASH_PAGE; ++mm ) /// 逻辑是8BIT相加
      checkdata += * ( dataBuffer + 1 + mm );

    dataBuffer[0] = FLASH_PAGEWRIT; ///  写命令
    dataBuffer[FLASH_PAGE + 1] = checkdata >> 8;
    dataBuffer[FLASH_PAGE + 2] = checkdata & 0xff; ///  校验码

    datalen = FLASH_PAGE + sizeof ( uint16_t ) + 1; ///  259  uint8_t

    ret = I2cBusInterface::Write ( I2cBusInterface::GetBusName ( 1 ),
                                   FlashWriteAddr, ( pageAddr + ii ),
                                   dataBuffer, datalen,
                                   I2C_SUB_ADDR_16_BIT );

    if ( ret < 0 )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "write data %d to flash failed\n", ii );
      return ret;
    }

    usleep ( 50 * 1000 ); /// 延时50ms 以上。
    #if 0
    /*  改为等待信号 sem_wait */
    #endif
  }

  if ( leve != 0 )                         ///   零头 写
  {
    ret = WriteRemain ( pageAddr, fileData, filelen );

    if ( ret != 0 )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, " WriteRemain data to flash failed\n" );
      return ret;
    }

    #if 0
    /*  改为等待信号 sem_wait */
    #endif
  }

  return 0;
}

int LightBrightnessCompensation::WriteRemain ( uint32_t pageAddr, uint8_t* fileData, uint32_t filelen )
{
  uint32_t ret;
  uint32_t  datalen;
  uint16_t checkdata = 0;
  short  mm;
  uint8_t  dataBuffer[260];
  uint32_t integer = filelen / FLASH_PAGE ;
  uint32_t leve = filelen % FLASH_PAGE;

  uint8_t* local = NULL;

  PRINT_LOG ( LOG_LEVEL_NORMAL, " enter remain write %d \n", leve );
  memset ( &dataBuffer, 0, FLASH_PAGE + 4 ); ///  初始化

  pageAddr += integer;

  local = fileData + integer * FLASH_PAGE;

  memcpy ( ( void* ) ( dataBuffer + 1 ), ( void* ) local, leve );

  for ( mm = 0; mm < FLASH_PAGE; ++mm )
    checkdata += * ( dataBuffer + 1 + mm );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "checkdata=0x%x \n", checkdata );

  dataBuffer[0] = FLASH_PAGEWRIT;      ///  写命令

  dataBuffer[FLASH_PAGE + 1] = checkdata >> 8; ///  校验码
  dataBuffer[FLASH_PAGE + 2] = checkdata & 0xff;      ///  校验码

  datalen = FLASH_PAGE + sizeof ( uint16_t ) + 1; ///  259  uint8_t

  ret = I2cBusInterface::Write ( I2cBusInterface::GetBusName ( 1 ),
                                 FlashWriteAddr,  pageAddr,
                                 dataBuffer, datalen,
                                 I2C_SUB_ADDR_16_BIT );

  usleep ( 50 * 1000 ); /// 延时50ms 以上。
  return ret;
}

int LightBrightnessCompensation::ReadData ( uint32_t startAddr, uint8_t* fileData, uint32_t filelen )
{
  return 0;
}

int LightBrightnessCompensation::WriteDataToFPGA ( std::vector<char>& vechar )
{
  FPGADisableLBCControl();
  LBCFPGASetDDR2ExtendAddress ( LBCFPGA_REG_EXADDR );

  FPGAConfigDdrLockReg ( 0 );   /* 写之前设置为0,放开保护*/
  FPGAArmWriteContol ( 1 );
  FPGASetDDR2WriteOnOff ( 1 );

  if ( vechar.size() % 2 )
    vechar.resize ( vechar.size() + 1, 0 );

  fpga_datan_t fpga_datan;
  fpga_datan.offset = 0;

  if ( vechar.size() % 2 )
    vechar.resize ( vechar.size() + 1, 0 );

  fpga_datan.cnt = vechar.size() / 2;
  char* pTemp = reinterpret_cast<char*> ( &fpga_datan );
  vechar.insert ( vechar.begin(), pTemp, pTemp + sizeof ( fpga_datan ) );

  //FpgaDev::DdrSetRegN ( reinterpret_cast<fpga_datan_t*> ( &vechar[0] ) );
  FPGA_DDR_SET_REGN ( reinterpret_cast<fpga_datan_t*> ( &vechar[0] ) );

  FPGASetDDR2WriteOnOff ( 0 );

  usleep ( 10 * 1000 + 1 );     /* 延时10ms，确保写入完成后再禁止写入 */
  FPGAConfigDdrLockReg ( 1 );   /* 写之后设置为1,禁止修改,保护数据*/

  FPGAEnablePictureProcessControl ( 0x0020 ); /* 使能LBC */

  return 0;
}

int LightBrightnessCompensation::WriteDataToFPGA ( std::string filename )
{
  std::vector<char> vecharFile ;

  if ( !FileHandle::Read ( filename, vecharFile ) )
    return -1;

  WriteDataToFPGA ( vecharFile );
  return 0;
}

