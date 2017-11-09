#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
//prototype
double getRand(double min, double max);
double** d,a,b,c;


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



int main(int argc, char*argv[])
{
    start();
    if(argc<2)
    {
        perror("\nUsage ./generateInput <squareMatrixSize>\n");
        exit(-1);
    }
    FILE *fp;
    int matrixSize = atoi(argv[1]), i, j,k;
    double min=0.00001, max=1000;
    d=malloc(1000*sizeof(double*));
    for(i=0;i<1000;++i)
        d[i]=malloc(4*sizeof(double));

    double** a=malloc(1000*sizeof(double*));
    for(i=0;i<1000;++i)
        a[i]=malloc(4*sizeof(double));

    double** b=malloc(1000*sizeof(double*));
    for(i=0;i<1000;++i)
        b[i]=malloc(4*sizeof(double));

    double** c=malloc(1000*sizeof(double*));
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


    //........Serial Matrix product using Loop Tiling..........

    double acc[2][2] = {0};

    for(i = 0; i < matrixSize; i += 2)
    {
        //for matrix rows
        for(j = 0; j < matrixSize; j += 2)
        {
            memset(acc, 0, sizeof acc);
            for (k = 0; k < matrixSize; k++)
            {
                acc[0][0] += (b)[k][j + 0] * (a)[i + 0][k];
                acc[0][1] += (b)[k][j + 1] * (a)[i + 0][k];
                acc[1][0] += (b)[k][j + 0] * (a)[i + 1][k];
                acc[1][1] += (b)[k][j + 1] * (a)[i + 1][k];
            }
            (c)[i + 0][j + 0] = acc[0][0];
            (c)[i + 0][j + 1] = acc[0][1];
            (c)[i + 1][j + 0] = acc[1][0];
            (c)[i + 1][j + 1] = acc[1][1];

        }

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