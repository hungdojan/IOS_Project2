/*
 * base.h
 * Reseni IOS-proj2 "Santa Claus problem", 20.04.21
 * Autor: Hung Do, VUT FIT
 * 
 * Hlavickovy soubor deklarujici struktury s globalnimi semafory a promennymi
 */
#ifndef __BASE_H__
#define __BASE_H__
#include <stdio.h>
#include <semaphore.h>

/**
 * @brief Struktura se sdilenymi semafory
 */
typedef struct sems{
    sem_t mutex;       /**< Semafor vzajemneho vylouceni */
    sem_t sem_santa;   /**< Santuv semafor */
    sem_t sem_elves;   /**< Semafor elfu */
    sem_t sem_rends;   /**< Semafor sobu */
    sem_t help;        /**< Blokada pri pomoci elfum */
    sem_t get_help;    /**< Blokada pri dostavani pomoci */
} Sems;

/**
 * @brief Struktura se globalnimi (sdilenymi) promennymi
 */
typedef struct glob {
    int n_elves;   /**< Pocet elfu pozadujici pomoc */
    int n_rends;   /**< Pocet sobu doma */
    int counter;   /**< Indikator poradi vypisu */
    int running;   /**< TRUE pokud je santa stale ve workshopu */
    int proc_done; /**< Pocet procesu, ktere jiz skoncili */
} Glob;

FILE *f;    /**< Soubor na zapis */
Glob *glob;
Sems *sems;

/**
 * @brief Inicializace semafory
 *
 * @param mutex_val     Vychozi hodnota semaforu MUTEX
 * @param santa_val     Vychozi hodnota semaforu SEM_SANTA
 * @param elves_val     Vychozi hodnota semaforu SEM_ELVES
 * @param rends_val     Vychozi hodnota semaforu SEM_RENDS
 * @param help_val      Vychozi hodnota semaforu HELP
 * @param get_help_val  Vychozi hodnota semaforu GET_HELP
 * @return Nulova hodnota, pokud inicializace probehla bez chyby
 */
int my_sems_init(int mutex_val, int santa_val, int elves_val,
              int rends_val, int help_val, int get_help_val);

/**
 * @brief Inicializace globalnich promennych
 * Hodnoty vychozich promennych jsou 0
 * @return Nulova hodnota, pokud inicializace probehla bez chyby
 */
int glob_var_init();

/**
 * @brief Uvolneni alokovanych pameti semaforu
 */
void my_sems_destroy();

/**
 * @brief Uvolneni alokovanych pameti globalnich promennych
 */
void glob_var_destoy();
#endif
/* base.h */
