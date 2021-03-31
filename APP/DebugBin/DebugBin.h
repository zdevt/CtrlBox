/*
 * =====================================================================================
 *
 *       Filename:  DebugBin.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/09/2015 01:08:11 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  DEBUGBIN_INC
#define  DEBUGBIN_INC

#define MAX_BUFF_SIZE (1024)

typedef struct message
{
  long msgtype; /* must > 0 */
  char buff[MAX_BUFF_SIZE];
} DebugMsg_t;


#endif   /* ----- #ifndef DEBUGBIN_INC  ----- */

