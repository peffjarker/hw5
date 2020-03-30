#include <iostream>
#include <mpi.h>
using namespace std;

// Checks to see if p>2 is prime.
//
bool is_prime(long long p) {
  long long i;
  
  i=2;
  while (i*i<=p) {
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
    long long r = 0;
    cin >> r;
    for (int i = 1; i < num_processes; ++i) {
      MPI_Send(&r, 1, MPI_LONG_LONG, i, 0, MPI_COMM_WORLD);
    }
    for (int i = 1; i < num_processes; ++i) {
      int process_sum;
      MPI_Recv(&process_sum, 1, MPI_LONG_LONG, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      global_sum += process_sum;
    }
    cout << "Total twin primes <= " << r << " = " << global_sum << endl;
  } else {
    bool last = false;
    long long r = 0;
    long long local_sum = 0;
    MPI_Recv(&r, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    long long start = max((long long)3, ((proc_num-1)*r/(num_processes-1)));
    if (start % 2 == 0) {
      start++;
    }
    long long end = min(r, (proc_num*r/(num_processes-1)-1)); 
    //cout << proc_num << " start: " << start << " end: " << end << endl;
    for (long long j=start;j<=end;j+=2) {
      bool curr = is_prime(j);
      if (last & curr) {
        local_sum++;
      }
      last = curr;
    }
    //cout << "process sum:" << local_sum << endl;
    MPI_Send(&local_sum, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
