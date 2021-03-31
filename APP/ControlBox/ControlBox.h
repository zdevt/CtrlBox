/*
 * =====================================================================================
 *
 *       Filename:  ControlBox.h
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
#ifndef  CONTROLBOX_INC
#define  CONTROLBOX_INC

#include <memory>
#include <string>

#include "LogPrint.h"
#include "MainboardInterface.h"
#include "PowerSupplyInterface.h"

class ControlBox
{
  public:
    explicit ControlBox ( std::string controlBoxName );
    virtual ~ControlBox();

  public:
    std::string GetControlBoxName();
    virtual bool Open() = 0;
    virtual bool Close() = 0;

  private:
    std::string m_controlBoxName;
};

#endif   /* ----- #ifndef ControlBox.h ----- */

