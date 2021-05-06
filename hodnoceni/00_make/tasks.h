/*
 * task.h
 * Reseni IOS-proj2 "Santa Claus problem", 20.04.21
 * Autor: Hung Do, VUT FIT
 * 
 * Prototypy funkci dilcich procesu
 */
#ifndef __TASKS_H__
#define __TASKS_H__

#define NOF_ELVES 3 // pocet pracujicich elfu

/**
 * @brief Santuv proces
 */
void santa_task(int n_rendeers);

/** 
 * @brief Elfuv proces
 *
 * @param id    Poradi elfa
 * @param te    Doba uspani
 */
void elf_task(int id, int te);

/** 
 * @brief Sobuv proces
 *
 * @param id            Poradi soba
 * @param n_rendeers    Pocet sobu
 * @param tr            Doba uspani
 */
void rendeer_task(int id, int n_rendeers, int tr);
#endif
/* tasks.h */
