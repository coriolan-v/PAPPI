#ifndef _EPD_DRIVE_GPIO_H_
#define _EPD_DRIVE_GPIO_H_

/**************-------------------------------------------**************
							Hardware interface
**************-------------------------------------------**************/
#include <bcm2835.h>

//GPIO config
#define RST 17
#define DC  25
#define BUSY 24

#define EPD_DC_1 bcm2835_gpio_write(DC,HIGH)
#define EPD_DC_0 bcm2835_gpio_write(DC,LOW)
#define isEPD_DC bcm2835_gpio_lev(DC)

#define EPD_RST_0 bcm2835_gpio_write(RST,LOW)
#define EPD_RST_1 bcm2835_gpio_write(RST,HIGH)
#define isEPD_RST bcm2835_gpio_lev(RST)

#define EPD_BUSY_LEVEL 0
#define isEPD_BUSY  bcm2835_gpio_lev(BUSY)

extern void SPI_Write(unsigned char value);
extern void driver_delay_xms(unsigned long xms);

#endif
