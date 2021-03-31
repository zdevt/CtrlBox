/*
 * =====================================================================================
 *
 *       Filename:  RoutineTask.h
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
#ifndef  ROUTINETASK_INC
#define  ROUTINETASK_INC

#include "DmdDdp442xReg.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  int32_t r;
  int32_t g;
  int32_t b;
} led_rgb_temp_t;

typedef struct
{
  int32_t dT; /*  driver Temp */
  int32_t rV; /*  r voltage */
  int32_t rC; /*  r current */
  int32_t gV;
  int32_t gC;
  int32_t bV;
  int32_t bC;
} led_status_t;

typedef struct
{
  int32_t v;
  int32_t a;
  int32_t w;
  int32_t c;
} power_status_t;

typedef struct
{
  int32_t a;
  int32_t b;
} mainboard_fan_t;

typedef struct
{
  int32_t dmdTemp;
  mainboard_fan_t mainboard_fan;
  led_rgb_temp_t led_rgb_temp;
  led_status_t led_status;
  power_status_t a;
  power_status_t b;

} all_device_status_t;
#pragma pack(pop)

class RoutineTask
{
  private:
    RoutineTask();
    ~RoutineTask();

  public:
    static int ReadAll();

  public:
    static int ReadMainboardFan( );
    static int ReadDmdTemp( );
    static int ReadLedTemp( );
    static int ReadLedStatus ( ); /*  led driver wtemp voltage current ..*/
    static int ReadPowerStatus ( );

  private:
    static all_device_status_t m_all_device_status;
};

#endif   /* ----- #ifndef RoutineTask.h ----- */

