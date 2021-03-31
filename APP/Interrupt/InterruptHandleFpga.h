/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleFpga.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月22日 15时55分15秒
 *  Last Modified:  2015年09月22日 15时55分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  INTERRUPTHANDLEFPGA_INC
#define  INTERRUPTHANDLEFPGA_INC

#include "InterruptHandle.h"

class InterruptHandleFpga : public InterruptHandle
{
  public:
    InterruptHandleFpga();
    virtual ~InterruptHandleFpga();

    virtual bool Handle ( void* p );

  public:
    static std::shared_ptr<InterruptHandle> GetObj ( );
};

#endif   /* ----- #ifndef InterruptHandleFpga.h ----- */

