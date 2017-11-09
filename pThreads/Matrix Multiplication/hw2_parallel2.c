#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int matrixSize;
int a[matrixSize][matrixSize];
int b[matrixSize][matrixSize];
int c[matrixSize][matrixSize];
int sliceSize;

void matMul(void *arg)
{
    int i,j,k;

    for(i =0; i < sliceSize; i++)
    {
        for(j = 0; i< sliceSize; j++)
        {
            for(k = 0; k<sliceSize; k++)
            {
                c[i][j] += a[i][k]*b[k][j];
            }
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
    //FILE *fp;
    matrixSize = atoi(argv[1]);
    int i, j,k;
    int p = atoi(argv[2]);
    int a[matrixSize][matrixSize],b[matrixSize][matrixSize],c[matrixSize][matrixSize];
    sliceSize = matrixSize/p;

    for(i=0;i<p;i++)
    {
        pthread_create(&thread[p], NULL, &i);
    }

}