#ifndef POPULATION_H
#define POPULATION_H

#include "member.h"

typedef struct
{
    Member *members;
    int size;
    char *target;
    double mutation_rate;
    Member *next_members;
    int *mating_pool;
    int mating_pool_size;
} Population;

Population *create_population(int size, double mutation_rate, char *target);
double calc_fitness_avg(Population *p);
void select_mating_pool(Population *p);
void reproduce(Population *p);
void evolve(Population *p);
int get_fittest(Population *p);
void cleanup(Population *p);

#endif // POPULATION_H