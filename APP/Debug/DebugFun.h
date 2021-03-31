/*
 * =====================================================================================
 *
 *       Filename:  DebugFun.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2015 10:35:32 AM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  DEBUGFUN_INC
#define  DEBUGFUN_INC

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "LogPrint.h"

typedef std::vector<std::string> vecstr_t;

class DebugFun
{
  public:
    DebugFun (  );
    virtual ~DebugFun();

  public:
    void GetAllArg ( std::string& str, vecstr_t& vecarg, char c = ' ' );
    int GetArgNum ( std::string& str );
    virtual bool Fun ( std::string funarg ) = 0;
    virtual void Help ( ) = 0;
};


#endif   /* ----- #ifndef DEBUGFUN_INC  ----- */

