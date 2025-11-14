#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Q8 8
#define Q16 16
int current_time;
struct PCP {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int responseTime;
    int completion_time;
    int TAT;
    bool completed;
};
/* (Code omitted in this snippet – full code will be included) */
