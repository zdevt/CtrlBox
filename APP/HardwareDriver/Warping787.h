/*
 * =====================================================================================
 *
 *       Filename:  Warping787.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/21/2016 02:00:29 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  WARPING787_INC
#define  WARPING787_INC

#include <string>
#include <vector>

#include <stdint.h>

#define WARPING787_BUS          "/dev/i2c-0"
#define WARPING787_SLAVE   			(0x36)

#define WARPING787_WPLG_ADDR    (0x0a)
#define WARPING787_WPLG_DATA   	(0x0b)
#define WARPING787_LUT_SET      (0x0c)
#define WARPING787_RES_SET      (0x0d)

#define WARPING787_DATA_NEW     (0x0a)
#define WARPING787_RES_NEW     	(0x0d)
#define WARPING787_VER_NEW     	(0x0e)
#define WARPING787_UC_ENABLE    (0x0f)//UniformityCorrection Enable
#define WARPING787_UC_SELPOS    (0x10)
#define WARPING787_UC_CANCELSELPOS    (0x11)
#define WARPING787_UC_GAIN      (0x12)
#define WARPING787_UC_ALLGAIN   (0x13)
#define WARPING787_UC_RESET     (0x14)

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t no;
  uint8_t grid;
  uint16_t len;
  uint8_t data[0];
} warping787_data_t;
#pragma pack(pop)

class Warping787
{
  private:
    Warping787 ( );
    ~Warping787();

  public:
    static int GetOnline ( void* parg, std::string i2cbus = WARPING787_BUS );
    static int SetWarpingData ( uint32_t grid, uint32_t datalen, uint8_t* data );
    static int SetLutCoeff ( uint8_t* hlut, uint8_t* vlut );
    static int SetWplgCoeff ( uint32_t* wplg );
    static int SetLutSet ( uint32_t lutset );
    static int SetRes ( );

    static int SetWarpingCoor ( void* p );
    static int GetWarpingCoor ( void* p );

    static int GetVer ( uint8_t& verh, uint8_t& verm, uint8_t& verl, uint8_t& verr );

    static int SetResol ( uint8_t& resNo );
    static int GetResol ( uint8_t& resNo );

    static int SetResol ( uint32_t width, uint32_t height );
    static int GetResol ( uint32_t& width, uint32_t& height );

    static int UCSetEnable ( uint8_t enable );
    static int UCGetEnable ( uint8_t& enable );

    static int UCSelectPos ( uint8_t x, uint8_t y );

    static int UCSetGain ( uint8_t level, uint8_t color, uint8_t x, uint8_t y, uint16_t gain );
    static int UCSetAllGain ( uint8_t level, uint32_t gainNum, uint16_t* gainData );
    static int UCGetAllGain ( uint8_t level, uint32_t gainNum, uint16_t* gainData );
    static int UCResetGain();

  private:
    static int WriteData ( uint8_t chipSubaddr, uint16_t ndata, uint8_t* pdata,
                           uint8_t res5 = 0, uint8_t res6 = 0, uint8_t res7 = 0 );
    static int ReadData ( uint8_t chipSubaddr, uint16_t ndata, uint8_t* pdata,
                          uint8_t res5 = 0, uint8_t res6 = 0, uint8_t res7 = 0 );
};

#endif   /* ----- #ifndef I2CEEPROM_INC  ----- */

