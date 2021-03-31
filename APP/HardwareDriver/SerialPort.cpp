/*
 * =====================================================================================
 *
 *       Filename:  SerialPort.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2017-12-11 10:46:38
 *  Last Modified:  2017-12-30 13:20:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "SerialPort.h"
#include "LogPrint.h"

/*
"/dev/ttyUSB0", "230400 n 8 1"
*/

static std::map<int, int> mapSerialBand =
{
  { 9600,   B9600},
  { 19200,  B19200},
  { 38400,  B38400},
  { 57600,  B57600},
  { 115200, B115200},
  { 230400, B230400},
};

SerialPort::SerialPort ( std::string devname, unsigned int band_rate,
                         char parity, int databits, int stopbits,
                         int vtime, int vmin )
  : m_fd ( -1 ), m_devname ( devname ), m_band_rate ( band_rate ),
    m_parity ( parity ), m_databits ( databits ), m_stopbits ( stopbits ),
    m_vtime ( vtime ), m_vmin ( vmin )
{
  Init();
}

SerialPort::~SerialPort()
{
  DeInit();
}

int SerialPort::Init ( )
{
  m_fd = open ( m_devname.c_str(), O_RDWR | O_NDELAY );

  if ( m_fd < 0 )
  {
    PRINT_LOG ( LOG_LEVEL_ERROR, "%s %d %d\n", m_devname.c_str(), errno, __LINE__ );
    return -2;
  }

  tcflush ( m_fd, TCIOFLUSH );

  int n = fcntl ( m_fd, F_GETFL, 0 );
  fcntl ( m_fd, F_SETFL, n & ~O_NDELAY );

  if ( tcgetattr ( m_fd, &m_oldtio ) != 0 )
    PRINT_LOG ( LOG_LEVEL_ERROR, "%s %d %d\n", m_devname.c_str(), errno, __LINE__ );

  auto iter = mapSerialBand.find ( m_band_rate );

  if ( iter != mapSerialBand.end() )
    return SetSerial ( iter->second, m_parity, m_databits, m_stopbits );

  return -3;
}

int SerialPort::DeInit ( )
{
  if ( m_fd > 0 )
  {
    close ( m_fd );
    m_fd = -1;
  }

  return 0;
}

int SerialPort::Write ( const void* pWbuffer, int wSize )
{
  int ret = -1;

  if ( (  m_fd < 0 ) && ( Init() < 0 ) && wSize > 0 )
    return ret;

  while ( 1 )
  {
    tcflush ( m_fd, TCOFLUSH );
    ret = write ( m_fd, pWbuffer, wSize );

    if ( ( ret > 0 ) && ( ret != wSize ) )
      wSize -= ret;
    else
      break;
  }

  if ( -1 == ret )
    DeInit();

  return ret;
}

int SerialPort::Write ( std::vector<unsigned char>& vecWrite )
{
  return Write ( reinterpret_cast<void*> ( &vecWrite[0] ), vecWrite.size() );
}

int SerialPort::Write ( std::vector<char>& vecWrite )
{
  return Write ( reinterpret_cast<void*> ( &vecWrite[0] ), vecWrite.size() );
}

int SerialPort::Read ( std::vector<unsigned char>& vecRead )
{
  vecRead.resize ( 1024, 0 );
  int ret = Read ( reinterpret_cast<void*> ( &vecRead[0] ), ( int ) vecRead.size() );

  if ( ret > 0 )
    vecRead.resize ( ret );

  return ret;
}

int SerialPort::Read ( std::vector<char>& vecRead )
{
  vecRead.resize ( 1024, 0 );
  int ret = Read ( reinterpret_cast<void*> ( &vecRead[0] ), ( int ) vecRead.size() );

  if ( ret > 0 )
    vecRead.resize ( ret );

  return ret;
}

int SerialPort::Read ( void* pBuffer, int iBufferSize )
{
  int ret = 0;

  if ( (  m_fd < 0 ) && ( Init() < 0 ) )
    return -1;

  struct timeval tmval;
  fd_set fds;
  tmval.tv_sec = 1;
  tmval.tv_usec = 0;

  FD_ZERO ( &fds );
  FD_SET ( m_fd, &fds );
  ret = select ( m_fd + 1, &fds, NULL, NULL, &tmval );

  if ( ret > 0 )
  {
    ret = read ( m_fd, ( unsigned char* ) pBuffer, iBufferSize );

    if ( ret < 0 )
    {
      DeInit();
    }
  }

  return ret;
}

int SerialPort::ReadPackage ( void* pBuffer, int iBufferSize, int expectReadSize )
{
  int i_ret = 0;
  int i_read_len = 0;
  int i_min_cnt = 50;
  int ret = 0;

  if ( ( expectReadSize > iBufferSize ) || ( NULL == pBuffer ) )
    return -1;

  if ( (  m_fd < 0 ) && ( Init() < 0 ) )
    return -1;

  struct timeval tmval;
  fd_set fds;
  tmval.tv_sec = 1;
  tmval.tv_usec = 0;

  FD_ZERO ( &fds );
  FD_SET ( m_fd, &fds );
  ret = select ( m_fd + 1, &fds, NULL, NULL, &tmval );

  if ( ret > 0 )
  {
    do
    {
      i_ret = read ( m_fd, ( unsigned char* ) pBuffer + i_read_len, iBufferSize - i_read_len );

      if ( ( i_ret > 0 ) && ( i_read_len < expectReadSize ) )
        i_read_len += i_ret;
    }
    while ( ( i_read_len < expectReadSize ) && ( i_min_cnt-- > 0 ) );

    if ( i_min_cnt < 0 )
    {
      //printf("retry error read %d left %d\n", i_read_len, rSize-i_read_len);
    }
  }
  else if ( 0 == ret ) /* Timeout */
  {
    return 0;
  }
  else
  {
    DeInit();
    return -1;
  }

  return i_read_len;
}

int SerialPort::SetSerial ( unsigned int band_rate, char parity, int databits, int stopbits )
{
  ( void ) parity;

  if ( tcgetattr ( m_fd, &m_newtio ) != 0 )
    PRINT_LOG ( LOG_LEVEL_ERROR, "%s %d %d\n", m_devname.c_str(), errno, __LINE__ );

  speed_t _baud = band_rate;

  cfsetospeed ( &m_newtio, ( speed_t ) _baud );
  cfsetispeed ( &m_newtio, ( speed_t ) _baud );

  switch ( databits )
  {
    case 5:
      m_newtio.c_cflag = ( m_newtio.c_cflag & ~CSIZE ) | CS5;
      break;

    case 6:
      m_newtio.c_cflag = ( m_newtio.c_cflag & ~CSIZE ) | CS6;
      break;

    case 7:
      m_newtio.c_cflag = ( m_newtio.c_cflag & ~CSIZE ) | CS7;
      break;

    case 8:
    default:
      m_newtio.c_cflag = ( m_newtio.c_cflag & ~CSIZE ) | CS8;
      break;
  }

  m_newtio.c_cflag |= CLOCAL | CREAD;

  m_newtio.c_cflag &= ~ ( PARENB | PARODD );

  m_newtio.c_cflag &= ~CRTSCTS;

  if ( stopbits == 2 )
    m_newtio.c_cflag |= CSTOPB;
  else
    m_newtio.c_cflag &= ~CSTOPB;

  m_newtio.c_iflag = IGNBRK;

  m_newtio.c_iflag &= ~ ( IXON | IXOFF | IXANY );

  m_newtio.c_lflag = 0;
  m_newtio.c_oflag = 0;

  m_newtio.c_cc[VTIME] = m_vtime;
  m_newtio.c_cc[VMIN] = m_vmin;

  if ( tcsetattr ( m_fd, TCSANOW, &m_newtio ) != 0 )
    PRINT_LOG ( LOG_LEVEL_ERROR, "%s %d %d\n", m_devname.c_str(), errno, __LINE__ );

  int mcs = 0;
  ioctl ( m_fd, TIOCMGET, &mcs );
  mcs |= TIOCM_RTS;
  ioctl ( m_fd, TIOCMSET, &mcs );

  if ( tcgetattr ( m_fd, &m_newtio ) != 0 )
    PRINT_LOG ( LOG_LEVEL_ERROR, "%s %d %d\n", m_devname.c_str(), errno, __LINE__ );

  m_newtio.c_cflag &= ~CRTSCTS;

  if ( tcsetattr ( m_fd, TCSANOW, &m_newtio ) != 0 )
    PRINT_LOG ( LOG_LEVEL_ERROR, "%s %d %d\n", m_devname.c_str(), errno, __LINE__ );

  return 0;
}



#ifdef TEST
int main ( int argc, char* argv[] )
{
  ( void ) argc;
  ( void ) argv;

  uint8_t buffer[1024] = { 0 };
  int ret = 0;
  SerialPort serialport ( argv[1], 115200, 'n', 8, 1, 1, 1 );

  while ( 1 )
  {
    ret = serialport.Read ( buffer, 100 );

    if ( ret > 0 )
    {
      serialport.Write ( buffer, ret );
    }

    usleep ( 100 * 1000 );
  }

  return 0;
}

#endif

