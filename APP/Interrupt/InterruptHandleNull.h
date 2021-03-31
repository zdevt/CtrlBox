/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandleNull.h
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
#ifndef  INTERRUPTHANDLENULL_INC
#define  INTERRUPTHANDLENULL_INC

#include "InterruptHandle.h"

class InterruptHandleNull : public InterruptHandle
{
  public:
    InterruptHandleNull();
    virtual ~InterruptHandleNull();

    virtual bool Handle ( void* p );

  public:
    static std::shared_ptr<InterruptHandle> GetObj ( );
};

#endif   /* ----- #ifndef InterruptHandleNull.h ----- */

