/*
 * =====================================================================================
 *
 *       Filename:  DebugDeskTopSet.h
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

#ifndef  DEBUGDESKTOPSET_INC
#define  DEBUGDESKTOPSET_INC

#include <string>

#include "DebugFun.h"


class DebugDeskTopSet : public DebugFun
{
  public:
    explicit DebugDeskTopSet();
    virtual ~DebugDeskTopSet();

    virtual bool Fun ( std::string funarg );
    virtual void Help ( );

  public:
    static std::shared_ptr<DebugFun> GetObj ( );

  private:

};


#endif   /* ----- #ifndef DEBUGFUNTEST_INC  ----- */

