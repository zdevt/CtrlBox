/*
 * =====================================================================================
 *
 *       Filename:  DmdDdp3021Reg.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 11时48分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  DMDDDP3021REG_INC
#define  DMDDDP3021REG_INC

#define  DDP3021_SLAVE_ADDR                   0x34

#define  DDP3021_DUTY_CYCLE                   0xc
#define  DDP3021_BC_CONTROL                   0xd
#define  DDP3021_GAMMA_CORRECTION             0x9
#define  DDP3021_HARDWARE_VERSIONS            0x9B   ///<READ ONLY
#define  DDP3021_SOFTWARE_VERSIONS            0x9C   ///<READ ONLY

#define  DDP3021_PROJECTION_MODE              0x2
#define  DDP3021_IMAGE_FLIP_SUBADDR           0x3
#define  DDP3021_READ_SUBADDR                 0x15
/*  Normal:         0xc0  */
/*  BlankMode:      0x40 */
/*  TestMode:       0x20 */
/*  VideoCurtain:   0x00 */
/*  CustomPattern:  0xa0 */
/*  FreezeMode:     0x80 */


#define  DDP3021_IMAGE_MODE                   0x3
#define  DDP3021_COLOROFFSET_MODE             0x0

#define  DDP3021_ENGIN_CONTRAST               0x01
#define  DDP3021_ENGIN_BRIGHT                 0x0a

#define  DDP3021_FANPWM_CONTROL               0x10
#define  DDP3021_FANPWM_ENABLE                0x11
#define  DDP3021_HSG_CONFIGE                  0x13
#define  DDP3021_HSG_READ_LED                 0x16
#define  DDP3021_DMD_UNLOCK                   0x20

#define  DDP3021_TEST_PATTERN                 0x33

#define  DDP3021_VERTICAL_POSITION_LED        0x05   ///<调节垂直位置
#define  DDP3021_HORIZONTAL_POSITION_LED      0x04  ///<调节水平位置
#define  DDP3021_ENGINE_HARDWARE_VERSION      0x9B  ///<硬件版本号获取
#define  DDP3021_ENGINE_SOFTWARE_VERSION      0x9C  ///<DMD软件版本号获取


#define  DDP3021_DSP_DAC_WRITE                0x91  ///<写DAC
#define  DDP3021_DSP_DAC_READ                 0xB1  ///<读DAC

enum
{
  ColorRed =     0x00, ///< 红
  ColorGreen =   0x01, ///< 绿
  ColorBlue    = 0x02, ///< 蓝
  ColorCyan    = 0x03, ///< 青
  ColorMagenta = 0x04, ///< 紫
  ColorYellow  = 0x05, ///< 黄
  ColorWhite   = 0x06, ///< 白
  ColorMax     = 0x07,
};

#define  DAC_RED_STROBE         0x0000
#define  DAC_GREEN_STROBE       0x0001
#define  DAC_BLUE_STROBE        0x0002
#define  DAC_SUBFRAME1_STROBE   0x0003
#define  DAC_SUBFRAME2_STROBE   0x0004
#define  DAC_YELLOW_STROBE      0x0005
#define  DAC_CYAN_STROBE        0x0006
#define  DAC_MAGENTA_STROBE     0x0007
#define  DAC_WHITE_STROBE       0x0008
#define  DAC_BLACK_STROBE       0x0009

#define  DDP3021_DSP_RED_MEASURED_WRITE       0x00  ///<Measured RED x, y and Lumens Color Point
#define  DDP3021_DSP_GREEN_MEASURED_WRITE     0x01  ///<Measured GREEN x, y and Lumens Color Point
#define  DDP3021_DSP_BLUE_MEASURED_WRITE      0x02  ///<Measured BLUE x, y and Lumens Color Point

///<equest Measured x, y and Lumens Setting 0=red, 1=green,2=blue,3-7=reserved
#define  DDP3021_DSP_MEASURED_READ            0xA1

///<internal color sensor Measured GREEN x, y and Lumens Color Point. 0=red, 1=green,2=blue,3-7=reserved
#define  DDP3021_DSP_INTERNAL_COLOR_SENSOR_MEASURED_READ    0xA2

///<internal color sensor  Measurements. 0=red, 1=green,2=blue,3-7=reserved
#define  DDP3021_DSP_INTERNAL_COLOR_SENSOR_MEASURED_WRITE   0x17

///<Color Point Processing Control.
#define  DDP3021_DSP_COLOR_POINT_PROCESS_CONTROL_WRITE      0x87

///<De-saturation Mode Select,
#define  DDP3021_DSP_DESATURATION_MODE_SELECT_WRITE         0x27

///<set Set Desired x, y and Gain,0 = Red,1 = Green,2 = Blue,3 = Yellow,4 = Cyan,5 = Magen,6 = White,
#define  DDP3021_DSP_COLOR_DESIRED_WRITE                    0x1E

///<Request Desired x, y and Gain,0 = Red,1 = Green,2 = Blue,3 = Yellow,4 = Cyan,5 = Magen,6 = White,
#define  DDP3021_DSP_COLOR_DESIRED_READ                     0xCB

///<Read of DSP Status Register
#define  DDP3021_DSP_STATUS_READ                            0x43

///<Read of DRIVER board temperature
#define  DDP3021_DSP_DRIVERBOARD_TEMP_READ                  0xB7

#define  DDP3021_DSP_READ_FLAG                              0xDE  ///<Dsp Read  addr
#define  DDP3021_DSP_WRITE_FLAG                             0x5E  ///<Dsp Write  addr

#define  DDP3021_DSP_ALL_DIS                                0x0   ///<  DAC 模式
#define  DDP3021_DSP_WP_EN                                  0x01  ///<White Processing (Color Management System) Enable.
#define  DDP3021_DSP_CAL_EN                                 0x02  ///<Calibration Mode Enable.
#define  DDP3021_HSG_EN                                     0x03  ///<HSG MODE enable
#define  DDP3021_DRIVER_INFOR                               0xB3  ///<获取DRIVER信息


#endif   /* ----- #ifndef OpticEngineDdp3021Reg.h ----- */

