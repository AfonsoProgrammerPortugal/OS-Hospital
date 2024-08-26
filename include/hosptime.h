/* Grupo SO-024
* Afonso Santos - fc59808
* Madalena Machado - fc59858
* Liliana Valente - fc59846
*/

#ifndef HOSPTIME_H
#define HOSPTIME_H

#include <time.h>
#include "memory.h"
#include "main.h"
/*
 * Funcao que retorna o instante temporal que foi invocada
*/
void get_current_time(struct timespec *time);

#endif