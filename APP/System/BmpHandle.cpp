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

#include <string.h>
#include <fstream>

#include "BmpHandle.h"

BmpHandle::BmpHandle()
{
}

BmpHandle::~BmpHandle()
{
}

bool BmpHandle::GetBmp ( std::string filename, BmpFileHeader& bmpHeader, BmpInfo& bmpInfo, vechar_t& vecBmpdata )
{
  std::ifstream ifs ( filename.c_str(), std::ifstream::binary );

  if ( !ifs )
    return false;

  ifs.read ( reinterpret_cast<char*> ( &bmpHeader ), sizeof ( bmpHeader ) );
  ifs.read ( reinterpret_cast<char*> ( &bmpInfo ), sizeof ( bmpInfo ) );

  uint32_t bytesPerLine =   ( bmpInfo.bWidth * bmpInfo.bBitCount ) / 8  ;
  uint32_t totalBytesPerLine = ( ( bytesPerLine + 3 ) / 4 ) * 4;
  uint32_t totalLine = bmpInfo.bHeight;
  uint32_t imgDataOffset = bmpHeader.bOffset;

  vecBmpdata.resize ( totalLine * bytesPerLine, 0 );

  for ( uint32_t j = 0; j < totalLine; ++j )
  {
    #if 1
    ifs.seekg ( imgDataOffset + ( totalLine - 1 - j ) * totalBytesPerLine, ifs.beg );
    #else
    ifs.seekg ( imgDataOffset + j * totalBytesPerLine, ifs.beg );
    #endif
    ifs.read ( &vecBmpdata[0] + bytesPerLine * j, bytesPerLine );
  }

  ifs.close();

  return true;
}

bool BmpHandle::GetBmpHeader ( std::string filename, BmpFileHeader& bmpHeader )
{
  std::ifstream ifs ( filename.c_str(), std::ifstream::binary );

  if ( !ifs )
    return false;

  ifs.read ( reinterpret_cast<char*> ( &bmpHeader ), sizeof ( bmpHeader ) );
  ifs.close();

  return true;
}

bool BmpHandle::GetBmpInfo ( std::string filename, BmpInfo& bmpInfo )
{
  std::ifstream ifs ( filename.c_str(), std::ifstream::binary );

  if ( !ifs )
    return false;

  ifs.seekg ( sizeof ( BmpFileHeader ), ifs.beg );
  ifs.read ( reinterpret_cast<char*> ( &bmpInfo ), sizeof ( bmpInfo ) );
  ifs.close();

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

#if 0
bool BmpHandle::Scale ( std::string fileIn, std::string fileOut, int width, int height )
{
  gdImagePtr in, out;
  FILE* fp = NULL;

  fp = fopen ( fileIn.c_str(), "rb" );
  in = gdImageCreateFromBmp ( fp );
  fclose ( fp );

  gdImageSetInterpolationMethod ( in, GD_HAMMING );
  out = gdImageScale ( in, width, height );

  fp = fopen ( fileOut.c_str(), "wb" );
  gdImageBmp ( out, fp, 100 );
  fclose ( fp );

  gdImageDestroy ( in );
  gdImageDestroy ( out );
  return true;
}

bool BmpHandle::String ( std::string file, int x, int y, std::string str, int color )
{
  gdImagePtr in;
  FILE* fp = NULL;

  fp = fopen ( file.c_str(), "rb" );
  in = gdImageCreateFromBmp ( fp );
  fclose ( fp );

  std::vector<unsigned char> vecharstr;

  for ( auto ele : str )
  {
    if ( ele == '\n' )
      vecharstr.push_back ( 0 );
    else
      vecharstr.push_back ( ele );
  }

  vecharstr.push_back ( 0 );

  gdImageString ( in, gdFontGetLarge(), x, y, &vecharstr[0],
                  gdImageColorAllocate ( in, 255, 0, 0 ) );

  fp = fopen ( file.c_str(), "wb" );
  gdImageBmp ( in, fp, 100 );
  fclose ( fp );

  gdImageDestroy ( in );
  return true;
}
#endif

