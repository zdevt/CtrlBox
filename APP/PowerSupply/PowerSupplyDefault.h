/*
 * =====================================================================================
 *
 *       Filename:  PowerSupplyDefault.h
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

#ifndef  POWERSUPPLYDEFAULT_INC
#define  POWERSUPPLYDEFAULT_INC

#include "PowerSupply.h"
#include "GpioDefine.h"

#define  POWERSUPPLYDEFAULTNAME           "PowerSupplyDefault"

#define  POWERSUPPLYDEFAULT_IIC_BUS       (3)
#define  POWERSUPPLYDEFAULT_IIC_SLAVE     (0xb0)
#define  POWERSUPPLYDEFAULT_IIC_REG_ADDR  (0x78)

#pragma pack(push)
#pragma pack(1)
typedef union
{
  struct
  {
    uint8_t vLsb : 2;
    uint8_t : 6;
    uint8_t vMsb;

    uint8_t tLsb : 2;
    uint8_t : 6;
    uint8_t tMsb;

    uint8_t : 8;
    uint8_t : 8;

    uint8_t aLsb : 2;
    uint8_t : 6;
    uint8_t aMsb;

    uint8_t vccLsb : 2;
    uint8_t : 6;
    uint8_t vccMsb;
  };
  uint8_t data[10];
} power_status_data_t;

#pragma pack(pop)

class PowerSupplyDefault : public PowerSupply
{
  public:
    explicit PowerSupplyDefault ( std::string powerSupplyName );
    virtual ~PowerSupplyDefault();

    virtual bool Open();
    virtual bool Close();

    virtual bool GetAll ( power_status_all_t&  power_status_all );

  public:
    static std::shared_ptr<PowerSupply> GetObj ( std::string infilename );
};

#endif   /* ----- #ifndef MAINBOARD_INC  ----- */

