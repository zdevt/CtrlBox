/*
 * =====================================================================================
 *
 *       Filename:  XmlConfig.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/21/2015 02:46:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <pthread.h>

#include "XmlConfig.h"
#include "Locker.h"

using namespace tinyxml2;

pthread_mutex_t XmlConfig::m_XmlCOnfigMutex = PTHREAD_MUTEX_INITIALIZER;

XmlConfig::XmlConfig ( )
{

}

XmlConfig::~XmlConfig()
{

}

bool XmlConfig::_GetParam ( std::string domain, std::string key, std::string& value )
{
  Locker locker ( &m_XmlCOnfigMutex );
  XMLDocument doc;

  if ( XML_ERROR_FILE_NOT_FOUND == doc.LoadFile ( XMLCONFIG_FILENAME ) )
    return false;

  if ( !doc.RootElement() )
    return false;

  XMLElement* domainElement = doc.RootElement()->FirstChildElement ( domain.c_str() );

  if ( !domainElement )
    return false;

  XMLElement* elementFindValue = domainElement->FirstChildElement ( key.c_str() );

  if ( !elementFindValue )
    return false;

  if ( elementFindValue->GetText() )
  {
    value =  elementFindValue->GetText();
    return true;
  }

  return false;
}

bool XmlConfig::_SetParam ( std::string domain, std::string key, std::string value )
{
  Locker locker ( &m_XmlCOnfigMutex );
  XMLDocument doc;

  if ( XML_ERROR_FILE_NOT_FOUND == doc.LoadFile ( XMLCONFIG_FILENAME ) )
  {
    XMLDeclaration* declaration = doc.NewDeclaration ( "xml version=\"1.0\" encoding=\"UTF-8\"" );
    doc.LinkEndChild ( declaration );
  }

  if ( !doc.RootElement() )
  {
    XMLElement* rootelement = doc.NewElement ( "SYSTEMCONFIG" );
    doc.LinkEndChild ( rootelement );
  }

  XMLElement* domainElement = doc.RootElement()->FirstChildElement ( domain.c_str() );

  if ( !domainElement )
  {
    domainElement = doc.NewElement ( domain.c_str() );
    doc.RootElement()->InsertEndChild ( domainElement );
  }

  XMLElement* keyElement = domainElement->FirstChildElement ( key.c_str() );

  if ( !keyElement )
  {
    keyElement = doc.NewElement ( key.c_str() );
    keyElement->SetText ( value.c_str() );
    domainElement->InsertEndChild ( keyElement );
  }
  else
    keyElement->SetText ( value.c_str() );

  //doc.Print();
  doc.SaveFile ( XMLCONFIG_FILENAME );

  return true;
}

bool XmlConfig::SetParamArray ( std::string domain, std::string key, uint8_t* p, int size )
{
  std::stringstream ss;

  for ( int i = 0; i < size; ++i )
    ss << ( int ) ( p[i] ) << ',';

  return XmlConfig::SetParam ( domain, key, ss.str() );
}

bool XmlConfig::GetParamArray ( std::string domain, std::string key, uint8_t* p, uint8_t* pdefault, int size )
{
  std::string str;
  std::string strdef = "0";

  if ( !XmlConfig::GetParam ( domain, key, str, strdef ) )
  {
    if ( pdefault )
      memcpy ( p, pdefault, size );
    else
      memset ( p, 0, size );

    return false;
  }

  std::size_t pos;

  while ( std::string::npos != ( pos = str.find ( ',' ) ) )
    str.replace ( pos, 1, 1, ' ' );

  std::stringstream ss ( str );

  int temp = 0;

  for ( int i = 0; ss >> temp; ++i )
    p[i] = temp;

  return true;
}

void XmlConfig::InitXmlFromEeprom()
{

}

void XmlConfig::SaveXmlToEeprom()
{

}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

int main ( int argc, char* argv[] )
{
  char aa[] = { 'a', 'b', 'c'};
  std::string model = ( char* ) ( &aa[0] );

  std::string str = "asdf";
  std::string str1;

  XmlConfig::SetParam ( "OpticEngine", "Dutycycle", model );
  XmlConfig::GetParam ( "OpticEngine", "Dutycycle", str1, str );

  printf ( "%s\n", str1.c_str() );

  return 0;
}

#endif

