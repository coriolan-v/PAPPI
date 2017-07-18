#include <bcm2835.h>

#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <time.h>  

#include "EPD_drive.h"
#include "EPD_drive_gpio.h"
#include "Display_Lib.h"		//Show library, picture, number of hexadecimal

void SPI_GPIO_config(void)
{
	bcm2835_gpio_fsel(RST,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(DC,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(BUSY,BCM2835_GPIO_FSEL_OUTP);
	
	bcm2835_spi_begin(); 										 //Start spi interface, set spi pin for the reuse function
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     //High first transmission
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                  //spi mode 0  
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);  //Frequency
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                     //set CE0
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);     //enable cs0
}

int main(void)
{
	time_t now; 
	struct tm *timenow;
	unsigned int now_sec,next_sec = 11;//Guaranteed next greater than 9
	if(!bcm2835_init()){	
		printf("bcm2835_init set failed  !!! \r\n");
		exit(0);
	}else{
		printf("bcm2835 init success  !!! \r\n");
	}
	//1.SPI Initialization Based on BCM2835 Librar
	SPI_GPIO_config();
	
	//2.show
	//Clear full screen
	printf("------------Clear full screen-----------------\r\n");
	Dis_Clear_full();
	
	//Show full pic
	printf("------------Show full pic-----------------\r\n");
	Dis_full_pic((unsigned char *)waveshare);
	driver_delay_xms(DELAYTIME);
	
	//Clear part screen
	printf("--------------Clear part screen------------\r\n");
	Dis_Clear_part();

	//Show part pic
	printf("--------------Show part pic-------------\r\n");
	Dis_part_pic(0,xDot-1,0,yDot-1,(unsigned char *)waveshare); //pic
	driver_delay_xms(DELAYTIME);

	//Show Circle and Line 
	printf("--------------Show Circle and Line-------------\r\n");
	Dis_Drawing((yDot-32)/8,5,(unsigned char *)Circle3232,32,32); //Circle
	Dis_Drawing((yDot-32)/8,0,(unsigned char *)Line3232,32,32); //Line
	driver_delay_xms(DELAYTIME);

	//Show string
	printf("--------------Show string-------------\r\n");
 	Dis_String(0, 10, "SHOW TIME :",16);
	Dis_String(0, 26, "I am an electronic paper display",12);
	driver_delay_xms(DELAYTIME);

	//Progress
	printf("--------------Show Progress-------------\r\n");
	Dis_Progress(9);	
	driver_delay_xms(DELAYTIME);

	//show time
	printf("--------------show time------------\r\n");
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
	
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
	
}

