/*
 * =====================================================================================
 *
 *       Filename:  SpiBusInterface.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/08/2015 01:32:25 AM EST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *        Company:
 *
 * =====================================================================================
 */

#ifndef  SPIBUSINTERFACE_INC
#define  SPIBUSINTERFACE_INC

#include <stdint.h>
#include <string>
#include <vector>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_BUS_10_NAME      "/dev/spidev1.0"
#define SPI_BUS_20_NAME      "/dev/spidev2.0"

#define SPI_PACK_LEN         (4096)

#define SPI_RW(a,b,c,d)      SpiBusInterface::RW(a,b,c,d)
#define SPI_RWN(a,b,c,d,e)   SpiBusInterface::RWN(a,b,c,d,e)

class SpiBusInterface
{
  private:
    SpiBusInterface ( );
    ~SpiBusInterface();

  public:
    static int RW ( uint8_t* pW, uint8_t* pR, int len, std::string devname = SPI_BUS_10_NAME );
    static int RWN ( uint8_t* pW, uint8_t* pR, int len, int packLen = SPI_PACK_LEN, std::string devname = SPI_BUS_20_NAME );
};

#endif   /* ----- #ifndef SPIBUSINTERFACE_INC ----- */


