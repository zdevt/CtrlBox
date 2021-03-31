/*
 * =====================================================================================
 *
 *       Filename:  NetLink.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/21/2015 01:52:35 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  NETLINK_INC
#define  NETLINK_INC

#include <linux/netlink.h>
#include <vector>
#include <pthread.h>

#define NETLINK_ZT              (22)
#define MAX_PAYLOAD           (1024)

enum
{
  MSG_TYPE_ENABLE  = 1,  /*  USER->KERNEL */
  MSG_TYPE_INTERRUPT,    /*  KERNEL->USER */

  MSG_TYPE_MAX,
};

#pragma pack(push)
#pragma pack(1)
/* For MSG_TYPE_ENABLE */
typedef struct
{
  unsigned int irqNo;  /* irq No */
  unsigned int status; /* 0: disable 1: enable */
} irq_opt_t;

/* For MSG_TYPE_INTERRUPT */
typedef struct
{
  unsigned long type;
  unsigned long val;
} interrupt_info_t;
#pragma pack(pop)

enum NETLINK_ERR
{
  ERROR_NETLINK_SOCKET          = 0x0001,
  ERROR_NETLINK_BIND,
  ERROR_NETLINK_SEND,
  ERROR_NETLINK_RECV,
  ERROR_NETLINK_BUFFER,

  ERROR_NETLINK_MAX,
};

class NetLink
{
  public:
    explicit NetLink ( int protocolType );
    virtual ~NetLink();

  private:
    int Init();
    int DeInit();

  public:
    int Send ( char* buffer, int len, int msgType = MSG_TYPE_ENABLE, pthread_t despid = 0 /* kernel */ );
    int Send ( std::vector<char> vecharSend, int msgType = MSG_TYPE_ENABLE, pthread_t despid = 0 /* kernel */ );

    int Recv ( char* buffer, int& len );
    int Recv ( std::vector<char>& vecharRecv );

  private:
    static int m_netlinkSocket;
    int m_protocolType;
    sockaddr_nl m_sockaddr_nl;
};


#endif   /* ----- #ifndef NETLINK_INC  ----- */


