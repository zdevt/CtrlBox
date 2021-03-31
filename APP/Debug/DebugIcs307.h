/*
 * =====================================================================================
 *
 *       Filename:  DebugIcs307.h
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

#ifndef  DEBUGICS307_INC
#define  DEBUGICS307_INC

#include <string>

#include "DebugFun.h"


class DebugIcs307 : public DebugFun
{
  public:
    explicit DebugIcs307();
    virtual ~DebugIcs307();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */

