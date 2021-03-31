/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageLogoAndDrgb.cpp
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

#include "FpgaImageLogoAndDrgb.h"
#include "LogPrint.h"
#include "OpticEngineInterface.h"

std::shared_ptr<FpgaImageHandle> FpgaImageLogoAndDrgb::GetObj ( )
{
  return std::make_shared<FpgaImageLogoAndDrgb> ( );
}

FpgaImageLogoAndDrgb::FpgaImageLogoAndDrgb()
{

}

FpgaImageLogoAndDrgb::~FpgaImageLogoAndDrgb()
{

}

bool FpgaImageLogoAndDrgb::Handle ( int index )
{
  /*  manual desk swicth */
  fpga_reg_desktop_sel_t fpga_reg_desktop_sel;
  fpga_reg_desktop_sel.data = FpgaGetReg ( FPGA_DESKTOP_SEL );

  if ( index == 0 )
    fpga_reg_desktop_sel.dvi_sel = 0x0; /*  dvi1 */
  else if ( index == 0xf )
    fpga_reg_desktop_sel.dvi_sel = 0x2; /*  dvi2 */
  else
    fpga_reg_desktop_sel.dvi_sel = 0x0; /*  dvi1 */

  FpgaSetReg ( FPGA_DESKTOP_SEL, fpga_reg_desktop_sel.data );

  fpga_reg_pic_pro_ctl_t fpga_reg_pic_pro_ctl;
  fpga_reg_pic_pro_ctl.data = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
  fpga_reg_pic_pro_ctl.sig_loss_mode = 0;
  FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, fpga_reg_pic_pro_ctl.data );

  /*  重写一次logo图 防止不知道 图片是1bit还是24bit */
  //GET_ENGPTR->WriteLogo( );

  FpgaSetReg ( FPGA_DESKTOP_REG, 0 );

  GET_MBPTR->CheckSignalAndShow( );

  return true;
}

void FpgaImageLogoAndDrgb::SetDoubleDesktopSwithMode ( int mode )
{
  fpga_reg_pic_pro_ctl_t fpga_reg_pic_pro_ctl;
  fpga_reg_pic_pro_ctl.data = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
  fpga_reg_pic_pro_ctl.auto_desk = ( mode & 0x3 );
  FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, fpga_reg_pic_pro_ctl.data );
}

