/*
 * =====================================================================================
 *
 *       Filename:  FunTest.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/09/2015 01:46:56 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "FunTest.h"

int FunTest ( int a, int b )
{
  return ( a + b );
}

int FunTest2 ( int a )
{
  return ( a * a );
}


#ifdef FUNTEST

#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char* argv[] )
{

  fprintf ( stderr, "%d\n", FunTest2 ( 4 ) );
  return 0;
}

#endif
