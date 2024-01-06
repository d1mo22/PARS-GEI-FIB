#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;

// TRUE COMPRA
// FALSE VENDA

void combinacions(VC &accions, int n, int c, int s, int idx) {
  if (idx == n) {
    for (char x : accions)
      cout << x;
    cout << endl;
    return;
  }
  if (c > 0) {
    accions.push_back('b');
    combinacions(accions, n, c - 1, s + 1, idx + 1);
    accions.pop_back();
  }
  if (s > 0) {
    accions.push_back('s');
    combinacions(accions, n, c + 1, s - 1, idx + 1);
    accions.pop_back();
  }
}

int main() {
  int n, c;
  cin >> n >> c;
  VC accions;
  combinacions(accions, n, c, 0, 0);
}
