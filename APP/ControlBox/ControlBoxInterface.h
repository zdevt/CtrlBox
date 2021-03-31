/*
 * =====================================================================================
 *
 *       Filename:  ControlBoxInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 22时40分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  CONTROLBOXINTERFACE_INC
#define  CONTROLBOXINTERFACE_INC

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <pthread.h>

#include "ControlBox.h"

#define GET_CTBOXPTR  ControlBoxInterface::GetControlBoxPtr()

typedef std::shared_ptr<ControlBox> ( *pGetControlBoxObj ) ( std::string );
typedef std::map<std::string, pGetControlBoxObj> mapGetControlBoxObj_t;

class ControlBoxInterface
{
  private:
    ControlBoxInterface();
    ~ControlBoxInterface();

    static std::shared_ptr<ControlBox> GetObj ( std::string controlBoxName );
    static std::string GetControlBoxName ( );

  public:
    static void Load ( ); /*  每次开机只需要调用一次 */
    static std::shared_ptr<ControlBox> GetControlBoxPtr();

  private:
    static mapGetControlBoxObj_t m_mapGetControlBoxObj;
    static std::string m_controlBoxName;
    static std::shared_ptr<ControlBox> m_pControlBox;
    static pthread_mutex_t m_ControlBoxInterfaceMutex;
};

#endif   /* ----- #ifndef ControlBoxInterface.h ----- */

