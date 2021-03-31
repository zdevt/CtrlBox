/*
 * =====================================================================================
 *
 *       Filename:  BmpHandle.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月05日 20时39分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <fstream>
#include <string.h>

#include "BmpHandle.h"

BmpHandle::BmpHandle()
{
}

BmpHandle::~BmpHandle()
{
}

bool BmpHandle::GetFile ( std::string filename, vechar_t& vechar )
{
  std::ifstream ifs ( filename.c_str(), std::ifstream::binary );

  if ( !ifs )
    return false;

  ifs.seekg ( 0, ifs.end );
  int len = ifs.tellg();
  ifs.seekg ( 0, ifs.beg );
  vechar.resize ( len, 0 );
  ifs.read ( &vechar[0], vechar.size() );

  return true;
}

void BmpHandle::PrintBmpFileHeader ( BmpFileHeader* p )
{
  fprintf ( stderr, "bType          = 0x%04x\n", p->bType );
  fprintf ( stderr, "bSize          = 0x%08x\n", p->bSize );
  fprintf ( stderr, "bReserved1     = 0x%04x\n", p->bReserved1 );
  fprintf ( stderr, "bReserved2     = 0x%04x\n", p->bReserved2 );
  fprintf ( stderr, "bOffset        = 0x%08x\n", p->bOffset );
}

void BmpHandle::PrintBmpInfo ( BmpInfo* p )
{
  fprintf ( stderr, "bInfoSize      = 0x%08x\n", p->bInfoSize );
  fprintf ( stderr, "bWidth         = 0x%08x\n", p->bWidth );
  fprintf ( stderr, "bHeight        = 0x%08x\n", p->bHeight );
  fprintf ( stderr, "bPlanes        = 0x%04x\n", p->bPlanes );
  fprintf ( stderr, "bBitCount      = 0x%04x\n", p->bBitCount );
  fprintf ( stderr, "bCompression   = 0x%08x\n", p->bCompression );
  fprintf ( stderr, "bmpImageSize   = 0x%08x\n", p->bmpImageSize );
  fprintf ( stderr, "bXPelsPerMeter = 0x%08x\n", p->bXPelsPerMeter );
  fprintf ( stderr, "bYPelsPerMeter = 0x%08x\n", p->bYPelsPerMeter );
  fprintf ( stderr, "bClrUsed       = 0x%08x\n", p->bClrUsed );
  fprintf ( stderr, "bClrImportant  = 0x%08x\n", p->bClrImportant );
}

bool BmpHandle::GenNewBmp ( vechar_t& input, vechar_t& output, int interval )
{
  BmpFileHeader*  pFileHeader = reinterpret_cast<BmpFileHeader*> ( &input[0] );
  BmpInfo*        pInfoHeader = reinterpret_cast<BmpInfo*> ( &input[0] + sizeof ( BmpFileHeader ) );
  char*    				pData = reinterpret_cast<char*> ( &input[0] + pFileHeader->bOffset );

  if ( pFileHeader->bType != 0x4d42 )
  {
    fprintf ( stderr, "bType = 0x%04x\n", pFileHeader->bType );
    return false;
  }

  vechar_t vecharTemp;
  uint32_t bmpBit = pInfoHeader->bBitCount;
  uint32_t bytesPerLine =   ( pInfoHeader->bWidth * bmpBit ) / 8  ;
  uint32_t totalBytesPerLine = ( ( bytesPerLine + 3 ) / 4 ) * 4;
  uint32_t totalLine = pInfoHeader->bHeight;
  uint32_t outputSize = bytesPerLine * totalLine;
  vecharTemp.resize ( outputSize, 0 );

  pInfoHeader->bWidth /= interval;
  uint32_t newbytesPerLine =   ( pInfoHeader->bWidth * bmpBit ) / 8  ;
  uint32_t newtotalBytesPerLine = ( ( newbytesPerLine + 3 ) / 4 ) * 4;

  pInfoHeader->bHeight /= interval;
  uint32_t newtotalLine = pInfoHeader->bHeight;

  uint32_t newoutputSize = newtotalBytesPerLine * newtotalLine;
  output.resize ( newoutputSize, 0 );

  pInfoHeader->bmpImageSize = output.size();
  pFileHeader->bSize = pInfoHeader->bmpImageSize  + pFileHeader->bOffset;

  for ( uint32_t i = 0; i < pInfoHeader->bHeight; ++i )
  {
    for ( uint32_t j = 0; j < pInfoHeader->bWidth; ++j )
      memcpy ( &output[0] + newtotalBytesPerLine * i + j * 3,
               pData + totalBytesPerLine * i * interval  + j * interval * 3, 3 );
  }

  std::ofstream ofs ( "out.bmp", std::ofstream::binary );
  ofs.write ( reinterpret_cast<char*> ( pFileHeader ), sizeof ( BmpFileHeader ) );
  ofs.write ( reinterpret_cast<char*> ( pInfoHeader ), pInfoHeader->bInfoSize );
  ofs.write ( &output[0], output.size() );
  ofs.close();

  return true;
}

#ifdef TEST
#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char* argv[] )
{
  vechar_t input, output;
  BmpHandle::GetFile ( argv[1], input );
  BmpHandle::GenNewBmp ( input, output, 7 );

  return 0;
}
#endif

