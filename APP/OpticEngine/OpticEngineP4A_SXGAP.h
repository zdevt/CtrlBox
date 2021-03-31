/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineP4A_SXGAP.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/26/2018 03:51:43 PM
 *  Last Modified:  07/26/2018 03:51:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  OPTICENGINEP4A_SXGAP_INC
#define  OPTICENGINEP4A_SXGAP_INC

#include <string>

#include "OpticEngine.h"
#include "DmdDdp442XInterface.h"
#include "OpticEngineP4A.h"

/*   */
#define  OPTIC_ENGINE_P4A_SXGAP_NAME   "YO_VATG_P3AHD"

class OpticEngineP4A_SXGAP : public OpticEngineP4A
{
  public:
    explicit OpticEngineP4A_SXGAP ( std::string engineName );
    virtual ~OpticEngineP4A_SXGAP();

  public:
    virtual uint32_t GetEngineRes ( int& width, int& height );

    virtual int WriteLogoAndTestPic();

    virtual int WriteLogo() ;
    virtual int WriteTestPic() ;

    virtual int SetFpgaPixel( );

    virtual uint8_t* GetEdid ( );

    static std::shared_ptr<OpticEngine> GetObj ( std::string engineName );
};

#endif   /* ----- #ifndef OpticEngineP4A_SXGAP.h ----- */

