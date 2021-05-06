/*
 * rendeer_task.c
 * Reseni IOS-proj2 "Santa Claus problem", 20.04.21
 * Autor: Hung Do, VUT FIT
 * 
 * Deklarace sobiho procesu
 */
#include "base.h"
#include "tasks.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

void rendeer_task(int id, int n_rendeers, int tr)
{
    time_t t;
    srand((unsigned) time(&t) * getpid());
    // sob jde na dovolenou
    sem_wait(&sems->mutex);
    fprintf(f,"%d: RD %d: rstarted\n", (glob->counter)++, id);
    fflush(f);
    sem_post(&sems->mutex);

    // time
    if (tr > 1)
    {
        int half_time = tr / 2;
        int milSec = (rand() % half_time + half_time);  // nahodne vygeneruje <t/2; t>
        usleep(milSec * 1000);
    }

    // sob se vratil z dovolene
    sem_wait(&sems->mutex);
    fprintf(f,"%d: RD %d: return home\n", (glob->counter)++, id);
    fflush(f);
    glob->n_rends -= 1;
    if (glob->n_rends == 0)
        sem_post(&sems->sem_santa);
    sem_post(&sems->mutex);

    // sob ceka nez prijdou vsichni (bariera)
    sem_wait(&sems->sem_rends);
    // sem_post(&sems->sem_rends);   // metoda turniketu

    // sob se necha zaprit
    sem_wait(&sems->mutex);
    fprintf(f,"%d: RD %d: get hitched\n", (glob->counter)++, id);
    fflush(f);
    glob->n_rends += 1;

    // vsichni sobi jsou zaprazeni
    if (glob->n_rends == n_rendeers)
        sem_post(&sems->sem_santa);

    sem_post(&sems->mutex);
}
/* rendeer_task.c */
