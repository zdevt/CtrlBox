/*
 * =====================================================================================
 *
 *       Filename:  ControlBoxDefault.h
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
#ifndef  CONTROLBOXDEFAULT_INC
#define  CONTROLBOXDEFAULT_INC

#include "ControlBox.h"

#define DEFAULTCONTROLBOXNAME   "defualt controlbox"

class ControlBoxDefault : public ControlBox
{
  public:
    explicit ControlBoxDefault ( std::string controlBoxName );
    virtual ~ControlBoxDefault();

  public:
    virtual bool Open();
    virtual bool Close();

    static std::shared_ptr<ControlBox> GetObj ( std::string controlBoxName );
};

#endif   /* ----- #ifndef ControlBoxDefault.h ----- */

