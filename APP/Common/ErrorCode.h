/*
 * =====================================================================================
 *
 *       Filename:  ErrorCode.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/18/2014 10:50:31 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  ERRORCODE_INC
#define  ERRORCODE_INC

enum
{
  ERROR_CODE_OK                 = 0,

  ERROR_TCPLINK_ERROR_BASE      = 0x10000,
  ERROR_NETLINK_ERROR_BASE      = 0x10100,
  ERROR_TCPSERVER_ERROR_BASE    = 0x10200,
  ERROR_UPGRADEFILE_ERROR_BASE  = 0x10300,
  ERROR_CONFIG_DATA_ERROR_BASE  = 0x10400,
  ERROR_HARDWARE_ERROR_BASE     = 0x10500,

  ERROR_CODE_MAX,
};

#endif   /* ----- #ifndef ERRORCODE_INC  ----- */


