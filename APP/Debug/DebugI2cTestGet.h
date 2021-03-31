/*
 * =====================================================================================
 *
 *       Filename:  DebugI2cTestGet.h
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

#ifndef  DEBUGI2CTESTGET_INC
#define  DEBUGI2CTESTGET_INC

#include <string>

#include "DebugFun.h"


class DebugI2cTestGet : public DebugFun
{
  public:
    explicit DebugI2cTestGet();
    virtual ~DebugI2cTestGet();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */

