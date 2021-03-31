/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBasicChroma.cpp
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

#include "NetCmdGetBasicChroma.h"

NetCmdGetBasicChroma::NetCmdGetBasicChroma (  )
{
}

NetCmdGetBasicChroma::~NetCmdGetBasicChroma()
{
}

int NetCmdGetBasicChroma::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_basicchroma_cmd_t ) ) )
    return 0;


  get_basicchroma_t get_basicchroma;
  #if !defined(__i386__) && !defined(__x86_64__)
  get_basicchroma_cmd_t* pget_basicchroma_cmd =
    reinterpret_cast<get_basicchroma_cmd_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  #ifdef MCP_CHROMA_USEING_STR
  std::string basicChromaX;
  std::string basicChromaY;
  std::string defalutStr = "0.0";
  #endif

  if ( pget_basicchroma_cmd->r )
  {
    #ifdef MCP_CHROMA_USEING_STR
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_R_x", basicChromaX, defalutStr );
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_R_y", basicChromaY, defalutStr );
    strncpy ( get_basicchroma.r.x, basicChromaX.c_str(), MCP_CHROMA_LEN );
    strncpy ( get_basicchroma.r.y, basicChromaY.c_str(), MCP_CHROMA_LEN );
    #else
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_R_x", get_basicchroma.r.x, ( uint32_t ) 0 );
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_R_y", get_basicchroma.r.y, ( uint32_t ) 0 );
    #endif
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_R_l", get_basicchroma.r.l, ( uint32_t ) 0 );
  }

  if ( pget_basicchroma_cmd->g )
  {
    #ifdef MCP_CHROMA_USEING_STR
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_G_x", basicChromaX, defalutStr );
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_G_y", basicChromaY, defalutStr );
    strncpy ( get_basicchroma.g.x, basicChromaX.c_str(), MCP_CHROMA_LEN );
    strncpy ( get_basicchroma.g.y, basicChromaY.c_str(), MCP_CHROMA_LEN );
    #else
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_G_x", get_basicchroma.g.x, ( uint32_t ) 0 );
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_G_y", get_basicchroma.g.y, ( uint32_t ) 0 );
    #endif
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_G_l", get_basicchroma.g.l, ( uint32_t ) 0 );
  }

  if ( pget_basicchroma_cmd->b )
  {
    #ifdef MCP_CHROMA_USEING_STR
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_B_x", basicChromaX, defalutStr );
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_B_y", basicChromaY, defalutStr );
    strncpy ( get_basicchroma.b.x, basicChromaX.c_str(), MCP_CHROMA_LEN );
    strncpy ( get_basicchroma.b.y, basicChromaY.c_str(), MCP_CHROMA_LEN );
    #else
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_B_x", get_basicchroma.b.x, ( uint32_t ) 0 );
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_B_y", get_basicchroma.b.y, ( uint32_t ) 0 );
    #endif
    XmlConfig::GetParam ( "OpticEngine", "BasicChroma_B_l", get_basicchroma.b.l, ( uint32_t ) 0 );
  }

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_BASICCHROMA, reinterpret_cast<char*> ( &get_basicchroma ), sizeof ( get_basicchroma ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetBasicChroma::GetObj (  )
{
  return std::make_shared<NetCmdGetBasicChroma> ();
}

