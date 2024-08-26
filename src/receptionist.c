/*
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "memory.h"
#include "main.h"
#include "receptionist.h"
#include "hosptime.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int count_receptionist_stats(struct data_container* data) {
    int count = 0;

    for (int i = 0; i < data->n_receptionists; i++) {
        count += data->receptionist_stats[i];
    }

    return count;
}

int execute_receptionist(int receptionist_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    struct admission *newAd = allocate_dynamic_memory(sizeof(struct admission));

    while (*data->terminate == 0){
        receptionist_receive_admission(newAd,data,comm,sems);
        printf("[Receptionist %d] Recebi a admissão %d!\n",receptionist_id,newAd->id);
        get_current_time(&newAd->receptionist_time);
        if(newAd->id !=-1){
            receptionist_process_admission(newAd, receptionist_id,data,sems);
            receptionist_send_admission(newAd,data,comm,sems);        
        }
    }
    return count_receptionist_stats(data); //numero de admissoes realizadas
}

void receptionist_receive_admission(struct admission* ad, struct data_container* data, struct communication* comm, struct semaphores* sems){
    //Caso data->terminate for 1 
    semaphore_lock(sems->terminate_mutex);
    if (*data->terminate == 1) {
        semaphore_unlock(sems->terminate_mutex);
        return;
    } 
    semaphore_unlock(sems->terminate_mutex);
    consume_begin(sems->patient_receptionist);
    read_patient_receptionist_buffer(comm->patient_receptionist,data->buffers_size,ad);
    consume_end(sems->patient_receptionist);

}

void receptionist_process_admission(struct admission* ad, int receptionist_id, struct data_container* data, struct semaphores* sems){
    //Alterar os dados
    ad->receiving_receptionist = receptionist_id;
    ad->status = 'R';

    semaphore_lock(sems->receptionist_stats_mutex);
    data->receptionist_stats[receptionist_id]++;
    semaphore_unlock(sems->receptionist_stats_mutex);

    //Atualizar a admission no data
    semaphore_lock(sems->results_mutex);
    data->results[ad->id] = *ad;
    semaphore_unlock(sems->results_mutex);
}

void receptionist_send_admission(struct admission* ad, struct data_container* data, struct communication* comm, struct semaphores* sems){
    produce_begin(sems->receptionist_doctor);
    write_receptionist_doctor_buffer(comm->receptionist_doctor, data->buffers_size, ad);
    produce_end(sems->receptionist_doctor);
}