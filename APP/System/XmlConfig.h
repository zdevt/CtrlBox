/*
 * =====================================================================================
 *
 *       Filename:  XmlConfig.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/21/2015 02:47:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  XMLCONFIG_INC
#define  XMLCONFIG_INC

#include <string>
#include <vector>
#include <sstream>
#include <stdint.h>

#include "tinyxml2.h"


#if defined(__arm__)
  #define XMLCONFIG_FILENAME  "/app/SystemConfig.xml"
#else
  #define XMLCONFIG_FILENAME  "SystemConfig.xml"
#endif
/*  支持 int short double float string 不支持unsigned char */
class XmlConfig
{
  private:
    XmlConfig ();
    ~XmlConfig();

  private:
    static bool _SetParam ( std::string domain, std::string key, std::string value );
    static bool _GetParam ( std::string domain, std::string key, std::string& value );

  public:
    template<typename T>
    static bool SetParam ( std::string domain, std::string key, T value )
    {
      std::stringstream ss;
      ss << value;
      return _SetParam ( domain, key, ss.str() );
    }

    template<typename T>
    static bool GetParam ( std::string domain, std::string key, T& value, T defaultvalue )
    {
      std::string output;

      if ( !_GetParam ( domain, key, output ) )
      {
        value = defaultvalue;
        return false;
      }

      std::stringstream ss ( output );
      ss >> value;

      return true;
    }

    static bool SetParamArray ( std::string domain, std::string key, uint8_t* p, int size );
    static bool GetParamArray ( std::string domain, std::string key, uint8_t* p, uint8_t* pdefault, int size );

    static void InitXmlFromEeprom();
    static void SaveXmlToEeprom();

  private:
    static pthread_mutex_t m_XmlCOnfigMutex;
};

#endif   /* ----- #ifndef XmlConfig.h ----- */

