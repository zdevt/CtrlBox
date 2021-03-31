/*
 * =====================================================================================
 *
 *       Filename:  NetCmdGetBasicChroma.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:13:32 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  NETCMDGETBASICCHROMA_INC
#define  NETCMDGETBASICCHROMA_INC

#include "NetCmd.h"

#pragma pack(push)
#pragma pack(1)

typedef union
{
  struct
  {
    uint8_t r: 1;
    uint8_t g: 1;
    uint8_t b: 1;
    uint8_t res: 5;
  };
  uint32_t mask;
} get_basicchroma_cmd_t;

typedef struct
{
  #ifdef MCP_CHROMA_USEING_STR
  char x[MCP_CHROMA_LEN];
  char y[MCP_CHROMA_LEN];
  #else
  uint32_t x;
  uint32_t y;
  #endif
  uint32_t l;
} get_basic_chroma_t;

typedef struct
{
  get_basicchroma_cmd_t cmd;
  get_basic_chroma_t r;
  get_basic_chroma_t g;
  get_basic_chroma_t b;
} get_basicchroma_t;
#pragma pack(pop)

class NetCmdGetBasicChroma : public NetCmd
{
  public:
    NetCmdGetBasicChroma (  );
    virtual ~NetCmdGetBasicChroma();

  public:
    virtual int HandleCmd ( vechar& cmd, vechar& rsp );

    static std::shared_ptr<NetCmd> GetObj (  );
};


#endif   /* ----- #ifndef NETCMDONOFF_INC  ----- */

