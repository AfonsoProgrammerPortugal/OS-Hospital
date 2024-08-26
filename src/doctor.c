/*
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "memory.h"
#include "main.h"
#include <stdio.h>
#include "doctor.h"
#include "hosptime.h"

int count_doctor_stats(struct data_container* data) {
    int count = 0;

    for (int i = 0; i < data->n_doctors; i++) {
        count += data->doctor_stats[i];
    }

    return count;
}

int execute_doctor(int doctor_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    struct admission *newAd = allocate_dynamic_memory(sizeof(struct admission));
    
    while (*data->terminate == 0){
        doctor_receive_admission(newAd, doctor_id, data,comm,sems);
        get_current_time(&newAd->doctor_time);
        if(newAd->id !=-1){
            doctor_process_admission(newAd,doctor_id,data,sems);
        }
        
    }
    return count_doctor_stats(data); //numero de consultas realizadas
}

void doctor_receive_admission(struct admission* ad, int doctor_id, struct data_container* data, struct communication* comm, struct semaphores* sems){
    semaphore_lock(sems->terminate_mutex);
    if (*data->terminate == 1) {
        semaphore_unlock(sems->terminate_mutex);
        return; // ja nao ha mais admissoes para admitir
    }
    semaphore_unlock(sems->terminate_mutex);
   
    consume_begin(sems->receptionist_doctor);
    read_receptionist_doctor_buffer(comm->receptionist_doctor, doctor_id, data->buffers_size, ad);
    consume_end(sems->receptionist_doctor);
}

void doctor_process_admission(struct admission* ad, int doctor_id, struct data_container* data, struct semaphores* sems){
    //AlteraCAo do receiving_doctor
    ad->receiving_doctor = doctor_id;
    
    //VariAveis
    semaphore_lock(sems->doctor_stats_mutex);
    int *docStats = data->doctor_stats;
    semaphore_unlock(sems->doctor_stats_mutex);

    //Verifica se existe espaCo para a admission
    //Caso tenha espaCo
    if (ad->id < data->max_ads) {
        ad->status = 'A';

        semaphore_lock(sems->doctor_stats_mutex);
        printf("[Doctor %d] Recebi a admissão %d!\n",doctor_id,ad->id);
        docStats[doctor_id]++;
        semaphore_unlock(sems->doctor_stats_mutex);

    }
    //Caso nAo tenha espaCo
    else {
        ad->status = 'N';
    }
    //Atualizar a admission no data
    semaphore_lock(sems->results_mutex);
    data->results[ad->id] = *ad;
    semaphore_unlock(sems->results_mutex);
}