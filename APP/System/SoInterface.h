/*
 * =====================================================================================
 *
 *       Filename:  SoInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/29/2014 09:42:11 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */
#ifndef  SOINTERFACE_INC
#define  SOINTERFACE_INC

#include <string>

class SoInterface
{
  public:
    explicit SoInterface ( std::string filename );
    virtual ~SoInterface();

  public:
    void* GetFunptr ( std::string funname );

  private:
    void* m_handle;
};

#endif   /* ----- #ifndef SOINTERFACE_INC----- */

