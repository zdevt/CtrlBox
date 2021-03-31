/*
 * =====================================================================================
 *
 *       Filename:  NetCmdVerSoftWare.cpp
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

#include "NetCmdVerSoftWare.h"
#include "SystemDefine.h"
#include "Warping787.h"

NetCmdVerSoftWare::NetCmdVerSoftWare (  )
{
}

NetCmdVerSoftWare::~NetCmdVerSoftWare()
{
}

int NetCmdVerSoftWare::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( ver_software_t ) ) )
    return 0;

  sw_version_t  sw_version;

  #if !defined(__i386__) && !defined(__x86_64__)
  ver_software_t* pver_software = reinterpret_cast<ver_software_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if (  pver_software->swType == 1 )
  {
    snprintf ( reinterpret_cast<char*> ( sw_version.swVersion ), MCP_VER_LEN,
               "%s %s", SystemDefine::GetVer().c_str(), __DATE__ );
  }
  else if (  pver_software->swType == 5 )
  {
    uint32_t version = 0;
    GET_ENGPTR->GetFirmwareVersion ( version );
    snprintf ( reinterpret_cast<char*> ( sw_version.swVersion ), MCP_VER_LEN,
               "%d", version );
  }
  else if (  pver_software->swType == 7 )
  {
    uint8_t verh, verm, verl, verr;
    Warping787::GetVer ( verh, verm, verl, verr );
    snprintf ( reinterpret_cast<char*> ( sw_version.swVersion ), MCP_VER_LEN,
               "%d.%d.%d.%d", verh, verm, verl, verr );
    //PRINT_LOG2 ( "ver = %s %d %d %d %d\n", sw_version.swVersion, verh, verm, verl, verr );
  }
  else
    snprintf ( reinterpret_cast<char*> ( sw_version.swVersion ), MCP_VER_LEN,
               "%s %s", SystemDefine::GetVer().c_str(), __DATE__ );

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_VER_SOFTWARE, ( char* ) &sw_version, sizeof ( sw_version ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdVerSoftWare::GetObj (  )
{
  return std::make_shared<NetCmdVerSoftWare> ( );
}

