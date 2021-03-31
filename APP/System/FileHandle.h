/*
 * =====================================================================================
 *
 *       Filename:  FileHandle.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/29/2014 09:42:11 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */
#ifndef  FILEHANDLE_INC
#define  FILEHANDLE_INC

#include <vector>
#include <string>

class FileHandle
{
  private:
    FileHandle ( );
    ~FileHandle();

  public:
    static bool Create ( std::string filename );
    static bool Read ( std::string filename, std::vector<char>& vecharFile );
    static bool Write ( std::string filename, std::vector<char>& vecharFile );

    static bool WriteAppend ( std::string filename, std::vector<char>& vecharFile );
    static bool WriteAppend ( std::string filename, char* buffer, uint32_t bufferLen );

    /* ************************** */
    static bool ListFile ( std::string filefilter, std::vector<std::string>& vecstrFile );
};

#endif   /* ----- #ifndef UPGRADE_INC  ----- */

