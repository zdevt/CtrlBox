/*
 * =====================================================================================
 *
 *       Filename:  MainboardDefault.h
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

#ifndef  MAINBOARDDEFAULT_INC
#define  MAINBOARDDEFAULT_INC

#include "Mainboard.h"
#include "FpgaDev.h"
#include "GpioDefine.h"


#define  MAINBOARDDEFAULTNAME   "LXBOX1000"


class MainboardDefault : public Mainboard
{
  public:
    explicit MainboardDefault ( std::string mainboardName );
    virtual ~MainboardDefault();

    virtual bool Open();
    virtual bool Close();
    virtual bool Init();
    virtual bool DeInit();

    virtual bool BlinkLed();
    virtual bool GetOnOffGpio( );
    virtual bool SetDmdReSetPin ( bool val );
    virtual std::string GetDmdI2cBus();
    virtual bool WriteBmpFileToFpga ( std::string filename, int addr );

    virtual bool SetFanSpeed ( uint8_t fanid, uint32_t speed );
    virtual bool GetFanSpeed ( uint8_t fanid, uint32_t& speed );

    virtual int FpgaLoad ( );
    virtual int FpgaIsLoad ( );
    virtual int FpgaUnLoad ( );
    virtual int FpgaInitGpioPin ( );

    virtual int FpgaRegGet ( int addr );
    virtual int FpgaRegSet ( int addr, int val );
    virtual int FpgaDdrGetReg ( int addr );
    virtual int FpgaDdrSetReg ( int addr, int val );
    virtual int FpgaSetRegN ( void* p );
    virtual int FpgaDdrSetRegN ( void* p );

    virtual int GpioSetPeriph ( uint32_t pin, int use_pullup );
    virtual int GpioSetAPeriph ( uint32_t pin, int use_pullup );
    virtual int GpioSetBPeriph ( uint32_t pin, int use_pullup );
    virtual int GpioSetInput ( uint32_t pin, int use_pullup );
    virtual int GpioSetOutput ( uint32_t pin, int value );
    virtual int GpioSetDeglitch ( uint32_t pin, int is_on );
    virtual int GpioSetMultiDriver ( uint32_t pin, int is_on );

    virtual int GpioSetValue ( uint32_t pin, int value );
    virtual int GpioGetValue ( uint32_t pin );

    virtual int SetDisplayTimming ( uint32_t w, uint32_t h, void* p );
    virtual int SetI2cPower ( std::string busname, bool onoff );

    virtual int CheckSignalAndShow( );
    virtual int SetInputSignalRectAndShow ( int x, int y, int w, int h, uint32_t hres, uint32_t vres );

    virtual int WriteEdid( );

    virtual int GetInputSignalResol ( uint32_t& w, uint32_t& h );

    virtual int SetInputSignalRect ( int x, int y, int w, int h );
    virtual int GetInputSignalRect ( int& x, int& y, int& w, int& h );

    virtual int SetOuputSignalRect ( int x, int y, int w, int h );
    virtual int GetOuputSignalRect ( int& x, int& y, int& w, int& h );

    virtual int SetVsHsFactorAndShow ( int ix, int iy, int iw, int ih,
                                       int ox, int oy, int ow, int oh );
  public:
    static std::shared_ptr<Mainboard> GetObj ( std::string mainboardName );
};

#endif   /* ----- #ifndef MAINBOARD_INC  ----- */

