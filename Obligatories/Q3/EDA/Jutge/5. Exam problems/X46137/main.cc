#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;

void combinacions(VC &lletres, int n, int a, int b, int idx) {
  if (abs(a - b) > 2)
    return;
  if (idx == n) {
    for (char c : lletres)
      cout << c;
    cout << endl;
    return;
  }
  lletres.push_back('a');
  combinacions(lletres, n, a + 1, b, idx + 1);
  lletres.pop_back();

  lletres.push_back('b');
  combinacions(lletres, n, a, b + 1, idx + 1);
  lletres.pop_back();
}

int main() {
  int n;
  cin >> n;
  VC lletres;
  combinacions(lletres, n, 0, 0, 0);
}
