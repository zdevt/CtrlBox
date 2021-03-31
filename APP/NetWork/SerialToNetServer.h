/*
 * =====================================================================================
 *
 *       Filename:  SerialToNetServer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月12日 19时45分08秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  SERIALTONETSERVER_INC
#define  SERIALTONETSERVER_INC

#include <map>
#include <string>
#include <vector>
#include <queue>
#include <list>

#include <semaphore.h>
#include <pthread.h>
#include <memory>

#include "Network.h"
#include "SerialPort.h"

#define GET_SERI_TO_NET SerialToNetServer::GetInstance()

class SerialToNetServer
{
  private:
    SerialToNetServer();
    ~SerialToNetServer();

  public:
    static SerialToNetServer* GetInstance();

  public:
    int Start();
    int Stop();

  private:
    static void* HandleDataTask ( void* pObj );
    void _HandleDataTask();

    static void* RecvDataTask ( void* pObj );
    void _RecvDataTask( );

    void Init();
    void DeInit();

    int HandleSerialData ( std::vector<char>& vecRecv, std::vector<char>& vecRsp );

    void ShowSeriData ( const char* description, char* buffer, int len );

    bool GetRunFlag();
    void SetRunFlag ( bool flag );

  private:
    bool m_runFlag;
    pthread_t m_tid;
    sem_t m_semHandle;
    sem_t m_semRecv;
    static pthread_mutex_t m_mutex;
    static pthread_mutex_t m_data_mutex;
    std::vector<char> m_serial_data_buffer;
    SerialPort m_SerialPort;
};

#endif   /* ----- #ifndef SerialToNetServer.h ----- */

