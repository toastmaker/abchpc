
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define DATA_TAG  0
#define STOP_TAG  1

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0)
            fprintf(stderr, "Run with 2 ranks\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        // PRODUCER
        for (int i = 1; i <= 5; i++) {
	    printf("Producer: creating %d\n", i);
	    sleep(1);
            printf("Producer: sending %d\n", i);
            MPI_Send(&i, 1, MPI_INT, 1,
                     DATA_TAG, MPI_COMM_WORLD);
        }

        // Signal end of stream
        MPI_Send(NULL, 0, MPI_INT, 1,
                 STOP_TAG, MPI_COMM_WORLD);

    } else {
        // CONSUMER
        int value;
        MPI_Status status;

        while (1) {
            MPI_Recv(&value, 1, MPI_INT, 0,
                     MPI_ANY_TAG, MPI_COMM_WORLD,
                     &status);

            if (status.MPI_TAG == STOP_TAG)
                break;
	    printf("Consumer: Getting %d\n", value);
	    sleep(1);
            printf("Consumer: %d squared = %d\n",
                   value, value * value);
        }
    }

    MPI_Finalize();
    return 0;
}

