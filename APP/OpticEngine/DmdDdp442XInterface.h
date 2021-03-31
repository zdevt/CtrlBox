/*
 * =====================================================================================
 *
 *       Filename:  DmdDdp442XInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 10:49:10 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  DMDDDP442XINTERFACE_INC
#define  DMDDDP442XINTERFACE_INC

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <pthread.h>
#include <arpa/inet.h>

#include "I2cBusInterface.h"
#include "DmdDdp442xReg.h"
#include "Locker.h"
#include "XmlConfig.h"
#include "MainboardInterface.h"

#define DMDDDP442X_I2CBUS       GET_MBPTR->GetDmdI2cBus()


class DmdDdp442XInterface
{
  private:
    DmdDdp442XInterface();
    ~DmdDdp442XInterface();

  public:
    static int SetSystemMode ( uint8_t index );
    static int GetSystemMode ( uint8_t* index  );

    static int SetGammaTable ( uint8_t index );
    static int GetGammaTable ( uint8_t* index );

    static int SetImageFlip ( uint8_t mode );
    static int GetImageFlip ( uint8_t& mode );

    //#define DDP442X_ALGORITHM_ENABLE_SUBADDR   (0x14)
    static int SetAlgorithmEnable ( uint8_t value );
    static int GetAlgorithmEnable ( uint8_t& value );

    //#define DDP442X_BRIGHTNESS_SUBADDR         (0x16)
    static int SetBrightness ( uint8_t* pSet );
    static int GetBrightness ( uint8_t* pGet );

    //#define DDP442X_CONTRAST_SUBADDR           (0x17)
    static int SetContrast ( uint8_t* pSet );
    static int GetContrast ( uint8_t* pGet );

    //#define DDP442X_SIP_P2W_SHARPNESS          (0x98)
    static int SetSipP2wSharpness ( uint8_t& value );
    static int GetSipP2wSharpness ( uint8_t& value );

    //#define DDP442X_SIP_P2W_PROJ_MODE                  (0xe9)
    static int SetSipP2wProjMode ( uint8_t& value );
    static int GetSipP2wProjMode ( uint8_t& value );

    //#define DDP442X_SIP_P2W_SIG_SHOW           (0xea)
    static int SetSipP2wSigShow ( uint8_t& value );
    static int GetSipP2wSigShow ( uint8_t& value );

    //#define DDP442X_SIP_P2W_HIGHLAND_MODE      (0xeb)
    static int SetSipP2wHighlandMode ( uint8_t& value );
    static int GetSipP2wHighlandMode ( uint8_t& value );

    //#define DDP442X_SIP_P2W_TEST_PIC           (0xec)
    static int SetSipP2wTestPic ( uint8_t& value );
    static int GetSipP2wTestPic ( uint8_t& value );

    //#define DDP442X_SIP_P2W_AdjuestRgbCurrent  (0xf4)
    static int SetSipP2wAdjuestRgbCurrent ( uint8_t& value );
    static int GetSipP2wAdjuestRgbCurrent ( uint8_t& value );

    //#define DDP442X_SIP_P2W_RESET_ADJUST       (0xf6)
    static int SetSipP2wResetAdjust ( uint8_t& value );
    static int GetSipP2wResetAdjust ( uint8_t& value );

    //define DDP442X_SIP_P2W_OPEN_METHOD        (0xf5)
    static int SetSipP2wOpenMethod ( uint8_t& value );
    static int GetSipP2wOpenMethod ( uint8_t& value );

    //#define DDP442X_SIP_P2W_OPEN               (0x84)
    static int SetSipP2wOpen ( uint8_t& value );
    static int GetSipP2wOpen ( uint8_t& value );

    //#define DDP442X_SIP_P2W_REMOTE_CONTROL     (0xee)
    static int SetSipP2wRemoteControl ( uint8_t& value );
    static int GetSipP2wRemoteControl ( uint8_t& value );

    //#define DDP442X_SIP_P2W_HSG                (0xef)
    static int SetSipP2wHsg ( uint8_t* pSet );
    static int GetSipP2wHsg ( uint8_t* pSet );

    //#define DDP442X_SIP_P2W_OVERLAP            (0xf7)
    static int SetSipP2wOverLap ( uint8_t& value );
    static int GetSipP2wOverLap ( uint8_t& value );

    //#define DDP442X_SIP_P2W_TEMPERATURE         (0xf8)
    static int GetSipP2wTemperature ( uint8_t* pGet );

    static int SetHsgAdjustment ( uint8_t* pSet );
    static int GetHsgAdjustment ( uint8_t* pGet );

    static int SetRedLedDac ( uint8_t* pSet );
    static int GetRedLedDac ( uint8_t* pGet );

    static int SetGreenLedDac ( uint8_t* pSet );
    static int GetGreenLedDac ( uint8_t* pGet );

    static int SetBlueLedDac ( uint8_t* pSet );
    static int GetBlueLedDac ( uint8_t* pGet );

    static int Set3D ( uint8_t* pSet );
    static int Get3D ( uint8_t* pGet );

    static int SetChannelSource ( uint8_t type );
    static int GetChannelSource ( uint8_t& type );

    static int GetDmdTemp ( int16_t* temp );

    static int SetCalibrationEnable ( uint8_t flag );
    static int GetDriverVersion ( uint8_t* pVersion );
    static int GetFirmwareVersion ( uint8_t* pVersion );

    static int SetDutycycle ( uint8_t value );
    static int GetDutycycle ( uint8_t* pValue );
    static int GetDutycycleValue ( uint8_t* p );

    static int SetColorBrightness ( uint8_t* pBrightness );
    static int GetColorBrightness ( uint8_t* pBrightness );

    static int SetColorContrast ( uint8_t* pContrast );
    static int GetColorContrast ( uint8_t* pContrast );

    static int SetColorOffset ( uint8_t* pOffset );
    static int GetColorOffset ( uint8_t* pOffset );

    static int SetBackGroundDisplay ( uint8_t* pVal );

    static int GetLedTempVA ( uint8_t* pTemp ); /*  442x 一般光机，获取driver，r，g，b，温度电压，电流等 */
    static int GetLedTempThin ( uint8_t index, int32_t* temp ); /*  超薄光机rgb温度只能在这个获取 */

    static int Set3DEnable ( uint8_t flag );
    static int GetInternalSensor ( uint8_t* pValue );
    static int GetThinCoordinate ( uint8_t* pValue );
    static int GetLampLit ( uint8_t* status );

    static int SetWpcMode ( uint8_t* pmode );
    static int SetWpcTarget ( uint8_t* pTarget );

    static int SetCCATarget ( uint8_t* pTarget );

    static int SetFanPwm ( uint8_t fanid, uint8_t pwm ); /*  0:; 1:led driver; 2:led,; 3: */
    static int GetFanPwm ( uint8_t fanid, uint8_t& pwm );

    static int SetFanSpeed ( uint8_t fanid, uint16_t speed );
    static int GetFanSpeed ( uint8_t fanid, uint16_t& speed );

    static int SetCommand ( uint8_t subaddr, uint8_t* pdata, uint32_t len );
    static int GetCommand ( uint8_t subaddr, uint8_t* pReadParam, uint32_t paramLen, uint8_t* pRead, uint32_t readLen );

  private:
    static int _SetCommand ( uint8_t subaddr, uint8_t* pdata, uint32_t len );
    static int _GetCommand ( uint8_t subaddr, uint8_t* pReadParam, uint32_t paramLen, uint8_t* pRead, uint32_t readLen );

  private:
    static pthread_mutex_t m_DmdDdp442XInterfaceMutex;
};

#endif   /* ----- #ifndef DmdDdp442XInterface.h_INC  ----- */

