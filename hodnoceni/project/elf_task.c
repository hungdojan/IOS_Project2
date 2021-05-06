/*
 * elf_task.c
 * Reseni IOS-proj2 "Santa Claus problem", 20.04.21
 * Autor: Hung Do, VUT FIT
 * 
 * Deklarace procesu elfa
 */
#include "base.h"
#include "tasks.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

void elf_task(int id, int te) 
{
    time_t t;
    srand((unsigned)time(&t) * getpid());

    // elf jde poprve do prace
    sem_wait(&sems->mutex);
    fprintf(f,"%d: Elf %d: started\n", (glob->counter)++, id);
    fflush(f);
    sem_post(&sems->mutex);

    while (glob->running)
    {
        // time
        if (te != 0)
            usleep((rand() % te) * 1000);

        sem_wait(&sems->mutex);
        fprintf(f,"%d: Elf %d: need help\n", (glob->counter)++, id);
        fflush(f);
        sem_post(&sems->mutex);

        // elf potrebuje pomoc
        sem_wait(&sems->sem_elves);

        // pravo na upravy hodnoty
        sem_wait(&sems->mutex);
        glob->n_elves += 1;
        // dostatecny pocet elfu jiz ceka pred workshopem
        if (glob->n_elves == 3)
        {
            if (glob->running)
                sem_post(&sems->sem_santa);
            else
                sem_post(&sems->sem_elves);
        }
        else
            sem_post(&sems->sem_elves);
        sem_post(&sems->mutex);


        // ceka na pomoc
        if (glob->running)
        {
            // cekaji na santu nez se probudi
            sem_wait(&sems->help);

            // pokud santa uz uzavrel workshop
            if (glob->running == 0)
            {
                sem_post(&sems->help);  // metoda turnstile
                break;
            }

            sem_wait(&sems->mutex);
            fprintf(f,"%d: Elf %d: get help\n", (glob->counter)++, id);
            fflush(f);
            // uvolneni mista pro 
            glob->n_elves -= 1;
            if (glob->n_elves == 0)
            {
                sem_post(&sems->sem_elves);
                // anti sob moznost
                sem_post(&sems->sem_santa);
                sem_post(&sems->get_help);
            }
            sem_post(&sems->mutex);
        }
        else
            break;
    }

    // odchod na dovolenou
    sem_wait(&sems->mutex);
    fprintf(f,"%d: Elf %d: taking holidays\n", (glob->counter)++, id);
    fflush(f);
    sem_post(&sems->mutex);
    sem_post(&sems->sem_elves);   // odblokovani tech co potrebuji pomoct
    // sem_post(&sems->help);        // odblokovani tech co cekaji na santu
}
/* elf_task.c */
