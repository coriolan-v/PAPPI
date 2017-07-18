#include "EPD_drive_gpio.h"
#include <bcm2835.h>

/**************-------------------------------------------**************
							Interface layer
**************-------------------------------------------**************/
 void SPI_Write(unsigned char value)                                    
{     		
	bcm2835_spi_transfer(value);
}

void driver_delay_xms(unsigned long xms)	
{	
	bcm2835_delay(xms);
}


