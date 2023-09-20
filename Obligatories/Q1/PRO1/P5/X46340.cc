#include <iostream>
using namespace std;

int max(int x,int y,int z) {
  if (x >= y and x >= z) return x;
  if (y >= z and y >= x) return y;
  if (z >= y and z >= x) return z;
  else return 0;
}

int min(int x,int y,int z) {
  if (x <= y and x <= z) return x;
  if (y <= z and y <= x) return y;
  if (z <= y and z <= x) return z;
  else return 0;
}

int sum_min_max(int x,int y,int z) {
  return max(x, y, z) + min(x, y, z);
}


int main() {
  int x,y,z;
  while (cin >> x >> y >> z) cout << sum_min_max(x,y,z) << endl;
}
