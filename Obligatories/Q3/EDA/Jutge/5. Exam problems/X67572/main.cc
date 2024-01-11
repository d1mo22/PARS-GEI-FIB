#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<string> VS;

bool valid(const string &s, const string &e) {
  return (s[s.length() - 1] != e[0]);
}

void combinacions(const VS &paraules, VS &sol, VI &usat, int n, int idx) {
  if (idx == n) {
    for (string s : sol)
      cout << s;
    cout << endl;
    return;
  } else {
    for (int i = 0; i < n; ++i) {
      if (!usat[i] and (sol.size() < 1 or valid(sol[idx - 1], paraules[i]))) {
        usat[i] = true;
        sol.push_back(paraules[i]);
        combinacions(paraules, sol, usat, n, idx + 1);
        sol.pop_back();
        usat[i] = false;
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  VS paraules(n);
  VS sol;
  VI usat(n, false);
  for (int i = 0; i < n; ++i) {
    cin >> paraules[i];
  }
  combinacions(paraules, sol, usat, n, 0);
}
