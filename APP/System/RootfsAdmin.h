/*
 * =====================================================================================
 *
 *       Filename:  RootfsAdmin.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/18/2015 03:30:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  ROOTFSADMIN_INC
#define  ROOTFSADMIN_INC

#include <string>

#define NAND_INFO_MTD "/dev/mtdblock6"
#define ASYS_CMDLINE  "mtdblock3"
#define BSYS_CMDLINE  "mtdblock5"

#define SYSTEM_MIN  (0)
#define SYSTEM_A    (1)
#define SYSTEM_B    (2)

#pragma pack(push)
#pragma pack(1)
/* NandFlash system info /dev/mtd6 */
typedef struct
{
  unsigned int cur_sys;
  unsigned int fs_update;
  unsigned int a_sys_err;
  unsigned int b_sys_err;
  unsigned int kernel_err;
  char res[2028];
} sys_info_t;
#pragma pack(pop)

class RootfsAdmin
{
  private:
    RootfsAdmin();
    ~RootfsAdmin();

  public:
    static void UpgradeBootloader ( std::string filename = "/app/bootloader.bin" );
    static void UpgradeKernel ( std::string filename = "/app/uImage_9G45.bin" );
    static void UpgradeRootfsAndWriteInfo ( std::string filename = "/app/fs.tlz" );
    static int  GetCurrentSys();
    static void CheckRootfs();

    static void SwitchSysTem();
    static void PrintSysInfo ( sys_info_t& sys_info );

  private:
    static bool GetSysInfo ( sys_info_t& sys_info );
    static bool SetSysInfo ( sys_info_t& sys_info );
    static void InitNandRootfs();
    static void UpgradeRootfs ( std::string filename = "/app/fs.tlz" );
};

#endif   /* ----- #ifndef RootfsAdmin.h ----- */

