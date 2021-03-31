#include "AesEncDec.h"

#include <string.h>
#include <fstream>
#include <iostream>

AesEncDec::AesEncDec ( void )
{
  _SetKey ( DEFAULT_PASSWD );
}

AesEncDec::AesEncDec ( std::string& passwd )
{
  _SetKey ( passwd.c_str() );
}

AesEncDec::AesEncDec ( const char* passwd )
{
  _SetKey ( passwd );
}


AesEncDec::~AesEncDec ( void )
{

}

/*密码不超过32字节，超过只取前面32个 */
int AesEncDec::_SetKey ( const char* key )
{
  memset ( ( char* ) m_key, 0, KEY_BUFFER_LEN );
  strncpy ( ( char* ) m_key, key, PASSWD_MAX_LEN );

  /* 对密码进行sha加密生成256bit密钥 */
  sha256_starts ( &m_sha_ctx );
  sha256_update ( &m_sha_ctx, m_key, KEY_BUFFER_LEN );
  sha256_finish ( &m_sha_ctx, m_key );

  aes_set_key ( &m_aes_ctx, m_key, DEFAULT_KEY_BITS );
  return 0;
}

void AesEncDec::_Encrypt ( uint8 input[16], uint8 output[16] )
{
  aes_encrypt ( &m_aes_ctx, input, output );
}

void AesEncDec::_Decrypt ( uint8 input[16], uint8 output[16] )
{
  aes_decrypt ( &m_aes_ctx, input, output );
}

/* 长度不能被16整除的部分不加密 */
void AesEncDec::Encrypt ( uint8* input, uint8* output, int len )
{
  memcpy ( output, input, len );

  for ( int i = 0; i < len / ENCDEC_BLOCK_BYTES; ++i )
    _Encrypt ( input + i * ENCDEC_BLOCK_BYTES, output + i * ENCDEC_BLOCK_BYTES );
}

/* 长度不能被16整除的部分不解密 */
void AesEncDec::Decrypt ( uint8* input, uint8* output, int len )
{
  memcpy ( output, input, len );

  for ( int i = 0; i < len / ENCDEC_BLOCK_BYTES; ++i )
    _Decrypt ( input + i * ENCDEC_BLOCK_BYTES, output + i * ENCDEC_BLOCK_BYTES );
}

int AesEncDec::EncryptDecryptFile ( const char* input, const char* output, int flag )
{
  int fileLen = 0;
  std::ifstream ifs ( input, std::ifstream::binary );

  if ( !ifs )
    return -1;

  ifs.seekg ( 0, ifs.end );
  fileLen = ifs.tellg();
  ifs.seekg ( 0, ifs.beg );

  std::ofstream ofs ( output, std::ofstream::binary );

  if ( !ofs )
    return -1;

  unsigned char* buffer = new unsigned char[fileLen];
  ifs.read ( ( char* ) buffer, fileLen );

  if ( AES_ENCRYPT == flag )
    Encrypt ( buffer, buffer, fileLen );
  else
    Decrypt ( buffer, buffer, fileLen );

  ofs.write ( ( char* ) buffer, fileLen );

  delete[] buffer;

  return 0;
}

int AesEncDec::EncryptFile ( const char* input, const char* output )
{
  return EncryptDecryptFile ( input, output, AES_ENCRYPT );
}

int AesEncDec::DecryptFile ( const char* input, const char* output )
{
  return EncryptDecryptFile ( input, output, AES_DECRYPT );
}


