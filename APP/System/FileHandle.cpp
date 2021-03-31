/*
 * =====================================================================================
 *
 *       Filename:  FileHandle.cpp
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
#include <dirent.h>
#include <string.h>

#include "FileHandle.h"

FileHandle::FileHandle ( )
{
}

FileHandle::~FileHandle()
{
}

bool FileHandle::Create ( std::string filename )
{
  std::ofstream ofs;
  ofs.open ( filename, std::ofstream::binary | std::ofstream::trunc );

  if ( !ofs || !ofs.good() )
    return false;

  ofs.close();

  return true;
}

bool FileHandle::Read ( std::string filename, std::vector<char>& vecharFile )
{
  std::ifstream ifs ( filename, std::ifstream::in | std::ifstream::binary );

  if ( !ifs )
    return false;

  ifs.seekg ( 0, ifs.end );
  int len = ifs.tellg();
  ifs.seekg ( 0, ifs.beg );

  vecharFile.resize ( len, 0 );

  ifs.read ( &vecharFile[0], vecharFile.size() );
  ifs.close();

  return true;
}

bool FileHandle::Write ( std::string filename, std::vector<char>& vecharFile )
{
  std::ofstream ofs ( filename, std::ofstream::binary );

  if ( !ofs )
    return false;

  ofs.write ( &vecharFile[0], vecharFile.size() );
  ofs.close();
  system ( "sync" );

  return true;
}

bool FileHandle::WriteAppend ( std::string filename, std::vector<char>& vecharFile )
{
  return WriteAppend ( filename, &vecharFile[0], vecharFile.size() );
}

bool FileHandle::WriteAppend ( std::string filename, char* buffer, uint32_t bufferLen )
{
  std::ofstream ofs;
  ofs.open ( filename, std::ofstream::binary | std::ofstream::app );

  if ( !ofs )
    return false;

  ofs.write ( buffer, bufferLen );
  ofs.close();
  system ( "sync" );

  return true;
}

#if  1
bool FileHandle::ListFile ( std::string filefilter, std::vector<std::string>& vecstrFile )
{
  if (  filefilter.size() == 0  )
    return false;

  const int bufferLen = 256;
  std::string cmd = "ls ";
  cmd += filefilter;

  char buffer[bufferLen] = { 0 };
  FILE* fp = popen ( cmd.c_str(), "r" );

  if ( !fp )
    return false;

  while ( NULL != fgets ( buffer, bufferLen, fp ) )
  {
    buffer[ strlen ( buffer ) - 1] = 0; 		/* remove \n */
    vecstrFile.push_back ( buffer );
    memset ( buffer, 0x0, bufferLen );
  }

  pclose ( fp );

  return true;
}
#else
bool FileHandle::ListFile ( std::string filePath, std::string filefilter, std::vector<std::string>& vecstrFile )
{
  if ( ( filefilter.size() == 0  )
       || ( filePath.size() == 0 ) )
    return false;

  std::string strTemp;
  DIR* pDir = opendir ( filePath.c_str() );
  dirent* ent = NULL;
  std::size_t found;

  if ( !pDir )
    return false;

  vecstrFile.clear();

  while ( NULL != ( ent = readdir ( pDir ) ) )
  {
    if ( ent->d_type == DT_DIR )
      continue;

    strTemp = ent->d_name;

    found = strTemp.rfind ( filefilter ) ;

    if ( ( std::string::npos == found )
         || ( ( strTemp.size() - found ) != filefilter.size() ) )
      continue;

    vecstrFile.push_back ( ent->d_name );
  }

  closedir ( pDir );

  return true;
}
#endif


#ifdef TEST

//#include "BmpHandle.h"

int main ( int argc, char* argv[] )
{
  std::vector<std::string> vecstrFile;

  FileHandle::ListFile ( argv[1], vecstrFile );

  printf ( "%ld\n", vecstrFile.size() );

  for ( auto ele : vecstrFile )
  {
    printf ( "%s\n", ele.c_str() );
  }

  return 0;
}

#endif

