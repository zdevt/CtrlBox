/*
 * =====================================================================================
 *
 *       Filename:  SerialToNetServer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月12日 19时45分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <algorithm>

#include "SerialToNetServer.h"
#include "Common.h"
#include "Locker.h"
#include "LogPrint.h"
#include "CmdInterface.h"


pthread_mutex_t SerialToNetServer::m_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t SerialToNetServer::m_data_mutex = PTHREAD_MUTEX_INITIALIZER;

SerialToNetServer* SerialToNetServer::GetInstance()
{
  static SerialToNetServer instance;
  return &instance;
}

SerialToNetServer::SerialToNetServer()
  : m_runFlag ( false ),
    m_SerialPort ( "/dev/ttyS2", 115200, 'n', 8, 1 )
{
  m_serial_data_buffer.reserve ( 2048 );
  Init();
  Start();
}

SerialToNetServer::~SerialToNetServer()
{
  Stop();
  DeInit();
}

void SerialToNetServer::Init()
{
  Locker locker ( &m_mutex );

  sem_init ( &m_semHandle, 0, 0 );
  sem_init ( &m_semRecv, 0, 0 );
}

void SerialToNetServer::DeInit()
{
  Locker locker ( &m_mutex );

  sem_destroy ( &m_semHandle );
  sem_destroy ( &m_semRecv );
}

int SerialToNetServer::Start()
{
  if ( !GetRunFlag() )
  {
    SetRunFlag ( true );
    pthread_create ( &m_tid, NULL, SerialToNetServer::RecvDataTask, reinterpret_cast<void*> ( this ) );
    pthread_create ( &m_tid, NULL, SerialToNetServer::HandleDataTask, reinterpret_cast<void*> ( this ) );
  }

  return 0;
}

int SerialToNetServer::Stop()
{
  if ( GetRunFlag ( ) )
  {
    SetRunFlag ( false );
    sem_wait ( &m_semHandle );
    sem_wait ( &m_semRecv );
  }

  return 0;
}

void SerialToNetServer::_HandleDataTask()
{
  bool dataFlag = false;
  int headerlen = sizeof ( MCP_HEADER_t );
  std::vector<char> vecReq ( 0, 0 );
  std::vector<char> vecRsp ( 0, 0 );

  while ( GetRunFlag() )
  {
    {
      Locker locker ( &m_data_mutex );

      int len = m_serial_data_buffer.size();

      if ( len >= headerlen )
      {
        for ( int i = 0; i < ( len - headerlen + 1 ); ++i )
        {
          MCP_HEADER_t* p = reinterpret_cast<MCP_HEADER_t*> ( &m_serial_data_buffer[i] );

          if ( MCP_MAGICWORD == p->mcp_magicword )
          {
            if ( i > 0 ) /* 抛弃不对数据，保证后面再次发送能正常解析*/
              m_serial_data_buffer.erase ( m_serial_data_buffer.begin(), m_serial_data_buffer.begin() + i );

            len = m_serial_data_buffer.size();

            if ( len >= ( int ) ( headerlen + p->mcp_datalen ) )
            {
              vecReq = m_serial_data_buffer;
              vecReq.resize ( headerlen + p->mcp_datalen );

              m_serial_data_buffer.erase ( m_serial_data_buffer.begin(),
                                           m_serial_data_buffer.begin() + headerlen + p->mcp_datalen );
              dataFlag = true;
            }

            break; /* 只要找到magic，长度够，跳出循环处理，不够，跳出，继续收数据*/
          }
        }
      }
      else
      {
        dataFlag = false;
      }
    }

    if ( dataFlag )
    {
      ShowSeriData ( "SERI REQ:", &vecReq[0], vecReq.size() );

      vecRsp.clear();
      HandleSerialData ( vecReq, vecRsp );

      m_SerialPort.Write ( vecRsp );

      ShowSeriData ( "SERI RSP:", &vecRsp[0], vecRsp.size() );

      dataFlag = false;
    }
    else
      usleep ( 1000 );
  }

  sem_post ( &m_semHandle );
}

void* SerialToNetServer::HandleDataTask ( void* pObj )
{
  PTHREAD_DETACH;
  reinterpret_cast<SerialToNetServer*> ( pObj )->_HandleDataTask();
  return NULL;
}

void SerialToNetServer::_RecvDataTask( )
{
  std::vector<char> vecRecv ( 1024, 0 );
  int ret = 0;

  while ( GetRunFlag() )
  {
    ret = m_SerialPort.Read ( vecRecv );

    if ( 0 < ret )
    {
      Locker locker ( &m_data_mutex );

      if ( m_serial_data_buffer.size() < 4096 )
        m_serial_data_buffer.insert ( m_serial_data_buffer.end(), vecRecv.begin(), vecRecv.end() );
    }
    else if ( 0 == ret )
    {
      //timeout
      usleep ( 50 * 1000 );
    }
    else if ( 0 > ret )
    {
      //error
      usleep ( 1000 * 1000 );
    }
  }

  sem_post ( &m_semRecv );
}

void* SerialToNetServer::RecvDataTask ( void* pObj )
{
  PTHREAD_DETACH;
  reinterpret_cast<SerialToNetServer*> ( pObj )->_RecvDataTask();
  return NULL;
}

bool SerialToNetServer::GetRunFlag()
{
  return m_runFlag;
}

void SerialToNetServer::SetRunFlag ( bool flag )
{
  m_runFlag = flag;
}

int SerialToNetServer::HandleSerialData ( std::vector<char>& vecRecv, std::vector<char>& vecRsp )
{
  return CmdInterface::SerialGetObj ( &vecRecv[0], vecRecv.size() )->HandleCmd ( vecRecv, vecRsp );
}

void SerialToNetServer::ShowSeriData ( const char* description, char* buffer, int len )
{
  PRINT_LOG2 ( "\n%s\n", description );
  PRINT_LOG2 ( "        maigc id    type  sub   status      len\n" );
  PRINT_LOG2 ( "Header: " );

  for ( int i = 0; i < len; ++i )
  {
    if ( ( i % 0x10 == 0 ) && ( 0 != i ) )
      PRINT_LOG2 ( "\n        " );

    PRINT_LOG2 ( "%02x ", buffer[i] );
  }

  PRINT_LOG2 ( "\n" );
}

