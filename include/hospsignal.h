/* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#ifndef HOSPSIGNAL_H_GUARD
#define HOSPSIGNAL_H_GUARD

#include "memory.h"
#include "synchronization.h"

/*
 * Função que imprime o estado atual de todas as admissões, incluindo as que já foram finalizadas
 * pelos médicos e as que ainda estão em andamento.
*/
void print_admission_status();

/*
 * Função que interrompe a execução do programa, ao capturar o sinal de interrupção do programa 
 * (SIGINT - ativado pela combinação de teclas CTRL-C). Deve proceder-se à invocação da função 
 * end_execution e garantir que tanto o processo pai como os processos filhos capturam o sinal. 
 * Para além disso, arma um alarme que em certos intervalos de tempo verifica e escreve para o ecrã 
 * o estado atual de todas as admissões.
*/
void signal_end();

/*
 * Função que trata de preparar os signal handlers.
*/
void signal_handlers(struct data_container* data, struct communication* comm, struct semaphores* sems);

#endif
