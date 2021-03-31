/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageLogoAndDrgb.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月21日 14时36分15秒
 *  Last Modified:  2015年09月21日 14时36分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  FPGAIMAGELOGOANDDRGB_INC
#define  FPGAIMAGELOGOANDDRGB_INC

#include "FpgaImageHandle.h"

#define FPGAIMAGE_LOGO_INDEX   			(0)
#define FPGAIMAGE_LOGO_INDEX_BACK   (0xf)

class FpgaImageLogoAndDrgb : public FpgaImageHandle
{
  public:
    FpgaImageLogoAndDrgb();
    virtual ~FpgaImageLogoAndDrgb();

    virtual bool Handle ( int index );

    static void SetDoubleDesktopSwithMode ( int mode );
    static int GetDoubleDesktopSwithMode ( int mode );

  public:
    static std::shared_ptr<FpgaImageHandle> GetObj ( );
};

#endif   /* ----- #ifndef FpgaImageLogoAndDrgb.h ----- */

