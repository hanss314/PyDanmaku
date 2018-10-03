//
// Created by hanss on 10/3/18.
//

#include <math.h>
#define GRANULARITY 1024

bool trig_inited = false;
double lookup_table[GRANULARITY+1];

void trig_init(){
    if (trig_inited) return;
    for (int i=0; i<=GRANULARITY; i++){
        lookup_table[i] = sin(M_PI_2*i/GRANULARITY);
    }
    trig_inited = true;
}

double l_sin(double x){
    if (!trig_inited) trig_init();
    int ind = (int)2*GRANULARITY*x/M_PI;
    if (ind < 0) ind += 4*GRANULARITY;
    ind %= 4*GRANULARITY;
    if (ind < GRANULARITY){
        return lookup_table[ind];
    } else if (ind < 2*GRANULARITY) {
        return lookup_table[2*GRANULARITY-ind];
    } else if (ind < 3*GRANULARITY) {
        return -lookup_table[ind-2*GRANULARITY];
    } else { // ind < 4*GRANULARITY
        return -lookup_table[4*GRANULARITY-ind];
    }
}

double l_cos(double x){
    return l_sin(x+M_PI_2);
}


