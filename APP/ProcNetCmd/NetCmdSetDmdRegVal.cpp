/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDmdRegVal.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:13:23 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <string>

#include "NetCmdSetDmdRegVal.h"
#include "OpticEngineInterface.h"

NetCmdSetDmdRegVal::NetCmdSetDmdRegVal ( )
{
}

NetCmdSetDmdRegVal::~NetCmdSetDmdRegVal()
{
}

int NetCmdSetDmdRegVal::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_dmd_reg_val_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_dmd_reg_val_t* pset_dmd_reg_val = reinterpret_cast<set_dmd_reg_val_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  GET_ENGPTR->SetDmdRegVal ( pset_dmd_reg_val->subaddr,
                             pset_dmd_reg_val->datalen, pset_dmd_reg_val->data );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetDmdRegVal::GetObj ()
{
  return std::make_shared<NetCmdSetDmdRegVal> (  );
}

