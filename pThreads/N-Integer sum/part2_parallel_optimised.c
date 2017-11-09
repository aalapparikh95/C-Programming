#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int numberIndex = 0;
int numThreads = 2;
pthread_mutex_t m1,m2;
long sum = 0;

void *SumUpto(void *arg)
{
    int *number = (int *)arg;
    int n = *number;
    int i;
    long threadSum = 0;


    pthread_mutex_lock(&m1);
        int min = numberIndex;
        if(min > n)
        {
            return NULL;
        }
        numberIndex += (int)n/numThreads;

        if(n - numberIndex < n%numThreads)
        {
            numberIndex = n;
        }
        int max = numberIndex;
        numberIndex++;
    pthread_mutex_unlock(&m1);

    //printf("New numberIndex: %d\n", numberIndex);

    //pthread_mutex_unlock(&m);
    for(i = min; i <= max; i++)
    {
        threadSum += i;
    }

    pthread_mutex_lock(&m2);
        sum += threadSum;
    pthread_mutex_unlock(&m2);

    //printf("From %d to %d: Sum is %d\n", min, max, threadSum);
    //printf("Global Sum is : %d\n", sum);
}

int main(int argc, char *argv[])
{
    clock_t start, end;
    double runtime;
    int number;
    //printf("%lu", sizeof(int));
    int p;
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
    numThreads = p;
    int i;
    pthread_mutex_init(&m1, NULL);
    pthread_mutex_init(&m2, NULL);

    pthread_t thread[p];
    start = clock();
    for(i = 0; i < p; i++)
    {
        pthread_create(&thread[i], NULL, SumUpto, &number);
        printf("Thread %d\n",i);
    }

    for(i = 0; i < p;  i++)
    {
        pthread_join(&thread[i], NULL);
    }
    end = clock();

    runtime = 1000*((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sum of numbers is: %ld\n", sum);
    printf("Execution time: %f milliseconds\n", runtime);
    return 0;
}