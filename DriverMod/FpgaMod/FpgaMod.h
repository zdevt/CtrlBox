/*
 * =====================================================================================
 *
 *       Filename:  FpgaMod.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/12/2015 10:15:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  FPGAMOD_INC
#define  FPGAMOD_INC

#define PIN_FUNC(fun,pin,arg) do{ if(pin){fun(pin,arg);} }while(0)

typedef int ( *PFUNC ) ( void* );

typedef enum
{
  CMD_FPGA_LOAD = 0,

  CMD_FPGA_INIT,
  CMD_FPGA_DEINIT,
  CMD_FPGA_RWEN,

  CMD_FPGA_GET,
  CMD_FPGA_SET,

  CMD_DDR_GET,
  CMD_DDR_SET,

  CMD_FPGA_SETN,
  CMD_DDR_SETN,

  CMD_FPGA_CMD_MAX,
} CMD_FPGA_E;

#define FPGA_PHY_START      (0x50000000)
#define FPGA_REMAP_SIZE     (SZ_1M)

#define DDR_PHY_START       (0x60000000)
#define DDR_REMAP_SIZE      (SZ_64M)

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  unsigned int  cnt;
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
  unsigned int nreset_en;
  unsigned int nreset;
  unsigned int rw_en;
} fpga_pin_t;
#pragma pack(pop)

#endif   /* ----- #ifndef FpgaMod.h ----- */

