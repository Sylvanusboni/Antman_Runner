#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    double x = atof(av[1]);
    printf("%f    %f\n", round(x), ceilf(x));
}
