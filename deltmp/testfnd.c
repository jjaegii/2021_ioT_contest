#include <stdio.h>
#include <wiringPi.h>
#include <sr595.h>

//int fnd[] = { 0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09 };

int num[3][7] = {{0, 1, 1, 0, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 1}};
int main() {



	wiringPiSetup();
	for(int i = 27; i <= 29; i++) {
		pinMode(i, OUTPUT);
	}

	//for(int i = 0; i < 3; i++) {
	//	for(int j = 0; j < 7; j++) {
	//		digitalWrite(100 + j, fnd[i][j]);
	//		delay(1000);
	//	}
	//
	//
	//}

	sr595Setup(70, 7, 27, 28, 29);

//	for(int i = 0; i < 10; i++) {
//		shiftOut(29, 27, fnd[i]);
//		digitalWrite(28, HIGH);
//		delay(100);
//	}
//	delay(10000);

	while(1)
	for(int b = 0; b <3; b++){
		for(int c = 0; c < 7; c++)
			digitalWrite(70 + c, 1);
	}


	while(1) {
        for (int b = 0; b < 3; b++) {
            for(int c = 0; c < 7; c++)
                digitalWrite(70 + c, num[b][c]);
            delay(2000);
	    for(int c = 0; c <7; c++)
		    digitalWrite(70 + c, 1);
	    delay(1000);
        }
    }
    return 0;
}
