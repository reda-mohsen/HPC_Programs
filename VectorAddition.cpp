/**************************************************************
Two vectors of the same length can be added by adding their corresponding elements
Ci = ai + bi, where 1 <= i <= n
**************************************************************/

/**************************************************************
FILE: VectorAddition.cpp
* DESCRIPTION:
* OpenMP Example Vector addition
************************************************************/

#include "stdio.h"
#include "omp.h"

#define N 12

int main()
{
	int id, tid, chunck, nthreads;
	double a[N], b[N], c[N];

	// initialize the two vectors a and b
	for (int i = 0; i < N; i++) {
		a[i] = b[i] = i+1;
	}

	nthreads = omp_get_max_threads();

	// start the parallel section
	#pragma omp parallel private(tid) num_threads(nthreads)
	{
		tid = omp_get_thread_num();


		// compute vector addition in parallel
		#pragma omp for
		
			for (int i = 0; i < N; i++) {
				printf("Thread %d starting ...\n", tid);
				c[i] = a[i] + b[i];
			}
		
	}
	// end of parallel section
	printf("\n");
	//print the result vector
	for (int i = 0; i < N; i++) {
		printf("C[%i] = %.2f\n",i, c[i]);
	}

}

