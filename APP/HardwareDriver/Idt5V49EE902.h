/*
 * =====================================================================================
 *
 *       Filename:  Idt5V49EE902.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/21/2016 02:00:29 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  IDT5V49EE902_INC
#define  IDT5V49EE902_INC

#include <string>
#include <vector>

#include <stdint.h>

#define IDT5V49_SLAVE   (0xD4)

class Idt5V49EE902
{
  private:
    Idt5V49EE902 ( );
    ~Idt5V49EE902();

  public:
    static int SetPll ( void* parg, std::string i2cbus = "/dev/i2c-4" );
};

#endif   /* ----- #ifndef I2CEEPROM_INC  ----- */

