/*
 * =====================================================================================
 *
 *       Filename:  MsgQueue.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/18/2015 04:52:37 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  MSGQUEUE_INC
#define  MSGQUEUE_INC


#include <string.h>
#include <mqueue.h>
#include <string>
#include <vector>

#define MAX_MSG_NUM               (80)
#define MAX_MSG_LEN               (128)
#define MSGQUEUE_DEFAULT_PRIO     (10)

class MsgQueue
{
  private:
    MsgQueue ();
    virtual ~MsgQueue();

  public:
    static int SendMsg ( std::string msgName, char* msg, int len,
                         unsigned int prio = MSGQUEUE_DEFAULT_PRIO, unsigned int timeoutMs = 0 );
    static int RecvMsg ( std::string msgName, char* msg, int len,
                         unsigned int prio = MSGQUEUE_DEFAULT_PRIO, unsigned int timeoutMs = 200 );

  private:
    static timespec* GetAbsTimeSpec ( unsigned int timeOutMs );
    static mqd_t CreateMsgQueue ( std::string msgName );
};

#endif   /* ----- #ifndef MSGQUEUE_INC  ----- */


