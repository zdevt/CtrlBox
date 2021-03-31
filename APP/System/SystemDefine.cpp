/*
 * =====================================================================================
 *
 *       Filename:  SystemDefine.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月08日 14时15分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include "SystemDefine.h"


std::string SystemDefine::m_strTemp;

SystemDefine::SystemDefine()
{

}

SystemDefine::~SystemDefine()
{

}

std::string SystemDefine::GetMakeTime()
{
  #ifdef MK_TIME_D
  m_strTemp = MK_TIME_D;
  #else
  m_strTemp = "2016-01-01 00:00:00";
  #endif

  return m_strTemp;
}

std::string SystemDefine::GetAuthor()
{
  #ifdef AUTHOR_D
  m_strTemp = AUTHOR_D;
  #else
  m_strTemp = "LinkShow";
  #endif

  return m_strTemp;
}

std::string SystemDefine::GetAuthorIp()
{
  #ifdef AUTHORIP_D
  m_strTemp = AUTHORIP_D;
  #else
  m_strTemp = "127.0.0.1";
  #endif

  return m_strTemp;
}

std::string SystemDefine::GetLoginTime()
{
  #ifdef LOGINTIME_D
  m_strTemp = LOGINTIME_D;
  #else
  m_strTemp = "2016-01-01 00:00:00";
  #endif

  return m_strTemp;
}

std::string SystemDefine::GetVer()
{
  #ifdef VER_D
  m_strTemp = VER_D;
  #else
  m_strTemp = "1.0.0.0";
  #endif

  return m_strTemp;
}

