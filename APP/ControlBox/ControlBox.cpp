/*
 * =====================================================================================
 *
 *       Filename:  ControlBox.cpp
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

#include "ControlBox.h"

ControlBox::ControlBox ( std::string controlBoxName )
  : m_controlBoxName ( controlBoxName )
{

}

ControlBox::~ControlBox()
{

}

std::string ControlBox::GetControlBoxName()
{
  return m_controlBoxName;
}

