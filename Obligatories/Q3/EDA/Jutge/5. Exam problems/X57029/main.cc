#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;

const char dir[3] = {'h', 'u', 'd'};

void combinacions(VC &sol, int n, int idx, int altura) {
  if (idx == n) {
    for (char c : sol)
      cout << c;
    cout << endl;
    return;
  }
  if (altura >= 1) {
    sol.push_back('d');
    combinacions(sol, n, idx + 1, altura - 1);
    sol.pop_back();
  }

  sol.push_back('h');
  combinacions(sol, n, idx + 1, altura);
  sol.pop_back();

  sol.push_back('u');
  combinacions(sol, n, idx + 1, altura + 1);
  sol.pop_back();
}

int main() {
  int n;
  cin >> n;
  VC sol;
  combinacions(sol, n, 0, 0);
}
