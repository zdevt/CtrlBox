/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageSwitch.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 22时40分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "FpgaImageSwitch.h"

#include "XmlConfig.h"

#include "FpgaImageLogoAndDrgb.h"
#include "FpgaImageTestPic.h"
#include "FpgaImageUserDefPic.h"
#include "FpgaImageFpga.h"

mapGetFpgaImageHandleObj_t FpgaImageSwitch::m_mapGetFpgaImageHandleObj =
{
  { FPGAIMAGE_LOGO_INDEX, 							FpgaImageLogoAndDrgb::GetObj },
  { FPGAIMAGE_LOGO_INDEX_BACK, 					FpgaImageLogoAndDrgb::GetObj },
  { FPGAIMAGE_TESTPIC_INDEX, 						FpgaImageTestPic::GetObj },
  { FPGAIMAGE_USERDEF_STRAT_INDEX, 			FpgaImageUserDefPic::GetObj },
  { FPGAIMAGE_USERDEF_STRAT_INDEX + 1, 	FpgaImageUserDefPic::GetObj },
  { FPGAIMAGE_USERDEF_STRAT_INDEX + 2, 	FpgaImageUserDefPic::GetObj },
  { FPGAIMAGE_USERDEF_STRAT_INDEX + 3, 	FpgaImageUserDefPic::GetObj },
  { FPGAIMAGE_USERDEF_STRAT_INDEX + 4, 	FpgaImageUserDefPic::GetObj },
  { FPGAIMAGE_USERDEF_STRAT_INDEX + 5, 	FpgaImageUserDefPic::GetObj },

};

FpgaImageSwitch::FpgaImageSwitch()
{

}

FpgaImageSwitch::~FpgaImageSwitch()
{

}

std::shared_ptr<FpgaImageHandle> FpgaImageSwitch::GetObj ( int index )
{
  auto iter = m_mapGetFpgaImageHandleObj.find ( index );

  if ( iter != m_mapGetFpgaImageHandleObj.end() )
    return ( iter->second ) ( );

  return FpgaImageFpga::GetObj ( );
}

bool FpgaImageSwitch::SetDeskTopIndex ( uint32_t index )
{
  XmlConfig::SetParam ( "DeskTopConf", "DeskTopIndex", index );
  return GetObj ( index )->Handle ( index );
}

int FpgaImageSwitch::GetDeskTopIndex ( )
{
  int desktopIndex = 0;
  XmlConfig::GetParam ( "DeskTopConf", "DeskTopIndex", desktopIndex, 0 );
  return desktopIndex;
}

