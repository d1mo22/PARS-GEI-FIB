#include <typeinfo>
#include <iostream>
using namespace std;

struct Racional {
  int num, den;
};

int mcd(int& n, int& d) {
  int mcd = 1;
  int a, b;
  if (n > d) {
    a = n;
    b = d;
  }
  else {
    a = d;
    b = n;
  }
  while (b != 0) {
    mcd = b;
    b = a%b;
    a = mcd;
  }
  return mcd;
}

Racional racional(int n, int d) {
  Racional r;
  int divisor = 0;
  if (n == 0) {
    r.num = 0;
    r.den = 1;
    return r; 
  }
  while (mcd(n,d) != 1) {
    divisor = mcd(n,d);
    n /= divisor;
    d /= divisor;
  }
  r.num = n;
  r.den = d;
  return r;
}



int main() {

  int num, den;
  while (cin >> num >> den) {
    Racional r = racional(num, den);
    cout << r.num << " " << r.den << endl;
  }
}
