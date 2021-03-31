/*
 * =====================================================================================
 *
 *       Filename:  SoInterface.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/29/2014 09:42:05 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <fstream>
#include <dlfcn.h>

#include "SoInterface.h"

SoInterface::SoInterface ( std::string filename )
  : m_handle ( NULL )
{
  m_handle = dlopen ( filename.c_str(), RTLD_LAZY );
}

SoInterface::~SoInterface()
{
  if ( m_handle )
  {
    dlclose ( m_handle );
    m_handle = NULL;
  }
}

void* SoInterface::GetFunptr ( std::string funname )
{
  if ( m_handle )
    return dlsym ( m_handle, funname.c_str() );

  fprintf ( stderr, "%s\n", dlerror() );
  return NULL;
}

