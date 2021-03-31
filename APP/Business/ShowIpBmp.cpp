/*
 * =====================================================================================
 *
 *       Filename:  ShowIpBmp.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年09月20日 16时55分51秒
 *  Last Modified:  2015年09月20日 16时55分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <iomanip>
#include <sstream>

#include "ShowIpBmp.h"

#if defined(__arm__)
  #include "GetNetWork.h"
  #include "SoInterface.h"
  #include "XmlConfig.h"
#endif

#include <gd.h>
#include <gdfontl.h>

#if defined(__arm__)
  #include "OpticEngineInterface.h"
  #include "FpgaTestPic.h"
#endif

//#include <memory>
//std::shared_ptr<SoInterface> pSoInterface = std::make_shared<SoInterface> ( "/lib/libgd.so" );

ShowIpBmp::ShowIpBmp()
{

}

ShowIpBmp::~ShowIpBmp()
{

}

bool ShowIpBmp::On( )
{
  std::string ip, mask;
  GetNetWork::GetIp ( ip, mask );

  std::stringstream ss;
  unsigned int temp = 0;
  XmlConfig::GetParam ( "CubeWallConf", "ID", temp, 0u );
  ss << "SYSID=" << temp;

  XmlConfig::GetParam ( "CubeWallConf", "CUBEID", temp, 0u );
  ss << " CUBEID=" << std::setw ( 2 ) << ( temp >> 8 ) << std::setw ( 2 ) << ( temp & 0xff );

  std::vector<std::string> vecstr;
  vecstr.push_back ( ip );
  vecstr.push_back ( ss.str() );

  int width = 1920;
  int height = 1080;

  #if defined(__arm__)
  GET_ENGPTR->GetEngineRes ( width, height );
  #endif

  ShowIpBmp::GenIpBmp ( "/app/ipbmpshow.bmp",
                        width, height, 150, 100, vecstr, 0xff0000 );

  #if defined(__arm__)

  if ( ( 1920 == width ) && ( 1080 == height ) )
    FpgaTestPic::WriteBmpLogo ( "/app/ipbmpshow.bmp", FPGA_PIC_SXGA );
  else if ( ( 1400 == width ) && ( 1050 == height ) )
    FpgaTestPic::WriteBmpLogo ( "/app/ipbmpshow.bmp", FPGA_PIC_SXGA );
  else if ( ( 1024 == width ) && ( 768 == height ) )
    FpgaTestPic::WriteBmpLogo ( "/app/ipbmpshow.bmp", FPGA_PIC_XGA );

  fpga_reg_pic_pro_ctl_t fpga_reg_pic_pro_ctl;
  fpga_reg_pic_pro_ctl.data = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
  fpga_reg_pic_pro_ctl.logo_en = 1;
  FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, fpga_reg_pic_pro_ctl.data );
  FpgaSetReg ( FPGA_DESKTOP_REG, 0 );
  #endif

  return true;
}

bool ShowIpBmp::Off()
{
  #if defined(__arm__)

  //if ( FpgaImageSwitch::GetDeskTopIndex() == 0 )
  {
    fpga_reg_pic_pro_ctl_t fpga_reg_pic_pro_ctl;
    fpga_reg_pic_pro_ctl.data = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
    fpga_reg_pic_pro_ctl.logo_en = 0;
    FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, fpga_reg_pic_pro_ctl.data );
  }

  FpgaImageSwitch::SetDeskTopIndex ( FpgaImageSwitch::GetDeskTopIndex() );

  GET_ENGPTR->WriteLogo( ); /*  重新写logo,因为ip图占了logo图的内存空间，需要重写 */

  #endif
  return true;
}

void ShowIpBmp::FormatStr ( std::string str, std::vector<unsigned char>& vecharstr )
{
  vecharstr.clear();

  for ( auto ele : str )
  {
    if ( ele == '\n' )
      vecharstr.push_back ( 0 );
    else
      vecharstr.push_back ( ele );
  }

  vecharstr.push_back ( 0 );
}

bool ShowIpBmp::GenIpBmp ( std::string fileOut, int width, int height, int xpos, int ypos,
                           std::vector<std::string> vecstr, int textColor )
{
  gdImagePtr in, out;
  FILE* fp = NULL;

  in = gdImageCreateTrueColor ( 400, 300 );
  gdImageFilledRectangle ( in, 0, 0, 400, 300, gdTrueColor ( 255, 255, 255 ) );

  const int interal = 20;
  int i = 0;

  for ( auto ele : vecstr )
  {
    std::vector<unsigned char> vecharstr;
    FormatStr ( ele, vecharstr );
    gdImageString ( in, gdFontGetLarge(), xpos, ypos + ( i++ ) * interal, &vecharstr[0], textColor );
  }

  gdImageSetInterpolationMethod ( in, GD_HAMMING );
  out = gdImageScale ( in, width, height );

  fp = fopen ( fileOut.c_str(), "wb" );
  gdImageBmp ( out, fp, 10 );
  fclose ( fp );

  gdImageDestroy ( in );
  gdImageDestroy ( out );

  return true;
}

#ifdef TESTSHOWBMP
int main ( int argc, char* argv[] )
{
  std::string ip, mask, mac, gw;
  GetNetWork::GetIp ( ip, mask );
  GetNetWork::GetMac (  mac );
  GetNetWork::GetGateWay ( gw );

  std::vector<std::string> vecstr;
  vecstr.push_back ( ip );
  vecstr.push_back ( mask );
  vecstr.push_back ( mac );
  vecstr.push_back ( gw );

  ShowIpBmp::GenIpBmp ( "b.bmp", 1920, 1080, 150, 100,
                        vecstr, 0xff0000 );
  return 0;
}
#endif

