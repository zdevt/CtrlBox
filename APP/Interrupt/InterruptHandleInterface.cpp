/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleInterface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 22时40分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "InterruptHandleInterface.h"
#include "InterruptHandleFpga.h"
#include "InterruptHandleNull.h"


mapGetInterruptHandleObj_t InterruptHandleInterface::m_mapGetInterruptHandleObj =
{
  { INTERRUPT_INFO_TYPE_FPGA,    InterruptHandleFpga::GetObj },

};

InterruptHandleInterface::InterruptHandleInterface()
{

}

InterruptHandleInterface::~InterruptHandleInterface()
{

}

std::shared_ptr<InterruptHandle> InterruptHandleInterface::GetObj ( int type )
{
  auto iter = m_mapGetInterruptHandleObj.find ( type );

  if ( iter != m_mapGetInterruptHandleObj.end() )
    return ( iter->second ) ( );

  return InterruptHandleNull::GetObj ( );
}

