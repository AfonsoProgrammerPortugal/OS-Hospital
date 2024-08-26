/* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include "main.h"
#include "synchronization.h"

#ifndef LOG_H_GUARD
#define LOG_H_GUARD

/*
* Função que cria o ficheiro que guarda a informacao sobre as operacoes realizadas
*/
void log_create(struct data_container* data);

/*
* Função que guarda num ficheiro a informacao sobre as operacoes realizadas
*/
void log_update(struct data_container* data, char* input, int* arguments);

#endif