/*
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "memory.h"
#include "main.h"
#include "patient.h"
#include "hosptime.h"
#include "synchronization.h"
#include <stdio.h>

int count_patient_stats(struct data_container* data) {
    int count = 0;

    for (int i = 0; i < data->n_patients; i++) {
        count += data->patient_stats[i];
    }

    return count;
}

int execute_patient(int patient_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    struct admission *newAd = allocate_dynamic_memory(sizeof(struct admission));
    
    
    while (*data->terminate == 0){
        patient_receive_admission(newAd, patient_id, data,comm,sems);
        get_current_time(&newAd->patient_time);
        if(newAd->id != -1){
            printf("[Patient %d] Recebi a admissão %d!\n",patient_id,newAd->id);
            patient_process_admission(newAd,patient_id,data,sems);
            patient_send_admission(newAd,data,comm,sems);        
        }
        else{
            produce_end(sems->main_patient);
        }
    }
    return count_patient_stats(data); //numero de admissoes pedidas
}

void patient_receive_admission(struct admission* ad, int patient_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    semaphore_lock(sems->terminate_mutex);
    if (*data->terminate == 1) {
        semaphore_unlock(sems->terminate_mutex);
        return; 
    }
    semaphore_unlock(sems->terminate_mutex);
    consume_begin(sems->main_patient);
    read_main_patient_buffer(comm->main_patient,patient_id,data->buffers_size,ad);
    consume_end(sems->main_patient);
}

void patient_process_admission(struct admission* ad, int patient_id, struct data_container* data, struct semaphores* sems){
    //Alterar os dados
    ad->receiving_patient = patient_id;
    ad->status = 'P';

    semaphore_lock(sems->patient_stats_mutex);
    data->patient_stats[patient_id] = data->patient_stats[patient_id] + 1;
    semaphore_unlock(sems->patient_stats_mutex);
    //Atualizar a admission no data
    semaphore_lock(sems->results_mutex);
    data->results[ad->id] = *ad;
    semaphore_unlock(sems->results_mutex);
}

void patient_send_admission(struct admission* ad, struct data_container* data, struct communication* comm, struct semaphores* sems){
    produce_begin(sems->patient_receptionist);

    write_patient_receptionist_buffer(comm->patient_receptionist, data->buffers_size, ad);
    
    produce_end(sems->patient_receptionist);
}
