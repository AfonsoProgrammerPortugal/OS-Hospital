/*
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "synchronization.h"
#include <fcntl.h>

/* Função que cria um novo semáforo com nome name e valor inicial igual a
* value. Pode concatenar o resultado da função getpid() a name, para tornar
* o nome único para o processo.
*/
sem_t * semaphore_create(char* name, int value) {
    sem_t *sem;
    char nomeUnico[256];
    sprintf(nomeUnico, "%s%d", name, getpid());
    sem = sem_open(nomeUnico, O_CREAT, 0xFFFFFFFF, value);
    if (sem == SEM_FAILED){
        perror("full");
        exit(6);
    }
    return sem;
}

/* Função que destroi o semáforo passado em argumento.
*/
void semaphore_destroy(char* name, sem_t* semaphore) {
    char nomeUnico[256];
    sprintf(nomeUnico, "%s%d", name, getpid());

    if (sem_close(semaphore) == -1){
        perror("sem_close");
    }
    if (sem_unlink(nomeUnico) == -1){
        perror("sem_unlink");
    }
}

/* Função que inicia o processo de produzir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_begin(struct prodcons* pc) {
    sem_wait(pc->empty);
    sem_wait(pc->mutex);
}

/* Função que termina o processo de produzir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_end(struct prodcons* pc) {
    sem_post(pc->mutex);
    sem_post(pc->full);
}

/* Função que inicia o processo de consumir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_begin(struct prodcons* pc) {
    sem_wait(pc->full);
    sem_wait(pc->mutex);
}

/* Função que termina o processo de consumir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_end(struct prodcons* pc) {
    sem_post(pc->mutex);
    sem_post(pc->empty);
}

/* Função que faz wait a um semáforo.
*/
void semaphore_lock(sem_t* sem) {
    if (sem_wait(sem) == -1){
        perror("sem_wait");
    }
}

/* Função que faz post a um semáforo.
*/
void semaphore_unlock(sem_t* sem) {
    if (sem_post(sem) == -1){
        perror("sem_post");
    }
}