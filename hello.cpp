#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <random>
#include <chrono>

void doWork(int n, int r){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed+r);
	//std::default_random_engine generator;
	std::normal_distribution<> distribution(0.0,1.0);
	for(int i=0;i<n;i++){	
		distribution(generator);
	}
}
int main(int argc, char *argv[]){
	int rank, nproc;
	MPI_Init (&argc, &argv);
	int it=atoi(argv[1]);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	double t1=MPI_Wtime();
	doWork(it/nproc,rank);
	double t2=MPI_Wtime();
	double td=t2-t1;
	double max;
	MPI_Reduce(&td, &max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	 if(rank==0)
	  	printf("Parallel Method time = %f seconds\n", max);
	MPI_Finalize();
	return 0;
}
