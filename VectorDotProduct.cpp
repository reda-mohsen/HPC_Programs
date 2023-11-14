/**************************************************************
* Author: Reda Mohsen
* Topic : Vector Dot Product
**************************************************************/
/**************************************************************
FILE: VectorDotProduct.cpp
* DESCRIPTION:
* OpenMP Example vector dot product
************************************************************/

#include <stdio.h>
#include <iostream>
#include "omp.h"

#define N 100

int main() {
	int tid, nthreads=8;
	int Vector_A[N], Vector_B[N];
	float sum = 0;

	// Initialize vector A and vector B
	for (int i = 0; i<N; i++) {
		Vector_A[i] = Vector_B[i] = i+1;
	}

	// Print vector A
	printf("Vector A [ ");
	for (int i = 0; i < N; i++) {
		printf("%i ",Vector_A[i]);
	}
	printf("] \n\n");
	// Print vector B
	printf("Vector B [ ");
	for (int i = 0; i < N; i++) {
		printf("%i ", Vector_B[i]);
	}
	printf("] \n\n");

	#pragma omp parallel private(tid) num_threads(nthreads) reduction(+:sum)
	{
		tid = omp_get_thread_num();

		#pragma omp for 
		{
			for (int i = 0; i < N; i++) {
				sum += Vector_A[i] * Vector_B[i];
			}
		}

		/*
			int start = tid * (N / nthreads);
		int end = (tid + 1) * (N / nthreads);

		// Calculate the dot product
		for (int i = start; i < end; i++) {
			sum += Vector_A[i] * Vector_B[i];
		}
		*/
	
	} 
	printf("Dot Product = %.2f\n", sum);

}




