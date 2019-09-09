#include <stdio.h>
#include "mpi.h"
#include "omp.h"
int main(int argc, char **argv)
    {
int thread_support;
int ierr;
int rank,size;
int namelen;
char processor_name[MPI_MAX_PROCESSOR_NAME];

ierr=MPI_Init_thread(&argc,&argv,MPI_THREAD_MULTIPLE,&thread_support);
if (ierr != MPI_SUCCESS ) return ierr;
ierr=MPI_Comm_rank(MPI_COMM_WORLD, &rank);
if (ierr != MPI_SUCCESS ) return ierr;
ierr=MPI_Comm_size(MPI_COMM_WORLD, &size);
if (ierr != MPI_SUCCESS ) return ierr;
if (rank==0){
if (thread_support == MPI_THREAD_MULTIPLE ) printf ("MPI_THREAD_MULTIPLE\n");
if (thread_support == MPI_THREAD_SERIALIZED ) printf ("MPI_THREAD_SERIALIZED\n");
if (thread_support == MPI_THREAD_FUNNELED ) printf ("MPI_THREAD_FUNNELED\n");
if (thread_support == MPI_THREAD_SINGLE ) printf ("MPI_THREAD_SINGLE\n");
}
if (rank==0) printf ("Number of Processes requested = %i\n",size);
MPI_Get_processor_name(processor_name,&namelen);
if (ierr != MPI_SUCCESS ) return ierr;
#pragma omp parallel
    {
if (rank==0){
#pragma omp master
                {
            printf ("Number of Threads requested = %i\n",omp_get_num_threads());
                }
        }
    printf ("MPI Process = %i :: Thread number = %i :: Hostname = %s\n",rank,omp_get_thread_num(),processor_name);
}

MPI_Finalize();
return 0;
}
