/*
 * =====================================================================================
 *
 *       Filename:  GenUpgradeFile.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/04/2015 12:40:57 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */
#include <string.h>

#include "GenUpgradeFile.h"

GenUpgradeFile::GenUpgradeFile()
{
}

GenUpgradeFile::~GenUpgradeFile()
{
}

/* filename filetype fileno ver("1.2.3.4") */
int GenUpgradeFile::GenFile ( int argc, char* argv[] )
{
  if ( argc < 6 )
  {
    fprintf ( stderr, "%s filename filetype fileno ver(1.2.3.4) outfilename   (all hex)!\n", argv[0] );
    return -1;
  }

  uint32_t ui_file_type = 0;
  uint32_t ui_file_no = 0;
  uint32_t ui_Major = 0;
  uint32_t ui_Sub = 0;
  uint32_t ui_Min = 0;
  uint32_t ui_Test = 0;

  if ( ( 1 == sscanf ( argv[2], "%x", &ui_file_type ) )
       && ( 1 == sscanf ( argv[3], "%x", &ui_file_no ) )
       && ( 4 == sscanf ( argv[4], "%x.%x.%x.%x", &ui_Major, &ui_Sub, &ui_Min, &ui_Test ) ) )
  {
  }
  else
  {
    fprintf ( stderr, "%s filename filetype fileno ver(1.2.3.4) outfilename   (all hex)!\n", argv[0] );
    return -2;
  }

  upgrade_file_header_t upgrade_file_header;
  memset ( reinterpret_cast<void*> ( &upgrade_file_header ), 0, sizeof ( upgrade_file_header_t ) );
  upgrade_file_header.magicNum  = UPGRADE_FILE_MAGIC_NUM;
  upgrade_file_header.fileType  = ui_file_type;
  upgrade_file_header.fileNo    = ui_file_no;
  upgrade_file_header.verMajor  = ui_Major;
  upgrade_file_header.verSub    = ui_Sub;
  upgrade_file_header.verMin    = ui_Min;
  upgrade_file_header.verTest   = ui_Test;

  return GenFile ( upgrade_file_header, argv[1], argv[5] );
}

int GenUpgradeFile::GenFile ( upgrade_file_header_t& upgrade_file_header, std::string infilename, std::string outfilename )
{
  if ( 0 != ReadInputFile ( infilename ) )
    return -3;

  m_vecharCompress.resize ( m_vechar.size() + 0x10000, 0 );

  unsigned long desLen = m_vecharCompress.size();
  unsigned long srcLen = m_vechar.size();

  if ( Z_OK != compress ( reinterpret_cast<uint8_t*> ( &m_vecharCompress[0] ), &desLen,
                          reinterpret_cast<uint8_t*> ( &m_vechar[0] ), srcLen ) )
    return -4;

  m_vecharCompress.resize ( desLen, 0 );

  upgrade_file_header.fileUnCompressSize = m_vechar.size();
  upgrade_file_header.fileCompressSize = m_vecharCompress.size();

  upgrade_file_header.fileCrc = CalcFileCrc ( &m_vecharCompress[0], m_vecharCompress.size() );

  upgrade_file_header.hearderChksum = CalcHeaderChkSum ( upgrade_file_header );

  std::ofstream ofs ( outfilename.c_str(), std::ofstream::binary );

  if ( !ofs )
    return -5;

  ofs.write ( reinterpret_cast<char*> ( &upgrade_file_header ), sizeof ( upgrade_file_header_t ) );
  ofs.write ( &m_vecharCompress[0], m_vecharCompress.size() );
  return 0;
}

int GenUpgradeFile::ReadInputFile ( std::string infile )
{
  m_vechar.clear();

  std::ifstream ifs ( infile.c_str(), std::ifstream::binary );

  if ( !ifs )
    return -1;

  ifs.seekg ( 0, ifs.end );
  int len = ifs.tellg();
  ifs.seekg ( 0, ifs.beg );

  m_vechar.resize ( len, 0 );

  ifs.read ( &m_vechar[0], m_vechar.size() );
  return 0;
}

uint32_t GenUpgradeFile::CalcHeaderChkSum ( upgrade_file_header_t& upgrade_file_header )
{
  uint32_t* p = reinterpret_cast<uint32_t*> ( &upgrade_file_header );
  uint32_t chksum = 0;

  for ( uint32_t i = 1; i < sizeof ( upgrade_file_header_t ) / sizeof ( int ); ++i )
    chksum += p[i];

  return chksum;
}

/* add -lz */
uint32_t GenUpgradeFile::CalcFileCrc ( char* buffer, int len )
{
  return crc32 ( 0, reinterpret_cast<uint8_t*> ( buffer ), len );
}


#ifdef TEST
/* filename filetype fileno ver("1.2.3.4") */
int main ( int argc, char* argv[] )
{
  GenUpgradeFile a;
  int ret = 0;

  if ( 0 != ( ret = a.GenFile ( argc, argv ) ) )
  {
    //printf ( "ret = %d \n", ret );
  }

  return 0;
}

#endif


