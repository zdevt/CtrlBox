/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetBasicChroma.cpp
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

#include "NetCmdSetBasicChroma.h"

NetCmdSetBasicChroma::NetCmdSetBasicChroma (  )
{
}

NetCmdSetBasicChroma::~NetCmdSetBasicChroma()
{
}

int NetCmdSetBasicChroma::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_basicchroma_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if !defined(__i386__) && !defined(__x86_64__)
  /*  TODO  */
  set_basicchroma_t* pset_basicchroma = reinterpret_cast<set_basicchroma_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  #ifdef MCP_CHROMA_USEING_STR
  std::string basicChromaX;
  std::string basicChromaY;
  #else
  uint32_t basicChromaX;
  uint32_t basicChromaY;
  #endif

  if ( pset_basicchroma->cmd.r )
  {
    basicChromaX = pset_basicchroma->r.x;
    basicChromaY = pset_basicchroma->r.y;
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_R_x", ( basicChromaX ) );
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_R_y", ( basicChromaY ) );
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_R_l", ( pset_basicchroma->r.l ) );
  }

  if ( pset_basicchroma->cmd.g )
  {
    basicChromaX = pset_basicchroma->g.x;
    basicChromaY = pset_basicchroma->g.y;
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_G_x", ( basicChromaX ) );
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_G_y", ( basicChromaY ) );
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_G_l", ( pset_basicchroma->g.l ) );
  }

  if ( pset_basicchroma->cmd.b )
  {
    basicChromaX = pset_basicchroma->b.x;
    basicChromaY = pset_basicchroma->b.y;
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_B_x", ( basicChromaX ) );
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_B_y", ( basicChromaY ) );
    XmlConfig::SetParam ( "OpticEngine", "BasicChroma_B_l", ( pset_basicchroma->b.l ) );
  }

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetBasicChroma::GetObj (  )
{
  return std::make_shared<NetCmdSetBasicChroma> ();
}

