/*
 * =====================================================================================
 *
 *       Filename:  PowerSupply.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/10/2015 10:33:01 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#include "PowerSupply.h"


PowerSupply::PowerSupply ( std::string mainboardName )
  : m_PowerSupplyName ( mainboardName )
{

}

PowerSupply::~PowerSupply()
{

}

std::string PowerSupply::GetPowerSupplyName()
{
  return m_PowerSupplyName;
}

