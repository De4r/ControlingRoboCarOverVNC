#include <iostream>
#include <wiringPi.h>
#include <pigpio.h>
#include <stdio.h>
#include <ncurses.h>

#include "Car.h"

// Updates the PWM duty (speedLevel) of the car
void Car::updatePWM()
{
	gpioPWM(pwmLeft, speedLevel);
	gpioPWM(pwmRight, speedLevel);
}

// Drive forward
void Car::driveForward()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 0);
	gpioWrite(inLeft2, 1);

	gpioWrite(inRight3, 1);
	gpioWrite(inRight4, 0);
}

// Drive backward
void Car::driveBackward()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 1);
	gpioWrite(inLeft2, 0);

	gpioWrite(inRight3, 0);
	gpioWrite(inRight4, 1);
}

// Trun left inplace
void Car::turnLeft()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 0);
	gpioWrite(inLeft2, 1);

	gpioWrite(inRight3, 0);
	gpioWrite(inRight4, 1);
}

// Trun right inplace
void Car::turnRight()
{
	// Set In pins to proper levels
	updatePWM();
	gpioWrite(inLeft1, 1);
	gpioWrite(inLeft2, 0);

	gpioWrite(inRight3, 1);
	gpioWrite(inRight4, 0);
}

// Stoping the car by slowing, smoothly stops.
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

// Emergency stop -> stall the DC motors with high levels on both pins, hard stop, can make car flip
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

// Setting the pins to control L298N brigde
void Car::setMotorPins(unsigned char pwmLeft, unsigned char pwmRight, unsigned char inLeft1, unsigned char inLeft2, unsigned char inRight3, unsigned char inRight4)
{
	this->pwmLeft = pwmLeft;
	this->pwmRight = pwmRight;
	this->inLeft1 = inLeft1;
	this->inLeft2 = inLeft2;
	this->inRight3 = inRight3;
	this->inRight4 = inRight4;
	updatePins();

}

// Setting the pins to control Sonars (rear and front)
void Car::setSonarPins(unsigned char rearTrig, unsigned char frontTrig, unsigned char rearEcho, unsigned char frontEcho)
{
	this->rearTrig = rearTrig;
	this->frontTrig = frontTrig;
	this->rearEcho = rearEcho;
	this->frontEcho = frontEcho;
	updatePins();
}

// Setting the pins of input of Infra Red sensors (collision in corners)
void Car::setInfraSensorPins(unsigned char rearLeftInfra, unsigned char rearRightInfra, unsigned char frontLeftInfra, unsigned char frontRightInfra)
{
	this->rearLeftInfra = rearLeftInfra;
	this->rearRightInfra = rearRightInfra;
	this->frontLeftInfra = frontLeftInfra;
	this->frontRightInfra = frontRightInfra;
	updatePins();
}

// Setting the pins of encoders (the IR interupt encoders)
void Car::setEncoderPins(unsigned char leftEncoder, unsigned char rightEncoder)
{
	this->leftEncoder = leftEncoder;
	this->rightEncoder = rightEncoder;
	updatePins();
}

// Constructor -> initialize pigpio or raise flag error, sets standard pins to thier mode;
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

// Destructor -> calls the pigpio Terminate!
Car::~Car()
{
	gpioTerminate();
}

// Returns error flag;
bool Car::getErrorFlag() {
	return errorFlag;
}

// Update pins mode after changing them
void Car::updatePins()
{
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