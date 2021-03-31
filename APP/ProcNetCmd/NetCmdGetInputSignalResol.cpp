/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetInputSignalResol.cpp
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

#include "NetCmdGetInputSignalResol.h"
#include "MainboardInterface.h"

NetCmdGetInputSignalResol::NetCmdGetInputSignalResol (  )
{
}

NetCmdGetInputSignalResol::~NetCmdGetInputSignalResol()
{
}

int NetCmdGetInputSignalResol::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) ) )
    return 0;

  get_inputsignalresol_t get_inputsignalresol;
  #if defined(__arm__)
  GET_MBPTR->GetInputSignalResol ( get_inputsignalresol.width, get_inputsignalresol.height );
  #endif

  HandleRsp ( cmd, rsp, MCP_RET_GET_INPUTSIGNALRESOL, reinterpret_cast<char*> ( &get_inputsignalresol ), sizeof ( get_inputsignalresol ) );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdGetInputSignalResol::GetObj (  )
{
  return std::make_shared<NetCmdGetInputSignalResol> ( );
}

