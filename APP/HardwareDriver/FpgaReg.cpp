/*
 * =====================================================================================
 *
 *       Filename:  FpgaReg.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月06日 00时54分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "FpgaReg.h"
#include "FpgaDev.h"


void FPGAConfigDdrLockReg ( unsigned short val )
{
  FpgaSetReg ( FPGA_DDR_LOCKE, val );
}

void FPGAArmWriteContol ( unsigned char Enable )
{
  if ( Enable )
    FpgaSetReg ( FPGA_REG_ARMWR_BE, 0x03 );
  else
    FpgaSetReg ( FPGA_REG_ARMWR_BE, 0x00 );
}

void FPGASetDDR2WriteOnOff ( unsigned short onOff )
{
  unsigned short val;
  val = FpgaGetReg ( FPGA_REG_DDR2_EX_ADDR );

  if ( onOff == 1 )
    val |= 0x8;
  else
    val &= 0xfff3;

  FpgaSetReg ( FPGA_REG_DDR2_EX_ADDR, val );
}

void FPGASetDDR2ExtendAddress ( unsigned short exAddr )
{
  unsigned short val;
  val = FpgaGetReg ( FPGA_REG_DDR2_EX_ADDR );

  exAddr &= 0x0033;
  val &= 0xffcc;
  val = val | exAddr;

  FpgaSetReg ( FPGA_REG_DDR2_EX_ADDR, val );
}

void FPGASetColorTypeRegister ( unsigned short val )
{
  FpgaSetReg ( FPGA_REG_PIC_TYPE, val ); //default is 0x0
}

void FPGADisableLBCControl()
{
  uint16_t old = 0;
  old = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
  old &= ( ~ ( 0x0020 ) );
  FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, old );
}

void LBCFPGASetDDR2ExtendAddress ( uint16_t exAddr )
{
  exAddr &= 0x0003;
  FpgaSetReg ( FPGA_REG_DDR2_EX_ADDR, exAddr );
}

void FPGAEnablePictureProcessControl ( uint16_t val )
{
  uint16_t old = 0;
  old = FpgaGetReg ( FPGA_REG_PIC_PRO_CTL );
  old |= val;
  FpgaSetReg ( FPGA_REG_PIC_PRO_CTL, old );
}


