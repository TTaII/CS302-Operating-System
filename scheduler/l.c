#include <stdio.h>
#include <sys/time.h>
#include <time.h>
int main(){
    long int curtime;
    curtime = time(NULL);
    printf("%s\n", ctime(&curtime));

    struct timeval interval;
    struct itimerval new;

    interval.tv_sec = 0;
	interval.tv_usec = 100;
    new.it_interval = interval;
	new.it_value = interval;
    new.it_interval.tv_sec = 10;
    printf("%ld\n",new.it_value.tv_sec);
    return 0;
}