/* A test program for RPI GPIO*/
// 03/16/2016
// =====================================================================

#include<stdio.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

// =====================================================================
// Macros
#define CS 7
#define I2CSDA 8
#define I2CSCL 9 

// =====================================================================
// Function declaration 	
void checkRet(int ret, int isDispRet);

// =====================================================================
// Main 
int main(void)
{
	int i;
	int fd, ret;

	fd = wiringPiI2CSetup(0x1e);
	printf("I2C Initialized: ID = %d\n", fd);
	
	pinMode(I2CSDA, OUTPUT);
	pinMode(I2CSCL, OUTPUT);
	
	ret = wiringPiI2CWriteReg8(fd, 0x20, 0x97);
	checkRet(ret, 0);

	
	
	printf("\n");
	
	// The loop --------------------------------------------------------
	for(i = 0; i < 10; i++)
	{		
		ret = wiringPiI2CReadReg8(fd, 0x20);
		checkRet(ret, 1);	
	}
	// -----------------------------------------------------------------
	
	return 0;
}

// Function declaration 	
void checkRet(int ret, int isDispRet)
{
	if(ret == -1)
	{
		printf("Error!\n");
	}
	else if(isDispRet)
	{
		printf(" %02x ", ret);
	}
}

