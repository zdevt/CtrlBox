
#ifndef  AESENCDEC_INC
#define  AESENCDEC_INC

#include <string>

#include "aes.h"
#include "sha256.h"


#define DEFAULT_PASSWD      "AesEncDec"
#define PASSWD_MAX_LEN      (32)

#define DEFAULT_KEY_BITS    (256)
#define KEY_BUFFER_LEN      (32)

#define ENCDEC_BLOCK_BYTES  (16)

#define AES_ENCRYPT         (1)
#define AES_DECRYPT         (2)


class AesEncDec
{
  public:
    AesEncDec ( void );
    AesEncDec ( const char* passwd );
    AesEncDec ( std::string& passwd );
    ~AesEncDec ( void );

  public:
    void Encrypt ( uint8* input, uint8* output, int len );
    void Decrypt ( uint8* input, uint8* output, int len );

    int EncryptFile ( const char* input, const char* output );
    int DecryptFile ( const char* input, const char* output );

  private:
    int EncryptDecryptFile ( const char* input, const char* output, int flag );
    void _Encrypt ( uint8 input[16], uint8 output[16] );
    void _Decrypt ( uint8 input[16], uint8 output[16] );
    int _SetKey ( const char* key );

  private:
    aes_context m_aes_ctx;
    sha256_context m_sha_ctx;
    uint8 m_key[KEY_BUFFER_LEN];
};

#endif
