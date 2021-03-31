/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageFpga.h
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
#ifndef  FPGAIMAGEFPGA_INC
#define  FPGAIMAGEFPGA_INC

#include "FpgaImageHandle.h"

class FpgaImageFpga : public FpgaImageHandle
{
  public:
    FpgaImageFpga();
    virtual ~FpgaImageFpga();

    virtual bool Handle ( int index );

  public:
    static std::shared_ptr<FpgaImageHandle> GetObj ( );
};

#endif   /* ----- #ifndef FpgaImageFpga.h ----- */

