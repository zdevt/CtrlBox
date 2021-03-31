/*
 * =====================================================================================
 *
 *       Filename:  Ics307.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月01日 22时45分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  ICS307_INC
#define  ICS307_INC

#include "At91GpioDev.h"
#include "GpioDefine.h"


#define ICS307_LOW            0
#define ICS307_HIGH           1

#define SET_GPIO_VALUE( pin, val )      At91SetGpioValue( pin, val )
#define SET_GPIO_OUTPUT( pin, val )     AT91SetGpioOutput( pin, val )

/* C1 C0 TTL F1 F0 S2 S1 S0 | V8 V7 V6 V5 V4 V3 V2 V1 | V0 R6 R5 R4 R3 R2 R1 R0 */
/* MSB                  LSB | MSB                 LSB | MSB                 LSB */
#define ICS307_OTHER_VAL(x)   ((unsigned long)(x & 0x001F) << 19)   /*C1 C0 TTL F1 F0*/
#define ICS307_OD_VAL(x)      ((unsigned long)(x & 0x0007) << 16)   /*S2-S0*/
#define ICS307_VDW_VAL(x)     ((unsigned long)(x & 0x01FF) << 7)    /*V8-V0*/
#define ICS307_RDW_VAL(x)     ((unsigned long)(x & 0x007F))         /*R6-R0*/

typedef enum
{
  ICS307_FREQUENCY_32500kHZ = 1,
  ICS307_FREQUENCY_54000KHZ,
  ICS307_FREQUENCY_81000KHZ,
  ICS307_FREQUENCY_42500KHZ,
  ICS307_FREQUENCY_74250KHZ,
  ICS307_FREQUENCY_27000KHZ,

  ICS307_FREQUENCY_MAX,
} ICS307FreqT;


class Ics307
{
  private:
    Ics307();
    ~Ics307();

  public:
    static void SetFrequency ( uint32_t val );

  private:
    static void _SetFrequency ( ICS307FreqT sFreq );
    static void Delay ( int32_t iNs );
    static void WriteOneBit ( char byBit );
    static void WriteData ( uint32_t dwData );
    static void SetStrobePulse ( );
    static void Init ( );
};

#endif   /* ----- #ifndef Ics307.h ----- */

