/*
 * =====================================================================================
 *
 *       Filename:  BmpHandle.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月05日 20时39分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  BMPHANDLE_INC
#define  BMPHANDLE_INC

#include <vector>
#include <map>
#include <string>
#include <stdint.h>

typedef std::vector<char> vechar_t;

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint16_t bType;              ///<  文件标识符
  uint32_t bSize;              ///<  文件的大小
  uint16_t bReserved1;         ///<  保留值,必须设置为0
  uint16_t bReserved2;         ///<  保留值,必须设置为0
  uint32_t bOffset;            ///<  文件头的最后到图像数据位开始的偏移量
} BmpFileHeader;

typedef struct
{
  uint32_t bInfoSize;          ///<  信息头的大小
  uint32_t bWidth;             ///<  图像的宽度
  uint32_t bHeight;            ///<  图像的高度
  uint16_t bPlanes;            ///<  图像的位面数
  uint16_t bBitCount;          ///<  每个像素的位数
  uint32_t bCompression;       ///<  压缩类型
  uint32_t bmpImageSize;       ///<  图像的大小,以字节为单位
  uint32_t bXPelsPerMeter;     ///<  水平分辨率
  uint32_t bYPelsPerMeter;     ///<  垂直分辨率
  uint32_t bClrUsed;           ///<  使用的色彩数
  uint32_t bClrImportant;      ///<  重要的颜色数
} BmpInfo;

typedef struct
{
  uint8_t g;
  uint8_t b;
  uint8_t r;
} BmpPixel24Bit_t;

typedef struct
{
  uint16_t pixel;
} BmpPixel16Bit_t;

#pragma pack(pop)

class BmpHandle
{
 private:
  BmpHandle();
  ~BmpHandle();

 public:
  static bool GetFile ( std::string filename, vechar_t& vechar );
  static bool GenNewBmp ( vechar_t& input, vechar_t& output, int interval );

  static void PrintBmpFileHeader ( BmpFileHeader* p );
  static void PrintBmpInfo ( BmpInfo* p );
};

#endif   /* ----- #ifndef BmpHandle.h ----- */

