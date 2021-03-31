/*
 * =====================================================================================
 *
 *       Filename:  FpgaECP3.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/11/2015 09:21:44 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <vector>
#include <fstream>

#include "FpgaECP3.h"
#include "LogPrint.h"
#include "Led74Hc595D.h"
#include "MainboardInterface.h"
#include "SpiBusInterface.h"
#include "FileHandle.h"
#include "FpgaDev.h"

FpgaECP3::FpgaECP3 ( )
{

}

FpgaECP3::~FpgaECP3()
{

}

static unsigned char cmdId[8] 	= { 0x7, 0x0, 0x0, 0x0, 0, 0, 0, 0};
static unsigned char cmdRef[4] 	= { 0x71, 0x0, 0x0, 0x0};
static unsigned char cmdEn[4] 	= { 0x4a, 0x0, 0x0, 0x0};
static unsigned char cmdInc[4] 	= { 0x41, 0x0, 0x0, 0x0};
static unsigned char cmdSta[8] 	= { 0x9, 0x0, 0x0, 0x0, 0, 0, 0, 0};
static unsigned char cmdDis[4] 	= { 0x4f, 0x0, 0x0, 0x0};
static unsigned char Temp[8];

int FpgaECP3::Load ( std::string fpgafile, std::string devname )
{
  int ret = 0;

  GPIO_SET_VALUE ( FPGA_ECP3_PROG_PIN, 1 );
  usleep ( 50 * 1000 );
  GPIO_SET_VALUE ( FPGA_ECP3_PROG_PIN, 0 );
  usleep ( 50 * 1000 );
  GPIO_SET_VALUE ( FPGA_ECP3_PROG_PIN, 1 );
  usleep ( 50 * 1000 );

  ret = SPI_RW ( cmdId, Temp, 8, devname );
  ret = SPI_RW ( cmdRef, Temp, 4, devname );
  ret = SPI_RW ( cmdEn, Temp, 4, devname );

  std::vector<char> vecharFile, vecharTemp;

  if ( !FileHandle::Read ( fpgafile, vecharFile ) )
    return -10;

  /*  insert inc */
  vecharFile.insert ( vecharFile.begin(), cmdInc, cmdInc + 4 );
  vecharFile.resize ( vecharFile.size() + 0x100, 0 ); /*  add dummy byte */
  vecharTemp.resize ( vecharFile.size(), 0 );

  ret = SPI_RWN ( reinterpret_cast<uint8_t*> ( &vecharFile[0] ),
                  reinterpret_cast<uint8_t*> ( &vecharTemp[0] ),
                  vecharFile.size(),
                  SPI_PACK_LEN, devname );

  ret = SPI_RW ( cmdSta, Temp, 8, devname );
  ret = SPI_RW ( cmdDis, Temp, 4, devname );

  usleep ( 500 * 1000 );
  AT91SetGpioOutput ( FPGA_ECP3_RESET_PIN, 1 );
  GPIO_SET_VALUE ( FPGA_ECP3_RESET_PIN, 0 );
  usleep ( 500 * 1000 );
  GPIO_SET_VALUE ( FPGA_ECP3_RESET_PIN, 1 );

  #if 0

  while ( ! IsLoad() )
  {
    sleep ( 1 );
    PRINT_LOG ( LOG_LEVEL_NORMAL, "Wait Ecp3 Ready!\n" );
  }

  PRINT_LOG ( LOG_LEVEL_NORMAL, "Ecp3 Ok!\n" );
  #endif

  return ret;
}

int FpgaECP3::UnLoad ( std::string devname )
{
  GPIO_SET_VALUE ( FPGA_ECP3_PROG_PIN, 0 );
  return 0;
}

bool FpgaECP3::IsLoad( )
{
  #if 0

  if ( GPIO_GET_VALUE ( FPGA_ECP3_CONFIG_DONE_PIN ) )
    return true;

  #endif

  SetReg ( FPGA_REG_TEST, 0x1234, SPI_BUS_10_NAME );
  int res = GetReg ( FPGA_REG_TEST, SPI_BUS_10_NAME );

  if ( 0x1234 == res )
    return true;

  return false;
}

void FpgaECP3::InitPin ( void* p, std::string devname )
{
  GPIO_SET_OUTPUT ( FPGA_ECP3_PROG_PIN, 1 );
  GPIO_SET_INPUT ( FPGA_ECP3_CONFIG_DONE_PIN, 1 );
}

int FpgaECP3::GetReg ( int addr, std::string devname )
{
  fpga_ecp3_reg_w_t fpga_ecp3_reg_w;
  fpga_ecp3_reg_r_t fpga_ecp3_reg_r;

  fpga_ecp3_reg_w.magic = FPGA_ECP3_GET_REG_MAGIC;
  fpga_ecp3_reg_w.addr = addr;

  SPI_RW (  reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg_w ),
            reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg_r ),
            sizeof ( fpga_ecp3_reg_w ), devname );

  return fpga_ecp3_reg_r.val;

  #if 0
  fpga_ecp3_reg_t fpga_ecp3_reg;
  fpga_ecp3_reg_t fpga_ecp3_reg_r;

  fpga_ecp3_reg.magic = FPGA_ECP3_GET_REG_MAGIC;
  fpga_ecp3_reg.addr = addr;

  SPI_RW (  reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg ),
            reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg_r ),
            sizeof ( fpga_ecp3_reg ), devname );

  return fpga_ecp3_reg_r.val;
  #endif
}

int FpgaECP3::SetReg ( int addr, int val, std::string devname )
{
  fpga_ecp3_reg_w_t fpga_ecp3_reg_w;
  fpga_ecp3_reg_r_t fpga_ecp3_reg_r;

  fpga_ecp3_reg_w.magic = FPGA_ECP3_SET_REG_MAGIC;
  fpga_ecp3_reg_w.addr = addr;
  fpga_ecp3_reg_w.val = ( uint16_t ) val;

  SPI_RW (  reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg_w ),
            reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg_r ),
            sizeof ( fpga_ecp3_reg_w ), devname );

  #if 0
  fpga_ecp3_reg_t fpga_ecp3_reg;
  fpga_ecp3_reg_t fpga_ecp3_reg_r;

  fpga_ecp3_reg.magic = FPGA_ECP3_SET_REG_MAGIC;
  fpga_ecp3_reg.addr = addr;
  fpga_ecp3_reg.val = ( uint16_t ) val;

  SPI_RW (  reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg ),
            reinterpret_cast<uint8_t*> ( &fpga_ecp3_reg_r ),
            sizeof ( fpga_ecp3_reg ), devname );

  #endif
  return 0;
}

int FpgaECP3::DdrGetReg ( int addr, std::string devname )
{
  return 0;
}

int FpgaECP3::DdrSetReg ( int addr, int val, std::string devname )
{
  return 0;
}

int FpgaECP3::SetRegN ( void* p, std::string devname )
{
  return 0;
}

int FpgaECP3::DdrSetRegN ( void* p, std::string devname )
{
  std::vector<uint8_t> vecW;
  std::vector<uint8_t> vecR;
  fpga_datan_t* pfpga_datan = reinterpret_cast<fpga_datan_t*> ( p );

  vecR.reserve ( 4 * SPI_PACK_LEN );
  vecW.reserve ( 4 * SPI_PACK_LEN );

  uint16_t addr = pfpga_datan->offset;
  uint8_t  countNouse = 0xff;
  vecW.push_back ( FPGA_ECP3_SET_DDRN_MAGIC );
  vecW.push_back ( ( uint8_t ) ( addr & 0xff ) );
  vecW.push_back ( ( uint8_t ) ( ( addr >> 8 ) & 0xff ) );
  vecW.push_back ( countNouse );

  vecW.insert ( vecW.end(), reinterpret_cast<char*> ( pfpga_datan->data ),
                reinterpret_cast<char*> ( pfpga_datan->data ) + pfpga_datan->cnt );
  vecW.push_back ( 0 ); /*  dummy byte for fpga test*/
  vecR.resize ( vecW.size(), 0 );

  return SPI_RWN ( &vecW[0], &vecR[0], vecW.size(), SPI_PACK_LEN, devname );
}

