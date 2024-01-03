#include <iostream>
#include <vector>
using namespace std;

const char lletres[4] = {'A', 'C', 'G', 'T'};

void combinacions(vector<char> &s, int idx, int n) {
  if (idx == n) {
    for (char l : s)
      cout << l;
    cout << endl;
    return;
  } else {
    for (char l : lletres) {
      s[idx] = l;
      combinacions(s, idx + 1, n);
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<char> c(n);
  combinacions(c, 0, n);
}
