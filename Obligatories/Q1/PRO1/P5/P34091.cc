#include <iostream>
using namespace std;

bool es_perfecte(int n) {
  if (n == 1) return false;
  int i = 2;
  int suma = 1;

  while (i*i < n) {
    if (suma > n) return false;
    if(n%i == 0) {
      suma = suma + i + n/i;
    }
    ++i;
  }
  if (n == suma) return true;
  else return false;
}

int main () {
  int n;
  while (cin >> n) cout << (es_perfecte(n) ? "true" : "false") << endl;
}
