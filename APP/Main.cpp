/*
 * =====================================================================================
 *
 *       Filename:  Main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/23/2014 04:11:51 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <memory>
#include <iostream>
#include <new>

#include "FileLock.h"
#include "AesEncDec.h"

#include "LogPrint.h"
#include "SystemDefine.h"
#include "MainApp.h"
#include "MainboardInterface.h"
#include "OpticEngineInterface.h"
#include "At91GpioDev.h"
#include "Led74Hc595D.h"
#include "PowerOn.h"
#include "PowerSupplyInterface.h"
#include "SerialToNetServer.h"
#include "GpioPwm.h"

void SigInt ( int signal )
{
  MainApp::SetRunFlag ( false );
}

int main ( int argc, char* argv[] )
{
  if ( !FileLock::GetLock() )
  {
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Instance Is Running!\n" );
    return -1;
  }

  signal ( SIGPIPE, SIG_IGN );
  signal ( SIGTERM, SIG_IGN );
  signal ( SIGINT,  SigInt );

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Maketime = % s\n", SystemDefine::GetMakeTime().c_str() );

  /*  复位起来先关闭电源 */
  PowerSupplyInterface::GetPowerSupplyPtr()->Close();
  sleep ( 3 );

  MainApp mainApp;

  //先初始化GPIO引脚
  GET_GPIOPWM->Init();

  Led74Hc595D::Disp ( "0" );

  uint8_t state = 0;

  /*  如果为开机状态则默认开机 */
  GET_ENGPTR->GetPowerState ( state );

  if (  state )
    PowerOn::SetOnOrOff ( state );
  else
    Led74Hc595D::Disp ( "." );


  sleep ( 1 );

  /*  启动串口转码服务 */
  SerialToNetServer::GetInstance();

  while ( MainApp::GetRunFlag() )
  {
    sleep ( 1 );
    PowerOn::CheckOnOffKey( );
    GET_ENGPTR->SetWorkTime ( );

    if ( PowerOn::GetOnOffFlag() )
    {
      GET_MBPTR->CheckSignalAndShow();
      GET_ENGPTR->Check(); /* check when engine is on */
    }
  }

  return 0;
}

