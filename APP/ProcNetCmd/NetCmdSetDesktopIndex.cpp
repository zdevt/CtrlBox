/*
 * =====================================================================================
 *
 *       Filename:  NetCmdSetDesktopIndex.cpp
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

#include "NetCmdSetDesktopIndex.h"
#include "XmlConfig.h"
#include "FpgaImageSwitch.h"

NetCmdSetDesktopIndex::NetCmdSetDesktopIndex ( )
{
}

NetCmdSetDesktopIndex::~NetCmdSetDesktopIndex()
{
}

int NetCmdSetDesktopIndex::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( set_desktop_index_t ) ) )
    return 0;

  MCP_STATUS_t mcp_status;
  mcp_status.status = 0;

  #if defined(__arm__)
  set_desktop_index_t* pset_desktop_index = reinterpret_cast<set_desktop_index_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  if ( FpgaImageSwitch::GetDeskTopIndex() == 0 || FpgaImageSwitch::GetDeskTopIndex() == 15 )
  {
    fpga_reg_pic_pro_ctl_t fpga_reg_pic_pro_ctl;
    fpga_reg_pic_pro_ctl.data = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
    fpga_reg_pic_pro_ctl.logo_en = 0;
    FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, fpga_reg_pic_pro_ctl.data );
  }

  FpgaImageSwitch::SetDeskTopIndex ( pset_desktop_index->desktopIndex );
  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_STATUS, reinterpret_cast<char*> ( &mcp_status ), sizeof ( mcp_status ) );
}

std::shared_ptr<NetCmd> NetCmdSetDesktopIndex::GetObj ()
{
  return std::make_shared<NetCmdSetDesktopIndex> (  );
}

