/*
 * =====================================================================================
 *
 *       Filename:  PowerSupplyInterface.h
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
#ifndef  POWERSUPLYINTERFACE_INC
#define  POWERSUPLYINTERFACE_INC

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <pthread.h>

#include "PowerSupply.h"

typedef std::shared_ptr<PowerSupply> ( *pGetPowerSupplyObj ) ( std::string );
typedef std::map<std::string, pGetPowerSupplyObj> mapGetPowerSupplyObj_t;

class PowerSupplyInterface
{
  private:
    PowerSupplyInterface();
    ~PowerSupplyInterface();

    static std::shared_ptr<PowerSupply> GetObj ( std::string PowerSupplyName );
    static std::string GetPowerSupplyName ( );

  public:
    static void Load ( ); /*  每次开机只需要调用一次 */
    static std::shared_ptr<PowerSupply> GetPowerSupplyPtr();

  private:
    static mapGetPowerSupplyObj_t m_mapGetPowerSupplyObj;
    static std::string m_PowerSupplyName;
    static std::shared_ptr<PowerSupply> m_pPowerSupply;
    static pthread_mutex_t m_PowerSupplyInterfaceMutex;
};

#endif   /* ----- #ifndef PowerSupplyInterface.h ----- */

