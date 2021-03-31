/*
 * =====================================================================================
 *
 *       Filename:  FpgaDev.cpp
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

#include <vector>

#include "FpgaDev.h"
#include "LogPrint.h"
#include "FileHandle.h"
#include "At91GpioDev.h"
#include "Led74Hc595D.h"
#include "GpioDefine.h"

FpgaDev::FpgaDev ( )
{

}

FpgaDev::~FpgaDev()
{

}

int FpgaDev::Load ( std::string fpgafile, std::string devname )
{
  std::vector<char> vechar;

  if ( !FileHandle::Read ( fpgafile, vechar ) )
    return -1;

  int len = vechar.size();

  vechar.insert ( vechar.begin(), reinterpret_cast<char*> ( &len ), reinterpret_cast<char*> ( &len ) + sizeof ( len ) );

  fpga_config_data_t* pfpga_config_data = reinterpret_cast<fpga_config_data_t*> ( &vechar[0] );

  return IoDevInterface::Ioctl ( devname, CMD_FPGA_LOAD, reinterpret_cast<unsigned long> ( pfpga_config_data ) );
}

int FpgaDev::UnLoad ( std::string devname )
{
  return 0;
}

int FpgaDev::InitPin ( fpga_pin_t* p, std::string devname )
{
  return IoDevInterface::Ioctl ( devname, CMD_FPGA_INIT, reinterpret_cast<unsigned long> ( p ) );
}

int FpgaDev::GetReg ( int addr, std::string devname )
{
  fpga_data_t fpga_data;
  fpga_data.offset = addr << 1;
  fpga_data.data = 0;

  if ( 0 == IoDevInterface::Ioctl ( devname, CMD_FPGA_GETREG, ( unsigned long ) &fpga_data ) )
    return fpga_data.data;

  return -1;
}

int FpgaDev::SetReg ( int addr, int val, std::string devname )
{
  fpga_data_t fpga_data;
  fpga_data.offset = addr << 1;
  fpga_data.data = val;

  return  IoDevInterface::Ioctl ( devname, CMD_FPGA_SETREG, ( unsigned long ) &fpga_data );
}

int FpgaDev::DdrGetReg ( int addr, std::string devname )
{
  fpga_data_t fpga_data;
  fpga_data.offset = addr << 1;

  if ( 0 == IoDevInterface::Ioctl ( devname, CMD_DDR_GETREG, ( unsigned long ) &fpga_data ) )
    return fpga_data.data;

  return -1;
}

int FpgaDev::DdrSetReg ( int addr, int val, std::string devname )
{
  fpga_data_t fpga_data;
  fpga_data.offset = addr << 1;
  fpga_data.data = val;

  return  IoDevInterface::Ioctl ( devname, CMD_DDR_SETREG, ( unsigned long ) &fpga_data );
}

int FpgaDev::SetRegN ( fpga_datan_t* p, std::string devname )
{
  p->offset <<= 1;
  return  IoDevInterface::Ioctl ( devname, CMD_FPGA_SETREGN, ( unsigned long ) p );
}

int FpgaDev::DdrSetRegN ( fpga_datan_t* p, std::string devname )
{
  return  IoDevInterface::Ioctl ( devname, CMD_DDR_SETREGN, ( unsigned long ) p );
}

bool FpgaDev::IsLoad( )
{
  if ( At91GetGpioValue ( FPGA_ALTEA_IS_LOAD ) )
    return true;

  return false;
}

