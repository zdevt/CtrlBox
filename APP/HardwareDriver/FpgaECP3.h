/*
 * =====================================================================================
 *
 *       Filename:  FpgaECP3.h
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

#ifndef  FPGAECP3_INC
#define  FPGAECP3_INC

#include <vector>

#include "IoDevInterface.h"
#include "SpiBusInterface.h"
#include "At91GpioDev.h"
#include "GpioDefine.h"

#define FPGA_ECP3_BIT_FILE_NAME 				"/app/fpga_ecp3.bit"
#define FPGA_ECP3_NAME  			  				SPI_BUS_10_NAME
#define FPGA_ECP3_CONFIG_NAME   				SPI_BUS_20_NAME

#define FPGA_ECP3_SET_REG_MAGIC         (0x05)
#define FPGA_ECP3_GET_REG_MAGIC         (0x50)
#define FPGA_ECP3_SET_DDRN_MAGIC        (0x0a)

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t magic;
  uint8_t addr;
  uint16_t val;
} fpga_ecp3_reg_t;

typedef struct
{
  uint8_t magic;
  uint8_t addr;
  uint16_t val;
  uint8_t dummy;
} fpga_ecp3_reg_w_t;

typedef struct
{
  uint8_t magic;
  uint8_t addr;
  uint8_t dummy;
  uint16_t val;
} fpga_ecp3_reg_r_t;

typedef struct
{
  uint8_t magic;
  uint16_t addr;
  uint32_t cnt;
  uint8_t data[0];
} fpga_ecp3_set_ddrn_t;

#pragma pack(pop)

class FpgaECP3
{
  private:
    FpgaECP3 ( );
    ~FpgaECP3();

  public:
    static int Load ( std::string fpgafile = FPGA_ECP3_BIT_FILE_NAME, std::string devname = FPGA_ECP3_CONFIG_NAME );
    static int UnLoad ( std::string devname = FPGA_ECP3_CONFIG_NAME );
    static bool IsLoad( );
    static void InitPin ( void* p, std::string devname = FPGA_ECP3_CONFIG_NAME );

    static int GetReg ( int addr, std::string devname = FPGA_ECP3_NAME );
    static int SetReg ( int addr, int val, std::string devname = FPGA_ECP3_NAME );

    static int DdrGetReg ( int addr, std::string devname = FPGA_ECP3_NAME );
    static int DdrSetReg ( int addr, int val, std::string devname = FPGA_ECP3_NAME );

    static int SetRegN ( void* p, std::string devname = FPGA_ECP3_NAME );
    static int DdrSetRegN ( void* p, std::string devname = FPGA_ECP3_NAME );
};

#endif   /* ----- #ifndef FPGADEV_INC  ----- */

