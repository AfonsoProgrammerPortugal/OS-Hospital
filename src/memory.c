/*
* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#include <stdio.h>
#include "../include/memory.h"
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

void* create_shared_memory(char* name, int size){
    int shm = shm_open(name, O_CREAT | O_RDWR , S_IRUSR | S_IWUSR);
    ftruncate(shm, size); 
    if(shm == -1){
        perror ("create_shared_memory_1");
        exit(1);
    }
    // com a notacao NULL e o SO que determina automaticamente o endereco
    // inicial da projecao
    void* ptrSharedMemory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
    if(ptrSharedMemory == MAP_FAILED){
        perror("create_shared_memory_2");
        exit(1);
    }
    memset(ptrSharedMemory,0,size);
    return ptrSharedMemory;
}

void* allocate_dynamic_memory(int size){
    //aloca memOria dinAmica com size
    int *ptr = malloc(size);
    //Houve erro a alocar
    bzero(ptr,size);
    return ptr;
}

void destroy_shared_memory(char* name, void* ptr, int size){
    int statusMap = munmap(ptr, size); 

    if(statusMap == -1){
        perror("destroy_shared_memory_1");
        exit(1);
    }

    int statusPointer = shm_unlink(name);

    if(statusPointer == -1){
        perror("destroy_shared_memory_2");
        exit(1);
    }
}

void deallocate_dynamic_memory(void* ptr){
    if (ptr != NULL){
        free(ptr);
        ptr = NULL;
    }
}

void write_main_patient_buffer(struct circular_buffer* buffer, int buffer_size, struct admission* ad){
    //Verifica se o buffer estA cheio
    if ((buffer->ptrs->in+1) % buffer_size != buffer->ptrs->out) {
        buffer->buffer[buffer->ptrs->in] = *ad;
        buffer->ptrs->in = (buffer->ptrs->in + 1) % buffer_size;
    }
}

void write_patient_receptionist_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct admission* ad){
    int i = 0;
    int written = 0;
    /* Itera pelo buffer, procurando pelas posiCOes vazias
    *  Verifica se Já escreveu ou se ultrapassou o buffer_size
    */
    while (written != 1 && i+1 <= buffer_size) {
        //Verifica se a position estA livre
        if (buffer->ptrs[i] == 0){
            buffer->buffer[i] = *ad;
            buffer->ptrs[i] = 1;
            written = 1;
        }
        i++;
    }
}

void write_receptionist_doctor_buffer(struct circular_buffer* buffer, int buffer_size, struct admission* ad){
    //Verifica se o buffer estA cheio
    if ((buffer->ptrs->in+1) % buffer_size != buffer->ptrs->out) {
        buffer->buffer[buffer->ptrs->in] = *ad;
        buffer->ptrs->in = (buffer->ptrs->in + 1) % buffer_size;
    }
}

void read_main_patient_buffer(struct circular_buffer* buffer, int patient_id, int buffer_size, struct admission* ad){
    //Verifica se ad foi pedida pelo paciente
    if (buffer->ptrs->in != buffer->ptrs->out && buffer->buffer[buffer->ptrs->out].requesting_patient == patient_id) {
        *ad = buffer->buffer[buffer->ptrs->out];
        buffer->ptrs->out = buffer->ptrs->out+1 % buffer_size;
    }
    //Caso nAo tenha lido uma ad disponIvel
    else {
        ad->id = -1;
    }
}

void read_patient_receptionist_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct admission* ad){
    int i = 0;
    /* Itera pelo buffer, procurando pelas posiCOes vazias
    *  Verifica se Já escreveu ou se ultrapassou o buffer_size
    */
    while (i < buffer_size) {
        //Verifica se a position estA livre
        if (buffer->ptrs[i] == 1){           
            *ad = buffer->buffer[i];
            buffer->ptrs[i] = 0;
            return;
        }
        i++;
    }
    ad->id = -1;
}

void read_receptionist_doctor_buffer(struct circular_buffer* buffer, int doctor_id, int buffer_size, struct admission* ad){
    //Itera pelo ads contidos no buffer
    //Verifica se o doutor foi pedido
    if (buffer->ptrs->in != buffer->ptrs->out && buffer->buffer[buffer->ptrs->out].requested_doctor == doctor_id) {
        *ad = buffer->buffer[buffer->ptrs->out];
        buffer->ptrs->out = (buffer->ptrs->out+1) % buffer_size;
    }
    //Caso nAo tenha lido uma ad disponIvel
    else {
        ad->id = -1;
    }
}