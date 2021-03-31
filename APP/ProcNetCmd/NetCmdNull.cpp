/*
 * =====================================================================================
 *
 *       Filename:  NetCmdNull.cpp
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

#include <stdio.h>
#include <string>

#include "NetCmdNull.h"

NetCmdNull::NetCmdNull (  )
{
}

NetCmdNull::~NetCmdNull()
{
}

int NetCmdNull::HandleCmd ( vechar& cmd, vechar& rsp )
{
  rsp.resize ( 0 );
  //HandleRsp ( cmd, rsp, 0, const_cast<char*> ( str.c_str() ), str.size() );
  return 0;
}

std::shared_ptr<NetCmd> NetCmdNull::GetObj ()
{
  return std::make_shared<NetCmdNull> (  );
}

