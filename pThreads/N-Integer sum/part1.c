#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#define N 100


void createMatrix(double (*p)[N][N])
{
	printf("Creating the matrix:\n");
	int i,j;
	//printf("P: %d", p);
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			(*p)[j][i] = ((double)rand()/RAND_MAX);
		}
	}
	printf("\n\n");
}

void naiveMatMul(double (*a)[N][N], double (*b)[N][N], double (*c)[N][N])
{
	int i,j,k;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			for (k = 0; k < N; k++)
			{
				(*c)[i][j] += (*a)[i][k] * (*b)[k][j];
			}
		}

	}
}

void optiMatMul(double (*a)[N][N], double (*b)[N][N], double (*c)[N][N])
{
	int i,j,k;
	double acc[2][2] = {0};
	//for matrix columns
	for(i = 0; i < N; i += 2)
	{
		//for matrix rows
		for(j = 0; j < N; j += 2)
		{
			memset(acc, 0, sizeof acc);
			for (k = 0; k < N; k++)
			{
				acc[0][0] += (*b)[k][j + 0] * (*a)[i + 0][k];
				acc[0][1] += (*b)[k][j + 1] * (*a)[i + 0][k];
				acc[1][0] += (*b)[k][j + 0] * (*a)[i + 1][k];
				acc[1][1] += (*b)[k][j + 1] * (*a)[i + 1][k];
			}
			(*c)[i + 0][j + 0] = acc[0][0];
			(*c)[i + 0][j + 1] = acc[0][1];
			(*c)[i + 1][j + 0] = acc[1][0];
			(*c)[i + 1][j + 1] = acc[1][1];

		}

	}

}

void showMatrix(double (*arr)[N][N])
{
	int i,j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			printf("%f  ", (*arr)[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int main()
{
	double a[N][N];

	double b[N][N];

	double c[N][N];

	double (*pa)[N][N];
	double (*pb)[N][N];
	double (*pc)[N][N];
	pa = &a[0][0];
	pb = &b[0][0];
	//srand(time(1));
	createMatrix(pa);
	createMatrix(pb);


	showMatrix(a);
	showMatrix(b);

	pc = &c[0][0];

	clock_t start, end;
	double naive_time, optimised_time;

	//The normal matmul execution
	start = clock();
	naiveMatMul(pa, pb, pc);
	end = clock();
	naive_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	//showMatrix(pc);

	//the optimised matmul execution using loop tiling
	start = clock();
	optiMatMul(pa, pb, pc);
	end = clock();
	//showMatrix(pc);
	optimised_time = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Time taken by Normal Matrix Multiplication: %f\n", naive_time);

	printf("Time taken by Optimised Matrix Multiplication: %f\n", optimised_time);


	return 0;
}