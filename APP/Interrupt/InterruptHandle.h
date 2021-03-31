/*
 * =====================================================================================
 *
 *       Filename:  InterruptHandle.h
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
#ifndef  INTERRUPTHANDLE_INC
#define  INTERRUPTHANDLE_INC

#include <string>
#include <memory>

class InterruptHandle
{
  public:
    InterruptHandle();
    virtual ~InterruptHandle();

    virtual bool Handle ( void* p ) = 0;
};

#endif   /* ----- #ifndef InterruptHandle.h ----- */

