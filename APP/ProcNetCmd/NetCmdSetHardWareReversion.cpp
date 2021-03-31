/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetHardWareReversion.cpp
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

#include "NetCmdSetHardWareReversion.h"

NetCmdSetHardWareReversion::NetCmdSetHardWareReversion (  )
{
}

NetCmdSetHardWareReversion::~NetCmdSetHardWareReversion()
{
}

int NetCmdSetHardWareReversion::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_hardwarereversion_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_hardwarereversion_t* pset_hardwarereversion =
    reinterpret_cast<set_hardwarereversion_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  std::string model = ( char* ) ( &pset_hardwarereversion->model[0] );
  std::string pcbVersion = ( char* ) ( &pset_hardwarereversion->pcbVersion[0] );
  std::string pcbaVersion = ( char* ) ( &pset_hardwarereversion->pcbaVersion[0] );

  if ( 0 == pset_hardwarereversion->hwType )
  {
    if ( model.length() )
    {
      XmlConfig::SetParam ( "Mainboard", "Model", model );
    }

    if ( pcbVersion.length() )
    {
      XmlConfig::SetParam ( "Mainboard", "Pcb", pcbVersion );
    }

    if ( pcbaVersion.length() )
    {
      XmlConfig::SetParam ( "Mainboard", "Pcba", pcbaVersion );
    }
  }

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetHardWareReversion::GetObj (  )
{
  return std::make_shared<NetCmdSetHardWareReversion> ( );
}

