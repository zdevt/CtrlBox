/*
 * =====================================================================================
 *
 *       Filename:  DebugBin.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/09/2015 01:07:42 AM EST
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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <string>

#include "DebugBin.h"

int main ( int argc, char* argv[] )
{
  int i = 0;
  int msg_id = -1;
  std::string arg;

  DebugMsg_t DebugMsg;

  memset ( &DebugMsg, 0, sizeof ( DebugMsg ) );
  DebugMsg.msgtype = 88888; /* must > 0 */

  for ( i = 0; i < argc; i++ )
  {
    arg += argv[i];
    arg += " ";
  }

  strncpy ( DebugMsg.buff, arg.c_str(), MAX_BUFF_SIZE );

  msg_id = msgget ( ( key_t ) 8888, IPC_CREAT | 0666 );

  if ( msg_id == -1 )
  {
    perror ( "msg_id error\n" );
    return -1;
  }

  if ( -1 == msgsnd ( msg_id, &DebugMsg, sizeof ( DebugMsg_t ), 0 ) )
    perror ( "send msg error\n" );

  return 0;
}


