#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define _1f_door 0
#define _2f_door 4
#define _3f_door 23

int main(int argc, char *argv[]) {
	wiringPiSetup();

	int floor = atoi(argv[1]);

	switch(floor) {
	case 1:
		softPwmCreate(_1f_door, 0, 200);
		softPwmWrite(_1f_door, 8);
		delay(3000);
		softPwmWrite(_1f_door, 24);
		delay(1000);
		break;
	case 2:
		softPwmCreate(_2f_door, 0, 200);
                softPwmWrite(_2f_door, 8);
                delay(3000);
                softPwmWrite(_2f_door, 24);
                delay(1000);
		break;
	case 3:
		softPwmCreate(_3f_door, 0, 200);
                softPwmWrite(_3f_door, 8);
                delay(3000);
                softPwmWrite(_3f_door, 24);
                delay(1000);
		break;

	}
}
