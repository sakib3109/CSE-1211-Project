#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// generating random numbers
// These random numbers are used to generate random characters to create the puzzle.

int randomNumber()
{
    srand(time(NULL));

    int num = rand();

    return num;
}