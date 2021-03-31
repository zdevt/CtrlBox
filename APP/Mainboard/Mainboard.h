/*
 * =====================================================================================
 *
 *       Filename:  Mainboard.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/10/2015 10:33:14 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  MAINBOARD_INC
#define  MAINBOARD_INC

#include <string>
#include <memory>
#include <semaphore.h>

#include "LogPrint.h"
#include "At91GpioDev.h"
#include "XmlConfig.h"
#include "SemaphoreLocker.h"

class Mainboard
{
  public:
    explicit Mainboard ( std::string mainboardName );
    virtual ~Mainboard();

    std::string GetMainboardName();

    virtual bool SetWorkTime ( uint32_t workTime );
    virtual bool GetWorkTime ( uint32_t& workTime );

    virtual bool Open() = 0;
    virtual bool Close() = 0;
    virtual bool Init() = 0;
    virtual bool DeInit() = 0;

    virtual bool SetFanSpeed ( uint8_t fanid, uint32_t speed ) = 0;
    virtual bool GetFanSpeed ( uint8_t fanid, uint32_t& speed ) = 0;

    virtual bool BlinkLed() = 0;
    virtual bool GetOnOffGpio( ) = 0;
    virtual bool SetDmdReSetPin ( bool val ) = 0;
    virtual std::string GetDmdI2cBus() = 0;
    virtual bool WriteBmpFileToFpga ( std::string filename, int addr ) = 0;

    virtual int FpgaLoad ( ) = 0;
    virtual int FpgaIsLoad ( ) = 0;
    virtual int FpgaUnLoad ( ) = 0;
    virtual int FpgaInitGpioPin ( ) = 0;

    virtual int FpgaRegGet ( int addr ) = 0;
    virtual int FpgaRegSet ( int addr, int val ) = 0;
    virtual int FpgaDdrGetReg ( int addr ) = 0;
    virtual int FpgaDdrSetReg ( int addr, int val ) = 0;
    virtual int FpgaSetRegN ( void* p ) = 0;
    virtual int FpgaDdrSetRegN ( void* p ) = 0;

    virtual int GpioSetPeriph ( uint32_t pin, int use_pullup ) = 0;
    virtual int GpioSetAPeriph ( uint32_t pin, int use_pullupa ) = 0;
    virtual int GpioSetBPeriph ( uint32_t pin, int use_pullup ) = 0;
    virtual int GpioSetInput ( uint32_t pin, int use_pullup ) = 0;
    virtual int GpioSetOutput ( uint32_t pin, int value  ) = 0;
    virtual int GpioSetDeglitch ( uint32_t pin, int is_on ) = 0;
    virtual int GpioSetMultiDriver ( uint32_t pin, int is_on ) = 0;

    virtual int GpioSetValue ( uint32_t pin, int value ) = 0;
    virtual int GpioGetValue ( uint32_t pin ) = 0;

    virtual int SetDisplayTimming ( uint32_t w, uint32_t h, void* p ) = 0;
    virtual int SetI2cPower ( std::string busname, bool onoff ) = 0;

    virtual int CheckSignalAndShow( ) = 0;
    virtual int SetInputSignalRectAndShow ( int x, int y, int w, int h, uint32_t hres, uint32_t vres ) = 0;

    virtual int WriteEdid( ) = 0;

    virtual int GetInputSignalResol ( uint32_t& w, uint32_t& h ) = 0;

    virtual int SetInputSignalRect ( int x, int y, int w, int h ) = 0;
    virtual int GetInputSignalRect ( int& x, int& y, int& w, int& h ) = 0;

    virtual int SetOuputSignalRect ( int x, int y, int w, int h ) = 0;
    virtual int GetOuputSignalRect ( int& x, int& y, int& w, int& h ) = 0;

    virtual int SetVsHsFactorAndShow ( int ix, int iy, int iw, int ih,
                                       int ox, int oy, int ow, int oh ) = 0;
    virtual sem_t* GetFpgaSem();

    virtual bool GetCutWinFlag( );
    virtual void SetCutWinFlag ( bool flag );

  private:
    std::string m_MainboardName;
    sem_t m_fpga_sem;
    bool m_cutwinFlag;
};

#endif   /* ----- #ifndef MAINBOARD_INC  ----- */

