/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetDmdRegVal.cpp
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

#include "NetCmdGetDmdRegVal.h"
#include "OpticEngineInterface.h"

NetCmdGetDmdRegVal::NetCmdGetDmdRegVal ( )
{
}

NetCmdGetDmdRegVal::~NetCmdGetDmdRegVal()
{
}

int NetCmdGetDmdRegVal::HandleCmd ( vechar& cmd, vechar& rsp )
{
  if ( cmd.size() < ( sizeof ( MCP_HEADER_t ) + sizeof ( get_dmd_reg_val_t ) ) )
    return 0;

  #if defined(__arm__)
  get_dmd_reg_val_t* pget_dmd_reg_val = reinterpret_cast<get_dmd_reg_val_t*> ( &cmd[0] + sizeof ( MCP_HEADER_t ) );

  vechar vecBuffer;
  vecBuffer.resize ( sizeof ( ret_get_dmd_reg_val_t ) + pget_dmd_reg_val->readlen, 0 );

  ret_get_dmd_reg_val_t* pret_get_dmd_reg_val = reinterpret_cast<ret_get_dmd_reg_val_t*> ( &vecBuffer[0] );

  pret_get_dmd_reg_val->datalen = pget_dmd_reg_val->readlen;

  GET_ENGPTR->GetDmdRegVal ( pget_dmd_reg_val->subaddr,
                             pget_dmd_reg_val->datalen, pget_dmd_reg_val->data,
                             pret_get_dmd_reg_val->datalen, pret_get_dmd_reg_val->data );

  #endif

  return HandleRsp ( cmd, rsp, MCP_RET_GET_DMDREGVAL, reinterpret_cast<char*> ( &vecBuffer[0] ), vecBuffer.size() );
}

std::shared_ptr<NetCmd> NetCmdGetDmdRegVal::GetObj ()
{
  return std::make_shared<NetCmdGetDmdRegVal> (  );
}

