/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDesktopCoor.cpp
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

#include "NetCmdSetDesktopCoor.h"

NetCmdSetDesktopCoor::NetCmdSetDesktopCoor (  )
{
}

NetCmdSetDesktopCoor::~NetCmdSetDesktopCoor()
{
}

int NetCmdSetDesktopCoor::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_desktopcoor_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_desktopcoor_t* pset_desktopcoor = reinterpret_cast<set_desktopcoor_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );
  XmlConfig::SetParam ( "SignalRect", "x", pset_desktopcoor->x );
  XmlConfig::SetParam ( "SignalRect", "y", pset_desktopcoor->y );
  XmlConfig::SetParam ( "SignalRect", "w", pset_desktopcoor->w );
  XmlConfig::SetParam ( "SignalRect", "h", pset_desktopcoor->h );

  if ( ( 0 == pset_desktopcoor->x ) &&
       ( 0 == pset_desktopcoor->y ) &&
       ( 0 == pset_desktopcoor->w ) &&
       ( 0 == pset_desktopcoor->h ) )
  {
    GET_MBPTR->SetCutWinFlag ( false );
  }
  else
  {
    GET_MBPTR->SetCutWinFlag ( true );

    uint32_t vd_hres, vd_vres;

    if ( 0 == GET_MBPTR->GetInputSignalResol ( vd_hres, vd_vres ) )
    {
      GET_MBPTR->SetInputSignalRectAndShow ( pset_desktopcoor->x, pset_desktopcoor->y,
                                             pset_desktopcoor->w, pset_desktopcoor->h,
                                             vd_hres, vd_vres );
    }
  }

  #endif

  HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdSetDesktopCoor::GetObj (  )
{
  return std::make_shared<NetCmdSetDesktopCoor> ( );
}

