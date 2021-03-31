/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 22时40分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef   INTERRUPTHANDLEINTERFACE_INC
#define   INTERRUPTHANDLEINTERFACE_INC

#include <map>
#include <memory>

#include "InterruptHandle.h"

enum
{
  INTERRUPT_INFO_TYPE_FPGA = 1,

  INTERRUPT_INFO_TYPE_MAX,
};

typedef std::shared_ptr<InterruptHandle> ( *pGetInterruptHandleObj ) ( );
typedef std::map<int, pGetInterruptHandleObj> mapGetInterruptHandleObj_t;

class InterruptHandleInterface
{
  private:
    InterruptHandleInterface();
    ~InterruptHandleInterface();

  public:
    static std::shared_ptr<InterruptHandle> GetObj ( int type );

  private:
    static mapGetInterruptHandleObj_t m_mapGetInterruptHandleObj;
};

#endif   /* ----- #ifndef InterruptHandleInterface.h ----- */

