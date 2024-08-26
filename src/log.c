/* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void log_create(struct data_container* data){
    FILE *log_file = fopen(data->log_filename, "w");
    if (log_file == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }    
    fclose(log_file);
}

void log_update(struct data_container* data, char* input, int* arguments) {
    // Abre o arquivo de log especificado na estrutura data_container
    FILE *log_file = fopen(data->log_filename, "a");
    if (log_file == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }

    // Obtém o timestamp atual
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);
    struct tm *local_time = localtime(&current_time.tv_sec);

    // Formata o timestamp
    char timestamp[256];
    snprintf(timestamp, sizeof(timestamp), "%02d/%02d/%d_%02d:%02d:%02d.%03ld",
             local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900,
             local_time->tm_hour, local_time->tm_min, local_time->tm_sec, current_time.tv_nsec / 1000000);

    // Escreve no arquivo de log
    if (strcmp(input, "ad") == 0) {
        fprintf(log_file, "%s %s %d %d\n", timestamp, input, arguments[0], arguments[1]);
    } 
    else if (strcmp(input, "info") == 0) {
        fprintf(log_file, "%s %s %d\n", timestamp, input, arguments[0]);
    }
    else {
        fprintf(log_file, "%s %s\n", timestamp, input);
    }
    fclose(log_file);
}