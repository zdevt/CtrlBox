/*
 * =====================================================================================
 *
 *       Filename:  OpticEngineInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/11/2015 10:49:10 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef  OPTICENGINEINTERFACE_INC
#define  OPTICENGINEINTERFACE_INC

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <pthread.h>

#include "OpticEngine.h"

#define GET_ENGPTR 		OpticEngineInterface::GetEnginePtr()

typedef std::shared_ptr<OpticEngine> ( *pGetOpticEngineObj ) ( std::string );
typedef std::map<std::string, pGetOpticEngineObj> mapGetOpticEngineObj_t;

class OpticEngineInterface
{
  private:
    explicit OpticEngineInterface();
    virtual ~OpticEngineInterface();

    static std::shared_ptr<OpticEngine> GetObj ( std::string enginename );
    static std::string GetEngineName ( );
    static std::string GetEngineNameFormXml();

  public:
    static void GetSupport ( );
    static void Load ( ); /*  每次开机只需要调用一次 */
    static std::shared_ptr<OpticEngine> GetEnginePtr();

  private:
    static mapGetOpticEngineObj_t m_mapGetOpticEngineObj;
    static std::string m_enginename;
    static std::shared_ptr<OpticEngine> m_pOpticEngine;
    static pthread_mutex_t m_OpticEngineInterfaceMutex;
};

#endif   /* ----- #ifndef OpticEngineInterface.h_INC  ----- */

