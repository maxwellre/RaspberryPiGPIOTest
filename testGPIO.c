/* A test program for RPI GPIO*/
// 03/16/2016
// =====================================================================

#include<stdio.h>
#include<time.h>
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
	
	FILE *fp;
	
	fp = fopen("RPI_acc_data.txt","wt");

	fd = wiringPiI2CSetup(0x1e);
	printf("I2C Initialized: ID = %d\n", fd);
	
	pinMode(I2CSDA, OUTPUT);
	pinMode(I2CSCL, OUTPUT);
	
	// CTRL_REG4: ODR = 1600 Hz(0x9*) or 400 Hz(0x7*) or 25 Hz(0x4*)
	ret = wiringPiI2CWriteReg8(fd, 0x20, 0x9F);

	checkRet(ret, 0);

	// CTRL_REG5: FSCALE = 8g(0x18) or 16g(0x20)
	ret = wiringPiI2CWriteReg8(fd, 0x24, 0x18);
	checkRet(ret, 0);
	
	printf("\n");
	
	printf("Running...\n");
	
	// Start the timer
	double startTime = clock();
	
	// The loop --------------------------------------------------------
	//while(1)
	int i;
	for(i=0; i<3000; i++)
	{	
		/*ret = wiringPiI2CReadReg8(fd, 0x27);
		if( (ret & 0x07) == 0x07)
		{*/
			outX = 16*wiringPiI2CReadReg8(fd, 0x29) + \
			wiringPiI2CReadReg8(fd, 0x28);
			
			outY = 16*wiringPiI2CReadReg8(fd, 0x2B) + \
			wiringPiI2CReadReg8(fd, 0x2A);
			
			outZ = 16*wiringPiI2CReadReg8(fd, 0x2D) + \
			wiringPiI2CReadReg8(fd, 0x2C);

			/*outX = wiringPiI2CReadReg8(fd, 0x29);
			outY = wiringPiI2CReadReg8(fd, 0x2B);
			outZ = wiringPiI2CReadReg8(fd, 0x2D);*/
			
			//printf(" %d  %d  %d\n", outX, outY, outZ);
			fprintf(fp, "%d,%d,%d,%.4f\r\n", outX, outY, outZ, \
			(clock() - startTime) / CLOCKS_PER_SEC );
		/*}
		else
		{
			checkRet(ret, 0);
		}*/	
	}
	// -----------------------------------------------------------------
	
	fclose(fp);
	
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

