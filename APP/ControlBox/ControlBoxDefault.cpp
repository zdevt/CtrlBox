/*
 * =====================================================================================
 *
 *       Filename:  ControlBoxDefault.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 22时40分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "ControlBoxDefault.h"
#include "Led74Hc595D.h"

std::shared_ptr<ControlBox> ControlBoxDefault::GetObj ( std::string controlBoxName )
{
  return std::make_shared<ControlBoxDefault> ( controlBoxName );
}

ControlBoxDefault::ControlBoxDefault ( std::string controlBoxName )
  : ControlBox ( controlBoxName )
{

}

ControlBoxDefault::~ControlBoxDefault()
{

}

bool ControlBoxDefault::Open()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );

  Led74Hc595D::Disp ( "1" );

  PowerSupplyInterface::GetPowerSupplyPtr()->Open();
  return GET_MBPTR->Open();
}

bool ControlBoxDefault::Close()
{
  PRINT_LOG ( LOG_LEVEL_NORMAL, "\n" );
  GET_MBPTR->Close();
  PowerSupplyInterface::GetPowerSupplyPtr()->Close();

  return true;
}

