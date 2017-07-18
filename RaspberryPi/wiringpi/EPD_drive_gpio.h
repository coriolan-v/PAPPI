#ifndef _EPD_DRIVE_GPIO_H_
#define _EPD_DRIVE_GPIO_H_

/********************------------------------------------------------------------

Hardware interface

------------------------------------------------------------------------------*/
#include <wiringPi.h>

//GPIO config
#define RST 17
#define DC  25
#define BUSY 24
#define CS 8	//CE0

#define EPD_RST_0	digitalWrite(RST,LOW)
#define EPD_RST_1	digitalWrite(RST,HIGH)
#define isEPD_RST  digitalRead(RST)

#define EPD_DC_1	digitalWrite(DC,HIGH)
#define EPD_DC_0	digitalWrite(DC,LOW)
#define isEPD_DC  digitalRead(DC)

#define EPD_BUSY_LEVEL 0
#define isEPD_BUSY  digitalRead(BUSY)


void SPI_Write(unsigned char value);
void driver_delay_xms(unsigned long xms);

#endif
