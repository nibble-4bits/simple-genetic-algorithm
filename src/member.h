#ifndef MEMBER_H
#define MEMBER_H

typedef struct
{
    char *target;
    char *keys; // ADN
} Member;

Member *create_member(char *target);
double get_member_fitness(Member *m);
Member *crossover_members(Member *ma, Member *mb);
void mutate_member(Member *m, double mutation_rate);

#endif // MEMBER_H
