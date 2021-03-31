/*
 * =====================================================================================
 *
 *       Filename:  CommunicateProtocol.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/23/2014 07:43:30 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  COMMUNICATEPROTOCOL_INC
#define  COMMUNICATEPROTOCOL_INC

#include <sys/types.h>


/*
 * 通讯协议包包头长度为16字节，其中：
 *  Magic Word为2字节，固定为“0xeb90”，用来标记协议包的开始。
 *  会话ID用来标志一个协议包的ID，由发送命令包或者消息包者来产生和保证其唯一性。
 *  消息类型是区分消息的类别，分为COMMAND、RETURN和MESSAGE三类。
 *  消息子类型是具体的消息操作命令码。
 *  状态位只在RETURN时生效，表示COMMAND指令操作结果或状态。
 *  数据长度是指消息数据的长度。
 */

#define MCP_ADDR_LEN      24
#define MCP_MAC_LEN       24
#define MCP_NAME_LEN      24
#define MCP_VER_LEN       8
#define MCP_MODEL_LEN     24
#define MCP_STATUS_LEN    28

#define MCP_MAGICWORD     (0xeb90)

#pragma pack(push)
#pragma pack(1)
//协议头部
struct _mcp_header_t
{
  u_int16_t     mcp_magicword;  /*0xeb90*/
  u_int16_t     mcp_id;         /*会话ID，由控制软件创建*/
  u_int16_t     mcp_type;       /*对应EnumMcpType */
  u_int16_t     mcp_subtype;    /*对应EnumMcpSubtype */
  int32_t       mcp_status;     /*状态位，0表示成功，其他表示失败*/
  u_int32_t     mcp_datalen;
  int8_t        mcp_data[0];
};
typedef struct _mcp_header_t    MCP_HEADER_t;

#define MCP_HEADER_T_LEN   (sizeof(MCP_HEADER_t))

struct _mcp_status_t
{
  int32_t     status;           /*状态位，0表示成功，其他表示失败*/
  int8_t      dsc[MCP_STATUS_LEN];  /*状态对应的描述信息*/
};
typedef struct _mcp_status_t MCP_STATUS_t;

#pragma pack(pop)

//命令定义
enum EnumMcpType
{
  MCP_COMMAND = 0x0001,
  MCP_RETURN,
  MCP_MESSAGE,
  MCP_MAX,
};


enum EnumMcpSubtype
{
  //操作设备
  MCP_CMD_SET_ENGINESTATE = 0x1,  /*设置光机开待机状态*/
  MCP_CMD_GET_ENGINESTATE,    /*查询光机开待机状态*/
  MCP_CMD_SET_BOARDSTATE, /*主控板设备*/

  //查询版本
  MCP_CMD_VER_SOFTWARE = 0x6, /*查询软件版本信息*/
  MCP_CMD_VER_HARDWARE,   /*查询硬件版本信息*/
  MCP_CMD_VER_MFG,        /*查询单板制造信息*/

  //配置系统
  MCP_CMD_SET_NETWORK = 0x10,/*设置网络参数：MAC/IP地址、子网掩码和网关*/
  MCP_CMD_GET_NETWORK = 0x11,       /*查询网络参数：MAC/IP地址、子网掩码和网关*/
  MCP_CMD_SET_SYSTIME = 0x12,      /*设置系统时间*/
  MCP_CMD_GET_SYSTIME = 0x13,      /*查询系统时间*/
  MCP_CMD_SET_TIMECALIBSERVER = 0x14,   /*设置时间校准服务参数*/
  MCP_CMD_GET_TIMECALIBSERVER = 0x15,   /*查询时间校准服务参数*/
  MCP_CMD_SET_TIMECALIB = 0x16,         /*设置时间校准服务状态*/
  MCP_CMD_GET_TIMECALIB = 0x17,         /*查询时间校准服务状态*/
  MCP_CMD_SET_CTRLSERVERIP = 0x18,      /*设置控制软件服务IP地址*/
  MCP_CMD_GET_CTRLSERVERIP = 0x19,      /*查询控制软件服务IP地址*/
  MCP_CMD_SET_CUBEWALLCONF = 0x1a,   /*设置单元的大墙配置参数*/
  MCP_CMD_GET_CUBEWALLCONF = 0x1b,    /*查询单元的大墙配置参数*/
  MCP_CMD_GET_ALLCUBEWALLCONF, /*查询单元的大墙配置参数*/
  MCP_CMD_DEL_CUBEWALLCONF,    /*删除单元的大墙配置参数*/
  MCP_CMD_GET_PARAMRANGE,      /*获取配置参数有效值范围*/
  MCP_CMD_ONLINE_CTRLSERVER,     /*控制服务上线广播，控制服务间使用*/

  //画面控制
  MCP_CMD_SET_PORJTYPE = 0x40,  /*设置投影方式*/
  MCP_CMD_GET_PORJTYPE,     /*设置投影方式*/
  MCP_CMD_SET_DESKTOPINDEX,   /*设置当前桌面显示信号*/
  MCP_CMD_GET_DESKTOPINDEX,   /*查询当前桌面显示信号*/
  MCP_CMD_GET_BGPICNUM ,    /*查询桌面背景图片数量*/
  MCP_CMD_SET_BGPICPLAYTYPE,    /*设置桌面背景图片播放方式*/
  MCP_CMD_GET_BGPICPLAYTYPE,    /*查询桌面背景图片播放方式*/
  MCP_CMD_SET_DSPEFFECT,        /*设置画面显示特效*/
  MCP_CMD_GET_DSPEFFECT,        /*查询画面显示特效*/
  MCP_CMD_SHOW_IP,              /*显示IP地址*/
  MCP_CMD_GET_ENGINETYPE,       /*  获取光机类型 */
  MCP_CMD_SHOW_ENGIN,       /*显示光机画面*/

  //颜色管理
  MCP_CMD_SET_BCMODE = 0x60,    /*设置极致色彩（BrilliantColor）模式*/
  MCP_CMD_GET_BCMODE,       /*查询极致色彩（BrilliantColor）模式*/
  MCP_CMD_SET_DMDGAMMA,   /*设置DMD伽玛曲线*/
  MCP_CMD_GET_DMDGAMMA,   /*查询DMD伽玛曲线*/
  MCP_CMD_SET_COLORTEMP,    /*设置色温*/
  MCP_CMD_GET_COLORTEMP,    /*查询色温*/
  MCP_CMD_SET_DAC,            /*设置DAC值*/
  MCP_CMD_GET_DAC = 0x67,            /*查询DAC值*/
  MCP_CMD_SET_BRIGHTNESSPCT,  /*  设置亮度百分比 */
  MCP_CMD_GET_BRIGHTNESSPCT,  /*   */
  MCP_CMD_SET_BASICCHROMA,   /*  设置基色 */
  MCP_CMD_GET_BASICCHROMA = 0x6b,
  MCP_CMD_SET_TARGETLUMINANCE, /*  设置目标亮度  */
  MCP_CMD_GET_TARGETLUMINANCE,
  MCP_CMD_CREATE_OPM,           /*创建光学参数模式*/
  MCP_CMD_OPEN_OPM,            /*调用光学参数模式*/
  MCP_CMD_SET_OPMNAME,         /*设置光学参数模式名称*/
  MCP_CMD_GET_OPMNAME,         /*查询光学参数模式名称*/
  MCP_CMD_SET_OPMPWD,          /*设置光学参数模式密码*/
  MCP_CMD_SET_OPMROOTPWD,     /*查询光学参数模式超级用户密码*/
  MCP_CMD_GET_OPMALLPARAMS,    /*查询光学参数模式所有参数*/
  MCP_CMD_SET_LLCSTATE,         /*设置局部亮度补偿（Local Luminance Compensate）状态*/
  MCP_CMD_GET_LLCSTATE,          /*查询局部亮度补偿（LLC）状态*/
  MCP_CMD_START_LLC,             /*开始局部亮度补偿（LLC）*/
  MCP_CMD_STOP_LLC,              /*停止局部亮度补偿（LLC）*/
  MCP_CMD_SET_LLCMASK,           /*保存局部亮度补偿掩码参数*/
  MCP_CMD_SAVE_LLCFILE,           /*保存局部亮度补偿参数文件*/
  MCP_CMD_GET_LLCFILELEN,         /*查询局部亮度补偿参数文件长度*/
  MCP_CMD_GET_LLCFILEPAGE,        /*获取局部亮度补偿参数文件页内容*/

  //图像回显
  MCP_CMD_SET_CAPTUREIMGSTATE = 0x100, /*设置图像回显状态*/
  MCP_CMD_GET_CAPTUREIMGSTATE,   /*查询图像回显状态*/
  MCP_CMD_SET_CAPTUREIMGSIZE,     /*设置图像回显大小*/
  MCP_CMD_GET_CAPTUREIMGSIZE,    /*查询图像回显大小*/
  MCP_CMD_SET_CAPTUREIMGRATE,    /*设置图像回显帧率*/
  MCP_CMD_GET_CAPTUREIMGRATE,    /*查询图像回显帧率*/

  //状态监控
  MCP_CMD_GET_ONLINESTATE     = 0x110,    /*查询主控板在线状态*/
  MCP_CMD_GET_BOARDSTATE,   /*获取单板在线状态*/
  MCP_CMD_SET_MONITOROPT,   /*设置监控轮询项*/
  MCP_CMD_GET_MONITOROPT,   /*查询监控轮询项*/
  MCP_CMD_SET_MONITORWARN,  /*设置监控警戒值*/
  MCP_CMD_GET_MONITORWARN,  /*获取监控警戒值*/
  MCP_CMD_GET_ENGINEWORKTIME  = 0x116, /*查询光机工作时间*/
  MCP_CMD_DEL_ENGINEWORKTIME  = 0x117, /*清除光机工作时间*/
  MCP_CMD_GET_FANSTATE        = 0x118, /*查询风扇状态*/
  MCP_CMD_GET_ENGINETEMP      = 0x119, /*查询温度*/
  MCP_CMD_GET_POWERSTATE      = 0x11a, /*查询电源状态*/

  //日志相关
  MCP_CMD_GET_LOG  = 0x150,   /*查询日志*/
  MCP_CMD_GET_LOGPAGES,     /*查询日志内容*/
  MCP_CMD_DEL_LOGS,       /*清除所有日志*/
  MCP_CMD_GET_LOGMODS,      /*查询日志模块*/

  //消息上报
  MCP_CMD_SET_MSGREPORTLEVEL = 0x160, /*设置消息上报级别*/
  MCP_CMD_GET_MSGREPORTLEVEL = 0x161, /*查询消息上报级别*/

  //系统升级
  MCP_CMD_UPGRADE_BEGIN     = 0x170, /* 升级开始 */
  MCP_CMD_UPGRADE_TRANSFILE = 0x171, /* 传输升级文件 */
  MCP_CMD_UPGRADE_END       = 0x172, /* 升级结束 */

  //命令返回指令
  MCP_RET_STATUS            = 0x500,   /*返回命令执行状态*/
  MCP_RET_BCSTATUS          = 0x501,    /*广播返回命令执行状态*/

  //返回操作设备状态
  MCP_RET_GET_ENGINESTATE   = 0x505,  /*返回光机开待机状态*/

  //返回版本信息
  MCP_RET_VER_SOFTWARE      = 0x510, /*返回软件版本信息*/
  MCP_RET_VER_HARDWARE,       /*返回硬件版本信息*/
  MCP_RET_VER_MFG,        /*返回单板制造信息*/

  //返回系统配置信息
  MCP_RET_GET_NETWORK       = 0x520,/*返回网络参数：MAC/IP地址、子网掩码和网关*/
  MCP_RET_GET_SYSTIME,      /*返回系统时间*/
  MCP_RET_GET_TIMECALIBSERVER,    /*返回时间校准服务参数*/
  MCP_RET_GET_TIMECALIB,          /*返回时间校准服务状态*/
  MCP_RET_GET_CTRLSERVERIP,       /*返回控制软件服务IP地址*/
  MCP_RET_GET_CUBEWALLCONF,     /*返回单元的大墙配置参数*/
  MCP_RET_GET_ALLCUBEWALLCONF,  /*返回单元的大墙配置参数*/
  MCP_RET_GET_PARAMRANGE,      /*返回配置参数有效值范围*/
  MCP_RET_ONLINE_CTRLSERVER,     /*控制服务上线广播反馈，控制服务间使用*/

  //画面控制
  MCP_RET_GET_PORJTYPE      = 0x550, /*返回投影方式*/
  MCP_RET_GET_DESKTOPINDEX,   /*返回当前桌面显示信号*/
  MCP_RET_GET_BGPICNUM ,        /*返回桌面背景图片数量*/
  MCP_RET_GET_BGPICPLAYTYPE,    /*返回桌面背景图片播放方式*/
  MCP_RET_GET_DSPEFFECT,        /*返回画面显示特效*/
  MCP_RET_GET_ENGINETYPE,

  //颜色管理
  MCP_RET_GET_BCMODE = 0x570,   /*返回极致色彩（BrilliantColor）模式*/
  MCP_RET_GET_DMDGAMMA,   /*返回DMD伽玛曲线*/
  MCP_RET_GET_COLORTEMP,        /*返回色温*/
  MCP_RET_GET_DAC,            /*返回DAC值*/
  MCP_RET_GET_BRIGHTNESSPCT,
  MCP_RET_GET_BASICCHROMA,
  MCP_RET_GET_TARGETLUMINANCE,
  MCP_RET_GET_OPMNAME,         /*返回光学参数模式名称*/
  MCP_RET_GET_OPMALLPARAMS,    /*返回光学参数模式所有参数*/
  MCP_RET_GET_LLCSTATE,           /*返回局部亮度补偿（LLC）状态*/
  MCP_RET_GET_LLCFILELEN,         /*返回局部亮度补偿参数文件长度*/
  MCP_RET_GET_LLCFILEPAGE,        /*返回局部亮度补偿参数文件页内容*/

  //图像回显
  MCP_RET_GET_CAPTUREIMGSTATE = 0x600, /*返回图像回显状态*/
  MCP_RET_GET_CAPTUREIMGSIZE,    /*查询图像回显大小*/
  MCP_RET_GET_CAPTUREIMGRATE,    /*查询图像回显帧率*/

  //状态监控
  MCP_RET_GET_ONLINESTATE = 0x610,   /*返回主控板在线状态*/
  MCP_RET_GET_BOARDSTATE,   /*返回单板在线状态*/
  MCP_RET_GET_MONITOROPT, /*返回监控轮询项*/
  MCP_RET_GET_MONITORWARN,      /*返回监控警戒值*/
  MCP_RET_GET_ENGINEWORKTIME, /*返回光机工作时间*/
  MCP_RET_GET_FANSTATE,         /*返回风扇状态*/
  MCP_RET_GET_ENGINETEMP,      /*返回温度*/
  MCP_RET_GET_POWERSTATE,     /*返回电源状态*/

  //日志相关
  MCP_RET_GET_LOG  = 0x640,   /*返回日志*/
  MCP_RET_GET_LOGPAGES,     /*返回日志内容*/
  MCP_RET_GET_LOGMODS,      /*返回日志模块*/

  //消息上报
  MCP_RET_GET_MSGREPORTLEVEL = 0x650, /*返回消息上报级别*/

  //内部调试命令
  MCP_SET_MAINBOARDREG = 0xf00,  /**<设置主控板FPGA的指定寄存器值*/
  MCP_GET_MAINBOARDREG,        /**<获取主控板FPGA的指定寄存器值*/
  MCP_RET_GET_MAINBOARDREG ,   /**<返回主控板FPGA的指定寄存器值*/

  //消息指令
  MCP_MSG_REPORTMSG = 0x1000,    /*主控板上报消息给控制服务*/
  MCP_MSG_UPDATEREPORT = 0x1001, /* 主控板上报升级进度给升级软件 */


  MCP_CMD_OR_RET_MAX,
};


#endif   /* ----- #ifndef COMMUNICATEPROTOCOL_INC  ----- */

