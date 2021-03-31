/*
 * =====================================================================================
 *
 *       Filename:  ShowIpBmp.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月20日 16时55分59秒
 *  Last Modified:  2015年09月20日 16时55分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef SHOWIPBMP_INC
#define SHOWIPBMP_INC

#include <string>
#include <vector>

class ShowIpBmp
{
  private:
    ShowIpBmp();
    ~ShowIpBmp();

  public:
    static bool On( );
    static bool Off();

    static bool GenIpBmp ( std::string fileOut, int width, int height, int xpos, int ypos,
                           std::vector<std::string> vecstr, int color );

    static void FormatStr ( std::string str, std::vector<unsigned char>& vecharstr );
};

#endif   /* ----- #ifndef ShowIpBmp.h ----- */

