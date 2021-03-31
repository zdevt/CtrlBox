/*
 * =====================================================================================
 *
 *       Filename:  TcpHandleUpgrade.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/21/2014 10:14:26 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   zt(),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  TCPHANDLEUPGRADE_INC
#define  TCPHANDLEUPGRADE_INC

#include <memory>
#include <vector>

#include "TcpHandle.h"
#include "CmdInterface.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  unsigned int fileLen;
} upgrade_start_t;

typedef struct
{
  unsigned int packNum;
  unsigned int packLen;
  unsigned char packData[0];
} upgrade_data_t;

typedef struct
{
} upgrade_end_t;

typedef struct
{
  unsigned int swType;
  unsigned short state;   /*  1 write 2 backup */
  unsigned short percent; /*  0~100  */
} upgrade_progress_t;
#pragma pack(pop)

#if defined(__arm__)
  #define TEMP_UPGRADE_FILE   "/app/new.hs"
#else
  #define TEMP_UPGRADE_FILE   "./new.hs"
#endif

class TcpHandleUpgrade : public TcpHandle
{
  public:
    TcpHandleUpgrade ( );
    virtual ~TcpHandleUpgrade();

  public:
    virtual int ProcCmd ( int fd, char* buffer, int len );

  private:
    virtual int ProcUpgradeData ( int fd, void* buffer, int len );
    virtual int GenRspData ( MCP_HEADER_t* pRecv, std::vector<char>& rsp, MCP_STATUS_t* pStatus );
    virtual int UpdateBegin ( int fd, MCP_HEADER_t* p );
    virtual int UpdateData ( int fd,  MCP_HEADER_t* p );
    virtual int UpdateEnd ( int fd, MCP_HEADER_t* p );

  public:
    static std::shared_ptr<TcpHandle> GetObj (  );
};

#endif   /* ----- #ifndef TCPLINK_INC  ----- */

