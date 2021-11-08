#include <stdlib.h>
#include "util.h"

int rand_int(int min, int max)
{
    int num = (rand() % (max - min + 1)) + min;
    return num;
}

double rand_double()
{
    double num = (double)rand() / RAND_MAX;
    return num;
}

char gen_rand_char()
{
    char c = (char)rand_int(32, 126);
    return c;
}
