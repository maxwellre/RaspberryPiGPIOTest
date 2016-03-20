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
	int fd, ret;
	int outX, outY, outZ;

	fd = wiringPiI2CSetup(0x1e);
	printf("I2C Initialized: ID = %d\n", fd);
	
	pinMode(I2CSDA, OUTPUT);
	pinMode(I2CSCL, OUTPUT);
	
	// CTRL_REG4: ODR = 1600 Hz
	ret = wiringPiI2CWriteReg8(fd, 0x20, 0x97);
	checkRet(ret, 0);

	// CTRL_REG5: FSCALE = 8g
	ret = wiringPiI2CWriteReg8(fd, 0x24, 0x18);
	checkRet(ret, 0);
	
	printf("\n");
	
	// The loop --------------------------------------------------------
	while(1)
	{	
		ret = wiringPiI2CReadReg8(fd, 0x27);
		if( (ret & 0x07) == 0x07)
		{
			outX = wiringPiI2CReadReg16(fd, 0x28);
			outY = wiringPiI2CReadReg16(fd, 0x2A);
			outZ = wiringPiI2CReadReg16(fd, 0x2C);
			
			printf(" %d  %d  %d\n", outX, outY, outZ);
		}
		else
		{
			checkRet(ret, 0);
		}	
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

