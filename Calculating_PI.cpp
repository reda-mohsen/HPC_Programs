/**************************************************************
* Author: Reda Mohsen
* Topic : Calculating PI
**************************************************************/
/**************************************************************
FILE: Calculating_PI.cpp
* DESCRIPTION:
* OpenMP Example calculating Pi
* One method to calculate PI (3.141592…) is by using Monte Carlo method.
* We have a circle of radius 0.5, enclosed by a 1 × 1 square.
* The area of the circle is 𝜋𝑟2 = 𝜋/4 , The area of the square is 1. if we divide the area of the circle by the area of square, we get 𝜋/4.
* We then generate a large number of uniformly distributed random points and count the number of points that fall inside the circle.
* When we divide the total number of points and the number of points inside circle, 
* We get a value that is an approximation of the ratio of the areas we calculated 𝜋/4.
************************************************************/

#include <stdio.h>
#include <iostream>
#include "omp.h"
#include <math.h>

int main()
{
	int nPoints = 10000000;
	int tid, nthreads = 8;
	double nInside=0;
	double rand_x, rand_y;

	#pragma omp parallel private(tid) num_threads(nthreads) reduction(+:nInside)
	{
		// get the thread id number
		tid = omp_get_thread_num();
		/*
		int start = tid * (nPoints / nthreads);
		int end = (tid + 1) * (nPoints / nthreads);

		for (int i = start; i < end; i++) {
			// random value for x and y
			rand_x = (double)(rand() % 100) / 100.0;
			rand_y = (double)(rand() % 100) / 100.0;

			// check if the point is inside the circle or not
			if (sqrt(pow(rand_x, (double)2) + pow(rand_y, 2)) <= 1) {
				// if inside the circle increment the nInside by one
				nInside++;
			}
		}
		*/
		
		#pragma omp for
		{
			for (int i = 0; i < nPoints; i++) {
				// random value for x and y
				rand_x = (double)(rand() % 100) / 100.0;
				rand_y = (double)(rand() % 100) / 100.0;

				// check if the point is inside the circle or not
				if (sqrt(pow(rand_x, (double)2) + pow(rand_y, 2)) <= 1) {
					// if inside the circle increment the nInside by one
					nInside++;
				}
			}
		}
	}
	// Print PI value which equals (#points inside circle / total #points) * 4
	printf("PI equals %.4f\n", (nInside / nPoints) * 4);

}