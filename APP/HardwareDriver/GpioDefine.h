
/*
 * =========================================================================
 *
 *       FileName:  GpioDefine.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2018-05-30 06:26:13
 *  Last Modified:  2018-05-30 06:54:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt ()
 *   Organization:
 *
 * =========================================================================
 */


#ifndef GPIODEFINE_INC
#define GPIODEFINE_INC

#include "At91GpioDev.h"

#define  POWERSUPPLYDEFAULT_ON_OFF_PIN        ( AT91_PIN_PD27 )
#define  POWERSUPPLYDEFAULT_LATCH             ( AT91_PIN_PB27 )
#define  POWERSUPPLYDEFAULT_GPIO              ( AT91_PIN_PC24 )

#define  MAINBOARDDEFAULT_LED                 ( AT91_PIN_PA0 )
#define  MAINBOARDDEFAULT_SYNC_ON_OFF         ( AT91_PIN_PB26 )
#define  MAINBOARDDEFAULT_DMD_RESET           ( AT91_PIN_PA3 )
#define  MAINBOARDDEFAULT_ON_OFF              ( AT91_PIN_PB21 )
#define  MAINBOARDDEFAULT_I2CBUS_ON_OFF       ( AT91_PIN_PC28 )

//Led74Hc595D
#define DATA                                  ( AT91_PIN_PD2 )
#define SCLK                                  ( AT91_PIN_PD0 )
#define STROBE                                ( AT91_PIN_PD1 )
#define ON_OFF                                ( AT91_PIN_PD18 )

#define ICS307_SCLK                           ( AT91_PIN_PD5 )
#define ICS307_DATA                           ( AT91_PIN_PD6 )
#define ICS307_STROBE                         ( AT91_PIN_PD7 )
#define ICS307_PDTS                           ( AT91_PIN_PD8 )

#define FPGA_ECP3_PROG_PIN                    ( AT91_PIN_PC17 )
#define FPGA_ECP3_CONFIG_DONE_PIN             ( AT91_PIN_PC19 )
#define FPGA_ECP3_RESET_PIN                   ( AT91_PIN_PC26 )

#define FPGA_ALTEA_IS_LOAD                    ( AT91_PIN_PC19 )

// Pwm
#define PWM_PIN_PB8                           ( AT91_PIN_PB8 )
#define PWM_PIN_PB9                           ( AT91_PIN_PB9 )

#endif /*  GPIODEFINE_INC  */

