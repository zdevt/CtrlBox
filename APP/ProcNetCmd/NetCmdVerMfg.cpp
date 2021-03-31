/*
 * =====================================================================================
 *
 *       Filename:  NetCmdVerMfg.cpp
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

#include "NetCmdVerMfg.h"

NetCmdVerMfg::NetCmdVerMfg (  )
{
}

NetCmdVerMfg::~NetCmdVerMfg()
{
}

int NetCmdVerMfg::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( mfg_type_t ) ) )
    return 0;

  mfg_version_t mfg_version;
  #if !defined(__i386__) && !defined(__x86_64__)
  mfg_type_t* pmfg_type = reinterpret_cast<mfg_type_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( pmfg_type->iType == 0 )
  {
    strncpy ( reinterpret_cast<char*> ( mfg_version.date ), "20150628", 12 );
    strncpy ( reinterpret_cast<char*> ( mfg_version.vender ), "IBM", 16 );
    strncpy ( reinterpret_cast<char*> ( mfg_version.seqnum ), "123456789", 16 );
  }
  else
  {
    strncpy ( reinterpret_cast<char*> ( mfg_version.date ), "20150628", 12 );
    strncpy ( reinterpret_cast<char*> ( mfg_version.vender ), "IBM", 16 );
    strncpy ( reinterpret_cast<char*> ( mfg_version.seqnum ), "123456789", 16 );
  }

  #endif
  HandleRsp ( cmd, rsp, MCP_RET_VER_MFG, ( char* ) &mfg_version, sizeof ( mfg_version ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdVerMfg::GetObj (  )
{
  return std::make_shared<NetCmdVerMfg> ( );
}

