/*
 * =====================================================================================
 *
 *       Filename:  Common.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/23/2014 06:54:36 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  COMMON_INC
#define  COMMON_INC

#ifndef PTHREAD_DETACH
#include <pthread.h>
#include <sys/prctl.h>
#define PTHREAD_DETACH  do{ pthread_detach(pthread_self()); prctl(PR_SET_NAME,__FUNCTION__);}while(0)
#endif


/****************TCP********************/
#define TCP_REMOTE_HEARTBEAT_PORT (7001)
#define TCP_SERVER_CONFIG_PORT    (7002)
#define TCP_SERVER_ALARM_PORT     (7003)
#define TCP_SERVER_UPGRADE_PORT   (7004)
#define TCPSERVER_ECHO_PORT       (7009)

#define TCPLINK_BUFFER_SIZE     (128*1024)

#define MAX_CONNECT_PER_SERVER  (5)
#define TCPLINK_SO_SNDTIMO      (2)
#define TCPLINK_SO_RCVTIMO      (2)
#define TCPLINK_TCP_NODELAY     (1)
#define TCPLINK_SO_KEEPALIVE    (1)
#define TCPLINK_TCP_KEEPIDLE    (5)
#define TCPLINK_TCP_KEEPINVL    (2)
#define TCPLINK_TCP_KEEPCNT     (3)

#define TCPLINK_TIME_OUT        (5)


#define UPGRADE_FILE_MAGIC_NUM  (0xaa550001)


#define CUBE_POWER_ON           (1)
#define CUBE_POWER_OFF          (0)

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  unsigned int hearderChksum;
  unsigned int magicNum;  /* 0xaa550001 */
  unsigned int fileType;
  unsigned int fileNo;
  unsigned char verMajor; /* Major.Sub.Min.Test */
  unsigned char verSub;
  unsigned char verMin;
  unsigned char verTest;
  unsigned int reserved[8];
  unsigned int fileUnCompressSize;
  unsigned int fileCompressSize;
  unsigned int fileCrc;
} upgrade_file_header_t;

typedef struct
{
  unsigned char type[24];
} engine_id_t;

#pragma pack(pop)


#endif   /* ----- #ifndef COMMON_INC  ----- */

