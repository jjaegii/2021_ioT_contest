#include <stdio.h>
#include <wiringPi.h>

#define SDI 27
#define RCLK 28
#define SRCLK 29

unsigned char SegCode[3] = {0x06,0x5b,0x4f};

void init(void) {
	pinMode(SDI, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(SRCLK, OUTPUT);

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

void hc595_shift(unsigned char dat) {
	for(int i = 0; i < 8; i++) {
		digitalWrite(SDI, 0x80 & (dat << i));
		digitalWrite(SRCLK, HIGH);
		delay(1);
		digitalWrite(SRCLK, LOW);
	}
		digitalWrite(RCLK, HIGH);
		delay(1);
		digitalWrite(RCLK, LOW);
}

int main(int argc, char *argv[]) {
	wiringPiSetup();

	init();

	int floor = atoi(argv[1]);
	
	hc595_shift(SegCode[floor - 1]);

	return 0;
}
