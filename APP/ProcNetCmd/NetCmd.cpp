/*
 * =====================================================================================
 *
 *       Filename:  NetCmd.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:08:05 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <string.h>

#include "NetCmd.h"

NetCmd::NetCmd ( )
{
}

NetCmd::~NetCmd()
{
}

int NetCmd::HandleRsp ( vechar& cmd, vechar& rsp, int ret_subtype, char* rspBuffer, int rspBufferLen )
{
  rsp.clear();
  rsp.resize (  MCP_HEADER_T_LEN + rspBufferLen, 0 );

  memcpy ( reinterpret_cast<void*> ( &rsp[0] ), &cmd[0], MCP_HEADER_T_LEN );

  if ( rspBuffer )
    memcpy ( reinterpret_cast<void*> ( &rsp[0] + MCP_HEADER_T_LEN ), rspBuffer, rspBufferLen );

  MCP_HEADER_t* p = reinterpret_cast<MCP_HEADER_t*> ( &rsp[0] );

  p->mcp_datalen = rspBufferLen;
  p->mcp_status = 0;
  p->mcp_type = MCP_RETURN;
  p->mcp_subtype = ret_subtype;

  return 0;
}

