/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleNull.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月22日 15时55分08秒
 *  Last Modified:  2015年09月22日 15时55分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "InterruptHandleNull.h"


std::shared_ptr<InterruptHandle> InterruptHandleNull::GetObj ( )
{
  return std::make_shared<InterruptHandleNull> ( );
}


InterruptHandleNull::InterruptHandleNull()
{

}

InterruptHandleNull::~InterruptHandleNull()
{

}

bool InterruptHandleNull::Handle ( void* p )
{
  printf ( "%s\n", __FUNCTION__ );
  return false;
}

