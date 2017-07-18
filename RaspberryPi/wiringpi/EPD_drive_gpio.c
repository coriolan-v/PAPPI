#include "EPD_drive_gpio.h"
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

/*********************************************


*********************************************/	
 void SPI_Write(unsigned char value)                                    
{     		
	int read_data;
	read_data = wiringPiSPIDataRW(0,&value,1);
    if(read_data < 0)
		perror("wiringPiSPIDataRW failed\r\n");	
}

/*********************************************


*********************************************/	
void driver_delay_xms(unsigned long xms)	
{	
	delay(xms);
}


