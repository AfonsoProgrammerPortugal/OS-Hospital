/* 
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "main.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* format_time(struct timespec time){
    // Obtém o timestamp atual
    clock_gettime(CLOCK_REALTIME, &time);
    struct tm *local_time = localtime(&time.tv_sec);

    // Formata o timestamp
    static char timestamp[256];
    snprintf(timestamp, sizeof(timestamp), "%02d/%02d/%d_%02d:%02d:%02d.%03ld",
             local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900,
             local_time->tm_hour, local_time->tm_min, local_time->tm_sec, time.tv_nsec / 1000000);

    return timestamp;
}

void print_stats(struct data_container* data){
    FILE *stats_file = fopen(data->statistics_filename, "w");
    if (stats_file == NULL) {
        printf("Erro ao abrir o arquivo de estatisticas.\n");
        return;
    }

    fprintf(stats_file,"Process Statistics:\n");
    for (int i = 0; i < data->n_patients; i++)
    {
        fprintf(stats_file,"    Patient %d requested %d admissions!\n",i,data->patient_stats[i]);
    }
    for (int i = 0; i < data->n_receptionists; i++)
    {
        fprintf(stats_file,"    Receptionist %d forwarded %d admissions!\n",i,data->receptionist_stats[i]);
    }
    for (int i = 0; i < data->n_doctors; i++)
    {
        fprintf(stats_file,"    Doctor %d processed %d admissions!\n",i,data->doctor_stats[i]);
    }

    fprintf(stats_file,"\nAdmission Statistics:\n");
    long totalSecs;
    long totalNSecs;
    int i = 0;
    int finished = 0;
    while(data->results[i].id < data->max_ads && finished == 0){
        if (data->results[i].status == '\0'){
            finished = 1;
        }
        else{
            // Imprime as estatIsticas para o ficheiro stats.txt
            fprintf(stats_file,"\nAdmission: %d\n",data->results[i].id);
            fprintf(stats_file,"Status: %c\n",data->results[i].status);
            fprintf(stats_file,"Patient id: %d\n",data->results[i].receiving_patient);
            fprintf(stats_file,"Receptionist id: %d\n",data->results[i].receiving_receptionist);
            fprintf(stats_file,"Doctor id: %d\n",data->results[i].receiving_doctor);
            fprintf(stats_file,"Start time: %s\n",format_time(data->results[i].create_time));
            fprintf(stats_file,"Patient time: %s\n",format_time(data->results[i].patient_time));
            fprintf(stats_file,"Receptionist time: %s\n",format_time(data->results[i].receptionist_time));
            fprintf(stats_file,"Doctor time: %s\n",format_time(data->results[i].doctor_time));
            
            totalSecs = data->results[i].doctor_time.tv_sec - data->results[i].create_time.tv_sec;
            totalNSecs = (((data->results[i].doctor_time.tv_nsec - data->results[i].create_time.tv_nsec)/1000000)%1000);

            fprintf(stats_file,"Total time: %ld.%03ld\n\n",totalSecs,totalNSecs);
        }
        i++;
    }
    
    fclose(stats_file);
}











