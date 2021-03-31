/*
 * =====================================================================================
 *
 *       Filename:  SystemDefine.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月08日 14时15分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  SYSTEMDEFINE_INC
#define  SYSTEMDEFINE_INC

#include <string>

class SystemDefine
{
  private:
    SystemDefine();
    ~SystemDefine();

  public:
    static std::string GetMakeTime();
    static std::string GetAuthor();
    static std::string GetAuthorIp();
    static std::string GetLoginTime();
    static std::string GetVer();

  private:
    static std::string m_strTemp;

};



#endif   /* ----- #ifndef SystemDefine.h ----- */

