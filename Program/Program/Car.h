
#include <iostream>
#include <wiringPi.h>
#include <pigpio.h>
#include <stdio.h>
#include <ncurses.h>
using namespace std;


class Car
{
private:
	// Motor pins
	unsigned char pwmLeft = 22;
	unsigned char pwmRight = 18;
	unsigned char inLeft1 = 27;
	unsigned char inLeft2 = 17;
	unsigned char inRight3 = 14;
	unsigned char inRight4 = 15;

	// Sonar range radars pins
	unsigned char rearTrig = 26;
	unsigned char frontTrig = 13;
	unsigned char rearEcho = 24;
	unsigned char frontEcho = 5;

	// IR sensors
	unsigned char rearLeftInfra = 16;
	unsigned char rearRightInfra = 9;
	unsigned char frontLeftInfra = 23;
	unsigned char frontRightInfra = 6;

	// Encoders
	unsigned char leftEncoder = 25;
	unsigned char rightEncoder = 10;
	
	// Flags
	bool errorFlag = 0;
	bool collisionFlag = 0;
	void updatePins();


public:
	unsigned char speedLevel = 0;
	bool getErrorFlag();
	void driveForward();
	void driveBackward();
	void turnLeft();
	void turnRight();
	void stopCar();
	void updatePWM();
	void emergencyStop();
	void setMotorPins(unsigned char pwmLeft, unsigned char pwmRight, unsigned char inLeft1, unsigned char inLeft2, unsigned char inRight3, unsigned char inRight4);
	void setSonarPins(unsigned char rearTrig, unsigned char frontTrig, unsigned char rearEcho, unsigned char frontEcho);
	void setInfraSensorPins(unsigned char rearLEftInfra, unsigned char rearRightInfra, unsigned char frontLeftInfra, unsigned char frontRightInfra);
	void setEncoderPins(unsigned char leftEncoder, unsigned char rightEncoder);
	Car();
	~Car();
};
