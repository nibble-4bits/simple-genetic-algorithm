#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "member.h"
#include "population.h"

Population *create_population(int size, double mutation_rate, char *target)
{
    Population *p = calloc(1, sizeof(Population));

    int target_len = strlen(target);
    p->members = calloc(size, sizeof(Member));
    p->size = size;
    p->target = calloc(target_len + 1, sizeof(char));
    p->mutation_rate = mutation_rate;
    p->next_members = calloc(size, sizeof(Member));
    p->mating_pool = calloc(size, sizeof(int));

    for (int i = 0; i < p->size; i++)
    {
        Member *m = create_member(target);
        p->members[i] = *m;
        p->next_members[i] = *m;
    }

    strcpy(p->target, target);

    return p;
}

double calc_fitness_avg(Population *p)
{
    double total_fitness = 0;
    double fitness_avg = 0;

    for (int i = 0; i < p->size; i++)
    {
        total_fitness += get_member_fitness(&p->members[i]);
    }

    fitness_avg = total_fitness / p->size;

    return fitness_avg;
}

void select_mating_pool(Population *p)
{
    double fitness_avg = calc_fitness_avg(p);
    int pool_idx = 0;

    for (int i = 0; i < p->size; i++)
    {
        Member m = p->members[i];
        double m_fitness = get_member_fitness(&m);
        if (m_fitness > fitness_avg)
        {
            p->mating_pool[pool_idx] = i;
            pool_idx++;
        }
    }
    p->mating_pool_size = pool_idx;

    if (p->mating_pool_size == 0)
    {
        int fittest_idx = get_fittest(p);
        p->mating_pool[pool_idx] = fittest_idx;
        p->mating_pool_size = 1;
    }
}

void reproduce(Population *p)
{
    for (int i = 0; i < p->size; i++)
    {
        int ma_idx = rand_int(0, p->mating_pool_size - 1);
        int mb_idx = rand_int(0, p->mating_pool_size - 1);

        Member ma = p->members[p->mating_pool[ma_idx]];
        Member mb = p->members[p->mating_pool[mb_idx]];

        Member *child = crossover_members(&ma, &mb);
        mutate_member(child, p->mutation_rate);

        strcpy(p->next_members[i].target, child->target);
        strcpy(p->next_members[i].keys, child->keys);

        free(child->keys);
        free(child->target);
        free(child);
    }

    memcpy(p->members, p->next_members, p->size * sizeof(Member));
}

void evolve(Population *p)
{
    int target_len = strlen(p->target);
    char *fittest_keys = calloc(target_len + 1, sizeof(char));
    int generation = 1;

    do
    {
        int fittest_idx = get_fittest(p);
        Member fittest = p->members[fittest_idx];
        strcpy(fittest_keys, fittest.keys);
        printf("%d\t%s\n", generation, fittest_keys);

        select_mating_pool(p);
        reproduce(p);

        generation++;
    } while (strcmp(p->target, fittest_keys) != 0);

    free(fittest_keys);
}

int get_fittest(Population *p)
{
    int max_score_idx = 0;
    for (int i = 1; i < p->size; i++)
    {
        double fitness_score = get_member_fitness(&p->members[i]);
        double max_fitness_score = get_member_fitness(&p->members[max_score_idx]);

        if (fitness_score > max_fitness_score)
        {
            max_score_idx = i;
        }
    }

    return max_score_idx;
}

void cleanup(Population *p)
{
    for (int i = 0; i < p->size; i++)
    {
        free(p->members[i].keys);
        free(p->members[i].target);
    }

    free(p->target);
    free(p->mating_pool);
    free(p->members);
    free(p->next_members);
    free(p);
}