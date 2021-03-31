/*
 * =====================================================================================
 *
 *       Filename:  UpgradeFile.cpp
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
#include <zlib.h>

#include "UpgradeFile.h"
#include "FileHandle.h"

UpgradeFile::UpgradeFile ( std::string infilename )
  : m_infilename ( infilename )
{
  ReadFileHeader();
}

UpgradeFile::~UpgradeFile()
{
}

int UpgradeFile::ReadFile ( std::vector<char>& vecharFile )
{
  if ( FileHandle::Read ( m_infilename, vecharFile ) )
    return 0;

  return ERROR_UPGRADEFILE_NOEXIST;
}

int UpgradeFile::UnCompress ( std::vector<char>& vecharOut )
{
  std::vector<char> vechar;

  int ret = 0;

  if ( 0 != ( ret = ReadFile ( vechar ) ) )
    return ret;

  upgrade_file_header_t* pupgrade_file_header = reinterpret_cast<upgrade_file_header_t*> ( &vechar[0] );

  system ( "sync;echo 3 > /proc/sys/vm/drop_caches;" );

  vecharOut.clear();
  vecharOut.resize ( pupgrade_file_header->fileUnCompressSize, 0 );

  unsigned long srcLen = pupgrade_file_header->fileCompressSize;
  unsigned long desLen = vecharOut.size();

  if ( Z_OK != uncompress ( reinterpret_cast<unsigned char*> ( &vecharOut[0] ), &desLen,
                            reinterpret_cast<unsigned char*> ( &vechar[0] + sizeof ( upgrade_file_header_t ) ), srcLen ) )
    return ERROR_UPGRADEFILE_UNCOMPRESS;

  return 0;
}

void UpgradeFile::ReadFileHeader()
{
  std::ifstream ifs ( m_infilename, std::ifstream::binary );
  ifs.read ( reinterpret_cast<char*> ( &m_fileHeader ), sizeof ( upgrade_file_header_t ) );
  ifs.close();
}

int UpgradeFile::GetFileNo()
{
  return m_fileHeader.fileNo;
}

int UpgradeFile::WriteFile ( std::string filename, std::vector<char>& vecharFileData )
{
  if ( FileHandle::Write ( filename, vecharFileData ) )
    return 0;

  return ERROR_UPGRADEFILE_SAVE;
}

int UpgradeFile::WriteFile ( std::string filename )
{
  std::vector<char> vecharOut;
  UnCompress ( vecharOut );

  return WriteFile ( filename, vecharOut );
}

