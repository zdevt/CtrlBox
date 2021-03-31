/*
 * =====================================================================================
 *
 *       Filename:  GpioMod.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/13/2015 05:57:26 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  GPIOMOD_INC
#define  GPIOMOD_INC


/* 管脚为空则不操作 */
#define PIN_FUNC(fun,pin,arg) do{ if(pin){fun(pin,arg);} }while(0)


typedef int ( *PFUNC ) ( void*  );


typedef struct GPIO_DATA
{
  uint32_t  addr;
  uint32_t  val;
} gpio_data_t;


enum
{
  CMD_GPIO_TEST     = 0,
  CMD_SET_GPIO_PERIPH,/* mux the pin to the "GPIO" peripheral role. */
  CMD_SET_A_PERIPH,   /* mux the pin to the "A" internal peripheral role. */
  CMD_SET_B_PERIPH,   /* mux the pin to the "B" internal peripheral role. */
  CMD_SET_GPIO_INPUT, /* mux the pin to the gpio controller , and configure it for an input. */
  CMD_SET_GPIO_OUTPUT,/* output */
  CMD_SET_DEGLITCH,   /* enable/disable the glitch filter; mostly used with IRQ handling */
  CMD_SET_MULTI_DRIVER, /* enable/disable the multi-driver output pin to run as an open collector output*/
  CMD_SET_GPIO_VALUE, /* assuming the pin is muxed as a gpio output, set its value. */
  CMD_GET_GPIO_VALUE, /* read the pin's value (works even if it's not muxed as a gpio). */

  CMD_GPIO_MAX,
} GPIO_CMD_E;


#endif   /* ----- #ifndef GPIOMOD_INC  ----- */

