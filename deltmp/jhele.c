#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <sys/time.h>

#define servo1 7

int main(int argc, char *argv[]) {
	char sel;
	if(wiringPiSetup() == -1) return -1;
	softPwmCreate(servo1, 0, 200);

	struct timeval bgn,end;
        double diff;
	while(1){
		if(argv[1]=='1'){
			break;
		}
	}
	delayL
	 while(1) {
                fputs("select c(멈춤), r(하강), l(상승), q : " , stdout);
                scanf("%c", &sel);
                getchar();
                if(sel == 'c') {
                        softPwmWrite(servo1,0);   // stop
                        gettimeofday(&end, NULL);
                        diff = end.tv_sec + end.tv_usec / 1000000.0 - bgn.tv_sec - bgn.tv_usec / 1000000.0;                       printf("%f\n", diff);
                }
                else if(sel == 'r'){
                        softPwmWrite(servo1,24); // 엘리베이터 하강
                        gettimeofday(&bgn, NULL);
                }
                else if(sel == 'l'){
                        softPwmWrite(servo1,8); // 엘리베이터 상승
                        gettimeofday(&bgn, NULL);
                }
                else if(sel == 'q'){
                        return 0;
                }
                sel = ' ';
        }
	
	return 0;
}
