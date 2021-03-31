/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineP3A_SXGAP.h
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

#ifndef  OPTICENGINEP3A_SXGAP_INC
#define  OPTICENGINEP3A_SXGAP_INC

#include <string>

#include "OpticEngine.h"
#include "DmdDdp442XInterface.h"
#include "OpticEngineP3A.h"

/*   */
#define  OPTIC_ENGINE_P3A_SXGAP_NAME   "YO_VATG_P3AHD"

class OpticEngineP3A_SXGAP : public OpticEngineP3A
{
  public:
    explicit OpticEngineP3A_SXGAP ( std::string engineName );
    virtual ~OpticEngineP3A_SXGAP();

  public:
    virtual uint32_t GetEngineRes ( int& width, int& height );

    virtual int WriteLogoAndTestPic();

    virtual int WriteLogo() ;
    virtual int WriteTestPic() ;

    virtual int SetFpgaPixel( );

    virtual int SetPowerState ( uint8_t state );
    virtual int GetPowerState ( uint8_t& state );


    virtual uint8_t* GetEdid ( );

    static std::shared_ptr<OpticEngine> GetObj ( std::string engineName );
};

#endif

