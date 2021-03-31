/*
 * =====================================================================================
 *
 *       Filename:  DebugGpioGet.h
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

#ifndef  DEBUGGPIOGET_INC
#define  DEBUGGPIOGET_INC

#include <string>

#include "DebugFun.h"


class DebugGpioGet : public DebugFun
{
  public:
    explicit DebugGpioGet();
    virtual ~DebugGpioGet();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */

