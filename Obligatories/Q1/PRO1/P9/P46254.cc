#include <iostream>
#include <cmath>
using namespace std;

struct Punt {
    double x, y;
};

double distancia(const Punt& a, const Punt& b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
  Punt x, y;
  int x1, x2, y1, y2;
  while(cin >> x1 >> x2 >> y1 >> y2) {
    x.x = x1;
    x.y = x2;
    y.x = y1;
    y.y = y2;
    cout << distancia(x, y) << endl;
  }
}
