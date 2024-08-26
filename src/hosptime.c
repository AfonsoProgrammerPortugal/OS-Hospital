/*
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "hosptime.h" 
#include <stdio.h>
#include <time.h>

void get_current_time(struct timespec *time){
    if(clock_gettime(CLOCK_REALTIME, time) == -1){
        printf("Erro no get_current_time");
        return;
    }
}