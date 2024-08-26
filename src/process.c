/*
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "../include/memory.h"
#include "../include/main.h"
#include "../include/process.h"
#include "../include/patient.h"
#include "../include/receptionist.h"
#include "../include/doctor.h"
#include "../include/synchronization.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int launch_patient(int patient_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    int pid = fork();

    if (pid == -1) { /* Houve algum erro */
        perror("launch_patient");
        exit(1);
    }

    if (pid == 0) { /* Processo filho */
        execute_patient(patient_id, data, comm, sems);
        exit(0);
    }

    else { /* Processo pai*/
        return pid;
    }
}

int launch_receptionist(int receptionist_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    int pid = fork();

    if (pid == -1) { /* Houve algum erro */
        perror("launch_receptionist");
        exit(1);
    }

    if (pid == 0) { /* Processo filho */
        execute_receptionist(receptionist_id, data, comm, sems);
        exit(0);
    }

    else { /* Processo pai*/
        return pid;
    }
}

int launch_doctor(int doctor_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    int pid = fork();

    if (pid == -1) { /* Houve algum erro */
        perror("launch_doctor");
        exit(1);
    }

    if (pid == 0) { /* Processo filho */
        execute_doctor(doctor_id, data, comm, sems);
        exit(0);
    }

    else { /* Processo pai*/
        return pid;
    }
}

int wait_process(int process_id){
    int status;
    pid_t processo = waitpid(process_id, &status, 0);
    
    if (processo == -1) { /*Houve um erro*/
        perror("wait_process");
        return -1;
    }

    else if (WIFEXITED(status)) { /*processo terminou normalmente*/
        return WEXITSTATUS(status);
    }

    else { /*erro na terminação*/
        return -1;
    }
}