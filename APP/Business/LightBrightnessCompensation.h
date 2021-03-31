/*
 * =====================================================================================
 *
 *       Filename:  LightBrightnessCompensation.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年05月25日 16时03分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  LIGHTBRIGHTNESSCOMPENSATION_INC
#define  LIGHTBRIGHTNESSCOMPENSATION_INC

#include <stdint.h>
#include <vector>
#include <semaphore.h>

#include "FpgaDev.h"

#define  FlashWriteAddr         0xe0
#define  FLASH_ERASE            0xc7  ///< falsh 整片擦除  耗时 50MS
#define  FLASH_BLOCK_ERASE      0x52  ///< falsh 整块擦除  耗时 50MS
#define  FLASH_PAGEWRIT         0xad  ///< falsh  页写
#define  FLASH_PAGEREAD         0xd3  ///< falsh  页读

#define  FLASH_BLOCK_SIZE       (32*1024) //falsh  整块空间是32k
#define  FLASH_PAGE             256   ///< falsh  页大小
#define  FLASH_BLOCK_PAGECOUNT  128   ///< falsh  整块里有多少页

#define  MAX_WAIT_TIME          500

class LightBrightnessCompensation
{
  private:
    LightBrightnessCompensation();
    ~LightBrightnessCompensation();

  public:
    static int WriteData ( uint32_t startAddr, uint8_t* fileData, uint32_t filelen );
    static int ReadData ( uint32_t startAddr, uint8_t* fileData, uint32_t filelen );

    static int WriteDataToFPGA ( std::vector<char>& vechar );
    static int WriteDataToFPGA ( std::string filename );

  private:
    static int WriteRemain ( uint32_t pageAddr, uint8_t* fileData, uint32_t filelen );

  private:
    static sem_t m_sem;
};


#endif   /* ----- #ifndef LightBrightnessCompensation.h ----- */

