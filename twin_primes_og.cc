#include <iostream>

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

  long long r;

  cin >> r;

  bool last = false;
  // Skip the evens
  long long sum = 0;
  // Count the twin primes
  
  for (long long j=3;j<=r;j+=2) {
    bool curr = is_prime(j);
    if (last & curr) {
      sum++;
      //cout << "Twin primes " << j-2 << " " << j << endl;
    }
    last = curr;
  }
  cout << "Total twin primes <= " << r << " = " << sum << endl;
  
  //cout << r << endl;
}
