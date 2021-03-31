/*
 * =====================================================================================
 *
 *       Filename:  MainboardInterface.h
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
#ifndef  MAINBOARDINTERFACE_INC
#define  MAINBOARDINTERFACE_INC

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <pthread.h>

#include "Mainboard.h"

#define GET_MBPTR 	MainboardInterface::GetMainboardPtr()

#define FpgaSetReg( addr, val )   GET_MBPTR->FpgaRegSet( addr, val )
#define FpgaGetReg( addr )        GET_MBPTR->FpgaRegGet( addr )
#define FPGA_DDR_SET_REGN( a)     GET_MBPTR->FpgaDdrSetRegN (a)

#define GPIO_SET_PERIPH(a,b)      GET_MBPTR->GpioSetPeriph(a,b)
#define GPIO_SET_APERIPH(a,b)     GET_MBPTR->GpioSetAPeriph(a,b)
#define GPIO_SET_BPERIPH(a,b)     GET_MBPTR->GpioSetBPeriph(a,b)
#define GPIO_SET_INPUT(a,b)       GET_MBPTR->GpioSetInput(a,b)
#define GPIO_SET_OUTPUT(a,b)      GET_MBPTR->GpioSetOutput(a,b)
#define GPIO_SET_DEGLITCH(a,b)    GET_MBPTR->GpioSetDeglitch(a,b)
#define GPIO_SET_MULTIDRIVER(a,b) GET_MBPTR->GpioSetMultiDriver(a,b)
#define GPIO_SET_VALUE(a,b)       GET_MBPTR->GpioSetValue(a,b)
#define GPIO_GET_VALUE(a)         GET_MBPTR->GpioGetValue(a)


typedef std::shared_ptr<Mainboard> ( *pGetMainboardObj ) ( std::string );
typedef std::map<std::string, pGetMainboardObj> mapGetMainboardObj_t;

class MainboardInterface
{
  private:
    MainboardInterface();
    ~MainboardInterface();

    static std::shared_ptr<Mainboard> GetObj ( std::string mainboardName );
    static std::string GetMainboardName ( );
    static std::string GetMainboardNameFormXml();

  public:
    static void GetSupport ( );
    static void Load ( ); /*  每次开机只需要调用一次 */
    static std::shared_ptr<Mainboard> GetMainboardPtr();

  private:
    static mapGetMainboardObj_t m_mapGetMainboardObj;
    static std::string m_mainboardName;
    static std::shared_ptr<Mainboard> m_pMainboard;
    static pthread_mutex_t m_MainboardInterfaceMutex;
};

#endif   /* ----- #ifndef MainboardInterface.h ----- */

