/*
 * =====================================================================================
 *
 *       Filename:  DebugI2cTestSet.h
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

#ifndef  DEBUGI2CTESTSET_INC
#define  DEBUGI2CTESTSET_INC

#include <string>

#include "DebugFun.h"


class DebugI2cTestSet : public DebugFun
{
  public:
    explicit DebugI2cTestSet();
    virtual ~DebugI2cTestSet();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */

