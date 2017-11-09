#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


void *SumUpto(int *number)
{
    int i;
    long sum = 0;
    for(i = 0; i < *number; i++) sum += i;
}

int main(int argc, char *argv[])
{
    clock_t start, end;

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

    pthread_t thread[p];
    start = clock();
    for(i = 0; i <= p; i++)
    {
        pthread_create(&thread[i], NULL, SumUpto, &number);
    }

    for(i = 0; i < p;  i++)
    {
        pthread_join(&thread[i], NULL);
    }
    end = clock();

    runtime = 1000*((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f milliseconds\n", runtime);
    return 0;
}