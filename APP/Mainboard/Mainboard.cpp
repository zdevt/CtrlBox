/*
 * =====================================================================================
 *
 *       Filename:  Mainboard.cpp
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

#include "Mainboard.h"


Mainboard::Mainboard ( std::string mainboardName )
  : m_MainboardName ( mainboardName ), m_cutwinFlag ( false )
{
  //XmlConfig::SetParam ( "Mainboard", "Name", mainboardName );
  sem_init ( &m_fpga_sem, 0, 1 );
}

Mainboard::~Mainboard()
{
  sem_destroy ( &m_fpga_sem );
}

std::string Mainboard::GetMainboardName()
{
  return m_MainboardName;
}

bool Mainboard::SetWorkTime ( uint32_t workTime )
{
  XmlConfig::SetParam ( "Mainboard", "WorkTime", workTime );
  return true;
}

bool Mainboard::GetWorkTime ( uint32_t& workTime )
{
  XmlConfig::GetParam ( "Mainboard", "WorkTime", workTime, ( uint32_t ) 0 );
  return true;
}

sem_t* Mainboard::GetFpgaSem()
{
  return &m_fpga_sem;
}

bool Mainboard::GetCutWinFlag( )
{
  int temp = 0;
  int val = 0;
  XmlConfig::GetParam ( "SignalRect", "flag", val, temp );

  if ( 1 == val )
    m_cutwinFlag = true;
  else
    m_cutwinFlag = false;

  return m_cutwinFlag;
}

void Mainboard::SetCutWinFlag ( bool flag )
{
  if ( flag )
    XmlConfig::SetParam ( "SignalRect", "flag", 1 );
  else
    XmlConfig::SetParam ( "SignalRect", "flag", 0 );

  m_cutwinFlag = flag;
}

