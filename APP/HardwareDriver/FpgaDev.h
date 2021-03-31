/*
 * =====================================================================================
 *
 *       Filename:  FpgaDev.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/11/2015 09:21:50 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  FPGADEV_INC
#define  FPGADEV_INC

#include "IoDevInterface.h"
#include "FpgaReg.h"
#include "MainboardInterface.h"

#define FPGA_DEV_NAME       "/dev/FpgaMod"
#define FPGA_RBF_FILE_NAME  "/app/FPGA.rbf"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  unsigned int  len;
  unsigned char data[0];
} fpga_config_data_t;

typedef struct
{
  unsigned int    offset;
  unsigned short  data;
} fpga_data_t;

typedef struct
{
  unsigned int   cnt;
  unsigned int   offset;
  unsigned short data[0];
} fpga_datan_t;

typedef struct
{
  unsigned int data0;
  unsigned int clk;
  unsigned int nconfig;
  unsigned int cfg_done;
  unsigned int nstatus;
  unsigned int nreset;
  unsigned int rw_en;
} fpga_pin_t;
#pragma pack(pop)

typedef enum
{
  CMD_FPGA_LOAD = 0,

  CMD_FPGA_INIT,
  CMD_FPGA_DEINIT,
  CMD_FPGA_RWEN,

  CMD_FPGA_GETREG,
  CMD_FPGA_SETREG,

  CMD_DDR_GETREG,
  CMD_DDR_SETREG,

  CMD_FPGA_SETREGN,
  CMD_DDR_SETREGN,

  CMD_FPGA_CMD_MAX,
} CMD_FPGA_E;

//#define FpgaSetReg( addr, val )   FpgaDev::SetReg( addr, val )
//#define FpgaGetReg( addr )        FpgaDev::GetReg( addr )

class FpgaDev
{
  private:
    FpgaDev ( );
    ~FpgaDev();

  public:
    static int Load ( std::string fpgafile = FPGA_RBF_FILE_NAME, std::string devname = FPGA_DEV_NAME );
    static int UnLoad ( std::string devname = FPGA_DEV_NAME );
    static int InitPin ( fpga_pin_t* p, std::string devname = FPGA_DEV_NAME );
    static bool IsLoad( );

    static int GetReg ( int addr, std::string devname = FPGA_DEV_NAME );
    static int SetReg ( int addr, int val, std::string devname = FPGA_DEV_NAME );

    static int DdrGetReg ( int addr, std::string devname = FPGA_DEV_NAME );
    static int DdrSetReg ( int addr, int val, std::string devname = FPGA_DEV_NAME );

    static int SetRegN ( fpga_datan_t* p, std::string devname = FPGA_DEV_NAME );
    static int DdrSetRegN ( fpga_datan_t* p, std::string devname = FPGA_DEV_NAME );
};

#endif   /* ----- #ifndef FPGADEV_INC  ----- */

