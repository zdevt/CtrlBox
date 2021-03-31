/*
 * =====================================================================================
 *
 *       Filename:  DmdDdp442xReg.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 15时11分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  DMDDDP442XREG_INC
#define  DMDDDP442XREG_INC

#include <stdint.h>

#define DDP442X_I2C_SLAVE_ADDR   (0x34)
#define DDP442X_GET_REG_SUBADDR  (0x15)

#define DDP442X_SYSTEM_MODE_SUBADDR        (0x02)

#define DDP442X_THIN_LAMP_LIT_SUBADDR      (0x07)

#define DDP442X_IMAGE_FLIP_SUBADDR         (0x10)

#define DDP442X_TEST_PATTERN_SUBADDR       (0x11)

#define DDP442X_SOLID_FIELD_COLOR_SUBADDR  (0x13)

#define DDP442X_ALGORITHM_ENABLE_SUBADDR   (0x14)
typedef union
{
  struct
  {
    uint8_t degamma: 1; /*  0:disable; 1:enable; */
    uint8_t cca: 1;  /* Color coordinate adjust */
    uint8_t bc: 1;   /* Brilliant Color */
    uint8_t stm: 1; /* Spatial Temporal Multiplexing */
    uint8_t brightSync: 1;
  };
  uint8_t data;
} ddp442x_alg_enable_t;

#define DDP442X_BRIGHTNESS_SUBADDR         (0x16)

#define DDP442X_CONTRAST_SUBADDR           (0x17)

#define DDP442X_COLOR_BRIGHTNESS_SUBADDR   (0x1b)

#define DDP442X_HSG_ADJUST_SUBADDR         (0x1c)

#define DDP442X_BACKGROUND_DISPLAY_SUBADDR (0x1e)


#define DDP442X_DISPLAYOUTPUT_SUBADDR      (0x23)

#define DDP442X_COLOR_OFFSET_SUBADDR       (0x25)

#define DDP442X_CHANNEL_SOURCE_SUBADDR     (0x28)

#define DDP442X_3D_SUBADDR                 (0x61)
#define DDP442X_3D_ENABLE_SUBADDR          (0x61)

#define DDP442X_DMD_RESOLUTION_SUBADDR     (0x81)

#define DDP442X_COLOR_CONTRAST_SUBADDR     (0x90)

#define DDP442X_LED_TEMP_THIN_SUBADDR      (0x91)

#define DDP442X_CCA_TARGET                 (0x98)

#define DDP442X_WPC_TARGET                 (0xb2)
#define DDP442X_WPC_MODE                   (0xb4)

#define DDP442X_THIN_COORDINATE_SUBADDR    (0xba)

#define DDP442X_DRIVER_VERSION_SUBADDR     (0xc0)

#define DDP442X_RED_LED_DAC_SUBADDR        (0xc1)
#define DDP442X_GREEN_LED_DAC_SUBADDR      (0xc2)
#define DDP442X_BLUE_LED_DAC_SUBADDR       (0xc3)

#define DDP442X_INTERNAL_SENSOR_SUBADDR    (0xca)

#define DDP442X_LASER_CURRENT_SUBADDR              (0xce)
#define DDP442X_LASER_COLORWHEEL_DELAY_SUBADDR     (0x03)
#define DDP442X_LASER_DEFAULT_CURRENT_SUBADDR      (0xdc)
#define DDP442X_LASER_CURRENT_PROPORTION_SUBADDR   (0xdd)

#define DDP442X_FIRMWARE_VERSION_SUBADDR   (0xd0)

#define DDP442X_DUTYCYCLE_VALUE_SUBADDR    (0xd3)
#define DDP442X_DUTYCYCLE_SUBADDR          (0xd4)

#define DDP442X_CALIBRATION_ENABLE_SUBADDR (0xd6)

#define DDP442X_LED_STATUS_SUBADDR         (0xda)
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uint8_t dT; /*  driver Temp */
  uint8_t rT; /*  r Temp  */
  uint8_t gT;
  uint8_t bT;

  uint8_t rV; /*  r voltage */
  uint8_t rC; /*  r current */
  uint8_t gV;
  uint8_t gC;
  uint8_t bV;
  uint8_t bC;
} ddp442x_led_status_t;
#pragma pack(pop)

#define DDP442X_LASER_DRIVER_TEMP_SUBADDR          (0xe9)

#define DDP442X_DMD_FAN_PWM_SUBADDR        (0xea)

#define DDP442X_DMD_FAN_SPEED_SUBADDR      (0xec)

#define DDP442X_DMD_TEMP_SUBADDR           (0xed)
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  int32_t r;
  int32_t g;
  int32_t b;
} ddp442x_led_temp_thin_t;
#pragma pack(pop)

#define DDP442X_GAMMA_TABLE_SUBADDR        (0xf3)


#define ALGORITHM_ENABLE_GAMMA          (1<<0)
#define ALGORITHM_ENABLE_CCA            (1<<1)
#define ALGORITHM_ENABLE_BC             (1<<2)
#define ALGORITHM_ENABLE_STM            (1<<3)
#define ALGORITHM_ENABLE_BRIGHTSYNC     (1<<4)

#define CALIBRATION_DISABLE             (0)
#define CALIBRATION_ENABLE              (1)

#define BACKGROUND_DISPLAY_ENABLE       (0)
#define BACKGROUND_DISPLAY_DISABLE      (1)

#define DISABLE_3D                      (0)
#define ENABLE_3D                       (1)

/* dmd升级命令 */
#define DDP442X_UPGRADE_UNLOCK_SUBADDR             (0x20)
#define DDP442X_UPGRADE_FLASH_QUERY_SUBADDR        (0x23)
#define DDP442X_UPGRADE_FLASH_INFO_SUBADDR         (0x15)
#define DDP442X_UPGRADE_FLASH_TYPE_SUBADDR         (0x2f)
#define DDP442X_UPGRADE_FLASH_STARTADDR_SUBADDR    (0x29)
#define DDP442X_UPGRADE_FLASH_ERASE_SUBADDR        (0x28)
#define DDP442X_UPGRADE_FLASH_DATALEN_SUBADDR      (0x2c)
#define DDP442X_UPGRADE_FLASH_WRITE_SUBADDR        (0x25)
#define DDP442X_UPGRADE_FLASH_CHECKSUM_SUBADDR     (0x26)
#define DDP442X_UPGRADE_PROGRAME_SUBADDR           (0x30)

/* add sipmle new engine cmd */
#define DDP442X_SIP_P2W_OPEN               (0x84)
#define DDP442X_SIP_P2W_SHARPNESS          (0x98)
#define DDP442X_SIP_P2W_PROJ_MODE          (0xe9)
#define DDP442X_SIP_P2W_SIG_SHOW           (0xea)
#define DDP442X_SIP_P2W_HIGHLAND_MODE      (0xeb)
#define DDP442X_SIP_P2W_TEST_PIC           (0xec)
#define DDP442X_SIP_P2W_REMOTE_CONTROL     (0xee)
#define DDP442X_SIP_P2W_HSG                (0x1c)
#define DDP442X_SIP_P2W_AdjuestRgbCurrent  (0xf4)
#define DDP442X_SIP_P2W_OPEN_METHOD        (0xf5)
#define DDP442X_SIP_P2W_RESET_ADJUST       (0xf6)
#define DDP442X_SIP_P2W_OVERLAP            (0xf7)
#define DDP442X_SIP_P2W_TEMPERATURE         (0xf8)

/* add sipmle new engine cmd end */

#endif   /* ----- #ifndef DmdDdp442xReg.h ----- */

