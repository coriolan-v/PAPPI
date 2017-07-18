#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <time.h>  

#include "EPD_drive.h"
#include "EPD_drive_gpio.h"
#include "Display_Lib.h"		//Show library, picture, number of hexadecimal

void SPI_GPIO_config(void)
{
	//1.wiringPiSetupGpio
	//if(wiringPiSetup() < 0)//use wiringpi Pin number table
	if(wiringPiSetupGpio() < 0)//use BCM2835 Pin number table
	{   
	  printf(" set wiringPi lib failed	!!! \r\n");
	}else{
	  printf(" set wiringPi lib success  !!! \r\n");
	}
	//2.GPIO config
	pinMode(RST,OUTPUT);
	pinMode(DC,OUTPUT);
	pinMode(BUSY,INPUT);
	pinMode(CS,OUTPUT);	//must set cs output,Otherwise it does not work
	
	//3.spi init
	wiringPiSPISetup(0,2000000);
	
	EPD_RST_1;
	driver_delay_xms(10);	
	EPD_RST_0;	
	driver_delay_xms(10);	
	EPD_RST_1;
	
}

int main(void)
{
	time_t now; 
	struct tm *timenow;
	unsigned int now_sec,next_sec = 11;//Guaranteed next greater than 9
	//1.SPI Initialization Based on BCM2835 Librar
	SPI_GPIO_config();
	
	//2.show
	//init and Clear full screen
	printf("--------------init and Clear full screen--------------\r\n");
	Dis_Clear_full();
	
	//Show full pic
	printf("--------------Show full pic--------------\r\n");
	Dis_full_pic((unsigned char *)waveshare);
	driver_delay_xms(DELAYTIME);
	
	//init and Clear part screen
	printf("--------------init and Clear part screen--------------\r\n");
	Dis_Clear_part();

	//Show part pic
	printf("--------------Show part pic--------------\r\n");
	Dis_part_pic(0,xDot-1,0,yDot-1,(unsigned char *)waveshare); //pic
	driver_delay_xms(DELAYTIME);

	//Show Circle and Line 
	printf("--------------Show Circle and Line--------------\r\n");
	Dis_Drawing((yDot-32)/8,5,(unsigned char *)Circle3232,32,32); //Circle
	Dis_Drawing((yDot-32)/8,0,(unsigned char *)Line3232,32,32); //Line
	driver_delay_xms(DELAYTIME);

	//Show string
	printf("--------------Show string--------------\r\n");
 	Dis_String(0, 10, "SHOW TIME :",16);
	Dis_String(0, 26, "I am an electronic paper display",12);
	driver_delay_xms(DELAYTIME);

	//Progress
	printf("--------------Show Progress--------------\r\n");
	Dis_Progress(9);	
	driver_delay_xms(DELAYTIME);

	//show time
	printf("--------------show time--------------\r\n");
	while(1)
	{
		time(&now);		
		timenow = localtime(&now);
		now_sec = timenow->tm_sec%10;
		if(now_sec != next_sec){
			Dis_showtime(timenow->tm_hour,timenow->tm_min,timenow->tm_sec);
			next_sec = timenow->tm_sec%10;
		}
	}
	return 0;
	
}

