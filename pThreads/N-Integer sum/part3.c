#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;
int rowCounter = 0;
int* m;
int sliceSize;
pthread_mutex_t m1;
int numC[10];
int (*numCount)[10] = &numC;

void createMatrix()
{
    printf("Creating Matrix:\n");
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            *((m + n*i) + j) = (int)rand()%10;
            //printf("%d  ", (*p)[i][j]);
        }
        //printf("\n");
    }
    printf("\n\n");
}

void showMatrix()
{
    printf("Showing Matrix:\n");
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d  ", *((m + n*i) + j));
        }
        printf("\n");
    }
    printf("\n\n");
}


void updateCount(int value)
{
    //printf("\n Value is : %d", value);
    switch(value)
    {
        case 0:
            (*numCount)[0]++;
            break;
        case 1:
            (*numCount)[1]++;
            break;
        case 2:
            (*numCount)[2]++;
            break;
        case 3:
            (*numCount)[3]++;
            break;
        case 4:
            (*numCount)[4]++;
            break;
        case 5:
            (*numCount)[5]++;
            break;
        case 6:
            (*numCount)[6]++;
            break;
        case 7:
            (*numCount)[7]++;
            break;
        case 8:
            (*numCount)[8]++;
            break;
        case 9:
            (*numCount)[9]++;
            break;
        default:
            break;
    }


}


void *countRowElements(void *number)
{
    int *temp = (int*)number;
    int threadNumber = *temp;
    printf("Execution here!\n");
    printf("ThreadNumber: %d\n", threadNumber);
    //printf("N is: %d\n", n);

    if(rowCounter > n)
    {
        return NULL;
    }
    int min = rowCounter;


    rowCounter += sliceSize;
    if(n - rowCounter < n%rowCounter)
    {
        rowCounter = n;
    }
    printf("RowCounter: %d\n", rowCounter);
    int max = rowCounter;
    printf("Max: %d Min: %d\n", min, max);
    pthread_mutex_lock(&m1);
    rowCounter += sliceSize;
    rowCounter++;
    int v;
    for (int i = min; i <= max; i++)
    {
        for (int j = 0; j < n; j++)
        {
            v = *((m + n*i) + j);
            printf("Value: %d\n", v);
            updateCount(v);
        }
    }
    pthread_mutex_unlock(&m1);
}




void showCounts(int (*v)[10])
{
    printf("\n Show counts \n");
    int i;
    for (i=0; i<10; i++)
    {
        printf("%d: %d times\n", i, (*v)[i]);
    }
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int p;
    if(argc <= 2)
    {
        n = 0;
        p = 0;
        printf("Enter som values");
        return 0;
    }
    else
    {
        n = atoi(argv[1]);
        p = atoi(argv[2]);
    }

    sliceSize = (int)(n/p);
    int start;
    //Array banavano
    m=(int *) malloc(n*n*sizeof(int));

    createMatrix();
    showMatrix();
    pthread_mutex_init(&m1, NULL);
    pthread_t thread[p];
    int i;
    for(i = 0; i < p; i++)
    {
        pthread_create(&thread[i], NULL, countRowElements, &i);
    }

    for(i = 0; i < p;  i++)
    {
        pthread_join(&thread[i], NULL);
    }

    showCounts(numCount);
    return 0;
}