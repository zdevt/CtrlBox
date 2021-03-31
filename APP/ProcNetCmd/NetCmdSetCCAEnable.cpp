/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetCCAEnable.cpp
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

#include "NetCmdSetCCAEnable.h"
#include "OpticEngineInterface.h"
#include "DmdDdp442xReg.h"

NetCmdSetCCAEnable::NetCmdSetCCAEnable ( )
{
}

NetCmdSetCCAEnable::~NetCmdSetCCAEnable()
{
}

int NetCmdSetCCAEnable::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_cca_enable_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_cca_enable_t* pset_cca_enable = reinterpret_cast<set_cca_enable_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  ddp442x_alg_enable_t ddp442x_alg_enable;

  GET_ENGPTR->GetAlgorithmEnable ( ddp442x_alg_enable.data );

  if ( pset_cca_enable->enable )
  {
    ddp442x_alg_enable.degamma =  1;
    ddp442x_alg_enable.cca     =  1;
    ddp442x_alg_enable.stm     =  1;
  }
  else
  {
    ddp442x_alg_enable.cca     =  0;
  }

  usleep ( 25 * 1000 );
  GET_ENGPTR->SetAlgorithmEnable ( ddp442x_alg_enable.data );

  int imode = ddp442x_alg_enable.cca;
  XmlConfig::SetParam ( "OpticEngine", "CcAEnable", imode );

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetCCAEnable::GetObj ()
{
  return std::make_shared<NetCmdSetCCAEnable> (  );
}

