/*
 * =====================================================================================
 *
 *       Filename:  OpticEngine.h
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
#ifndef  OPTICENGINE_INC
#define  OPTICENGINE_INC

#include <vector>
#include <string>
#include <memory>
#include <stdint.h>

#include "FpgaImageSwitch.h"
#include "LogPrint.h"
#include "XmlConfig.h"
#include "FpgaDev.h"
#include "FpgaTestPic.h"
#include "FpgaDev.h"
#include "Ics307.h"
#include "Led74Hc595D.h"

#define MAX_DAC_VAL    (4095)

enum ENGINE_RES_TYPE_E
{
  OPTIC_ENGINE_RES_XGA          = 1,
  OPTIC_ENGINE_RES_SXGA,
  OPTIC_ENGINE_RES_1080P,

  OPTIC_ENGINE_RES_MAX,
};

enum ENGINE_TYPE_E
{
  OPTIC_ENGINE_TYPE_LED         = 1,

  OPTIC_ENGINE_TYPE_MAX,
};

enum ENGINE_PLATFORM_E
{
  OPTIC_ENGINE_PLATFORM_DDP3021  = 1,
  OPTIC_ENGINE_PLATFORM_DDP442X,

  OPTIC_ENGINE_PLATFORM_MAX,
};

enum ENGINE_2D_3D_E
{
  OPTIC_ENGINE_2D                = 1,
  OPTIC_ENGINE_3D,

  OPTIC_ENGINE2D3D_MAX,
};

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint16_t g;
  uint16_t r;
  uint16_t b;
} color_offset_cfg_t;

typedef struct
{
  uint16_t r;
  uint16_t g;
  uint16_t b;
} brightness_cfg_t;

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} contrast_cfg_t;

typedef struct
{
  uint16_t redDac;
  uint16_t greenDac;
  uint16_t blueDac;
  uint16_t sub0Dac;
  uint16_t sub1Dac;
  uint16_t yellowDac;
  uint16_t cyanDac;
  uint16_t magentaDac;
  uint16_t whiteDac;
  uint16_t blackDac;
} dac_cfg_t;

typedef struct
{
  uint16_t r;
  uint16_t g;
  uint16_t b;

  bool IsValid()
  {
    return ( ( r <= MAX_DAC_VAL ) && ( g <= MAX_DAC_VAL ) && ( b <= MAX_DAC_VAL ) );
  }
} dac_t;

typedef struct
{
  uint16_t rGain;
  uint16_t rSturation;
  uint16_t rHue;

  uint16_t gGain;
  uint16_t gSturation;
  uint16_t gHue;

  uint16_t bGain;
  uint16_t bSturation;
  uint16_t bHue;

  uint16_t cGain;
  uint16_t cSturation;
  uint16_t cHue;

  uint16_t mGain;
  uint16_t mSturation;
  uint16_t mHue;

  uint16_t yGain;
  uint16_t ySturation;
  uint16_t yHue;

  uint16_t wGain;
  uint16_t wSturation;
  uint16_t wHue;
} hsg_cfg_t;

#pragma pack(pop)

class OpticEngine
{
  public:
    explicit OpticEngine ( std::string enginename );
    virtual ~OpticEngine();

  public:
    std::string GetEngineName();

    virtual uint32_t GetEngineRes ( int& width, int& height ) = 0;
    virtual uint32_t GetEngineType() = 0;
    virtual uint32_t GetEnginePlatform() = 0;
    virtual uint32_t GetEngine2Dor3D() = 0;
    virtual int WriteLogoAndTestPic() = 0;

    virtual int WriteLogo() = 0;
    virtual int WriteTestPic() = 0;

    virtual int SetFpgaPixel( ) = 0;

    virtual int SetPowerState ( uint8_t state ) = 0;
    virtual int GetPowerState ( uint8_t& state ) = 0;

    virtual int SetBcMode ( uint8_t mode ) = 0;
    virtual int GetBcMode ( uint8_t& mode ) = 0;

    virtual int SetDmdGamma ( uint8_t gammaType ) = 0;
    virtual int GetDmdGamma ( uint8_t& gammaType ) = 0;

    virtual int SetProjMode ( uint8_t mode ) = 0;
    virtual int GetProjMode ( uint8_t& mode ) = 0;

    virtual int SetColorOffset ( uint16_t r, uint16_t g, uint16_t b ) = 0;
    virtual int GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b ) = 0;

    virtual int SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b ) = 0;
    virtual int GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b ) = 0;

    virtual int SetColorContrast ( uint16_t r, uint16_t g, uint16_t b ) = 0;
    virtual int GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b ) = 0;

    virtual int SetDutycycle ( uint8_t dc ) = 0;
    virtual int GetDutycycle ( uint8_t* dc ) = 0;
    virtual int GetDutycycleValue ( void* p ) = 0;

    virtual int SetHsgAdjustment ( void* hsg ) = 0;
    virtual int GetHsgAdjustment ( void* hsg ) = 0;

    virtual int SetLedDacRed ( void* p ) = 0;
    virtual int SetLedDacRedBasic ( void* p ) = 0;
    virtual int GetLedDacRedBasic ( void* p ) = 0;
    virtual int GetLedDacRed ( void* p ) = 0;

    virtual int SetLedDacGreen ( void* p ) = 0;
    virtual int SetLedDacGreenBasic ( void* p ) = 0;
    virtual int GetLedDacGreenBasic ( void* p ) = 0;
    virtual int GetLedDacGreen ( void* p ) = 0;

    virtual int SetLedDacBlue ( void* p ) = 0;
    virtual int SetLedDacBlueBasic ( void* p ) = 0;
    virtual int GetLedDacBlueBasic ( void* p ) = 0;
    virtual int GetLedDacBlue ( void* p ) = 0;

    virtual int LumCompStart() = 0;

    virtual int SetDspEffect ( uint32_t dspEffect ) = 0;

    virtual int GetMaxDac ( void* p ) = 0;

    virtual int GetDmdTemp ( int& temp ) = 0;

    virtual int GetLedTemp ( int* ptemp ) = 0;

    virtual int GetLedStatus ( void* p ) = 0;

    virtual int SetWpcMode ( uint8_t mode ) = 0;
    virtual int GetWpcMode ( uint8_t& mode ) = 0;

    virtual int SetWpcTarget ( uint8_t* pTarget ) = 0;
    virtual int GetWpcTarget ( uint8_t* pTarget ) = 0;

    virtual int SetAlgorithmEnable ( uint8_t value ) = 0;
    virtual int GetAlgorithmEnable ( uint8_t& value ) = 0;

    virtual int SetCCATarget ( uint8_t* pTarget ) = 0;
    virtual int GetCCATarget ( uint8_t* pTarget ) = 0;

    virtual int SetDmdRegVal ( uint8_t subaddr, uint32_t datalen, uint8_t* data ) = 0;
    virtual int GetDmdRegVal ( uint8_t subaddr, uint32_t paramlen, uint8_t* param, uint32_t datalen, uint8_t* data ) = 0;

    virtual bool SetWorkTime ( );
    virtual bool SetWorkTime ( uint32_t workTime );
    virtual bool GetWorkTime ( uint32_t& workTime );

    virtual bool SetUsePeriodEnable ( uint8_t enable );
    virtual bool GetUsePeriodEnable ( );

    virtual bool SetUsePeriod ( uint32_t usePeriodInSec );
    virtual bool GetUsePeriod ( uint32_t& usePeriodInSec );
    virtual bool GetUsePeriodRemain ( uint32_t& usePeriodInSecRemain );

    virtual bool GetUsePeriodStartTime ( uint32_t& startTime );
    virtual bool CheckUsePeriodValid( );

    virtual bool SetFanPwm ( uint8_t fanid, uint8_t pwm ) = 0; /*  0:; 1:led driver; 2:led,; 3: */
    virtual bool GetFanPwm ( uint8_t fanid, uint8_t& pwm ) = 0;

    virtual bool SetFanSpeed ( uint8_t fanid, uint16_t speed ) = 0;
    virtual bool GetFanSpeed ( uint8_t fanid, uint16_t& speed ) = 0;

    virtual uint8_t* GetEdid ( ) = 0;

    virtual int SetOverLap ( uint16_t overlap ) = 0;
    virtual int GetOverLap ( uint16_t& overlap ) = 0;

    virtual int GetFirmwareVersion ( uint32_t& version ) = 0;

    virtual int Check();

  private:
    std::string m_enginename;
};

#endif   /* ----- #ifndef OpticEngine.h ----- */

