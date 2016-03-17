/* A test program for RPI GPIO*/
// 03/16/2016
// =====================================================================

#include<stdio.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

// =====================================================================
// Macros
#define CS 7
#define I2CPIN0 8

// =====================================================================
// Main 
int main(void)
{
	wiringPiSetup();
	//wiringPiI2CSetup();

	pinMode(CS, OUTPUT);
	
	digitalWrite(CS, HIGH); // Enable chip
	printf("Chip Enabled!\n");

	int i;
	
	// The loop --------------------------------------------------------
	for(i = 0; i < 10000; i++)
	{
		delay(50);
	}
	// -----------------------------------------------------------------
	
	digitalWrite(CS, LOW); // Disable chip
	return 0;
}

