#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define BLOCK_LOW(id,p,n) ((id)*(n)/(p))
#define BLOCK_HIGH(id,p,n) (BLOCK_LOW((id)+1,p,n)-1)
#define BLOCK_SIZE(id,p,n) (BLOCK_LOW((id)+1,p,n)-BLOCK_LOW(id,p,n))
#define BLOCK_OWNER(index,p,n) ((((p)*(index)+1)-1)/(n))

int main (int argc, char *argv[]) {
    int count;          /* Solutions found by this processus*/
    int global_count;   /* Global Solutions */
    int i;
    int id;             /* Process rank */
    int p;              /* Number of processes */
    double elapsed_time;/* Time consumming */

    int n;
    int low_value;
    int high_value;
    int size;
    int proc0_size;
    char* marked;
    int prime;
    int index;
    int first;

    printf("the beginning\n");

    MPI_Init(&argc, &argv);
    MPI_Barrier(MPI_COMM_WORLD);
    elapsed_time = -MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (argc != 2) {
        if(!id) printf("Command line: %s <m>\n", argv[0]);
        MPI_Finalize(); exit(1);
    }

    n = atoi(argv[1]);
    low_value = 2 + BLOCK_LOW(id,p,n-1);
    high_value = 2 + BLOCK_HIGH(id,p,n-1);
    size = BLOCK_SIZE(id,p,n-1);
    proc0_size = (n-1)/p;

    if((2+proc0_size) < (int) sqrt((double) n)) {
        if(!id) printf("Too many processes\n");
        MPI_Finalize();
        exit(1);
    }

    marked = (char *) malloc(size*sizeof(char));
    if(marked == NULL) {
        printf("Processus %d cannot allocate enough memory\n", id);
        fflush(stdout);
        MPI_Finalize();
        exit(1);
    }

    for(i = 0; i < size; i++) marked[i] = 0;
    if(!id) index = 0;
    prime = 2;
    do {
        if(prime * prime > low_value) {
            first = prime * prime - low_value;
        } else {
            if(!(low_value % prime)) first = 0;
            else first = prime - (low_value % prime);
        }
        for(i = first; i < size; i += prime) marked[i] = 1;
        if(!id) {
            while(marked[++index]);
            prime = index+2;
        }
        MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } while(prime * prime <= n);

    // First step we compute the local twin number
    count = 0;
    for (i = 0; i + 2 < size; i++)
    {
        if (i + 2 < size)
        {
            if (!marked[i] && !marked[i + 2])
                count++;
        }
    }

    char two_last_marked[2];
    // two_last_marked = (char *)malloc(2 * sizeof(char));
    two_last_marked[0] = marked[size - 2];
    two_last_marked[1] = marked[size - 1];
    printf("Process %d: two_last_marked: First value: %d, seconde value: %d \n", id, two_last_marked[0], two_last_marked[1]);
    
    

    MPI_Win our_win;
    // Create a Window to get the info if the rank is different of p-1

    int soc = sizeof(char);
    MPI_Win_create(two_last_marked, soc*2, soc, MPI_INFO_NULL, MPI_COMM_WORLD, &our_win);

    // //Wait
    MPI_Win_fence(0,our_win);
    

    // //Second step, get the buffer
    char *buf;
    buf = (char *)malloc(2 * sizeof(char)); //2 because we want to have only the two last

    if(id != 0) {
        
        MPI_Get(buf, 1, MPI_INT, id-1, 0, 2, MPI_INT, our_win);
                
    }
    MPI_Win_fence(0,our_win);

    printf("Process %d: First value: %d, second value: %d\n", id, buf[0], buf[1]);

    if(id != 0) {
        if (!marked[0] && !buf[0])
            count++;
        if (!marked[1] && !buf[1])
            count++;
    }
    

    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Win_fence(MPI_MODE_NOSUCCEED,our_win);
    MPI_Win_free(&our_win);
    elapsed_time += MPI_Wtime();
    if(!id) {
        printf("%d primes are less than or equal to %d.\n", global_count, n);
        printf("Total elapsed time: %10.6f\n", elapsed_time);
    }

    printf("Process %d is working  n: %d, low_value: %d, high_value: %d, size: %d, proc0_size: %d; \n", id, n, low_value, high_value, size, proc0_size);
    fflush(stdout);


    MPI_Finalize();     /* End of parallelism */

    printf("that's all\n");

    return(0);

}