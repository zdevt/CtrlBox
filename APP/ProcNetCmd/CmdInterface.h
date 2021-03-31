/*
 * =====================================================================================
 *
 *       Filename:  CmdInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:07:31 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  CMDINTERFACE_INC
#define  CMDINTERFACE_INC

#include <memory>
#include <map>

#include "NetCmd.h"

typedef std::shared_ptr<NetCmd> ( *pGetNetCmdObj ) (  );

class CmdInterface
{
  public:
    CmdInterface();
    virtual ~CmdInterface();

  public:
    static std::shared_ptr<NetCmd> GetObj ( char* buffer, int len );
    static std::shared_ptr<NetCmd> SerialGetObj ( char* buffer, int len );

  private:
    static std::shared_ptr<CmdInterface> GeInstance();

  private:
    std::shared_ptr<NetCmd> GetObj ( int cmd );

  private:
    static std::map<int, pGetNetCmdObj> m_mapCmdpGetObj;
    static std::shared_ptr<CmdInterface> m_CmdInterface;
};

#endif   /* ----- #ifndef CMDINTERFACE_INC  ----- */

