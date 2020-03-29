#include <iostream>
#include <mpi.h>
using namespace std;

// Checks to see if p>2 is prime.
//
bool is_prime(long long p) {
  long long i;
  
  i=2;
  while (i*i<p) {
    if (p%i == 0) {
      return false;
    }
    i++;
  }
  


  return true;
}

int main() {
	int num_processes;
	int proc_num;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_num);

  long long global_sum = 0;
  
  if (proc_num == 0) {
    long long r;
    cin >> r;
    for (int i = 1; i < num_processes; ++i) {
      MPI_Send(&r, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      int process_sum;
      MPI_Recv(&process_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      global_sum += process_sum;
    }
  } else {
    bool last = false;
    long long r;
    long long local_sum;
    MPI_Recv(&r, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    long long start = max(3, ((proc_num-1)*r/num_processes));
    long long end = min(r, (proc_num*r/num_processes-1)); 
    for (long long j=start;j<=end;j+=2) {
      bool curr = is_prime(j);
      if (last & curr) {
        local_sum++;
      }
      last = curr;
    }
    MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  
  cout << "Total twin primes <= " << r << " = " << sum << endl;

}
