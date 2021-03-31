/*
 * =====================================================================================
 *
 *       Filename:  DebugGetSupport.h
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

#ifndef  DEBUGGETSUPPORT_INC
#define  DEBUGGETSUPPORT_INC

#include <string>

#include "DebugFun.h"


class DebugGetSupport : public DebugFun
{
  public:
    explicit DebugGetSupport();
    virtual ~DebugGetSupport();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */
