/*
 * =====================================================================================
 *
 *       Filename:  DebugFun.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2015 10:35:31 AM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <sstream>

#include "DebugFun.h"


DebugFun::DebugFun ( )
{
}


DebugFun::~DebugFun()
{
}

void DebugFun::GetAllArg ( std::string& str, vecstr_t& vecarg, char c )
{
  std::stringstream ssIn ( str );
  std::string strTemp;

  vecarg.clear();

  while ( NULL != getline ( ssIn, strTemp, c ) )
  {
    if ( strTemp.size() != 0 )
      vecarg.insert ( vecarg.end(), strTemp );
  }
}

int DebugFun::GetArgNum ( std::string& str )
{
  vecstr_t vecarg;
  GetAllArg ( str, vecarg );
  return vecarg.size();
}


#ifdef TEST

int main ( int argc, char* argv[] )
{
  std::string str = "1 2 3 444";

  std::vector<std::string> vecstrout;
  DebugFun::GetAllArg ( str, vecstrout );

  for ( auto iter = vecstrout.begin(); iter != vecstrout.end(); ++iter )
    fprintf ( stderr, "%s\n", ( *iter ).c_str() );


  return 0;
}

#endif


