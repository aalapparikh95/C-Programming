#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//prototype
double getRand(double min, double max);
double** d;
double** a;
double** b;
double** c;
int sliceSize;
int matrixSize;

#include<sys/time.h>

struct timeval tm1, tm2;

void start()
{
    gettimeofday(&tm1, NULL);
}

void stop()
{
    gettimeofday(&tm2, NULL);
    unsigned long long t = ((tm2.tv_sec - tm1.tv_sec) * 1000000) + (tm2.tv_usec - tm1.tv_usec);
    printf("\n%llu microseconds occured\n",t);
}

void *matmul(void *start)
{
    int rowStart = (int*)start;

    //printf("Here row Starts with %d\n", rowStart);
    int rowEnd = rowStart + sliceSize;
    //printf("Here threadEnd is %d\n", rowEnd);
    //printf("Execution here!\n");

    //printf("N is: %d\n", n);

    if(matrixSize-rowEnd < sliceSize)
    {
        rowEnd = matrixSize;
    }

    int i, j, k;

    printf("threadStart: %d\t threadEnd: %d\n", rowStart, rowEnd);

    for(i = rowStart; i < rowEnd; i++)
    {
        //printf("\n II %d", i);

        for(j = 0; j < matrixSize; j++)
        {
            for(k = 0; k < matrixSize; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
            //printf("Value: %d\n", v);
        }

    }
}


int main(int argc, char*argv[])
{
    start();
    if(argc<2)
    {
        perror("\nUsage ./generateInput <squareMatrixSize>\n");
        exit(-1);
    }
    FILE *fp;
    matrixSize = atoi(argv[1]);
    int i, j,k;
    int p = atoi(argv[2]);
    double min=0, max=100;
    d=malloc(1000*sizeof(double*));
    for(i=0;i<1000;++i)
        d[i]=malloc(4*sizeof(double));

    a=malloc(1000*sizeof(double*));
    for(i=0;i<1000;++i)
        a[i]=malloc(4*sizeof(double));

    b=malloc(1000*sizeof(double*));
    for(i=0;i<1000;++i)
        b[i]=malloc(4*sizeof(double));

    c=malloc(1000*sizeof(double*));
    for(i=0;i<1000;++i)
        c[i]=malloc(4*sizeof(double));


    //----------------------------------------Write matrices to a csv file-----------------------------------------
    fp = fopen("inputMatrix.csv", "w+");
    srand(time(NULL));

    for(i=0;i<matrixSize;i++)
    {
        //   sprintf(comma, "%s", "");
        for(j=0;j<matrixSize;j++)
        {
            fprintf(fp, "%f  ",getRand(min, max));
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "\n");

    for(i=0;i<matrixSize;i++)
    {
        //   sprintf(comma, "%s", "");
        for(j=0;j<matrixSize;j++)
        {
            fprintf(fp, "%f  ",getRand(min, max));
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "\n");

    //-----------------------------------------Read the matrices to 2D arrays-----------------------------------------
    rewind(fp);

    //...Store all contents in a huge matrix d.. We will later divide d into two individual matrices...
    for(i = 0; i < 2*matrixSize; i++)
    {
        for(j = 0; j < matrixSize; j++)
        {

            if (!fscanf(fp, "%lf", &d[i][j]))
                break;
        }

    }
    //.......Divide d into a & b..........
    for(i=0;i<matrixSize;i++)
    {
        for(j=0;j<matrixSize;j++)
        {
            a[i][j]=d[i][j];
            b[i][j]=d[i+matrixSize][j];
        }
    }


    //........Parallel Matrix product using Loop Tiling..........

    //We will divide the matrix into smaller slices, each thread with a slice.
    //The slice size is 2. The slice in turn will be divided into
    i = 0;
    pthread_t thread[p];
    int threadStart=0;

    sliceSize = matrixSize/p;
    if(sliceSize < 1)
        sliceSize = 1;
    for(i = 0; i< p; i++)
    {
        threadStart = i*sliceSize;
        if(threadStart > matrixSize)
        {
            continue;
        }
        printf("Thread Start: %d\n", threadStart);
        pthread_create(&thread[i], NULL, matmul, (void*)threadStart);
    }

    for(i = 0; i < p; i++)
    {
        pthread_join(&thread, NULL);
    }

    //..........write it to the file..............
    fprintf(fp, "\n");
    for(i=0;i<matrixSize;i++)
    {
        //   sprintf(comma, "%s", "");
        for(j=0;j<matrixSize;j++)
        {
            fprintf(fp, "%f  ",c[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    stop();

}


double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}