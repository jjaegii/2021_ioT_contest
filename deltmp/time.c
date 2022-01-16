#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <sys/time.h>

#define servo1 6

int main(int argc, char *argv[]) {
	char sel;
	if(wiringPiSetup() == -1) return -1;
	softPwmCreate(servo1, 0, 200);

	softPwmWrite(servo1, 5);
	delay(800);
	softPwmWrite(servo1, 0);
	delay(3000);
	softPwmWrite(servo1, 16);
	delay(2400);

	
	return 0;
}
