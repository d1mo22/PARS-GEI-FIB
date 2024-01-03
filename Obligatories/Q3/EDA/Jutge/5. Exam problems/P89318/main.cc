#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool combinacio_valida(const vector<char> &paraula) {
  int n = paraula.size();
  for (int i = 0; i < n - 1; ++i) {
    if (paraula[i] - paraula[i + 1] == -1)
      return false;
  }
  return true;
}

void permutacions(int idx, int n, vector<char> &lletres, vector<int> &usat) {
  if (idx == n and combinacio_valida(lletres)) {
    string paraula(lletres.begin(), lletres.end());
    cout << paraula << endl;
  }
  for (int i = 0; i < n; ++i) {
    if (!usat[i]) {
      lletres.push_back('a' + i);
      usat[i] = true;
      permutacions(idx + 1, n, lletres, usat);
      usat[i] = false;
      lletres.pop_back();
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<char> lletres;
  vector<int> usat(n, false);
  permutacions(0, n, lletres, usat);
}
