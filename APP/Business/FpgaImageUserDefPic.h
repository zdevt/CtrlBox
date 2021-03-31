/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageUserDefPic.h
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
#ifndef  FPGAIMAGEUSERDEFPIC_INC
#define  FPGAIMAGEUSERDEFPIC_INC

#include <vector>

#include "FpgaImageHandle.h"

#define FPGAIMAGE_USERDEF_STRAT_INDEX  (31)

class FpgaImageUserDefPic : public FpgaImageHandle
{
  public:
    FpgaImageUserDefPic();
    virtual ~FpgaImageUserDefPic();

    virtual bool Handle ( int index );

    static void GetBgpNum ( std::vector<uint32_t>& vecinbgpNum );

  public:
    static std::shared_ptr<FpgaImageHandle> GetObj ( );
};

#endif   /* ----- #ifndef FpgaImageUserDefPic.h ----- */

