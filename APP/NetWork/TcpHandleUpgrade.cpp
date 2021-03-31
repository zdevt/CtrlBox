/*
 * =====================================================================================
 *
 *       Filename:  TcpHandleUpgrade.cpp
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

#include <stdio.h>
#include <string.h>

#include "TcpHandleUpgrade.h"
#include "UpgradeFileInterface.h"
#include "FileHandle.h"

std::shared_ptr<TcpHandle> TcpHandleUpgrade::GetObj ( )
{
  return std::make_shared<TcpHandleUpgrade> ();
}

TcpHandleUpgrade::TcpHandleUpgrade ( )
{
}

TcpHandleUpgrade::~TcpHandleUpgrade()
{

}

int TcpHandleUpgrade::ProcCmd ( int fd, char* buffer, int len )
{
  ProcUpgradeData ( fd, buffer, len );
  return 0;
}

int TcpHandleUpgrade::ProcUpgradeData ( int fd, void* buffer, int len )
{
  MCP_HEADER_t* pMcpHeader = reinterpret_cast<MCP_HEADER_t*> ( buffer );

  switch ( pMcpHeader->mcp_subtype )
  {
    case MCP_CMD_UPGRADE_BEGIN:
      return UpdateBegin ( fd, pMcpHeader );
      break;

    case MCP_CMD_UPGRADE_TRANSFILE:
      return UpdateData ( fd, pMcpHeader );
      break;

    case MCP_CMD_UPGRADE_END:
      return UpdateEnd ( fd, pMcpHeader );
      break;

    default:
      break;
  }

  return 0;
}

int TcpHandleUpgrade::GenRspData ( MCP_HEADER_t* pRecv, std::vector<char>& rsp, MCP_STATUS_t* pStatus )
{
  rsp.clear();
  rsp.resize ( sizeof ( MCP_HEADER_t ) + sizeof ( MCP_STATUS_t ), 0 );
  memcpy ( &rsp[0], reinterpret_cast<char*> ( pRecv ), sizeof ( MCP_HEADER_t ) );

  MCP_HEADER_t* pMCP_HEADER = reinterpret_cast<MCP_HEADER_t*> ( &rsp[0] );
  pMCP_HEADER->mcp_datalen = sizeof ( MCP_STATUS_t );
  pMCP_HEADER->mcp_subtype = MCP_RET_STATUS;

  if ( pStatus )
  {
    memcpy ( ( ( ( char* ) pMCP_HEADER ) + sizeof ( MCP_HEADER_t ) ), ( void* ) pStatus, sizeof ( MCP_STATUS_t ) );
  }

  return 0;
}

int TcpHandleUpgrade::UpdateBegin ( int fd, MCP_HEADER_t* p )
{
  if ( p->mcp_datalen < sizeof ( upgrade_start_t ) )
    return -1;

  std::vector<char> vecharSend;
  MCP_STATUS_t MCP_STATUS;
  MCP_STATUS.status = 0;
  GenRspData ( p, vecharSend, &MCP_STATUS );

  #if defined(__arm__)

  if ( !FileHandle::Create ( TEMP_UPGRADE_FILE ) )
    return -1;

  #endif

  SendData ( fd, &vecharSend[0], vecharSend.size() );
  return 0;
}

int TcpHandleUpgrade::UpdateData ( int fd,  MCP_HEADER_t* p )
{
  upgrade_data_t* pupgrade_data = reinterpret_cast<upgrade_data_t*> ( p->mcp_data );

  if ( p->mcp_datalen < sizeof ( upgrade_data_t ) + pupgrade_data->packLen )
    return -1;

  #if defined(__arm__)

  if ( !FileHandle:: WriteAppend ( TEMP_UPGRADE_FILE,
                                   reinterpret_cast<char*> ( pupgrade_data->packData ),
                                   pupgrade_data->packLen ) )
    return -1;

  #endif

  std::vector<char> vecharSend;
  MCP_STATUS_t MCP_STATUS;
  MCP_STATUS.status = 0;
  GenRspData ( p, vecharSend, &MCP_STATUS );

  SendData ( fd, &vecharSend[0], vecharSend.size() );
  return 0;
}

int TcpHandleUpgrade::UpdateEnd ( int fd, MCP_HEADER_t* p )
{
  std::vector<char> vecharSend;
  MCP_STATUS_t MCP_STATUS;
  MCP_STATUS.status = 0;
  GenRspData ( p, vecharSend, &MCP_STATUS );

  #if defined(__arm__)
  UpgradeFileInterface::HandleUpgradeFile ( TEMP_UPGRADE_FILE, NULL );
  #endif

  SendData ( fd, &vecharSend[0], vecharSend.size() );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );

  return 0;
}

