main:main.o EPD_drive.o EPD_drive_gpio.o
	gcc -Wall -o main main.o EPD_drive.o EPD_drive_gpio.o -lbcm2835
EPD_drive.o:EPD_drive.c EPD_drive.h
	gcc -Wall -c EPD_drive.c -lbcm2835
EPD_drive_gpio.o:EPD_drive_gpio.c EPD_drive_gpio.h
	gcc -Wall -c EPD_drive_gpio.c -lbcm2835	
main.o:main.c EPD_drive.h EPD_drive_gpio.h Display_Lib.h
	gcc -Wall -c main.c -lbcm2835
clean:
	rm EPD_drive.o main.o EPD_drive_gpio.o main
