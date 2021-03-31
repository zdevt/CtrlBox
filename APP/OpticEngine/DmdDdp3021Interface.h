/*
 * =====================================================================================
 *
 *       Filename:  DmdDdp3021Interface.h
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
#ifndef  DMDDDP3021INTERFACE_INC
#define  DMDDDP3021INTERFACE_INC

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <pthread.h>
#include <arpa/inet.h>

#include "I2cBusInterface.h"
#include "DmdDdp3021Reg.h"
#include "Locker.h"
#include "XmlConfig.h"
#include "MainboardInterface.h"

#define DMDDDP3021_I2CBUS      GET_MBPTR->GetDmdI2cBus()

typedef struct
{
  uint16_t red_strobe;
  uint16_t green_strobe;
  uint16_t blue_strobe;
  uint16_t subframe1_strobe;
  uint16_t subframe2_strobe;
  uint16_t yellow_strobe;
  uint16_t cyan_strobe;
  uint16_t magenta_strobe;
  uint16_t white_strobe;
  uint16_t black_strobe;
} set_dac_strobe_t;

class DmdDdp3021Interface
{
  private:
    DmdDdp3021Interface();
    ~DmdDdp3021Interface();

  public:
    static int SetProjMode ( uint8_t mode );
    static int GetProjMode ( uint8_t& mode );

    static int SetDmdGamma ( uint8_t gammaType );
    static int GetDmdGamma ( uint8_t& gammaType );

    static int SetColorOffset ( uint16_t r, uint16_t g, uint16_t b );
    static int GetColorOffset ( uint16_t& r, uint16_t& g, uint16_t& b );

    static int SetColorBrightness ( uint16_t r, uint16_t g, uint16_t b );
    static int GetColorBrightness ( uint16_t& r, uint16_t& g, uint16_t& b );

    static int SetColorContrast ( uint16_t r, uint16_t g, uint16_t b );
    static int GetColorContrast ( uint16_t& r, uint16_t& g, uint16_t& b );

    static int SetBcMode ( uint8_t mode );
    static int GetBcMode ( uint8_t& mode );

    static int SetDutycycle ( uint8_t dc );
    static int GetDutycycle ( uint8_t dc );

    static int SetHsg ( void* hsg );
    static int GetHsg ( void* hsg );

    static int DmdColorPointControlProcessWrite ( uint8_t data = DDP3021_DSP_ALL_DIS );

    static int SetDac ( uint8_t color, set_dac_strobe_t* pset_dac_strobe );

    static int SetRedDac ( uint16_t r, uint16_t g, uint16_t b );
    static int GetRedDac ( uint16_t& r, uint16_t& g, uint16_t& b );

    static int SetGreenDac ( uint16_t r, uint16_t g, uint16_t b );
    static int GetGreenDac ( uint16_t& r, uint16_t& g, uint16_t& b );

    static int SetBlueDac ( uint16_t r, uint16_t g, uint16_t b );
    static int GetBlueDac ( uint16_t& r, uint16_t& g, uint16_t& b );


  private:
    static int _SetDac ( uint8_t color, uint8_t speColr, uint16_t current );
    static int _GetDac ( uint8_t color, uint8_t speColr, uint16_t& current );
    static int _GetDacSafety ( uint8_t color, uint8_t speColr, uint16_t& current );

  private:
    static pthread_mutex_t m_DmdDdp3021InterfaceMutex;
};

#endif   /* ----- #ifndef DmdDdp3021Interface.h_INC  ----- */

