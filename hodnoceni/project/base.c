/*
 * base.h
 * Reseni IOS-proj2 "Santa Claus problem", 20.04.21
 * Autor: Hung Do, VUT FIT
 * 
 * Inicializace a uklid semaforu a globalnich promennych
 */
#include "base.h"
#include <sys/mman.h>
#include <stdio.h>

#define PSHARED    1
#define SEM_ERROR -1

/**
 * @brief Alokuje sdilenou pamet
 *
 * @param size  Velikost alokovane pameti v baitech
 * @return Ukazatel na sdilenou pamet; NULL pri neuspechu
 */
static void *create_shm(size_t size)
{
    // nastaveni bitu pro viditelnost a moznosti cteni a zapisu
    int protect = PROT_READ  | PROT_WRITE;
    int mode    = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL, size, protect, mode, -1, 0);
}


int my_sems_init(int mutex_val, int santa_val, int elves_val,
              int rends_val, int help_val, int get_help_val)
{
    // Kontrola spravne inicializace
    if ((sems = create_shm(sizeof(Sems))) == NULL)        { goto err_struct_init;}
    if (sem_init(&sems->mutex    , PSHARED, mutex_val)    == SEM_ERROR) { goto err_mutex_init; }
    if (sem_init(&sems->sem_santa, PSHARED, santa_val)    == SEM_ERROR) { goto err_santa_init; }
    if (sem_init(&sems->sem_elves, PSHARED, elves_val)    == SEM_ERROR) { goto err_elves_init; }
    if (sem_init(&sems->sem_rends, PSHARED, rends_val)    == SEM_ERROR) { goto err_rends_init; }
    if (sem_init(&sems->help     , PSHARED, help_val)     == SEM_ERROR) { goto err_help_init;  }
    if (sem_init(&sems->get_help , PSHARED, get_help_val) == SEM_ERROR) { goto err_get_help_init;  }

    return 0;   // EXIT_SUCCESS

// Error-handeling
// Uklid vsech alokovanych pameti
err_get_help_init:
    sem_destroy(&sems->help);
err_help_init:
    sem_destroy(&sems->sem_rends);
err_rends_init:
    sem_destroy(&sems->sem_elves);
err_elves_init:
    sem_destroy(&sems->sem_santa);
err_santa_init:
    sem_destroy(&sems->mutex);
err_mutex_init:
    munmap(sems, sizeof(Sems));
err_struct_init:
    fprintf(stderr, "Neuspesna inicializace semaforu\n");
    return 1;   // EXIT_FAILURE
}

int glob_var_init()
{
    // tvorba pameti
    if ((glob = create_shm(sizeof(Glob))) == NULL)      { goto err_struct_init; }

    // nastaveni vychozich hodnot
    glob->n_elves   = 0;
    glob->n_rends   = 0;
    glob->counter   = 0;
    glob->running   = 0;
    glob->proc_done = 0;
    return 0;   // EXIT_SUCCESS


// Error-handeling
// Uklid vsech alokovanych pameti
err_struct_init: 
    fprintf(stderr, "Neuspesne vytvoreni sdilene pameti pro glob. promenne.\n");
    return 1;   // EXIT_FAILURE
}

void my_sems_destroy()
{
    sem_destroy(&sems->get_help);
    sem_destroy(&sems->help);
    sem_destroy(&sems->sem_rends);
    sem_destroy(&sems->sem_elves);
    sem_destroy(&sems->sem_santa);
    sem_destroy(&sems->mutex);
    munmap(sems, sizeof(Sems));
}

void glob_var_destoy()
{
    munmap(glob, sizeof(Glob));
}
/* base.c */
