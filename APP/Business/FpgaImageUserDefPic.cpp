/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageUserDefPic.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月21日 14时36分05秒
 *  Last Modified:  2015年09月21日 14时36分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <string>

#include "FpgaImageUserDefPic.h"
#include "FileHandle.h"

std::shared_ptr<FpgaImageHandle> FpgaImageUserDefPic::GetObj ( )
{
  return std::make_shared<FpgaImageUserDefPic> ( );
}

FpgaImageUserDefPic::FpgaImageUserDefPic()
{

}

FpgaImageUserDefPic::~FpgaImageUserDefPic()
{

}

bool FpgaImageUserDefPic::Handle ( int index )
{
  FpgaSetReg ( FPGA_DESKTOP_REG, 0x10 );

  /*  USERDEF PIC INDEX  */
  FpgaSetReg ( FPGA_USERDEF_SEL, index - FPGAIMAGE_USERDEF_STRAT_INDEX );

  /*  SYNC  */
  fpga_reg_win_flush_t fpga_reg_win_flush;
  fpga_reg_win_flush.data = FpgaGetReg ( FPGA_REG_WIN_FLUSH );
  fpga_reg_win_flush.update_user_def = 1;
  FpgaSetReg ( FPGA_REG_WIN_FLUSH, fpga_reg_win_flush.data );
  fpga_reg_win_flush.update_user_def = 0;
  FpgaSetReg ( FPGA_REG_WIN_FLUSH, fpga_reg_win_flush.data );

  return true;
}

void FpgaImageUserDefPic::GetBgpNum ( std::vector<uint32_t>& vecuintbgpNum )
{
  std::vector<std::string> vecstrFile;

  FileHandle::ListFile ( "/app/user_def_*.bmp | cut -d \".\" -f 1 | cut -d \"_\" -f 3", vecstrFile );

  vecuintbgpNum.clear();
  vecuintbgpNum.push_back ( ( uint32_t ) ( vecstrFile.size() ) );

  for ( auto ele : vecstrFile )
  {
    uint32_t val = 0;
    std::stringstream ss ( ele );
    ss >> val ;
    vecuintbgpNum.push_back ( val );
  }
}

