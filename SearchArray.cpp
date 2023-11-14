/**************************************************************
Given an array with size N=100, search in the array for a specific number and print ALL indices in
which this number appears, and the id of the thread in which this number was found.
**************************************************************/
/**************************************************************
FILE: SearchArray.cpp
* DESCRIPTION:
* OpenMP Example Search in an array
************************************************************/

#include <stdio.h>
#include <iostream>
#include "omp.h"

#define N 100
#define MOD 20

int main(){

	int num = 15;
	int arr[N];

	// Initialize the array with random values from 0 to 19
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % MOD;
	}
	// print the array
	printf("The array is [ ");
	for (int i = 0; i < N; i++) {
		printf("%i, ",arr[i]);
	}
	printf("]\n\n");

	int tid, nthreads=8;
	#pragma omp parallel private(tid) num_threads(nthreads)
	{
		tid = omp_get_thread_num();
		// Divide the array over threads
		int start = tid * N / nthreads;
		int end = (tid + 1) * N / nthreads;
		// Search in each portion for number 15
		for (int i = start; i < end; i++) {
			// the num is found
			if (arr[i] == num) {
				// print the index of the number and the current tid
				printf("The number (%i) is found in thread [%i] at index {%i}\n", num,tid,i);
			}
		}
	}
}