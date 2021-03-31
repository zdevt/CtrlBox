/*
 * =====================================================================================
 *
 *       Filename:  DmdDdp442XInterface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 10:49:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <vector>

#include "DmdDdp442XInterface.h"
#include "LogPrint.h"

pthread_mutex_t DmdDdp442XInterface::m_DmdDdp442XInterfaceMutex = PTHREAD_MUTEX_INITIALIZER;

DmdDdp442XInterface::DmdDdp442XInterface()
{

}

DmdDdp442XInterface::~DmdDdp442XInterface()
{

}

int DmdDdp442XInterface::SetCommand ( uint8_t subaddr, uint8_t* pdata, uint32_t len )
{
  int ret = _SetCommand ( subaddr, pdata, len );
  int i = 0;

  while ( ( ret < 0 ) && ( ++i < 20 ) )
  {
    ret = _SetCommand ( subaddr, pdata, len );
    usleep ( 50 * 1000 );
  }

  if ( ret < 0 )
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Write error ret %d,subaddr 0x%x\n", ret, subaddr );

  return ret;
}

int DmdDdp442XInterface::_SetCommand ( uint8_t subaddr, uint8_t* pdata, uint32_t len )
{
  int ret = -1;

  if ( !pdata )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "NULL==pdata\n" );
    return -1;
  }

  ret = I2cBusInterface::Write ( DMDDDP442X_I2CBUS,
                                 DDP442X_I2C_SLAVE_ADDR, subaddr, pdata,
                                 len, I2C_SUB_ADDR_8_BIT );

  usleep ( 1 * 1000 );
  return ret;
}


int DmdDdp442XInterface::GetCommand ( uint8_t subaddr, uint8_t* pReadParam, uint32_t paramLen,
                                      uint8_t* pRead, uint32_t readLen )
{
  int ret = _GetCommand ( subaddr, pReadParam, paramLen, pRead, readLen );
  int i = 0;

  while ( ( ret < 0 ) && ( ++i < 20 ) )
  {
    ret = _GetCommand ( subaddr, pReadParam, paramLen, pRead, readLen );
    usleep ( 50 * 1000 );
  }

  if ( ret < 0 )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "read error ret %d, subaddr 0x%x\n", ret, subaddr );
  }

  return ret;
}

int DmdDdp442XInterface::_GetCommand ( uint8_t subaddr, uint8_t* pReadParam, uint32_t paramLen,
                                       uint8_t* pRead, uint32_t readLen )
{
  int ret = -1;

  if ( !pRead )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "NULL==pRead\n" );
    return -1;
  }

  /* 先写参数 */
  if ( !pReadParam )
  {
    ret = I2cBusInterface::Write ( DMDDDP442X_I2CBUS,
                                   DDP442X_I2C_SLAVE_ADDR, DDP442X_GET_REG_SUBADDR, &subaddr,
                                   1, I2C_SUB_ADDR_8_BIT );

    if ( ret < 0 )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "write cmd error ret %d,subaddr 0x%x\n",
                  ret, subaddr );
      return -1;
    }
  }
  else
  {
    std::vector<uint8_t> vecuint8;
    vecuint8.insert ( vecuint8.begin(), pReadParam, pReadParam + paramLen );
    vecuint8.insert ( vecuint8.begin(), subaddr );

    ret = I2cBusInterface::Write ( DMDDDP442X_I2CBUS,
                                   DDP442X_I2C_SLAVE_ADDR, DDP442X_GET_REG_SUBADDR,
                                   &vecuint8[0], vecuint8.size(),
                                   I2C_SUB_ADDR_8_BIT );

    if ( ret < 0 )
    {
      PRINT_LOG ( LOG_LEVEL_NORMAL, "write cmd error ret %d,subaddr 0x%x\n",
                  ret, subaddr );
      return -1;
    }
  }

  usleep ( 10 * 1000 );

  ret = I2cBusInterface::Read ( DMDDDP442X_I2CBUS,
                                DDP442X_I2C_SLAVE_ADDR, DDP442X_GET_REG_SUBADDR,
                                pRead, readLen,
                                I2C_SUB_ADDR_8_BIT );

  return ret;
}

int DmdDdp442XInterface::SetImageFlip ( uint8_t mode )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_IMAGE_FLIP_SUBADDR, &mode, 1 );
}

int DmdDdp442XInterface::GetImageFlip ( uint8_t& mode )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_IMAGE_FLIP_SUBADDR, NULL, 0, &mode, 1 );
}

int DmdDdp442XInterface::SetAlgorithmEnable ( uint8_t value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_ALGORITHM_ENABLE_SUBADDR, &value, 1 );
}

int DmdDdp442XInterface::GetAlgorithmEnable ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_ALGORITHM_ENABLE_SUBADDR, NULL, 0, &value, 1 );
}

//#define DDP442X_ALGORITHM_ENABLE_SUBADDR   (0x14)
int DmdDdp442XInterface::SetBrightness ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_BRIGHTNESS_SUBADDR, pSet, 2 );
}

int DmdDdp442XInterface::GetBrightness ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_BRIGHTNESS_SUBADDR, NULL, 0, pGet, 2 );
}

//#define DDP442X_BRIGHTNESS_SUBADDR         (0x16)
int DmdDdp442XInterface::SetContrast ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_CONTRAST_SUBADDR, pSet, 2 );
}

int DmdDdp442XInterface::GetContrast ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_CONTRAST_SUBADDR, NULL, 0, pGet, 2 );
}

//#define DDP442X_SIP_P2W_SHARPNESS          (0x98)
int DmdDdp442XInterface::SetSipP2wSharpness ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_SHARPNESS, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wSharpness ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_SHARPNESS, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_PROJ_MODE                  (0xe9)
int DmdDdp442XInterface::SetSipP2wProjMode ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_PROJ_MODE, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wProjMode ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_PROJ_MODE, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_SIG_SHOW           (0xea)
int DmdDdp442XInterface::SetSipP2wSigShow ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_SIG_SHOW, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wSigShow ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_SIG_SHOW, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_HIGHLAND_MODE      (0xeb)
int DmdDdp442XInterface::SetSipP2wHighlandMode ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_HIGHLAND_MODE, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wHighlandMode ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_HIGHLAND_MODE, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_TEST_PIC           (0xec)
int DmdDdp442XInterface::SetSipP2wTestPic ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_TEST_PIC, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wTestPic ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_TEST_PIC, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_AdjuestRgbCurrent  (0xf4)
int DmdDdp442XInterface::SetSipP2wAdjuestRgbCurrent ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_AdjuestRgbCurrent, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wAdjuestRgbCurrent ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_AdjuestRgbCurrent, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_RESET_ADJUST       (0xf6)
int DmdDdp442XInterface::SetSipP2wResetAdjust ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_RESET_ADJUST, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wResetAdjust ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_RESET_ADJUST, NULL, 0, &value, 1 );
}

//define DDP442X_SIP_P2W_OPEN_METHOD        (0xf5)
int DmdDdp442XInterface::SetSipP2wOpenMethod ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_OPEN_METHOD, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wOpenMethod ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_OPEN_METHOD, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_OPEN               (0x84)
int DmdDdp442XInterface::SetSipP2wOpen ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_OPEN, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wOpen ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_OPEN, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_REMOTE_CONTROL     (0xee)
int DmdDdp442XInterface::SetSipP2wRemoteControl ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_REMOTE_CONTROL, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wRemoteControl ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_REMOTE_CONTROL, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_HSG                (0xef)
int DmdDdp442XInterface::SetSipP2wHsg ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_HSG, pSet, 7 );
}

int DmdDdp442XInterface::GetSipP2wHsg ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_HSG, NULL, 0, pGet, 7 );
}

//#define DDP442X_SIP_P2W_OVERLAP            (0xf7)
int DmdDdp442XInterface::SetSipP2wOverLap ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_SIP_P2W_OVERLAP, &value, 1 );
}

int DmdDdp442XInterface::GetSipP2wOverLap ( uint8_t& value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_OVERLAP, NULL, 0, &value, 1 );
}

//#define DDP442X_SIP_P2W_TEMPERATURE         (0xf8)
int DmdDdp442XInterface::GetSipP2wTemperature ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_SIP_P2W_TEMPERATURE, NULL, 0, pGet, 4 );
}

int DmdDdp442XInterface::SetHsgAdjustment ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_HSG_ADJUST_SUBADDR, pSet, 42 );
}

int DmdDdp442XInterface::GetHsgAdjustment ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_HSG_ADJUST_SUBADDR, NULL, 0, pGet, 42 );
}

int DmdDdp442XInterface::SetRedLedDac ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_RED_LED_DAC_SUBADDR, pSet, 20 );
}

int DmdDdp442XInterface::GetRedLedDac ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_RED_LED_DAC_SUBADDR, NULL, 0, pGet, 20 );
}

/* 3.13 Green DAC */
int DmdDdp442XInterface::SetGreenLedDac ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_GREEN_LED_DAC_SUBADDR, pSet, 20 );
}

int DmdDdp442XInterface::GetGreenLedDac ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_GREEN_LED_DAC_SUBADDR, NULL, 0, pGet, 20 );
}

/* 3.14 Blue DAC */
int DmdDdp442XInterface::SetBlueLedDac ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_BLUE_LED_DAC_SUBADDR, pSet, 20 );
}

int DmdDdp442XInterface::GetBlueLedDac ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_BLUE_LED_DAC_SUBADDR, NULL, 0, pGet, 20 );
}

int DmdDdp442XInterface::Set3D ( uint8_t* pSet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_3D_SUBADDR, pSet, 1 );
}

int DmdDdp442XInterface::Get3D ( uint8_t* pGet )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_3D_SUBADDR, NULL, 0, pGet, 1 );
}

/* 相当于以前设置显示模式，显示来源 */
int DmdDdp442XInterface::SetChannelSource ( uint8_t type )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_CHANNEL_SOURCE_SUBADDR, &type, 1 );
}

int DmdDdp442XInterface::GetChannelSource ( uint8_t& type )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_CHANNEL_SOURCE_SUBADDR, NULL, 0, &type, 1 );
}

/* 3.27 gammba table 0-6 */
int DmdDdp442XInterface::SetGammaTable ( uint8_t index )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_GAMMA_TABLE_SUBADDR, &index, 1 );
}

int DmdDdp442XInterface::GetGammaTable ( uint8_t* index )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_GAMMA_TABLE_SUBADDR, NULL, 0, index, 1 );
}

int DmdDdp442XInterface::SetSystemMode ( uint8_t index )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  int ret = 0;
  uint8_t data[2] = { 0 };

  data[0] = index;
  data[1] = 0;

  ret = SetCommand ( DDP442X_SYSTEM_MODE_SUBADDR, data, 2 );

  return ret;
}

int DmdDdp442XInterface::GetSystemMode ( uint8_t* index  )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  int ret = -1;
  uint8_t data[2] = { 0 };
  ret = GetCommand ( DDP442X_SYSTEM_MODE_SUBADDR, NULL, 0, data, 2 );

  if ( ret == 0 )
    *index = data[0];

  return ret;
}

int DmdDdp442XInterface::GetDmdTemp ( int16_t* temp )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  uint8_t data[2];
  memset ( data, 0, 2 );
  GetCommand ( DDP442X_DMD_TEMP_SUBADDR, NULL, 0, data, 2 );
  *temp = * ( int16_t* ) ( data );
  return 0;
}

int DmdDdp442XInterface::SetCalibrationEnable ( uint8_t flag )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_CALIBRATION_ENABLE_SUBADDR, &flag, 1 );
}

int DmdDdp442XInterface::GetDriverVersion ( uint8_t* pVersion )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_DRIVER_VERSION_SUBADDR, NULL, 0, pVersion, 12 );
}

int DmdDdp442XInterface::GetFirmwareVersion ( uint8_t* pVersion )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_FIRMWARE_VERSION_SUBADDR, NULL, 0, pVersion, 4 );
}

int DmdDdp442XInterface::SetDutycycle ( uint8_t value )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_DUTYCYCLE_SUBADDR, &value, 1 );
}

int DmdDdp442XInterface::GetDutycycle ( uint8_t* pValue )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_DUTYCYCLE_SUBADDR, NULL, 0, pValue, 1 );
}

int DmdDdp442XInterface::GetDutycycleValue ( uint8_t* p )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_DUTYCYCLE_VALUE_SUBADDR, NULL, 0, p, 20 );
}

int DmdDdp442XInterface::SetColorBrightness ( uint8_t* pBrightness )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_COLOR_BRIGHTNESS_SUBADDR, pBrightness, 6 );
}

int DmdDdp442XInterface::GetColorBrightness ( uint8_t* pBrightness )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_COLOR_BRIGHTNESS_SUBADDR, NULL, 0, pBrightness, 6 );
}

int DmdDdp442XInterface::SetColorContrast ( uint8_t* pContrast )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_COLOR_CONTRAST_SUBADDR, pContrast, 3 );
}

int DmdDdp442XInterface::GetColorContrast ( uint8_t* pContrast )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_COLOR_CONTRAST_SUBADDR, NULL, 0, pContrast, 3 );
}

int DmdDdp442XInterface::SetColorOffset ( uint8_t* pOffset )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_COLOR_OFFSET_SUBADDR, pOffset, 6 );
}

int DmdDdp442XInterface::GetColorOffset ( uint8_t* pOffset )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_COLOR_OFFSET_SUBADDR, NULL, 0, pOffset, 6 );
}

int DmdDdp442XInterface::SetBackGroundDisplay ( uint8_t* pVal )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_BACKGROUND_DISPLAY_SUBADDR, pVal, 2 );
}

int DmdDdp442XInterface::GetLedTempVA ( uint8_t* pTemp )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_LED_STATUS_SUBADDR, NULL, 0, pTemp, 10 );
}

int DmdDdp442XInterface::GetLedTempThin ( uint8_t index, int32_t* temp )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  uint8_t data[2];
  memset ( data, 0, 2 );
  GetCommand ( DDP442X_LED_TEMP_THIN_SUBADDR, &index, 1, data, 2 );
  *temp = ( ( data[1] << 8 ) | ( data[0] ) );

  return 0;
}

int DmdDdp442XInterface::Set3DEnable ( uint8_t flag )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_3D_ENABLE_SUBADDR, &flag, 1 );
}

int DmdDdp442XInterface::GetInternalSensor ( uint8_t* pValue )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_INTERNAL_SENSOR_SUBADDR, NULL, 0, pValue, 10 );
}

int DmdDdp442XInterface::GetThinCoordinate ( uint8_t* pValue )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_THIN_COORDINATE_SUBADDR, NULL, 0, pValue, 12 );
}

int DmdDdp442XInterface::GetLampLit ( uint8_t* status )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_THIN_LAMP_LIT_SUBADDR, NULL, 0, status, 1 );
}

int DmdDdp442XInterface::SetWpcMode ( uint8_t* pmode )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_WPC_MODE, pmode, 1 );
}

int DmdDdp442XInterface::SetWpcTarget ( uint8_t* pTarget )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_WPC_TARGET, pTarget, 12 );
}

int DmdDdp442XInterface::SetCCATarget ( uint8_t* pTarget )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return SetCommand ( DDP442X_CCA_TARGET, pTarget, 13 );
}

int DmdDdp442XInterface::SetFanPwm ( uint8_t fanid, uint8_t pwm ) /*  0:; 1:led driver; 2:led,; 3: */
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  uint8_t pTarget[2];
  pTarget[0] = fanid;
  pTarget[1] = pwm;

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Set fan %d pwm %d, subaddr 0x%x\n", fanid, pwm, DDP442X_DMD_FAN_PWM_SUBADDR );
  return SetCommand ( DDP442X_DMD_FAN_PWM_SUBADDR, pTarget, 2 );
}

int DmdDdp442XInterface::GetFanPwm ( uint8_t fanid, uint8_t& pwm )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_DMD_FAN_PWM_SUBADDR, &fanid, 1, &pwm, 1 );
}

int DmdDdp442XInterface::SetFanSpeed ( uint8_t fanid, uint16_t speed )
{
  /*  TODO  */
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return 0;
}

int DmdDdp442XInterface::GetFanSpeed ( uint8_t fanid, uint16_t& speed )
{
  Locker locker ( &m_DmdDdp442XInterfaceMutex );
  return GetCommand ( DDP442X_DMD_FAN_SPEED_SUBADDR, &fanid, 1, reinterpret_cast<uint8_t*> ( &speed ), 2 );
}

