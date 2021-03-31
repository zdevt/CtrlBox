/*
 * =====================================================================================
 *
 *       Filename:  TcpHandleConfig.cpp
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

#include "TcpHandleConfig.h"
#include "TcpHandle.h"

bool TcpHandleConfig::m_showTcpData = false;

std::shared_ptr<TcpHandle> TcpHandleConfig::GetObj ( )
{
  return std::make_shared<TcpHandleConfig> ();
}

TcpHandleConfig::TcpHandleConfig ( )
{
}

TcpHandleConfig::~TcpHandleConfig()
{

}

int TcpHandleConfig::ProcCmd ( int fd, char* buffer, int len )
{
  std::vector<char> vecharRsp;
  std::vector<char> m_vecharCmd;

  if ( len > 0 )
  {
    m_vecharCmd.resize ( len, 0 );
    memcpy ( &m_vecharCmd[0], buffer, len );
  }

  if ( m_showTcpData )
    ShowTcpData ( "Recv:", buffer, len );

  CmdInterface::GetObj ( buffer, len )->HandleCmd ( m_vecharCmd, vecharRsp );

  if ( vecharRsp.size() > 0 )
    SendData ( fd,  &vecharRsp[0], vecharRsp.size() );

  if ( m_showTcpData )
    ShowTcpData ( "Send:", &vecharRsp[0], vecharRsp.size() );

  #if 0
  MCP_HEADER_t* pCmd = reinterpret_cast<MCP_HEADER_t*> ( &m_vecharCmd[0] );
  MCP_HEADER_t* pRsp = reinterpret_cast<MCP_HEADER_t*> ( &vecharRsp[0] );

  PRINT_LOG ( LOG_LEVEL_NORMAL, " cmd NO = 0x%04x\n", pCmd->mcp_id );

  if ( vecharRsp.size() >= sizeof ( MCP_HEADER_t ) )
    PRINT_LOG ( LOG_LEVEL_NORMAL, " rsp NO = 0x%04x\n", pRsp->mcp_id );

  #endif

  return 0;
}

bool TcpHandleConfig::GetShowTcpDataFlag()
{
  return m_showTcpData;
}

void TcpHandleConfig::SetShowTcpDataFlag ( bool flag )
{
  m_showTcpData = flag;
}

