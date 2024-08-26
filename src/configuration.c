/* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "main.h"
#include "configuration.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void config_args(FILE* config_text, struct data_container* data) {
    // Guardar cada linha nas respetivas variAveis do data
    fscanf(config_text,"%d",&data->max_ads);
    fscanf(config_text,"%d",&data->buffers_size);
    fscanf(config_text,"%d",&data->n_patients);
    fscanf(config_text,"%d",&data->n_receptionists);
    fscanf(config_text,"%d",&data->n_doctors);
    fscanf(config_text,"%s",data->log_filename);
    fscanf(config_text,"%s",data->statistics_filename);
    fscanf(config_text,"%d",&data->alarm_time);
}