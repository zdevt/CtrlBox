/*
 * =====================================================================================
 *
 *       Filename:  RootfsAdmin.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/18/2015 03:30:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "RootfsAdmin.h"
#include "LogPrint.h"


void RootfsAdmin::UpgradeRootfsAndWriteInfo ( std::string filename )
{
  UpgradeRootfs ( filename );

  sys_info_t sys_info;
  GetSysInfo ( sys_info );
  sys_info.fs_update = 1;
  SetSysInfo ( sys_info );

  SwitchSysTem();
}

void RootfsAdmin::UpgradeBootloader ( std::string filename )
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "!!!!!!!!!!!!!!!!!!!!!!\n" );
  std::string cmd;
  cmd += "sync;";
  cmd += "modprobe NorflashMod;";
  cmd += "sleep 1;";
  cmd += "flashcp FILENAME /dev/mtd8 -v;";
  cmd += "rmmod NorflashMod;";
  cmd.replace ( cmd.find ( "FILENAME" ), strlen ( "FILENAME" ), filename );
  system ( cmd.c_str() );
}

RootfsAdmin::RootfsAdmin()
{

}

RootfsAdmin::~RootfsAdmin()
{

}

bool RootfsAdmin::GetSysInfo ( sys_info_t& sys_info )
{
  int fd = open ( NAND_INFO_MTD, O_RDWR );

  if ( fd < 0 )
    return false;

  memset ( &sys_info, 0, sizeof ( sys_info ) );
  read ( fd, &sys_info, sizeof ( sys_info ) );
  close ( fd );

  return true;
}

bool RootfsAdmin::SetSysInfo ( sys_info_t& sys_info )
{
  int fd = open ( NAND_INFO_MTD, O_RDWR );

  if ( fd < 0 )
    return false;

  write ( fd, &sys_info, sizeof ( sys_info ) );
  close ( fd );

  return true;
}

void RootfsAdmin::PrintSysInfo ( sys_info_t& sys_info )
{
  PRINT_LOG2 ( "\n" );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "CURRENT SYSTEM=%d\n", sys_info.cur_sys );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "ROOTFS_UPDATE =%d\n", sys_info.fs_update );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "SYSTEMA_ERROR =%d\n", sys_info.a_sys_err );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "SYSTEMB_ERROR =%d\n", sys_info.b_sys_err );
  PRINT_LOG ( LOG_LEVEL_NORMAL, "KERNEL_ERROR  =%d\n", sys_info.kernel_err );
}

int RootfsAdmin::GetCurrentSys()
{
  char buffer[32] = "";
  FILE* fp = popen ( "cat /proc/cmdline | cut -d \"v\" -f2 | cut -d \"/\" -f2 | awk '{print $1}'", "r" );

  if ( !fp )
    return SYSTEM_MIN;

  fgets ( buffer, 32, fp );
  pclose ( fp );

  if ( 0 == strncmp ( buffer, ASYS_CMDLINE, strlen ( ASYS_CMDLINE ) ) )
    return SYSTEM_A;

  if ( 0 == strncmp ( buffer, BSYS_CMDLINE, strlen ( BSYS_CMDLINE ) ) )
    return SYSTEM_B;

  return SYSTEM_MIN;
}

void RootfsAdmin::CheckRootfs()
{
  sys_info_t sys_info;
  GetSysInfo ( sys_info );
  PrintSysInfo ( sys_info );

  /* first time or all system error */
  if ( ( GetCurrentSys() == SYSTEM_MIN )
       && ( sys_info.a_sys_err >= 3 )
       && ( sys_info.b_sys_err >= 3 ) )
  {
    InitNandRootfs();
    memset ( &sys_info, 0, sizeof ( sys_info ) );
    sys_info.cur_sys = SYSTEM_A;
    SetSysInfo ( sys_info );
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Now Reboot .......!\n" );
    system ( "reboot;" );
    return;
  }

  /* sync update */
  if ( sys_info.fs_update > 0 )
  {
    UpgradeRootfs();
    sys_info.fs_update = 0;
    SetSysInfo ( sys_info );
    return;
  }

  /* fix error system */
  if ( sys_info.a_sys_err >= 3 )
  {
    UpgradeRootfs();
    sys_info.a_sys_err = 0;
    SetSysInfo ( sys_info );
    return ;
  }

  if ( sys_info.b_sys_err >= 3 )
  {
    UpgradeRootfs();
    sys_info.b_sys_err = 0;
    SetSysInfo ( sys_info );
    return ;
  }

  /* fix error kernel */
  if ( ( SYSTEM_MIN == GetCurrentSys() )
       && ( sys_info.kernel_err ) )
  {
    UpgradeKernel();
    system ( "reboot;" );
  }
}


void RootfsAdmin::InitNandRootfs()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "InitNandRootfs\n" );
  std::string cmd;
  cmd += "sync;";
  cmd += "mount -t yaffs2 /dev/mtdblock3 /mnt/fs;sync;";
  //cmd += "rm -rf /mnt/fs/*;sync";
  cmd += "tar -xvf /app/fsm.tlz -C /mnt/fs >/dev/null;sync;";
  cmd += "umount /mnt/fs;sync;";
  system ( cmd.c_str() );

  cmd[cmd.find_first_of ( "3" )] = '5';
  system ( cmd.c_str() );

  UpgradeKernel();
}

void RootfsAdmin::UpgradeRootfs ( std::string filename )
{
  std::string cmd;

  cmd += "sync;";

  if (  SYSTEM_A == GetCurrentSys() )
    cmd += "mount -t yaffs2 /dev/mtdblock5 /mnt/fs;sync;";
  else
    cmd += "mount -t yaffs2 /dev/mtdblock3 /mnt/fs;sync;";

  cmd += "rm -rf /mnt/fs/*;sync;";
  cmd += "echo UpgradeRootfs;";

  cmd += "tar -xvf FILENAME -C /mnt/fs >/dev/null;sync;";
  cmd.replace ( cmd.find ( "FILENAME" ), strlen ( "FILENAME" ), filename.c_str() );

  cmd += "cp -f FILENAME /mnt/fs/app;sync;";
  cmd.replace ( cmd.find ( "FILENAME" ), strlen ( "FILENAME" ), filename.c_str() );

  cmd += "cp -f /app/SystemConfig.xml /mnt/fs/app;sync;";

  cmd += "rm -f /mnt/fs/app/dump.txt;sync;";
  cmd += "cp -f /app/dump.txt /mnt/fs/app;sync;";

  cmd += "rm -f /mnt/fs/app/user_def_*;sync;";
  cmd += "cp -f /app/user_def_* /mnt/fs/app;sync;";
  //cmd += "cp -f /etc/init.d/rcS /mnt/fs/etc/init.d;sync;";
  cmd += "sh /app/network.sh;sync;";

  cmd += "umount /mnt/fs;sync;";

  system ( cmd.c_str() );
}

void RootfsAdmin::SwitchSysTem()
{
  sys_info_t sys_info;
  GetSysInfo ( sys_info );

  std::string cmd;
  cmd += "sync;";

  if (  SYSTEM_A == GetCurrentSys() )
  {
    sys_info.cur_sys = SYSTEM_B;
    sys_info.b_sys_err = 0;
    sys_info.a_sys_err = 3;
    cmd += "mount -t yaffs2 /dev/mtdblock5 /mnt/fs;sync;";
  }
  else
  {
    sys_info.cur_sys = SYSTEM_A;
    sys_info.a_sys_err = 0;
    sys_info.b_sys_err = 3;
    cmd += "mount -t yaffs2 /dev/mtdblock3 /mnt/fs;sync;";
  }

  SetSysInfo ( sys_info );

  cmd += "cp -f /app/SystemConfig.xml /mnt/fs/app;sync;";
  cmd += "rm -f /mnt/fs/app/dump.txt;sync;";
  cmd += "cp -f /app/dump.txt /mnt/fs/app;sync;";
  cmd += "rm -f /mnt/fs/app/user_def_*;sync;";
  cmd += "cp -f /app/user_def_* /mnt/fs/app;sync;";
  cmd += "sh /app/network.sh;sync;";
  cmd += "umount /mnt/fs;sync;";

  system ( cmd.c_str() );
}

void RootfsAdmin::UpgradeKernel ( std::string filename )
{
  std::string cmd;
  cmd += "sync;";
  cmd += "flashcp FILENAME /dev/mtd2 -v;";
  cmd += "flashcp FILENAME /dev/mtd4 -v;";
  cmd.replace ( cmd.find ( "FILENAME" ), strlen ( "FILENAME" ), filename.c_str() );
  cmd.replace ( cmd.find ( "FILENAME" ), strlen ( "FILENAME" ), filename.c_str() );
  system ( cmd.c_str() );

  sys_info_t sys_info;
  GetSysInfo ( sys_info );
  sys_info.kernel_err = 0;
  SetSysInfo ( sys_info );
}

#ifdef TEST
int main ( int argc, char* argv[] )
{
  RootfsAdmin::CheckRootfs();
  return 0;
}
#endif

