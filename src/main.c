#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "population.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    char target[] = "Target";
    Population *p = create_population(1000, 0.01, target);
    evolve(p);
    cleanup(p);

    return 0;
}
