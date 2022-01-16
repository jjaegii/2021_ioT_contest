#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
#include "LCD_I2C.h"

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

void publicgate_run() {
	softPwmCreate(publicgate_servo, 0, 200);
	
	softPwmWrite(publicgate_servo, 12); // 공동현관문 열림
	delay(950); // delay 시간 수정 필요
	softPwmWrite(publicgate_servo, 8); // 공동현관문 stop
	delay(3000);
	softPwmWrite(publicgate_servo, 10); // 공동현관문 닫힘
	delay(950); // delay 시간 수정 필요
	softPwmWrite(publicgate_servo, 8); // 공동현관문 stop
}

void elevator_run(int floor) {
	softPwmCreate(elevator_servo, 0, 200);

	if(elevator_floor != 1) { // 엘리베이터가 1층에 없다면
		softPwmWrite(elevator_servo, 5); // 엘리베이터 하강
		delay(3000 * (floor - 1));
	}
	softPwmWrite(elevator_servo, 8); // 엘리베이터 중지
	delay(5000);
	softPwmWrite(elevator_servo, 24); // 엘리베이터 상승
	delay(3000 * (floor - 1));
	softPwmWrite(elevator_servo, 8); // 엘리베이터 중지
	
	elevator_floor = floor; // 엘리베이터가 현재 있는 위치 재설정
	
	switch(floor) {
	case 1:
		softPwmCreate(_1f_elevator_door_L, 0, 200);
		softPwmCreate(_1f_elevator_door_R, 0, 200);
		
		break;
	case 2:
		softPwmCreate(_2f_elevator_door_L, 0, 200);
		softPwmCreate(_2f_elevator_door_R, 0, 200);

		break;
	case 3:
		softPwmCreate(_3f_elevator_door_L, 0, 200);
		softPwmCreate(_3f_elevator_door_R, 0, 200);

		break;
	default:
		break;
	}
}

void door_run(int floor) {
	switch(floor) {
	case 1:
		softPwmCreate(_1f_door, 0, 200);
		softPwmWrite(_1f_door, 24); // 열림? 닫힘?
		delay(3000);
		softPwmWrite(_1f_door, 8); // 열림? 닫힘?
		break;
	case 2:
		
		break;
	case 3:

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

	LCD_begin(0x27, 16, 8, LCD_5x8DOTS);
	LCD_print("    System On");

	int floor = atoi(argv[1]);
	
	LCD_run(floor);
	publicgate_run();
	elevator_run(floor);
	led_run(floor);
	
	LCD_clear();
	LCD_print("    System On");
	return 0;
}
