#include <iostream>
#include <wiringPi.h>
#include <pigpio.h>
#include <stdio.h>
#include <ncurses.h>

#include "Car.h"

using namespace std;

int main() {

	Car car;
	if (car.getErrorFlag() == 0)
	{
		car.speedLevel = 123;
		for (; ; ) {
			initscr();
			keypad(stdscr, TRUE);
			refresh();

			int keypressed = getch();

			if (keypressed == KEY_UP || keypressed == 'W' || keypressed == 'w') {
				car.speedLevel = 123;
				car.driveForward();
			}
			if (keypressed == KEY_DOWN || keypressed == 'S' || keypressed == 's') {
				car.speedLevel = 80;
				car.driveBackward();
			}
			if (keypressed == KEY_RIGHT || keypressed == 'D' || keypressed == 'd') {
				car.speedLevel = 100;
				car.turnRight();
			}
			if (keypressed == KEY_LEFT || keypressed == 'A' || keypressed == 'a') {
				car.speedLevel = 100;
				car.turnLeft();
			}
			if (keypressed == ' ') {
				car.stopCar();
			}
			if (keypressed == 'B' || keypressed == 'b') {
				car.speedLevel = 0;
				car.emergencyStop();
			}
			if (keypressed == 'x') {

				break;
			}
			refresh();
		}
		endwin();
	}
	else
	{
		cout << "Error flag raised. Closing" << endl;
	}
	return 0;
}
