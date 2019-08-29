#include <iostream>
#include <wiringPi.h>
#include <pigpio.h>
#include <stdio.h>
#include <ncurses.h>

#include "Car.h"

void Car::updatePWM()
{
	gpioPWM(pwmLeft, speedLevel);
	gpioPWM(pwmRight, speedLevel);
}

void Car::driveForward()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 0);
	gpioWrite(inLeft2, 1);

	gpioWrite(inRight3, 1);
	gpioWrite(inRight4, 0);
}

void Car::driveBackward()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 1);
	gpioWrite(inLeft2, 0);

	gpioWrite(inRight3, 0);
	gpioWrite(inRight4, 1);
}

void Car::turnLeft()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 1);
	gpioWrite(inLeft2, 0);

	gpioWrite(inRight3, 1);
	gpioWrite(inRight4, 0);
}
void Car::turnRight()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 0);
	gpioWrite(inLeft2, 1);

	gpioWrite(inRight3, 0);
	gpioWrite(inRight4, 1);
}
void Car::stopCar()
{
	while (speedLevel > 0)
	{
		speedLevel--;
		updatePWM();
		gpioDelay(500);
	}

	gpioWrite(inLeft1, 0);
	gpioWrite(inLeft2, 0);

	gpioWrite(inRight3, 0);
	gpioWrite(inRight4, 0);
	
}
void Car::emergencyStop()
{
	updatePWM();
	gpioWrite(inLeft1, 1);
	gpioWrite(inLeft2, 1);

	gpioWrite(inRight3, 1);
	gpioWrite(inRight4, 1);

	gpioDelay(100000);

	gpioWrite(inLeft1, 0);
	gpioWrite(inLeft2, 0);

	gpioWrite(inRight3, 0);
	gpioWrite(inRight4, 0);
}

void Car::setMotorPins(unsigned char pwmLeft, unsigned char pwmRight, unsigned char inLeft1, unsigned char inLeft2, unsigned char inRight3, unsigned char inRight4)
{

}

void Car::setSonarPins(unsigned char rearTrig, unsigned char frontTrig, unsigned char rearEcho, unsigned char frontEcho)
{

}

void Car::setInfraSensorPins(unsigned char rearLEftInfra, unsigned char rearRightInfra, unsigned char frontLeftInfra, unsigned char frontRightInfra)
{

}

void Car::setEncoderPins(unsigned char leftEncoder, unsigned char rightEncoder)
{

}

void Car::updatePinStatus()
{

}

Car::Car()
{
	if (gpioInitialise() < 0)
	{
		errorFlag = 1;
	}
	else
	{
		// pigpio initialised okay.
		gpioPWM(pwmLeft, speedLevel);
		gpioPWM(pwmRight, speedLevel);

		gpioSetMode(inLeft2, PI_OUTPUT); //in 1
		gpioSetMode(inLeft1, PI_OUTPUT); //in 2
		
		gpioSetMode(inRight3, PI_OUTPUT); // in3
		gpioSetMode(inRight4, PI_OUTPUT); // in4

		gpioSetMode(rearTrig, PI_OUTPUT);
		gpioSetMode(frontTrig, PI_OUTPUT);

		gpioSetMode(rearEcho, PI_INPUT);
		gpioSetPullUpDown(rearEcho, PI_PUD_UP);

		gpioSetMode(frontEcho, PI_INPUT);
		gpioSetPullUpDown(frontEcho, PI_PUD_UP);

		gpioSetMode(rearLeftInfra, PI_INPUT);
		gpioSetMode(frontLeftInfra, PI_INPUT);
		gpioSetMode(rearRightInfra, PI_INPUT);
		gpioSetMode(frontRightInfra, PI_INPUT);

		gpioSetPullUpDown(rearLeftInfra, PI_PUD_UP);
		gpioSetPullUpDown(frontLeftInfra, PI_PUD_UP);
		gpioSetPullUpDown(rearRightInfra, PI_PUD_UP);
		gpioSetPullUpDown(frontRightInfra, PI_PUD_UP);


		gpioSetMode(leftEncoder, PI_INPUT);
		gpioSetMode(rightEncoder, PI_INPUT);
		gpioSetPullUpDown(leftEncoder, PI_PUD_UP);
		gpioSetPullUpDown(rightEncoder, PI_PUD_UP);


	
	}
}

Car::~Car()
{
	
	gpioTerminate();
}

bool Car::getErrorFlag() {
	return errorFlag;
}
