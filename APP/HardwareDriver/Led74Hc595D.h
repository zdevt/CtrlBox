/*
 * =====================================================================================
 *
 *       Filename:  Led74Hc595D.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/17/2015 01:15:59 PM
 *  Last Modified:  2018-05-30 06:30:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  LED74HC595D_INC
#define  LED74HC595D_INC

#include <stdint.h>
#include <string>
#include <map>

#include "At91GpioDev.h"
#include "GpioDefine.h"

#pragma pack(push)
#pragma pack(1)

#pragma pack(pop)

typedef std::map<std::string, uint8_t> mapStrUint8_t;


#define LOW           0
#define HIGH          1

class Led74Hc595D
{
  private:
    Led74Hc595D();
    ~Led74Hc595D();

  public:
    static Led74Hc595D* GetInstance();
    static bool Disp ( std::string c );

  private:
    void Delay ( int32_t ims );
    void SetPinLevel ( uint32_t dwPin, uint8_t byLevel );
    void WriteOneBit ( uint8_t byBit );
    void SetStrobePulse ( void );
    void WriteData ( uint8_t Data );

  public:

  private:
    static mapStrUint8_t m_mapStrUint8;
};

#endif   /* ----- #ifndef Led74Hc595D.h ----- */

