#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "member.h"

Member *create_member(char *target)
{
    Member *m = calloc(1, sizeof(Member));

    int target_len = strlen(target);
    m->target = calloc(target_len + 1, sizeof(char));
    m->keys = calloc(target_len + 1, sizeof(char));

    strcpy(m->target, target);

    for (int i = 0; i < target_len; i++)
    {
        m->keys[i] = gen_rand_char();
    }

    return m;
}

double get_member_fitness(Member *m)
{
    int matches = 0;
    int target_len = strlen(m->target);

    for (int i = 0; i < target_len; i++)
    {
        if (m->target[i] == m->keys[i])
            matches++;
    }

    double fitness = (double)matches / target_len;
    return fitness;
}

Member *crossover_members(Member *ma, Member *mb)
{
    Member *child = create_member(ma->target);
    int target_len = strlen(ma->target);

    for (int i = 0; i < target_len; i++)
    {
        if (i % 2 == 0)
            child->keys[i] = ma->keys[i];
        else
            child->keys[i] = mb->keys[i];
    }

    return child;
}

void mutate_member(Member *m, double mutation_rate)
{
    int target_len = strlen(m->target);

    for (int i = 0; i < target_len; i++)
    {
        double r = rand_double();
        if (r < mutation_rate)
        {
            m->keys[i] = gen_rand_char();
        }
    }
}
