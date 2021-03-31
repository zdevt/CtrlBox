/*
 * =====================================================================================
 *
 *       Filename:  DebugAdmin.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/05/2015 10:09:12 AM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  DEBUGADMIN_INC
#define  DEBUGADMIN_INC

#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

#include <map>
#include <string>

#ifndef PTHREAD_DETACH
  #include <pthread.h>
  #include <sys/prctl.h>
  #define PTHREAD_DETACH  do{ pthread_detach(pthread_self()); prctl(PR_SET_NAME,__FUNCTION__);}while(0)
#endif

#include "DebugFun.h"

#define MAX_BUFF_SIZE (1024)

typedef struct message
{
  long msgtype; /* must > 0 */
  char buff[MAX_BUFF_SIZE];
} DebugAdminMsg_t;

typedef std::shared_ptr<DebugFun> ( *pGetObj ) ( );
typedef std::map<std::string, pGetObj> funMap_t;

class DebugAdmin
{
  private:
    DebugAdmin();
    ~DebugAdmin();

  public:
    static DebugAdmin* GetInstance();
    static funMap_t& GetMap();

  private:
    void Init();
    int AddFun ( std::string funname );
    void HandleFun ( std::string funname, std::string funarg );
    void StrSimplification ( std::string& str, char c = ' ' );
    void GetNameAndArg ( std::string funcmd, std::string& funname, std::string& funarg );
    void _DebugAdminTask();

    bool GetRunFlag();
    void SetRunFlag ( bool flag );

    static void* DebugAdminTask ( void* pObj );

    void Start();
    void Stop();

  private:
    int m_msg_id;
    bool m_runFlag;
    sem_t m_sem;
    pthread_t m_pid;
    static funMap_t m_funMap;
    DebugAdminMsg_t m_DebugAdminMsg;
};


#endif   /* ----- #ifndef DEBUG_INC  ----- */

