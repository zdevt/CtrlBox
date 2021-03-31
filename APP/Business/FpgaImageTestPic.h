/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageTestPic.h
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
#ifndef  FPGAIMAGETESTPIC_INC
#define  FPGAIMAGETESTPIC_INC

#include "FpgaImageHandle.h"

#define FPGAIMAGE_TESTPIC_INDEX  (1)

class FpgaImageTestPic : public FpgaImageHandle
{
  public:
    FpgaImageTestPic();
    virtual ~FpgaImageTestPic();

    virtual bool Handle ( int index );

  public:
    static std::shared_ptr<FpgaImageHandle> GetObj ( );
};

#endif   /* ----- #ifndef FpgaImageTestPic.h ----- */

