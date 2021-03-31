/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleFpga.cpp
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

#include "InterruptHandleFpga.h"


std::shared_ptr<InterruptHandle> InterruptHandleFpga::GetObj ( )
{
  return std::make_shared<InterruptHandleFpga> ( );
}


InterruptHandleFpga::InterruptHandleFpga()
{

}

InterruptHandleFpga::~InterruptHandleFpga()
{

}

bool InterruptHandleFpga::Handle ( void* p )
{
  printf ( "%s\n", __FUNCTION__ );
  return false;
}

