/*
 * =====================================================================================
 *
 *       Filename:  Upgrade.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年03月25日 16时23分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

#include "Network.h"

#pragma pack(push)
#pragma pack(1)
//协议头部
typedef struct
{
  u_int16_t     mcp_magicword;  /*0xeb90*/
  u_int16_t     mcp_id;         /*会话ID，由控制软件创建*/
  u_int16_t     mcp_type;       /*对应EnumMcpType */
  u_int16_t     mcp_subtype;    /*对应EnumMcpSubtype */
  int32_t       mcp_status;     /*状态位，0表示成功，其他表示失败*/
  u_int32_t     mcp_datalen;
  int8_t        mcp_data[0];
} MCP_HEADER_t;

#define MCP_HEADER_T_LEN   (sizeof(MCP_HEADER_t))

#define MCP_STATUS_LEN    28
struct _mcp_status_t
{
  int32_t     status;           /*状态位，0表示成功，其他表示失败*/
  int8_t      dsc[MCP_STATUS_LEN];  /*状态对应的描述信息*/
};
typedef struct _mcp_status_t MCP_STATUS_t;

//命令定义
enum EnumMcpType
{
  MCP_COMMAND = 0x0001,
  MCP_RETURN,
  MCP_MESSAGE,
};

enum EnumMcpUpdateStatus
{
  MCP_CMD_UPGRADE_BEGIN = 0x170,
  MCP_CMD_UPGRADE_TRANSFILE = 0x171,
  MCP_CMD_UPGRADE_END = 0x172,
};

typedef struct
{
  //unsigned int swType;
  unsigned int fileLen;
} upgrade_start_t;

#define SEND_PACK_SIZE    (32*1024)
//#define SEND_PACK_SIZE    (998)
#define RECV_SIZE         (sizeof(MCP_HEADER_t) + sizeof(MCP_STATUS_t))

typedef struct
{
  //unsigned int swType;
  unsigned int packNum;
  unsigned int packLen;
  unsigned char packData[0];
} upgrade_data_t;

typedef struct
{
  //unsigned int swType;
} upgrade_end_t;

typedef struct
{
  unsigned int swType;
  unsigned short state;   /*  1 write 2 backup */
  unsigned short percent; /*  0~100  */
} upgrade_progress_t;

#pragma pack(pop)


bool GetFile ( std::string filename, std::vector<char>& vechar )
{
  std::ifstream ifs ( filename.c_str(), std::ifstream::binary );

  if ( !ifs )
    return false;

  ifs.seekg ( 0, ifs.end );
  int len = ifs.tellg();
  ifs.seekg ( 0, ifs.beg );
  vechar.resize ( len, 0 );

  ifs.read ( &vechar[0], vechar.size() );

  ifs.close();
  return true;
}

int SendStart ( int fd )
{
  char buffer[RECV_SIZE];
  std::vector<char> vecharsend;
  vecharsend.resize ( sizeof ( MCP_HEADER_t ) + sizeof ( upgrade_start_t ), 0 );
  MCP_HEADER_t* p = ( MCP_HEADER_t* ) &vecharsend[0];
  p->mcp_magicword = 0xeb90;
  p->mcp_type = MCP_COMMAND;
  p->mcp_subtype = MCP_CMD_UPGRADE_BEGIN;

  p->mcp_datalen = sizeof ( upgrade_start_t );

  int ret = 0;
  ret = Network::Sendn ( fd, &vecharsend[0], vecharsend.size() );

  if ( ret < 0 )
    printf ( " %s %d ret = %d \n", __FUNCTION__, __LINE__, ret );

  ret = Network::Recvn ( fd, buffer, RECV_SIZE );

  if ( ret < 0 )
    printf ( " %s %d ret = %d \n", __FUNCTION__, __LINE__, ret );

  return ret;
}

int SendData ( int fd, char* pdata, int len )
{
  char buffer[RECV_SIZE];
  std::vector<char> vecharsend;
  vecharsend.resize ( sizeof ( MCP_HEADER_t ) + sizeof ( upgrade_data_t ) + len, 0 );
  MCP_HEADER_t* p = ( MCP_HEADER_t* ) ( &vecharsend[0] );
  p->mcp_magicword = 0xeb90;
  p->mcp_type = MCP_COMMAND;
  p->mcp_subtype = MCP_CMD_UPGRADE_TRANSFILE;
  p->mcp_datalen = sizeof ( upgrade_data_t ) + len;

  upgrade_data_t* p2 = ( upgrade_data_t* ) ( p->mcp_data );
  p2->packLen = len;
  memcpy ( p2->packData, pdata, len );

  int ret = 0;
  ret = Network::Sendn ( fd, &vecharsend[0], vecharsend.size() );

  if ( ret < 0 )
    printf ( " %s %d ret = %d \n", __FUNCTION__, __LINE__, ret );

  ret = Network::Recvn ( fd, buffer, RECV_SIZE );

  if ( ret < 0 )
    printf ( " %s %d ret = %d \n", __FUNCTION__, __LINE__, ret );

  return ret;
}

int SendEnd ( int fd )
{
  char buffer[RECV_SIZE];
  std::vector<char> vecharsend;
  vecharsend.resize ( sizeof ( MCP_HEADER_t ) + sizeof ( upgrade_start_t ), 0 );
  MCP_HEADER_t* p = ( MCP_HEADER_t* ) &vecharsend[0];
  p->mcp_magicword = 0xeb90;
  p->mcp_type = MCP_COMMAND;
  p->mcp_subtype = MCP_CMD_UPGRADE_END;

  p->mcp_datalen = sizeof ( upgrade_end_t );

  int ret = 0;
  ret = Network::Sendn ( fd, &vecharsend[0], vecharsend.size() );

  if ( ret < 0 )
    printf ( " %s %d ret = %d \n", __FUNCTION__, __LINE__, ret );

  ret = Network::Recvn ( fd, buffer, RECV_SIZE );

  if ( ret < 0 )
    printf ( " %s %d ret = %d \n", __FUNCTION__, __LINE__, ret );

  return 0;
}

int SendFile ( std::string filename, std::string ipaddr, int port )
{
  int packsize;
  int lastpacksize;
  int totalpack;
  int sendsize = 0;
  int offset = 0;

  int ret = -1;
  int fd = Network::MakeTCPClient ( ipaddr.c_str(), port );

  if ( fd < 0 )
  {
    printf ( "Connect error fd=%d %s %d!\n", fd, ipaddr.c_str(), port );
    return -1;
  }

  Network::SetSendBuf ( fd, SEND_PACK_SIZE );

  std::vector<char> vechar, vecharsend;
  GetFile ( filename.c_str(), vechar );

  if ( SendStart ( fd ) <= 0 )
  {
    printf ( "SendStart error!\n" );
    goto done;
  }

  packsize = SEND_PACK_SIZE;
  lastpacksize =  vechar.size() % packsize;
  totalpack  =  ( lastpacksize ) ? ( ( vechar.size() / packsize ) + 1 ) : ( vechar.size() / packsize );

  for ( int i = 0; i < totalpack; ++i )
  {
    if ( i != totalpack - 1 )
      sendsize = packsize;
    else
      sendsize = lastpacksize;

    SendData ( fd, &vechar[0] + offset, sendsize );
    offset += sendsize;
    fprintf ( stderr, "%d\r", ( int ) ( ( ( i + 1 ) * 1.0 / totalpack ) * 100 ) );
    usleep ( 10 * 1000 );
  }

  SendEnd ( fd );

  fprintf ( stderr, "\n" );

done:
  shutdown ( fd, SHUT_RDWR );
  close ( fd );
}

int main ( int argc, char* argv[] )
{
  if ( argc == 2 )
    SendFile ( argv[1], "172.16.129.252", 17004 );
  else if ( argc == 3 )
    SendFile ( argv[1], argv[2], 17004 );
  else if ( argc == 4 )
    SendFile ( argv[1], argv[2], atoi ( argv[3] ) );

  return 0;
}


