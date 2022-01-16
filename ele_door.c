#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define _1L 2
#define _1R 3

#define _2L 21
#define _2R 22

#define _3L 25
#define _3R 26

int main(int argc, char *argv[]) {
	if(wiringPiSetup() == -1) return -1;

	int floor = atoi(argv[1]);
	switch(floor) {
		case 1:
			softPwmCreate(_1L, 0, 200);
        		softPwmCreate(_1R, 0, 200);
        		
			softPwmWrite(_1L, 20);
        		softPwmWrite(_1R, 14);
        		delay(4000);
        		softPwmWrite(_1L, 8);
        		softPwmWrite(_1R, 24);
        		delay(1000);
			break;
		case 2:
			softPwmCreate(_2L, 0, 200);
       			softPwmCreate(_2R, 0, 200);
				
        		softPwmWrite(_2L, 20);
        		softPwmWrite(_2R, 14);
        		delay(4000);
        		softPwmWrite(_2L, 8);
        		softPwmWrite(_2R, 24);
        		delay(1000);
			break;
		case 3:
			softPwmCreate(_3L, 0, 200);
        		softPwmCreate(_3R, 0, 200);

       			softPwmWrite(_3L, 24);
        		softPwmWrite(_3R, 14);
        		delay(4000);
        		softPwmWrite(_3L, 8);
        		softPwmWrite(_3R, 24);
        		delay(1000);
			break;
	}
	
}
