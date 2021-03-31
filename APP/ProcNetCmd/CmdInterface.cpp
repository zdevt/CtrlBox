/*
 * =====================================================================================
 *
 *       Filename:  CmdInterface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/06/2015 03:07:14 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "CmdInterface.h"
#include "ErrorCode.h"
#include "GetNetWork.h"

#include "NetCmdSetFanPwmEngine.h"
#include "NetCmdSetUniformityCorrectionEnable.h"
#include "NetCmdGetUniformityCorrectionEnable.h"
#include "NetCmdSetUniformityCorrectionSelPos.h"
#include "NetCmdSetUniformityCorrectionGain.h"
#include "NetCmdSetUniformityCorrectionAllGain.h"
#include "NetCmdGetUniformityCorrectionAllGain.h"
#include "NetCmdSetUniformityCorrectionReset.h"

#include "NetCmdGetUsePeriod.h"
#include "NetCmdSetUsePeriod.h"
#include "NetCmdSetUsePeriodEnable.h"
#include "NetCmdGetUsePeriodEnable.h"
#include "NetCmdGetSerialID.h"
#include "NetCmdGetWarpingCoor.h"
#include "NetCmdSetWarpingCoor.h"
#include "NetCmdGetInputSignalResol.h"
#include "NetCmdGetDesktopCoor.h"
#include "NetCmdSetDesktopCoor.h"
#include "CommunicateProtocol.h"
#include "LogPrint.h"

#include "NetCmdSetScreensState.h"
#include "NetCmdSetLutSet.h"
#include "NetCmdSetWplgCoeff.h"
#include "NetCmdSetLutCoeff.h"
#include "NetCmdSetWarpingData.h"
#include "NetCmdGetWarpingResol.h"
#include "NetCmdSetWarpingResol.h"
#include "NetCmdGetWarpingOnlineState.h"
#include "NetCmdSetHardWareReversion.h"
#include "NetCmdSetEngineType.h"
#include "NetCmdGetHSGValue.h"
#include "NetCmdSetHSGValue.h"
#include "NetCmdGetCCATarget.h"
#include "NetCmdSetCCATarget.h"
#include "NetCmdGetCCAEnable.h"
#include "NetCmdSetCCAEnable.h"
#include "NetCmdGetWpc.h"
#include "NetCmdSetWpc.h"
#include "NetCmdSetDmdRegVal.h"
#include "NetCmdGetDmdRegVal.h"
#include "NetCmdGetBgPicNum.h"
#include "NetCmdSetDutyCycle.h"
#include "NetCmdGetDutyCycle.h"
#include "NetCmdGetDutyCycleValue.h"
#include "NetCmdSetDoubleDesktopSwitchMode.h"
#include "NetCmdGetDoubleDesktopSwitchMode.h"
#include "NetCmdSetLlcState.h"
#include "NetCmdGetLlcState.h"
#include "NetCmdGetMonitorOpt.h"
#include "NetCmdSetMonitorOpt.h"
#include "NetCmdGetEngineType.h"
#include "NetCmdGetPowerState.h"
#include "NetCmdGetEngineTemp.h"
#include "NetCmdSetEngineState.h"
#include "NetCmdGetEngineState.h"
#include "NetCmdSetEngineStateSerial.h"
#include "NetCmdSetBoardState.h"
#include "NetCmdVerSoftWare.h"
#include "NetCmdVerHardWare.h"
#include "NetCmdVerMfg.h"
#include "NetCmdSetNetWork.h"
#include "NetCmdGetNetWork.h"
#include "NetCmdSetSysTime.h"
#include "NetCmdGetSysTime.h"
#include "NetCmdSetCubewallConf.h"
#include "NetCmdGetCubewallConf.h"
#include "NetCmdSetProjType.h"
#include "NetCmdGetProjType.h"
#include "NetCmdSetBcMode.h"
#include "NetCmdGetBcMode.h"
#include "NetCmdSetDesktopIndex.h"
#include "NetCmdGetDesktopIndex.h"
#include "NetCmdSetDspEffect.h"
#include "NetCmdGetDspEffect.h"
#include "NetCmdGetEngineType.h"
#include "NetCmdShowIp.h"
#include "NetCmdShowIpSerial.h"
#include "NetCmdShowEngin.h"
#include "NetCmdCreateColorTemp.h"
#include "NetCmdSetColorTemp.h"
#include "NetCmdGetColorTemp.h"
#include "NetCmdSetDac.h"
#include "NetCmdGetDac.h"
#include "NetCmdSetBrightnessPct.h"
#include "NetCmdGetBrightnessPct.h"
#include "NetCmdSetBasicChroma.h"
#include "NetCmdGetBasicChroma.h"
#include "NetCmdSetTargetLuminance.h"
#include "NetCmdGetTargetLuminance.h"
#include "NetCmdSetDmdGamma.h"
#include "NetCmdGetDmdGamma.h"
#include "NetCmdGetBoardState.h"
#include "NetCmdGetEngineWorkTime.h"
#include "NetCmdDelEngineWorkTime.h"
#include "NetCmdGetFanState.h"
#include "NetCmdNull.h"

std::shared_ptr<CmdInterface> CmdInterface::m_CmdInterface = NULL;

CmdInterface::CmdInterface()
{

}

CmdInterface::~CmdInterface()
{

}

std::shared_ptr<CmdInterface> CmdInterface::GeInstance()
{
  if ( !m_CmdInterface )
    m_CmdInterface = std::make_shared<CmdInterface>();

  return m_CmdInterface;
}

std::shared_ptr<NetCmd> CmdInterface::SerialGetObj ( char* buffer, int len )
{
  MCP_HEADER_t* pMCP_HEADER = reinterpret_cast<MCP_HEADER_t*> ( buffer );
  std::string ip, mask;
  GetNetWork::GetIp ( ip, mask );
  uint16_t sessionid = ( uint16_t ) ( ( ( uint32_t ) inet_addr ( ip.c_str() ) ) >> 16 );
  uint32_t cubeid;
  XmlConfig::GetParam ( "CubeWallConf", "CUBEID", cubeid, 0u );

  #if 0
  PRINT_LOG ( LOG_LEVEL_NORMAL, "%04x %04x %04x %04x %08x %08x\n",
              pMCP_HEADER->mcp_magicword, pMCP_HEADER->mcp_id, pMCP_HEADER->mcp_type,
              pMCP_HEADER->mcp_subtype, pMCP_HEADER->mcp_status, pMCP_HEADER->mcp_datalen );
  #endif

  if ( pMCP_HEADER->mcp_type != MCP_COMMAND )
    return std::make_shared<NetCmdNull> (  );

  if ( pMCP_HEADER->mcp_subtype != MCP_CMD_SHOW_IP && /*  显示IP 不过滤 */
       pMCP_HEADER->mcp_subtype != MCP_CMD_SET_ENGINESTATE_SERIAL ) /*  串口开关机 不过滤 */
  {
    if ( pMCP_HEADER->mcp_id != sessionid &&
         pMCP_HEADER->mcp_id != 0xfefe &&
         pMCP_HEADER->mcp_id != ( u_int16_t ) cubeid ) /* 过滤 session id */
      return std::make_shared<NetCmdNull> (  );
  }

  PRINT_LOG ( LOG_LEVEL_NORMAL, "mcp_subtype = 0x%02x\n", pMCP_HEADER->mcp_subtype );

  if ( 0xfefe == pMCP_HEADER->mcp_id  &&
       pMCP_HEADER->mcp_subtype == MCP_CMD_GET_SERIALID )
  {
    //特殊指令处理，每个单元根据IP用户地址休眠不一样的时间，以实现不同应答包可以错开的目的。
    long to = ( ( unsigned char ) ( sessionid >> 8 ) ) * 1000000 / 254;
    usleep ( to );
  }

  if ( pMCP_HEADER->mcp_subtype == MCP_CMD_SHOW_IP &&
       pMCP_HEADER->mcp_id      != sessionid )
  {
    return GeInstance()->GetObj ( MCP_CMD_SHOW_IP_SERIAL );
  }
  else
  {
    return GeInstance()->GetObj ( pMCP_HEADER->mcp_subtype );
  }
}

std::shared_ptr<NetCmd> CmdInterface::GetObj ( char* buffer, int len )
{
  MCP_HEADER_t* pMCP_HEADER = reinterpret_cast<MCP_HEADER_t*> ( buffer );

  if ( pMCP_HEADER->mcp_type != MCP_COMMAND )
    return std::make_shared<NetCmdNull> (  );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "mcp_subtype = 0x%02x\n", pMCP_HEADER->mcp_subtype );

  return GeInstance()->GetObj ( pMCP_HEADER->mcp_subtype );
}

std::shared_ptr<NetCmd> CmdInterface::GetObj ( int cmd )
{
  auto iter = m_mapCmdpGetObj.find ( cmd );

  if ( iter != m_mapCmdpGetObj.end() )
    return ( iter->second ) ( );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "cmd=0x%02x Not Found!!!!!!\n", cmd );
  return std::make_shared<NetCmdNull> ();
}

/* 添加新的命令只需要添加头文件后在这里添加即可 */
std::map<int, pGetNetCmdObj> CmdInterface::m_mapCmdpGetObj =
{
  { MCP_CMD_SET_ENGINESTATE,        NetCmdSetEngineState::GetObj },
  { MCP_CMD_GET_ENGINESTATE,        NetCmdGetEngineState::GetObj },

  { MCP_CMD_SET_ENGINESTATE_SERIAL, NetCmdSetEngineStateSerial::GetObj },

  { MCP_CMD_SET_BOARDSTATE,         NetCmdSetBoardState::GetObj  },
  { MCP_CMD_VER_SOFTWARE,           NetCmdVerSoftWare::GetObj },
  { MCP_CMD_VER_HARDWARE,           NetCmdVerHardWare::GetObj },
  { MCP_CMD_VER_MFG,                NetCmdVerMfg::GetObj },

  { MCP_CMD_SET_NETWORK,            NetCmdSetNetWork::GetObj },
  { MCP_CMD_GET_NETWORK,            NetCmdGetNetWork::GetObj },

  { MCP_CMD_SET_SYSTIME,            NetCmdSetSysTime::GetObj },
  { MCP_CMD_GET_SYSTIME,            NetCmdGetSysTime::GetObj },

  { MCP_CMD_SET_CUBEWALLCONF,       NetCmdSetCubewallConf::GetObj },
  { MCP_CMD_GET_CUBEWALLCONF,       NetCmdGetCubewallConf::GetObj },

  { MCP_CMD_SET_PORJTYPE,           NetCmdSetProjType::GetObj },
  { MCP_CMD_GET_PORJTYPE,           NetCmdGetProjType::GetObj },

  { MCP_CMD_SET_BCMODE,             NetCmdSetBcMode::GetObj },
  { MCP_CMD_GET_BCMODE,             NetCmdGetBcMode::GetObj },

  { MCP_CMD_SET_DESKTOPINDEX,       NetCmdSetDesktopIndex::GetObj },
  { MCP_CMD_GET_DESKTOPINDEX,       NetCmdGetDesktopIndex::GetObj },

  { MCP_CMD_SET_DSPEFFECT,          NetCmdSetDspEffect::GetObj },
  { MCP_CMD_GET_DSPEFFECT,          NetCmdGetDspEffect::GetObj },

  { MCP_CMD_GET_ENGINETYPE,         NetCmdGetEngineType::GetObj },
  { MCP_CMD_SHOW_IP,                NetCmdShowIp::GetObj },
  { MCP_CMD_SHOW_IP_SERIAL,         NetCmdShowIpSerial::GetObj },
  { MCP_CMD_SHOW_ENGIN,             NetCmdShowEngin::GetObj },

  { MCP_CMD_SET_COLORTEMP,          NetCmdSetColorTemp::GetObj },
  { MCP_CMD_GET_COLORTEMP,          NetCmdGetColorTemp::GetObj },

  { MCP_CMD_SET_DAC,                NetCmdSetDac::GetObj },
  { MCP_CMD_GET_DAC,                NetCmdGetDac::GetObj },

  { MCP_CMD_SET_BRIGHTNESSPCT,      NetCmdSetBrightnessPct::GetObj },
  { MCP_CMD_GET_BRIGHTNESSPCT,      NetCmdGetBrightnessPct::GetObj },

  { MCP_CMD_SET_BASICCHROMA,        NetCmdSetBasicChroma::GetObj },
  { MCP_CMD_GET_BASICCHROMA,        NetCmdGetBasicChroma::GetObj },

  { MCP_CMD_SET_TARGETLUMINANCE,    NetCmdSetTargetLuminance::GetObj },
  { MCP_CMD_GET_TARGETLUMINANCE,    NetCmdGetTargetLuminance::GetObj },

  { MCP_CMD_SET_DMDGAMMA,           NetCmdSetDmdGamma::GetObj },
  { MCP_CMD_GET_DMDGAMMA,           NetCmdGetDmdGamma::GetObj },

  { MCP_CMD_GET_BOARDSTATE,         NetCmdGetBoardState::GetObj },

  { MCP_CMD_GET_ENGINEWORKTIME,     NetCmdGetEngineWorkTime::GetObj },
  { MCP_CMD_DEL_ENGINEWORKTIME,     NetCmdDelEngineWorkTime::GetObj },

  { MCP_CMD_GET_FANSTATE,           NetCmdGetFanState::GetObj },
  { MCP_CMD_GET_ENGINETEMP,         NetCmdGetEngineTemp::GetObj },

  { MCP_CMD_GET_POWERSTATE,         NetCmdGetPowerState::GetObj },
  { MCP_CMD_GET_ENGINETYPE,         NetCmdGetEngineType::GetObj },

  { MCP_CMD_SET_MONITOROPT,         NetCmdSetMonitorOpt::GetObj },
  { MCP_CMD_GET_MONITOROPT,         NetCmdGetMonitorOpt::GetObj },

  { MCP_CMD_SET_LLCSTATE,           NetCmdSetLlcState::GetObj },
  { MCP_CMD_GET_LLCSTATE,           NetCmdGetLlcState::GetObj },
  { MCP_CMD_SET_DOUBLEDESKTOP_SWITCHMODE,           NetCmdSetDoubleDesktopSwitchMode::GetObj },
  { MCP_CMD_GET_DOUBLEDESKTOP_SWITCHMODE,           NetCmdGetDoubleDesktopSwitchMode::GetObj },

  { MCP_CMD_SET_DCINDEX,            NetCmdSetDutyCycle::GetObj },
  { MCP_CMD_GET_DCINDEX,            NetCmdGetDutyCycle::GetObj },
  { MCP_CMD_GET_DCVALUE,            NetCmdGetDutyCycleValue::GetObj },
  { MCP_CMD_GET_BGPICNUM,           NetCmdGetBgPicNum::GetObj },

  { MCP_CMD_SET_DMDREGVAL,          NetCmdSetDmdRegVal::GetObj },
  { MCP_CMD_GET_DMDREGVAL,          NetCmdGetDmdRegVal::GetObj },

  { MCP_CMD_SET_WPC,          			NetCmdSetWpc::GetObj },
  { MCP_CMD_GET_WPC,          			NetCmdGetWpc::GetObj },

  { MCP_CMD_SET_CCAENABLE,          NetCmdSetCCAEnable::GetObj },
  { MCP_CMD_GET_CCAENABLE,          NetCmdGetCCAEnable::GetObj },

  { MCP_CMD_SET_CCATARGET,          NetCmdSetCCATarget::GetObj },
  { MCP_CMD_GET_CCATARGET,          NetCmdGetCCATarget::GetObj },

  { MCP_CMD_SET_HSGVALUE,          	NetCmdSetHSGValue::GetObj },
  { MCP_CMD_GET_HSGVALUE,          	NetCmdGetHSGValue::GetObj },

  { MCP_CMD_SET_ENGINETYPE,         NetCmdSetEngineType::GetObj },
  { MCP_CMD_SET_HARDWAREREVERSION,  NetCmdSetHardWareReversion::GetObj },

  { MCP_CMD_GET_WARPINGONLINESTATE, NetCmdGetWarpingOnlineState::GetObj },
  { MCP_CMD_SET_WARPINGRESOL, 			NetCmdSetWarpingResol::GetObj },
  { MCP_CMD_GET_WARPINGRESOL, 			NetCmdGetWarpingResol::GetObj },
  { MCP_CMD_SET_WARPINGREDATA, 			NetCmdSetWarpingData::GetObj },
  { MCP_CMD_SET_LUTCOEFF,           NetCmdSetLutCoeff::GetObj },
  { MCP_CMD_SET_WPLGCOEFF,          NetCmdSetWplgCoeff::GetObj },
  { MCP_CMD_SET_LUTSET,             NetCmdSetLutSet::GetObj },

  { MCP_CMD_SET_SCREENSTATE,        NetCmdSetScreensState::GetObj },

  { MCP_CMD_SET_DESKTOPCOOR,        NetCmdSetDesktopCoor::GetObj },
  { MCP_CMD_GET_DESKTOPCOOR,        NetCmdGetDesktopCoor::GetObj },
  { MCP_CMD_GET_INPUTSIGNALRESOL,   NetCmdGetInputSignalResol::GetObj },
  { MCP_CMD_SET_WARPINGCOOR,   			NetCmdSetWarpingCoor::GetObj },
  { MCP_CMD_GET_WARPINGCOOR,   			NetCmdGetWarpingCoor::GetObj },

  { MCP_CMD_SET_USEPERIODENABLE,    NetCmdSetUsePeriodEnable::GetObj },
  { MCP_CMD_GET_USEPERIODENABLE,    NetCmdGetUsePeriodEnable::GetObj },
  { MCP_CMD_SET_USEPERIOD,          NetCmdSetUsePeriod::GetObj },
  { MCP_CMD_GET_USEPERIOD,          NetCmdGetUsePeriod::GetObj },
  { MCP_CMD_GET_SERIALID,           NetCmdGetSerialID::GetObj },

  { MCP_CMD_SET_UCENABLE,    			  NetCmdSetUniformityCorrectionEnable::GetObj },
  { MCP_CMD_GET_UCENABLE,    			  NetCmdGetUniformityCorrectionEnable::GetObj },
  { MCP_CMD_SET_UCSELPOS,      		  NetCmdSetUniformityCorrectionSelPos::GetObj },
  { MCP_CMD_SET_UCGAIN,      			  NetCmdSetUniformityCorrectionGain::GetObj },
  { MCP_CMD_SET_UCALLGAIN,   			  NetCmdSetUniformityCorrectionAllGain::GetObj },
  { MCP_CMD_GET_UCALLGAIN,          NetCmdGetUniformityCorrectionAllGain::GetObj },
  { MCP_CMD_SET_UCRESET,      		  NetCmdSetUniformityCorrectionReset::GetObj },

  { MCP_CMD_SET_FANPWM,      		  NetCmdSetFanPwmEngine::GetObj },
};

