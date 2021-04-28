/*
 * santa_task.c
 * Reseni IOS-proj2 "Santa Claus problem", 20.04.21
 * Autor: Hung Do, VUT FIT
 * 
 * Deklarace Santova procesu
 */
#include "base.h"
#include "tasks.h"
#include <stdio.h>
#include <unistd.h>

void santa_task(int n_rendeers) 
{
    while (glob->running)
    {
        // santa jde spat
        sem_wait(&sems->mutex);
        fprintf(f,"%d: Santa: going to sleep\n", (glob->counter)++);
        fflush(f);
        sem_post(&sems->mutex);

        sem_wait(&sems->sem_santa);
        // santa je probuzen

        sem_wait(&sems->mutex);
        // pokud jsou vsichni soby doma
        if (glob->n_rends == 0)
        {
            fprintf(f,"%d: Santa: closing workshop\n", (glob->counter)++);
            fflush(f);

            for (int i = 0; i < n_rendeers; i++)
                sem_post(&sems->sem_rends);   // odstraneni bariery

            // odchazi z workshopu
            glob->running = 0;
        }
        else if (glob->n_elves == NOF_ELVES)
        {
            fprintf(f,"%d: Santa: helping elves\n", (glob->counter)++);
            fflush(f);
            sem_post(&sems->mutex);
            for (int i = 0; i < NOF_ELVES; i++)
                sem_post(&sems->help);       // otevreni bariery pro elfy

            sem_wait(&sems->sem_santa);
            sem_wait(&sems->get_help);       // ochrana proti sobum

            sem_wait(&sems->mutex);
        }
        sem_post(&sems->mutex);
    }

    // ceka nez vsechni soby se zaprou
    sem_wait(&sems->sem_santa);
    // while (glob->n_rends != n_rendeers) usleep(1);

    sem_wait(&sems->mutex);
    fprintf(f,"%d: Santa: Christmas started\n", (glob->counter)++);
    fflush(f);
    sem_post(&sems->mutex);

    // hlasi 3 elfum cekajici pred workshopem
    // ze uz muzou jit na dovolenou
    sem_post(&sems->help);
}
/* santa_task.c */
