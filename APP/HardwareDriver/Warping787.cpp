/*
 * =====================================================================================
 *
 *       Filename:  Warping787.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/21/2016 02:00:18 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "Warping787.h"
#include "I2cBusInterface.h"
#include "LogPrint.h"
#include "OpticEngineInterface.h"

Warping787::Warping787 ( )
{
}

Warping787::~Warping787 ( )
{
}

int Warping787::GetOnline ( void* parg, std::string i2cbus )
{
  return 0;
}

int Warping787::SetResol ( uint32_t width, uint32_t height )
{
  return 0;
}

int Warping787::GetResol ( uint32_t& width, uint32_t& height )
{
  return 0;
}

int Warping787::SetWarpingData ( uint32_t grid, uint32_t datalen, uint8_t* data )
{
  uint8_t* p = reinterpret_cast<uint8_t*> ( data );
  int ret = 0;
  std::vector<uint8_t> vec8;

  const int packLen = 2995;
  int totalpack = datalen / packLen;

  if ( datalen % packLen )
    totalpack += 1;

  vec8.resize ( packLen + sizeof ( warping787_data_t ) + 1, 0 );
  warping787_data_t* pwarping787_data = reinterpret_cast<warping787_data_t*> ( &vec8[0] );

  pwarping787_data->grid = grid;

  for ( int i = 0 ; i < totalpack; ++i )
  {
    pwarping787_data->no = i;

    if ( i != totalpack - 1 )
      pwarping787_data->len = packLen;
    else
      pwarping787_data->len = datalen % packLen;

    memcpy ( pwarping787_data->data, p + i * packLen, pwarping787_data->len );

    vec8[vec8.size() - 1] = 0xff; /*  cksum  */

    ret = I2cBusInterface::Write ( WARPING787_BUS, WARPING787_SLAVE, WARPING787_WPLG_DATA, &vec8[0], vec8.size(), 0x1 );

    if ( ret != 0 )
      PRINT_LOG ( LOG_LEVEL_NORMAL, "i = %d ret=%d no=%d\n", i, ret, pwarping787_data->no );

    usleep ( 150 * 1000 ); /* 787处理延时 */
  }

  return 0;
}

int Warping787::SetLutCoeff ( uint8_t* hlut, uint8_t* vlut )
{
  return 0;
}

int Warping787::SetWplgCoeff ( uint32_t* wplg )
{
  std::vector<uint8_t> vec8;
  uint8_t* p = reinterpret_cast<uint8_t*> ( wplg );
  vec8.insert ( vec8.begin(), p, p + sizeof ( uint32_t ) * 9 );
  vec8.insert ( vec8.begin(), 0 );
  vec8.push_back ( 0xff );

  int ret = I2cBusInterface::Write ( WARPING787_BUS, WARPING787_SLAVE, WARPING787_WPLG_ADDR, &vec8[0], vec8.size(), 0x1 );
  PRINT_LOG2 ( "ret = %d \n", ret );

  return 0;
}

int Warping787::SetLutSet ( uint32_t lutset )
{
  uint8_t data = ( uint8_t ) ( lutset );
  int ret = I2cBusInterface::Write ( WARPING787_BUS, WARPING787_SLAVE,
                                     WARPING787_LUT_SET, &data, 1, 0x1 );

  PRINT_LOG2 ( "ret = %d \n", ret );

  return 0;
}

int Warping787::SetRes ( )
{
  int ret = 0;
  int width = 0;
  int height = 0;
  GET_ENGPTR->GetEngineRes ( width, height );

  uint8_t data = 0;

  if ( ( 1920 == width ) && ( 1080 == height ) )
    data = 0;
  else if ( ( 1366 == width ) && ( 768 == height ) )
    data = 1;
  else if ( ( 1360 == width ) && ( 768 == height ) )
    data = 1;
  else if ( ( 1600 == width ) && ( 1200 == height ) )
    data = 2;
  else if ( ( 1400 == width ) && ( 1050 == height ) )
    data = 3;
  else if ( ( 1024 == width ) && ( 768 == height ) )
    data = 4;

  uint8_t verh = 1;
  //uint8_t verm, verl, verr;
  //Warping787::GetVer ( verh, verm, verl, verr );

  if ( verh < 2 )
    ret = I2cBusInterface::Write ( WARPING787_BUS, WARPING787_SLAVE,
                                   WARPING787_RES_SET, &data, 1, 0x1 );
  else
    ret = Warping787::SetResol ( data );

  PRINT_LOG2 ( "verh=%02x ret = %d \n", verh, ret );
  return ret;
}

int Warping787::SetWarpingCoor ( void* p )
{
  return WriteData ( WARPING787_DATA_NEW, 0x40, reinterpret_cast<uint8_t*> ( p ) );
}

int Warping787::GetWarpingCoor ( void* p )
{
  return ReadData ( WARPING787_DATA_NEW, 0x40, reinterpret_cast<uint8_t*> ( p ) );
}

int Warping787::WriteData ( uint8_t chipSubaddr, uint16_t ndata, uint8_t* pdata,
                            uint8_t res5, uint8_t res6, uint8_t res7 )
{
  int ret = -1;

  std::vector<uint8_t> vecharCmd;
  vecharCmd.resize ( 7, 0 );
  vecharCmd[0] = 0;
  vecharCmd[1] = chipSubaddr;
  vecharCmd[2] = ( ( ndata + 3 ) & 0xff00 ) >> 8;
  vecharCmd[3] = ( ndata + 3 ) & 0xff;
  vecharCmd[4] = res5;
  vecharCmd[5] = res6;
  vecharCmd[6] = res7;

  ret = I2cBusInterface::Write ( WARPING787_BUS, WARPING787_SLAVE, 0,
                                 &vecharCmd[0], vecharCmd.size(), 0x1 );

  std::vector<uint8_t> vechardata;
  #if 1
  vechardata.resize ( ndata + 2, 0 );
  vechardata[0] = 0xaa;
  vechardata[1] = 0x55;

  std::copy ( pdata, pdata + ndata, &vechardata[2] );
  #else
  vechardata.resize ( 0, 0 );
  vechardata.push_back ( 0xaa );
  vechardata.push_back ( 0x55 );
  vechardata.insert ( vechardata.end(), pdata, pdata + ndata );
  #endif

  ret = I2cBusInterface::Write ( WARPING787_BUS, WARPING787_SLAVE, chipSubaddr,
                                 &vechardata[0], vechardata.size(), 0x1 );

  return ret;
}

int Warping787::ReadData ( uint8_t chipSubaddr, uint16_t ndata, uint8_t* pdata,
                           uint8_t res5, uint8_t res6, uint8_t res7 )
{
  int ret = -1;

  std::vector<uint8_t> vecharCmd;
  vecharCmd.resize ( 7, 0 );
  vecharCmd[0] = 0x1;
  vecharCmd[1] = chipSubaddr;
  vecharCmd[2] = ( ( ndata + 2 ) & 0xff00 ) >> 8;
  vecharCmd[3] = ( ndata + 2 ) & 0xff;
  vecharCmd[4] = res5;
  vecharCmd[5] = res6;
  vecharCmd[6] = res7;

  ret = I2cBusInterface::Write ( WARPING787_BUS, WARPING787_SLAVE, 0x0,
                                 &vecharCmd[0], vecharCmd.size(), 0x1 );

  usleep ( 30 * 1000 );

  std::vector<uint8_t> vechardata;
  vechardata.resize ( ndata + 2, 0 );

  ret = I2cBusInterface::Read ( WARPING787_BUS, WARPING787_SLAVE, chipSubaddr,
                                &vechardata[0], vechardata.size(), 0x1 );

  std::copy ( &vechardata[2], &vechardata[2] + ndata, pdata );

  return ret;
}

int Warping787::GetVer ( uint8_t& verh, uint8_t& verm, uint8_t& verl, uint8_t& verr )
{
  uint8_t p[4] = { 0 };
  ReadData ( WARPING787_VER_NEW, 0x4, p );
  verh = p[0];
  verm = p[1];
  verl = p[2];
  verr = p[3];

  return 0;
}

int Warping787::SetResol ( uint8_t& resNo )
{
  return WriteData ( WARPING787_RES_NEW, 0x1, &resNo );
}

int Warping787::GetResol ( uint8_t& resNo )
{
  return ReadData ( WARPING787_RES_NEW, 0x1, &resNo );
}

int Warping787::UCSetEnable ( uint8_t enable )
{
  return WriteData ( WARPING787_UC_ENABLE, 0x1, &enable );
}

int Warping787::UCGetEnable ( uint8_t& enable )
{
  return ReadData ( WARPING787_UC_ENABLE, 0x1, &enable );
}

int Warping787::UCSelectPos ( uint8_t x, uint8_t y )
{
  if ( x == 0xff && y == 0xff )
  {
    uint8_t cancel = 0;
    return WriteData ( WARPING787_UC_CANCELSELPOS, 0x1, &cancel );
  }
  else
  {
    uint8_t pos[2] = {x, y};
    return WriteData ( WARPING787_UC_SELPOS, 0x2, pos );
  }
}

int Warping787::UCSetGain ( uint8_t level, uint8_t color, uint8_t x, uint8_t y, uint16_t gain )
{
  uint8_t data[6] = {level, color, x, y, ( uint8_t ) gain, ( uint8_t ) ( gain >> 8 ) };
  return WriteData ( WARPING787_UC_GAIN, 0x6, data );
}

int Warping787::UCSetAllGain ( uint8_t level, uint32_t gainNum, uint16_t* gainData )
{
  return WriteData ( WARPING787_UC_ALLGAIN, gainNum * 2, reinterpret_cast<uint8_t*> ( gainData ), level );
}

int Warping787::UCGetAllGain ( uint8_t level, uint32_t gainNum, uint16_t* gainData )
{
  ReadData ( WARPING787_UC_ALLGAIN, gainNum * 2, reinterpret_cast<uint8_t*> ( gainData ), level );
  return 0;
}

int Warping787::UCResetGain()
{
  uint8_t reset = 1;
  return WriteData ( WARPING787_UC_RESET, 0x1, &reset );
}

