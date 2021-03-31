/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineDefault.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/30/2014 02:43:34 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  OPTICENGINEDEFAULT_INC
#define  OPTICENGINEDEFAULT_INC

#include <string>

#include "OpticEngine.h"
#include "DmdDdp3021Interface.h"

#define  OPTIC_ENGINE_DEFALUT_NAME   "YO_HHTG_P3WHD"

class OpticEngineDefault : public OpticEngine
{
  public:
    explicit OpticEngineDefault ( std::string engineName );
    virtual ~OpticEngineDefault();

  public:
    virtual uint32_t GetEngineRes ( int& width, int& height );
    virtual uint32_t GetEngineType();
    virtual uint32_t GetEnginePlatform();
    virtual uint32_t GetEngine2Dor3D();
    virtual int WriteLogoAndTestPic();

    virtual int WriteLogo();
    virtual int WriteTestPic();

    virtual int SetFpgaPixel( );

    virtual int SetPowerState ( uint8_t state );
    virtual int GetPowerState ( uint8_t& state );

    virtual int SetBcMode ( uint8_t mode );
    virtual int GetBcMode ( uint8_t& mode );

    virtual int SetDmdGamma ( uint8_t gammaType );
    virtual int GetDmdGamma ( uint8_t& gammaType );

    virtual int SetProjMode ( uint8_t mode );
    virtual int GetProjMode ( uint8_t& mode );

    virtual int SetColorOffset ( uint16_t r, uint16_t g, uint16_t b );
    virtual int GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b );

    virtual int SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b );
    virtual int GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b );

    virtual int SetColorContrast ( uint16_t r, uint16_t g, uint16_t b );
    virtual int GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b );

    virtual int SetDutycycle ( uint8_t dc );
    virtual int GetDutycycle ( uint8_t* dc );

    virtual int GetDutycycleValue ( void* p );

    virtual int SetHsgAdjustment ( void* hsg );
    virtual int GetHsgAdjustment ( void* hsg );

    virtual int SetLedDacRed ( void* p );
    virtual int SetLedDacRedBasic ( void* p );
    virtual int GetLedDacRedBasic ( void* p );
    virtual int GetLedDacRed ( void* p );

    virtual int SetLedDacGreen ( void* p );
    virtual int SetLedDacGreenBasic ( void* p );
    virtual int GetLedDacGreenBasic ( void* p );
    virtual int GetLedDacGreen ( void* p );

    virtual int SetLedDacBlue ( void* p );
    virtual int SetLedDacBlueBasic ( void* p );
    virtual int GetLedDacBlueBasic ( void* p );
    virtual int GetLedDacBlue ( void* p );

    virtual int LumCompStart();

    virtual int SetDspEffect ( uint32_t dspEffect );

    virtual int GetMaxDac ( void* p );

    virtual int GetDmdTemp ( int& temp );

    virtual int GetLedTemp ( int* ptemp );

    virtual int GetLedStatus ( void* p );

    virtual int SetWpcMode ( uint8_t mode );
    virtual int GetWpcMode ( uint8_t& mode );

    virtual int SetWpcTarget ( uint8_t* pTarget );
    virtual int GetWpcTarget ( uint8_t* pTarget );

    virtual int SetAlgorithmEnable ( uint8_t value );
    virtual int GetAlgorithmEnable ( uint8_t& value );

    virtual int SetCCATarget ( uint8_t* pTarget );
    virtual int GetCCATarget ( uint8_t* pTarget );

    virtual int SetDmdRegVal ( uint8_t subaddr, uint32_t datalen, uint8_t* data );
    virtual int GetDmdRegVal ( uint8_t subaddr, uint32_t paramlen, uint8_t* param, uint32_t datalen, uint8_t* data );

    virtual bool SetFanPwm ( uint8_t fanid, uint8_t pwm ); /*  0:; 1:led driver; 2:led,; 3: */
    virtual bool GetFanPwm ( uint8_t fanid, uint8_t& pwm );

    virtual bool SetFanSpeed ( uint8_t fanid, uint16_t speed );
    virtual bool GetFanSpeed ( uint8_t fanid, uint16_t& speed );

    virtual uint8_t* GetEdid ( );

    virtual int SetOverLap ( uint16_t overlap ) ;
    virtual int GetOverLap ( uint16_t& overlap ) ;

    virtual int GetFirmwareVersion ( uint32_t& version );

    static std::shared_ptr<OpticEngine> GetObj ( std::string engineName );
};

#endif   /* ----- #ifndef UPGRADEFPGAFILE_INC  ----- */

