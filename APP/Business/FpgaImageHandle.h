/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageHandle.h
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
#ifndef  FPGAIMAGEHANDLE_INC
#define  FPGAIMAGEHANDLE_INC

#include <string>
#include <memory>

#include "FpgaTestPic.h"
#include "FpgaReg.h"
#include "FpgaDev.h"

class FpgaImageHandle
{
  public:
    FpgaImageHandle();
    virtual ~FpgaImageHandle();

    virtual bool Handle ( int number ) = 0;
};


#endif   /* ----- #ifndef FpgaImageHandle.h ----- */

