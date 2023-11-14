/*
*	Author: Reda Mohsen
*	Topic: Ping Pong MPI (Point-to-Point Communication)
*/

#include <mpi.h>
#include <iostream>
#include "stdio.h"

int main(int argc, char* argv[])
{
	// Initialize the MPI environment
	MPI_Init(&argc, &argv);

	// Get the number of processes
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Get the rank of processes
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	int data = 1, sender, receiver, tag=0;

	if (rank == 0) {
		receiver = 1;
		sender = 1;
		MPI_Send(&data, 1, MPI_INT, receiver, tag, MPI_COMM_WORLD);
		MPI_Status stat;
		MPI_Recv(&data, 1, MPI_INT, sender, tag, MPI_COMM_WORLD, &stat);
		printf("PONG");
	}
	else if (rank == 1) {
		receiver = 0;
		sender = 0;
		MPI_Status stat;
		MPI_Recv(&data, 1, MPI_INT, sender, tag, MPI_COMM_WORLD, &stat);
		printf("PING");
		MPI_Send(&data, 1, MPI_INT, receiver, tag, MPI_COMM_WORLD);
	}

	// Print off a hello world message
	//printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);

	// Finalize MPI Environment
	MPI_Finalize();

}
