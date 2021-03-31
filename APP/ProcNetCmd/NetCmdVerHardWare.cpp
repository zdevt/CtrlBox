/*
 * =====================================================================================
 *
 *       Filename:  NetCmdVerHardWare.cpp
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

#include "NetCmdVerHardWare.h"
#include "MainboardDefault.h"

NetCmdVerHardWare::NetCmdVerHardWare (  )
{
}

NetCmdVerHardWare::~NetCmdVerHardWare()
{
}

int NetCmdVerHardWare::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( hw_type_t ) ) )
    return 0;

  hw_version_t hw_version;
  #if defined(__arm__)
  hw_type_t* phw_type = reinterpret_cast<hw_type_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if (  phw_type->hwType == 0 )
  {
    std::string str1, str2, str3;
    std::string model, pcbVersion, pcbaVersion;

    str1 = MAINBOARDDEFAULTNAME;
    XmlConfig::GetParam ( "Mainboard", "Model", model, str1 );

    str2 = "E.1";
    XmlConfig::GetParam ( "Mainboard", "Pcb", pcbVersion, str2 );

    str3 = "E.1";
    XmlConfig::GetParam ( "Mainboard", "Pcba", pcbaVersion, str3 );

    PRINT_LOG ( LOG_LEVEL_NORMAL, "%s %s %s\n", model.c_str(), pcbVersion.c_str(), pcbaVersion.c_str() );

    strncpy ( reinterpret_cast<char*> ( hw_version.model ), model.c_str(), MCP_MODEL_LEN );
    strncpy ( reinterpret_cast<char*> ( hw_version.pcbVersion ), pcbVersion.c_str(), MCP_VER_LEN );
    strncpy ( reinterpret_cast<char*> ( hw_version.pcbaVersion ), pcbaVersion.c_str(), MCP_VER_LEN );
  }
  else
  {
    strncpy ( reinterpret_cast<char*> ( hw_version.model ), "LXBOX1000", MCP_MODEL_LEN );
    strncpy ( reinterpret_cast<char*> ( hw_version.pcbVersion ), "A.2", MCP_VER_LEN );
    strncpy ( reinterpret_cast<char*> ( hw_version.pcbaVersion ), "A.2", MCP_VER_LEN );
  }

  #endif
  HandleRsp ( cmd, rsp, MCP_RET_VER_HARDWARE, ( char* ) &hw_version, sizeof ( hw_version ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdVerHardWare::GetObj (  )
{
  return std::make_shared<NetCmdVerHardWare> ( );
}

