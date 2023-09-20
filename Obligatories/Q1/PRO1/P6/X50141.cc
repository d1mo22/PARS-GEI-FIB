#include <iostream>
using namespace std;

int inverse(int x) {
  int y = 0;
  
  while(x != 0) {
    y = y*10 + x%10;
    x /= 10;
  }
  return y;
}

int max(int x, int y) {
  if (x > y) return x;
  return y;
}

int fatten(int x) {
  if (x < 10) return x;
  return fatten(max(x/10, x%10));

}


int main() {
  int x;
  cin >> x;
  cout << inverse(x) << endl;
  //while (cin >> x) cout << fatten(x) << endl;
}
