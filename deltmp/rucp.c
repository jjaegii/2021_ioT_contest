#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
#include "LCD_I2C.h"
#include <fcntl.h>
#include <stdlib.h>

#define publicgate_servo 6
#define elevator_servo 7

#define _1f_door 0
#define _1f_led 1
#define _1f_elevator_door_L 2
#define _1f_elevator_door_R 3

#define _2f_door 4
#define _2f_led 5
#define _2f_elevator_door_L 21
#define _2f_elevator_door_R 22

#define _3f_door 23
#define _3f_led 24
#define _3f_elevator_door_L 25
#define _3f_elevator_door_R 26

#define SDI 27
#define RCLK 28
#define SRCLK 29

int elevator_floor = 1; // 엘리베이터 현재 위치

unsigned char Seg[3] = {0x06, 0x5b, 0x4f};

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
	

void publicgate_run() {
	softPwmCreate(publicgate_servo, 0, 200);
	
	softPwmWrite(publicgate_servo, 5); // 공동현관문 열림
	delay(800); 
	softPwmWrite(publicgate_servo, 0); // 공동현관문 stop
	delay(3000);
	softPwmWrite(publicgate_servo, 16); // 공동현관문 닫힘
	delay(2400); 
	softPwmWrite(publicgate_servo, 0); // 공동현관문 stop
}

void elevator_run(int floor) {
	softPwmCreate(elevator_servo, 0, 200);

	if(elevator_floor = 2) {
		softPwmWrite(elevator_servo, 24);
		delay(3600);
		softPwmWrite(elevator_servo, 0);
	}
	else if(elevator_floor = 3) {
		softPwmWrite(elevator_servo, 24);
		delay(6550);
		softPwmWrite(elevator_servo, 0);
	}

	system("./ele_door 1");
	
	if(floor = 2) {
		softPwmWrite(elevator_servo, 8);
		delay(4200);
		softPwmWrite(elevator_servo, 0);
		system("./ele_door 2");
	}
	else if(floor = 3) {
		softPwmWrite(elevator_servo, 8);
		dedelay(7500);
		softPwmWrite(elevator_servo, 0);
		system("./ele_door 3");
	}
	
	elevator_floor = floor;
}

void door_run(int floor) {
	switch(floor) {
	case 1:
		softPwmCreate(_1f_door, 0, 200);
		softPwmWrite(_1f_door, 8); // 열림
		delay(3000);
		softPwmWrite(_1f_door, 24); // 닫힘
		delay(1000);
		softPwmWrite(_1f_door, 0);
		break;
	case 2:
              	softPwmCreate(_2f_door, 0, 200);
                softPwmWrite(_2f_door, 8);
                delay(3000);
                softPwmWrite(_2f_door, 24);
                delay(1000);
		softPwmWrite(_2f_door, 0);
		break;
	case 3:
		softPwmCreate(_3f_door, 0, 200);
                softPwmWrite(_3f_door, 8);
                delay(3000);
                softPwmWrite(_3f_door, 24);
                delay(1000);
		softPwmWrite(_3f_door, 0);
		break;
	default:
		break;
	}
}

void led_run(int floor) {
	switch(floor) {
	case 1:
		pinMode(_1f_led, OUTPUT);
		digitalWrite(_1f_led, HIGH);
		door_run(1);
		digitalWrite(_1f_led, LOW);
		break;
	case 2:
		pinMode(_2f_led, OUTPUT);
		digitalWrite(_2f_led, HIGH);
		door_run(2);
		digitalWrite(_2f_led, LOW);
		break;
	case 3:
		pinMode(_3f_led, OUTPUT);
		digitalWrite(_3f_led, HIGH);
		door_run(3);
		digitalWrite(_3f_led, LOW);
		break;
	default:
		break;
	}
}

void LCD_run(int floor) {
	LCD_clear();
	switch(floor) {
	case 1:
		LCD_print("    Welcome!");
		LCD_setCursor(0,1);
		LCD_print("      1F");
		break;
	case 2:
		LCD_print("    Welcome!");
		LCD_setCursor(0,1);
		LCD_print("      2F");
		break;
	case 3:
		LCD_print("    Welcome!");
		LCD_setCursor(0,1);
		LCD_print("      3F");
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[]) {
	if(wiringPiSetup() == -1) {
		printf("wiringPi 오류\n");
		return -1;	
	}
	
	pinMode(SDI, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(SRCLK, OUTPUT);
	
	digitalWrite(SDI, LOW);
	digitalWrite(RCLK, LOW);
	digitalWrite(SRCLK, LOW);

	int fd = open("./elevator.txt", O_RDONLY);
	char buf[10];
       	read(fd, buf, sizeof(buf));
	close(fd);
	elevator_floor = atoi(buf);
	hc595_shift(Seg[elevator_floor - 1]);
	printf("ele : %d\n", elevator_floor);

	LCD_begin(0x27, 16, 8, LCD_5x8DOTS);
	LCD_print("    System On");

	int floor = atoi(argv[1]);
	
	LCD_run(floor);
	publicgate_run();
	char tmp[30];
	sprintf(tmp, "./ele %d %d", elevator_floor, floor);
	system(tmp);
	//elevator_run(floor);
	led_run(floor);
	
	LCD_clear();
	LCD_print("    System On");

	fd = open("./elevator.txt", O_WRONLY);
	sprintf(buf, "%d", elevator_floor);
	write(fd, buf, strlen(buf));
	close(fd);
	return 0;
}
