/*
 * =====================================================================================
 *
 *       Filename:  PowerSupply.h
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

#ifndef  POWERSUPPLY_INC
#define  POWERSUPPLY_INC

#include <string>
#include <memory>
#include <unistd.h>
#include <vector>

#include "LogPrint.h"
#include "At91GpioDev.h"
#include "I2cBusInterface.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint32_t voltage;
  uint32_t ampere;
  uint32_t watt;
  int32_t celsius;
  uint32_t status;
} power_status_all_t;
#pragma pack(pop)


class PowerSupply
{
  public:
    explicit PowerSupply ( std::string mainboardName );
    virtual ~PowerSupply();

    std::string GetPowerSupplyName();
    virtual bool Open() = 0;
    virtual bool Close() = 0;

    virtual bool GetAll ( power_status_all_t&  power_status_all ) = 0;

  private:
    std::string m_PowerSupplyName;
};

#endif   /* ----- #ifndef MAINBOARD_INC  ----- */

