/*
 * =====================================================================================
 *
 *       Filename:  MainboardMini.h
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

#ifndef  MAINBOARDMINI_INC
#define  MAINBOARDMINI_INC

#include "MainboardDefault.h"
#include "FpgaECP3.h"

#define  MAINBOARDMININAME "LXBOX500"

class MainboardMini : public MainboardDefault
{
  public:
    explicit MainboardMini ( std::string mainboardName );
    virtual ~MainboardMini();

    virtual bool Open();
    virtual bool Close();
    virtual bool Init();
    virtual bool DeInit();

    virtual std::string GetDmdI2cBus();
    virtual bool WriteBmpFileToFpga ( std::string filename, int addr );

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

    virtual int SetDisplayTimming ( uint32_t w, uint32_t h, void* p );
    virtual int SetI2cPower ( std::string busname, bool onoff );

    virtual bool CheckSignalChange ( uint32_t& w, uint32_t& h );
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

