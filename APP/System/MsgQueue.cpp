/*
 * =====================================================================================
 *
 *       Filename:  MsgQueue.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/18/2015 04:52:30 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <memory>
#include <unistd.h>

#include "MsgQueue.h"


MsgQueue::MsgQueue ( )
{
}

MsgQueue::~MsgQueue()
{
}


mqd_t MsgQueue::CreateMsgQueue ( std::string msgName )
{
  mq_attr attr ;
  attr.mq_maxmsg = MAX_MSG_NUM;
  attr.mq_msgsize = MAX_MSG_LEN;
  attr.mq_flags = 0; /* BLOCK */

  return mq_open ( msgName.c_str(), O_RDWR | O_CREAT | O_EXCL, 0666, &attr );
}

timespec* MsgQueue::GetAbsTimeSpec ( unsigned int timeoutMs )
{
  const long LIMIT_NUM = 1000 * 1000 * 1000;
  std::shared_ptr<timespec> ptms = std::make_shared<timespec>();

  timeval tmval;
  gettimeofday ( &tmval, NULL );

  ptms->tv_sec = tmval.tv_sec;
  ptms->tv_nsec = ( tmval.tv_usec + timeoutMs * 1000 ) * 1000;

  if ( ptms->tv_nsec >= LIMIT_NUM )
  {
    ptms->tv_nsec -= LIMIT_NUM;
    ptms->tv_sec++;
  }

  return ptms.get();
}

int MsgQueue::SendMsg ( std::string msgName, char* msg, int len, unsigned int prio, unsigned int timeoutMs  )
{
  mqd_t msgId = mq_open ( msgName.c_str(), O_WRONLY );
  int ret = 0;

  if ( ( msgId < 0 ) && ( ENOENT == errno ) )
    msgId = CreateMsgQueue ( msgName.c_str() );

  if ( msgId < 0 )
    return -3;

  if ( len > MAX_MSG_LEN )
    return -2;

  if ( timeoutMs != 0 )
    ret = mq_timedsend ( msgId, msg, len, prio, GetAbsTimeSpec ( timeoutMs ) );
  else
    ret = mq_send ( msgId, msg, len, prio );

  return ret;
}


int MsgQueue::RecvMsg ( std::string msgName, char* msg, int len, unsigned int prio, unsigned int timeoutMs )
{
  mqd_t msgId = mq_open ( msgName.c_str(), O_RDONLY );
  int ret = 0;

  if ( ( msgId < 0 ) && ( ENOENT == errno ) )
    msgId = CreateMsgQueue ( msgName.c_str() );

  if ( msgId < 0 )
    return -2;

  if ( timeoutMs != 0 )
    ret = mq_timedreceive ( msgId, msg, MAX_MSG_LEN, &prio, GetAbsTimeSpec ( timeoutMs ) );
  else
    ret = mq_receive ( msgId, msg, MAX_MSG_LEN, &prio );

  mq_close ( msgId );

  return ret;
}


#ifdef TESTMQ
int main ( int argc, char* argv[] )
{
  char send[32] = "testmsgq";
  char recv[32] = { 0 };
  int recvLen = 0;
  int ret = 0;

  ret = MsgQueue::SendMsg ( "/msg_interrupt", send, 15 );
  fprintf ( stderr, "ret=%d\n", ret );

  ret = MsgQueue::SendMsg ( "/msg_interrupt", send, 15 );
  fprintf ( stderr, "ret=%d\n", ret );

  sleep ( 1 );
  recvLen = MsgQueue::RecvMsg ( "/msg_interrupt", recv, recvLen );
  fprintf ( stderr, "recvLen=%d %s\n", recvLen, recv );

  recvLen = MsgQueue::RecvMsg ( "/msg_interrupt", recv, recvLen );
  fprintf ( stderr, "recvLen=%d %s\n", recvLen, recv );

  return 0;
}
#endif

