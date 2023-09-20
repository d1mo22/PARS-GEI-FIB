#include <iostream>
using namespace std;

int sum_of_digits(int n) {
  if (n < 10) return n;
  return sum_of_digits(n/10) + n%10;
}

int reduction_of_digits(int n) {
  int sum = sum_of_digits(n);
  
  if (n < 10) return sum;
  return reduction_of_digits(sum);
}


int main() {
  int n;
  while (cin >> n) {
    cout << reduction_of_digits(n) << endl;
  }
}
