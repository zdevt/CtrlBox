/*
 * =====================================================================================
 *
 *       Filename:  FpgaTestPic.h
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
#ifndef  FPGATESTPIC_INC
#define  FPGATESTPIC_INC

#include <vector>
#include <map>
#include <string>
#include <stdint.h>

typedef std::vector<char> vechar_t;

#define FPGA_TEST_PIC_0_COLOR  (0x000000)
#define FPGA_TEST_PIC_1_COLOR  (0xffffff)

#pragma pack(push)
#pragma pack(1)
typedef struct
{
  std::string name;
  uint32_t CpuAddr;
  uint32_t FpgaAddr;
  uint32_t ExAddr;
} display_ctrl_ddr_addr_t;

#pragma pack(pop)

#define FPGA_LOGO_NAME          "/app/logo_FILENO.bmp"
#define FPGA_TEST_PIC_NAME      "/app/test_pic_FILENO.bmp"
#define FPGA_USER_DEF_DSK_NAME  "/app/user_def_FILENO.bmp"

enum
{
  FPGA_PIC_SXGA   = 8,
  FPGA_PIC_XGA    = 9,
  FPGA_LBC        = 13,
  FPGA_TEST_PIC   = 14,

  USER_DEF_DSK0   = 15,
  USER_DEF_DSK1   = 16,
  USER_DEF_DSK2   = 17,
  USER_DEF_DSK3   = 18,
  USER_DEF_DSK4   = 19,
  USER_DEF_DSK5   = 20,
};

typedef std::map<int, display_ctrl_ddr_addr_t> mapiDispDdrAddr_t;
typedef std::map<uint32_t, uint32_t> mapFpgaEcp3DdrAddr_t;

class FpgaTestPic
{
  private:
    FpgaTestPic();
    ~FpgaTestPic();

  public:
    static bool WriteBmpLogo ( std::string filename, int addr );
    static bool WriteBmpTestPic ( std::string filename, int addr );
    static bool WriteBmpUserDef ( std::string filename, int picNo );

  public:
    static bool WriteBmpFileToFpga ( std::string filename, int addr );
    static bool WriteBmpFileToFpgaEcp3 ( std::string filename, int addr );

  private:
    static mapiDispDdrAddr_t m_mapiDispDdrAddr;
    static mapFpgaEcp3DdrAddr_t m_mapFpgaEcp3DdrAddr;
    static std::map<int, int> m_mapDeskIndex;
};

#endif   /* ----- #ifndef FpgaTestPic.h ----- */

