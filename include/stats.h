/* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#ifndef STATS_H_GUARD
#define STATS_H_GUARD

#include "sys/types.h"
#include "memory.h"
#include "synchronization.h"

/*
* Função que converte um tempo "raw" num formato que indique o dia, mês, ano, hora, minuto, 
* segundo e milissegundo , usando a função localtime da biblioteca time.h.
*/
char* format_time(struct timespec time);

/*
* Função que imprime as estatísticas finais do hOSpital, que inclui as estatísticas dos vários processos
* (pacientes, rececionistas, médicos) e das várias admissões.
*/
void print_stats(struct data_container* data);

#endif