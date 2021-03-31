/*
 * =====================================================================================
 *
 *       Filename:  DebugLightBrightnessCompensation.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2015 10:45:02 AM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  DEBUGLIGHTNESSCOMPENSATION_INC
#define  DEBUGLIGHTNESSCOMPENSATION_INC

#include <string>

#include "DebugFun.h"


class DebugLightBrightnessCompensation : public DebugFun
{
  public:
    explicit DebugLightBrightnessCompensation();
    virtual ~DebugLightBrightnessCompensation();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */

