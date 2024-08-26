/* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "main.h"
#include "memory.h"
#include "synchronization.h"
#include "hospsignal.h"
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// VariAveis globais para guardar os parAmetros passados na funCAo signal_handlers
struct data_container* data_global;
struct communication* comm_global;
struct semaphores* sems_global;

void print_admission_status(){
    int finished = 0;
    for (int i = 0; i < data_global->max_ads && finished==0; i++){
        switch (data_global->results[i].status){
            case 'M':
                printf("ad:%d ",data_global->results[i].id);
                printf("status:%c ",data_global->results[i].status);
                printf("start_time: %ld \n",data_global->results[i].create_time.tv_sec);
                break;
            case 'P':
                printf("ad:%d ",data_global->results[i].id);
                printf("status:%c ",data_global->results[i].status);
                printf("start_time: %ld \n",data_global->results[i].create_time.tv_sec);
            case 'R':
                printf("ad:%d ",data_global->results[i].id);
                printf("status:%c ",data_global->results[i].status);
                printf("start_time: %ld ",data_global->results[i].create_time.tv_sec);
                printf("patient:%d ", data_global->results[i].receiving_patient);
                printf("patient_time: %ld ", data_global->results[i].patient_time.tv_sec);
                printf("receptionist:%d ", data_global->results[i].receiving_receptionist);
                printf("receptionist_time: %ld\n ", data_global->results[i].receptionist_time.tv_sec);
            case 'A'||'N':
                printf("ad:%d ",data_global->results[i].id);
                printf("status:%c ",data_global->results[i].status);
                printf("start_time: %ld ",data_global->results[i].create_time.tv_sec);
                printf("patient:%d ", data_global->results[i].receiving_patient);
                printf("patient_time: %ld ", data_global->results[i].patient_time.tv_sec);
                printf("receptionist:%d ", data_global->results[i].receiving_receptionist);
                printf("receptionist_time: %ld ", data_global->results[i].receptionist_time.tv_sec);
                printf("doctor:%d ", data_global->results[i].receiving_doctor);
                printf("doctor_time: %ld\n", data_global->results[i].doctor_time.tv_sec);
            default:
                break;
        }
    }
    signal(SIGALRM,print_admission_status);
}


void signal_handlers(struct data_container* data, struct communication* comm, struct semaphores* sems){
    data_global = data;
    comm_global = comm;
    sems_global = sems;

    struct itimerval val;
    signal(SIGALRM,print_admission_status);

    val.it_interval.tv_sec = data->alarm_time;
    val.it_value.tv_sec = data->alarm_time;
    val.it_interval.tv_usec=0;
    val.it_value.tv_usec=0;
    setitimer(ITIMER_REAL, &val, 0);

    signal(SIGINT,signal_end);
}

void signal_end(){
    end_execution(data_global,comm_global,sems_global);
    exit(0);
}


