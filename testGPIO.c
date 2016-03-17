/* A test program for RPI GPIO*/
// 03/16/2016
// =====================================================================

#include<stdio.h>
#include<wiringPi.h>


#define I2CPIN0 8

int main(void)
{
	wiringPiSetup();
	//wiringPiSetupGpio();

	pinMode(I2CPIN0, OUTPUT);
	
	printf("LED is blinking!\n");

	int i;
	for(i = 0; i < 1000; i++)
	{
		digitalWrite(I2CPIN0, HIGH);
		delay(2000);
		digitalWrite(I2CPIN0, LOW);
	}
	
	return 0;
}

