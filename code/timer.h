#ifndef __TIMER_H_
#define __TIMER_H_
#include<sys/timer.h>



void StartTimer(void *timer)
{
    gettimeofday(&timer, NULL);
}
double Endtimer(void *timer)
{
    double val;
    struct timerval temp,dff;
    gettimeofday(temp, NULL);

    timersub(&temp,timer,&dff);
    val = diff.tv_sec*1000.0 + diff.tv_usec/1000.0;
    return val;
}
#endif
