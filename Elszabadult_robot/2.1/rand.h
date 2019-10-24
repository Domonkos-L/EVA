#ifndef RAND_H
#define RAND_H

#include <time.h>
#include <stdlib.h>

static bool RAND_H_FIRST_TIME = true;

void RAND_H_INIT(){
    if(RAND_H_FIRST_TIME){
        srand(time(nullptr));
        RAND_H_FIRST_TIME = false;
    }
}

int randint(int n){
    RAND_H_INIT();
    return rand() % n;
}

int randint(int n, int m){
	RAND_H_INIT();
	return n + rand() % (m-n);
}

#endif // RAND_H