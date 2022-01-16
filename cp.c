#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
#include "LCD_I2C.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define publicgate_servo 6
#define elevator_servo 7

#define _1f_door 0
#define _1f_elevator_door_L 2
#define _1f_elevator_door_R 3

#define _2f_door 4
#define _2f_elevator_door_L 21
#define _2f_elevator_door_R 22

#define _3f_door 23
#define _3f_elevator_door_L 25
#define _3f_elevator_door_R 26

#define SDI 27
#define RCLK 28
#define SRCLK 29

int cur_floor = 1; // 엘리베이터 현재 위치

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
	cur_floor = atoi(buf);
	printf("ele : %d\n", cur_floor);

	LCD_begin(0x27, 16, 8, LCD_5x8DOTS);
	LCD_print("    System On");

	int cli_floor = atoi(argv[1]);
	
	LCD_run(cli_floor);
	publicgate_run();
	char tmp[30];
	sprintf(tmp, "./ele %d %d", cur_floor, cli_floor);
	system(tmp);
	
	LCD_clear();
	LCD_print("    System On");

	fd = open("./elevator.txt", O_WRONLY);
	sprintf(buf, "%d", cur_floor);
	write(fd, buf, strlen(buf));
	close(fd);
	return 0;
}
