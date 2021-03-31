/*
 * =====================================================================================
 *
 *       Filename:  TcpHandle.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/21/2014 10:14:14 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   zt(),
 *        Company:
 *
 * =====================================================================================
 */

#include "TcpHandle.h"

static char buffer[TCPLINK_BUFFER_SIZE] = { 0 };

TcpHandle::TcpHandle ( )
  : m_buffer ( NULL )
{
  //m_buffer = new char[TCPLINK_BUFFER_SIZE];
  m_buffer = buffer;
}

TcpHandle::~TcpHandle()
{
  #if 0

  if ( m_buffer )
    delete m_buffer;

  #endif
}

int TcpHandle::HandleConnectSocket ( int fd )
{
  int recvLen = 0;

  if ( RecvData ( fd, m_buffer, recvLen ) < 0 )
    return -1;

  ProcData ( fd, m_buffer, recvLen );
  return 0;
}

int TcpHandle::RecvData ( int fd, char* buffer, int& len )
{
  /*  recv header  */
  MCP_HEADER_t* pMCP_HEADER = reinterpret_cast<MCP_HEADER_t*> ( buffer );
  len = Network::Recvn ( fd, reinterpret_cast<void*> ( buffer ), MCP_HEADER_T_LEN );

  if ( len != MCP_HEADER_T_LEN )
  {
    return -1;
  }

  if ( ( pMCP_HEADER->mcp_magicword != MCP_MAGICWORD ) || ( pMCP_HEADER->mcp_type >= MCP_MAX ) )
  {
    PRINT_LOG ( LOG_LEVEL_ALARM, "maigc = 0x%x mcp_type = 0x%x, SIZE=0x%x\n",
                pMCP_HEADER->mcp_magicword, pMCP_HEADER->mcp_type, pMCP_HEADER->mcp_datalen );
    return -1;
  }

  if ( TCPLINK_BUFFER_SIZE < pMCP_HEADER->mcp_datalen + MCP_HEADER_T_LEN )
    return len;

  if ( pMCP_HEADER->mcp_datalen == 0 )
    return len;

  /*  recv data  */
  len = Network::Recvn ( fd, reinterpret_cast<void*> ( buffer + MCP_HEADER_T_LEN ), pMCP_HEADER->mcp_datalen );

  if ( len == ( int ) pMCP_HEADER->mcp_datalen )
    len += MCP_HEADER_T_LEN;
  else
    return -1; /*  读取数据头之外的数据失败，也算失败 */

  return len;
}

int TcpHandle::ProcData ( int fd, char* buffer, int len )
{
  MCP_HEADER_t* pMCP_HEADER = reinterpret_cast<MCP_HEADER_t*> ( buffer );

  if ( len == ( int ) ( MCP_HEADER_T_LEN + pMCP_HEADER->mcp_datalen ) )
    return ProcCmd ( fd, buffer, len );

  return 0;
}

int TcpHandle::SendData ( int fd, char* buffer, int len )
{
  tcp_info tcpInfo;
  int infoLen = sizeof ( tcpInfo );

  if ( len <= 0 )
    return -1;

  if ( getsockopt ( fd, IPPROTO_TCP, TCP_INFO, ( &tcpInfo ), ( socklen_t* ) ( &infoLen ) ) < 0 )
    return -1;

  if ( tcpInfo.tcpi_state != TCP_ESTABLISHED )
    return -1;

  return Network::Sendn ( fd, reinterpret_cast<void*> ( buffer ), len );
}

void TcpHandle::ShowTcpData ( const char* description, char* buffer, int len )
{
  PRINT_LOG2 ( "\n%s\n", description );
  PRINT_LOG2 ( "        maigc id    type  sub   status      len\n" );
  PRINT_LOG2 ( "Header: " );

  for ( int i = 0; i < len; ++i )
  {
    if ( ( i % 0x10 == 0 ) && ( 0 != i ) )
      PRINT_LOG2 ( "\n        " );

    PRINT_LOG2 ( "%02x ", buffer[i] );
  }

  PRINT_LOG2 ( "\n" );
}

