#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SumUpto(int number)
{
    int i, sum = 0;
    for(i = 0; i < number; i++) sum += i;
    printf("The sum is %d\n",sum);
}

int main(int argc, char *argv[])
{
    clock_t start, end;
    start = clock();
    double runtime;
    int number, p;
    if(argc == 1)
    {
        number = 0;
        p = 2;
    }
    else
    {
        number = atoi(argv[1]);
        p = atoi(argv[2]);
    }
    int i;
    for(i = 0; i <= p; i++)
    {
        SumUpto(number);
    }

    end = clock();

    runtime = 1000*((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f milliseconds\n", runtime);
    return 0;
}