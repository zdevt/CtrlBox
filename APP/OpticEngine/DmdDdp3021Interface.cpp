/*
 * =====================================================================================
 *
 *       Filename:  DmdDdp3021Interface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 10:49:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <vector>

#include "DmdDdp3021Interface.h"
#include "LogPrint.h"

pthread_mutex_t DmdDdp3021Interface::m_DmdDdp3021InterfaceMutex = PTHREAD_MUTEX_INITIALIZER;

DmdDdp3021Interface::DmdDdp3021Interface()
{

}

DmdDdp3021Interface::~DmdDdp3021Interface()
{

}

int DmdDdp3021Interface::SetProjMode ( uint8_t mode )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );

  uint8_t projmode = 0xc0;
  I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                           DDP3021_PROJECTION_MODE, &projmode, sizeof ( projmode ), I2C_SUB_ADDR_8_BIT );

  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  DDP3021_IMAGE_FLIP_SUBADDR, &mode, sizeof ( mode ), I2C_SUB_ADDR_8_BIT );
}

int DmdDdp3021Interface::GetProjMode ( uint8_t& mode )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );

  uint8_t readAddr = DDP3021_IMAGE_FLIP_SUBADDR;

  if ( I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                DDP3021_READ_SUBADDR, &readAddr, 1, I2C_SUB_ADDR_8_BIT ) > 0 )
    return I2cBusInterface::Read ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR, 0x0, &mode, sizeof ( mode ), I2C_SUB_ADDR_0_BIT );

  return -1;
}

int DmdDdp3021Interface::SetDmdGamma ( uint8_t gammaType )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  std::vector<uint8_t> vechar;
  vechar.push_back ( 0x40 );
  vechar.push_back ( gammaType );
  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  DDP3021_GAMMA_CORRECTION, &vechar[0], vechar.size(), I2C_SUB_ADDR_8_BIT );
}

int DmdDdp3021Interface::GetDmdGamma ( uint8_t& gammaType )
{
  return 0;
}

int DmdDdp3021Interface::SetColorOffset ( uint16_t r, uint16_t g, uint16_t b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  std::vector<uint8_t> vechar;
  vechar.push_back ( ( uint8_t ) ( g & 0xff ) );
  vechar.push_back ( ( uint8_t ) ( g >> 8 ) );
  vechar.push_back ( ( uint8_t ) ( r & 0xff ) );
  vechar.push_back ( ( uint8_t ) ( r >> 8 ) );
  vechar.push_back ( ( uint8_t ) ( b & 0xff ) );
  vechar.push_back ( ( uint8_t ) ( b >> 8 ) );

  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  DDP3021_COLOROFFSET_MODE, &vechar[0], vechar.size(), I2C_SUB_ADDR_8_BIT );
}

int DmdDdp3021Interface::GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  return 0;
}

int DmdDdp3021Interface::SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  std::vector<uint8_t> vechar;
  vechar.push_back ( ( uint8_t ) ( ( g >> 8 ) & ( 0x7f ) ) );
  vechar.push_back ( ( uint8_t ) ( g & 0xff ) );

  vechar.push_back ( ( uint8_t ) ( ( r >> 8 ) & ( 0x7f ) ) );
  vechar.push_back ( ( uint8_t ) ( r & 0xff ) );

  vechar.push_back ( ( uint8_t ) ( ( b >> 8 ) & ( 0x7f ) ) );
  vechar.push_back ( ( uint8_t ) ( b & 0xff ) );

  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  DDP3021_ENGIN_BRIGHT, &vechar[0], vechar.size(), I2C_SUB_ADDR_8_BIT );
}

int DmdDdp3021Interface::GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  return 0;
}

int DmdDdp3021Interface::SetColorContrast ( uint16_t r, uint16_t g, uint16_t b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  std::vector<uint8_t> vechar;
  vechar.push_back ( g );
  vechar.push_back ( r );
  vechar.push_back ( b );
  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  DDP3021_ENGIN_CONTRAST, &vechar[0], vechar.size(), I2C_SUB_ADDR_8_BIT );
}

int DmdDdp3021Interface::GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  return 0;
}

int DmdDdp3021Interface::SetBcMode ( uint8_t mode )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  std::vector<uint8_t> vechar;

  if ( mode != 0 )
  {
    mode = mode - 1;
    mode |= ( 1 << 7 );
  }

  vechar.push_back ( mode );
  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  DDP3021_BC_CONTROL, &vechar[0], vechar.size(), I2C_SUB_ADDR_8_BIT );
}

int DmdDdp3021Interface::GetBcMode ( uint8_t& mode )
{
  return 0;
}

int DmdDdp3021Interface::SetDutycycle ( uint8_t dc )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  std::vector<uint8_t> vechar;
  vechar.push_back ( dc );
  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  DDP3021_DUTY_CYCLE, &vechar[0], vechar.size(), I2C_SUB_ADDR_8_BIT );
}

int DmdDdp3021Interface::GetDutycycle ( uint8_t dc )
{
  return 0;
}

int DmdDdp3021Interface::SetHsg ( void* hsg )
{
  return 0;
}

int DmdDdp3021Interface::GetHsg ( void* hsg )
{
  return 0;
}

int DmdDdp3021Interface::DmdColorPointControlProcessWrite ( uint8_t data )
{
  std::vector<uint8_t> vechar;
  vechar.push_back ( DDP3021_DSP_WRITE_FLAG );
  vechar.push_back ( DDP3021_DSP_COLOR_POINT_PROCESS_CONTROL_WRITE );
  vechar.resize ( 8, 0 );
  vechar.push_back ( data );

  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  0x0, &vechar[0], vechar.size(), I2C_SUB_ADDR_0_BIT );
}

int DmdDdp3021Interface::_SetDac ( uint8_t color, uint8_t speColr, uint16_t current )
{
  uint8_t* pTemp = reinterpret_cast<uint8_t*> ( &current );
  std::vector<uint8_t> vechar;
  vechar.push_back ( DDP3021_DSP_WRITE_FLAG );
  vechar.push_back ( DDP3021_DSP_DAC_WRITE );
  vechar.push_back ( color );
  vechar.push_back ( speColr );
  vechar.resize ( 7, 0 );
  vechar.push_back ( pTemp[1] );
  vechar.push_back ( pTemp[0] );

  return I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                  0x0, &vechar[0], vechar.size(), I2C_SUB_ADDR_0_BIT );

}

int DmdDdp3021Interface::_GetDac ( uint8_t color, uint8_t speColr, uint16_t& current )
{
  std::vector<uint8_t> vechar;
  vechar.push_back ( DDP3021_DSP_DAC_READ );
  vechar.push_back ( color );
  vechar.push_back ( speColr );
  vechar.resize ( 8, 0 );

  if ( I2cBusInterface::Write ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                DDP3021_DSP_READ_FLAG, &vechar[0], vechar.size(), I2C_SUB_ADDR_8_BIT ) > 0 )
  {
    vechar.resize ( 4, 0 );
    usleep ( 50 * 1000 );
    int ret = I2cBusInterface::Read ( DMDDDP3021_I2CBUS, DDP3021_SLAVE_ADDR,
                                      0x0, &vechar[0], vechar.size(), I2C_SUB_ADDR_0_BIT );

    current = * ( ( uint16_t* ) &vechar[2] );
    current = ntohs ( current );

    return ret;
  }

  return -1;
}

int DmdDdp3021Interface::_GetDacSafety ( uint8_t color, uint8_t speColr, uint16_t& current )
{
  int ret = _GetDac ( color, speColr, current );
  int i = 0;

  while ( ( ret < 0 ) && ( ++i < 20 ) )
  {
    usleep ( 50 * 1000 );
    ret = _GetDac ( color, speColr, current );
  }

  if ( ret < 0 )
    PRINT_LOG ( LOG_LEVEL_NORMAL, "read error ret %d\n", ret );

  return ret;
}

int DmdDdp3021Interface::SetDac ( uint8_t color, set_dac_strobe_t* pset_dac_strobe )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  DmdColorPointControlProcessWrite ( DDP3021_DSP_ALL_DIS );
  _SetDac ( color, DAC_RED_STROBE,       pset_dac_strobe->red_strobe );
  _SetDac ( color, DAC_GREEN_STROBE,     pset_dac_strobe->green_strobe );
  _SetDac ( color, DAC_BLUE_STROBE,      pset_dac_strobe->blue_strobe );
  _SetDac ( color, DAC_SUBFRAME1_STROBE, pset_dac_strobe->subframe1_strobe );
  _SetDac ( color, DAC_SUBFRAME2_STROBE, pset_dac_strobe->subframe2_strobe );
  _SetDac ( color, DAC_YELLOW_STROBE,    pset_dac_strobe->yellow_strobe );
  _SetDac ( color, DAC_CYAN_STROBE,      pset_dac_strobe->cyan_strobe );
  _SetDac ( color, DAC_MAGENTA_STROBE,   pset_dac_strobe->magenta_strobe );
  _SetDac ( color, DAC_WHITE_STROBE,     pset_dac_strobe->white_strobe );
  _SetDac ( color, DAC_BLACK_STROBE,     pset_dac_strobe->black_strobe );

  return 0;
}

int DmdDdp3021Interface::SetRedDac ( uint16_t r, uint16_t g, uint16_t b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  DmdColorPointControlProcessWrite ( DDP3021_DSP_ALL_DIS );

  _SetDac ( ColorRed, DAC_RED_STROBE,     r );
  _SetDac ( ColorRed, DAC_GREEN_STROBE,   g );
  _SetDac ( ColorRed, DAC_BLUE_STROBE,    b );

  _SetDac ( ColorRed, DAC_YELLOW_STROBE,  r );
  return 0;
}

int DmdDdp3021Interface::GetRedDac ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );

  _GetDacSafety ( ColorRed, DAC_RED_STROBE,     r );
  _GetDacSafety ( ColorRed, DAC_GREEN_STROBE,   g );
  _GetDacSafety ( ColorRed, DAC_BLUE_STROBE,    b );

  return 0;
}

int DmdDdp3021Interface::SetGreenDac ( uint16_t r, uint16_t g, uint16_t b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  DmdColorPointControlProcessWrite ( DDP3021_DSP_ALL_DIS );

  _SetDac ( ColorGreen, DAC_RED_STROBE,     r );
  _SetDac ( ColorGreen, DAC_GREEN_STROBE,   g );
  _SetDac ( ColorGreen, DAC_BLUE_STROBE,    b );

  _SetDac ( ColorGreen, DAC_YELLOW_STROBE,  g );
  _SetDac ( ColorGreen, DAC_CYAN_STROBE,    g );
  return 0;
}

int DmdDdp3021Interface::GetGreenDac ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );

  _GetDacSafety ( ColorGreen, DAC_RED_STROBE,     r );
  _GetDacSafety ( ColorGreen, DAC_GREEN_STROBE,   g );
  _GetDacSafety ( ColorGreen, DAC_BLUE_STROBE,    b );

  return 0;
}

int DmdDdp3021Interface::SetBlueDac ( uint16_t r, uint16_t g, uint16_t b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );
  DmdColorPointControlProcessWrite ( DDP3021_DSP_ALL_DIS );

  _SetDac ( ColorBlue, DAC_RED_STROBE,     r );
  _SetDac ( ColorBlue, DAC_GREEN_STROBE,   g );
  _SetDac ( ColorBlue, DAC_BLUE_STROBE,    b );

  _SetDac ( ColorBlue, DAC_CYAN_STROBE,    b );
  return 0;
}

int DmdDdp3021Interface::GetBlueDac ( uint16_t& r, uint16_t& g, uint16_t& b )
{
  Locker locker ( &m_DmdDdp3021InterfaceMutex );

  _GetDacSafety ( ColorBlue, DAC_RED_STROBE,     r );
  _GetDacSafety ( ColorBlue, DAC_GREEN_STROBE,   g );
  _GetDacSafety ( ColorBlue, DAC_BLUE_STROBE,    b );

  return 0;
}
