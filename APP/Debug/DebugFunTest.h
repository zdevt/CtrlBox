/*
 * =====================================================================================
 *
 *       Filename:  DebugFunTest.h
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

#ifndef  DEBUGFUNTEST_INC
#define  DEBUGFUNTEST_INC

#include <string>

#include "DebugFun.h"


class DebugFunTest : public DebugFun
{
  public:
    explicit DebugFunTest();
    virtual ~DebugFunTest();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

    void Test();

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */

