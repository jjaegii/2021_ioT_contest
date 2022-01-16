#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <sys/time.h>

#define servo1 7

int main(int argc, char *argv[]) {
	if(wiringPiSetup() == -1) return -1;
	softPwmCreate(servo1, 0, 200);
	
	if(argv[2][0] == '1') {
		system("./door 1");
		return 0;
	}

	if(argv[1][0] == '1') {
		system("./fnd 1");
		system("./door 1");
	}
	else if(argv[1][0] =='2'){
		system("./fnd 2");
		softPwmWrite(servo1, 24);
		delay(9200);
		system("./fnd 1");
		softPwmWrite(servo1, 0);
		system("./ele_door 1");
	}
	else if(argv[1][0]=='3'){
		system("./fnd 3");
		softPwmWrite(servo1, 24);
		delay(3550);
		system("./fnd 2");
		delay(3000);
		system("./fnd 1");
		softPwmWrite(servo1, 0);
		system("./ele_door 1");
	}
	
	if(argv[2][0] == '2') {
		softPwmWrite(servo1, 8);
		delay(10090);
		system("./fnd 2");
		softPwmWrite(servo1, 0);
		system("./ele_door 2");
		system("./door 2");
	}
	else if(argv[2][0]=='3'){
		softPwmWrite(servo1, 8);
		delay(3500);
		system("./fnd 2");
		delay(4000);
		system("./fnd 3");
		softPwmWrite(servo1, 0);
		system("./ele_door 3");
		system("./door 3");
	}
	return 0;
}
