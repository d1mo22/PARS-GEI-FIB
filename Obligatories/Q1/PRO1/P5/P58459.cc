#include <iostream>
using namespace std;

bool is_leap_year(int year) {
  if (year%100 != 0 and year%4 == 0) return true;
  else if ((year/100)%4 == 0 and year%4 == 0) return true;
  else return false;
}

bool is_valid_date(int d, int m, int a) {
  if (m <= 0 or m > 12 or d > 31 or d <= 0) return false;

  if (m%2 != 0 and m <= 7) {
    if (d <= 0 or d > 31) return false;
    return true;
  }

  if (m%2 == 0 and m >= 8) {
    if (d <= 0 or d > 31) return false;
    return true;
  }

  if (m == 2) {
    if (is_leap_year(a) == false) {
      if (d <= 0 or d > 28) return false;
      return true;
    } 
    
    if (d <= 0 or d > 29) return false;
    return true; 
  }

  if (d <= 0 or d > 30) return false;
  return true;
}


int main() {
  int d, m, a;
  while (cin >> d >> m >> a)
    cout << (is_valid_date(d, m, a) ? "true" : "false") << endl;
}
