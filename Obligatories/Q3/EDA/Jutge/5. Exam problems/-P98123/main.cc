#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
  int n, x, suma, max;
  cin >> n;
  string s;
  multiset<int, greater<int>> gems;
  while (cin >> s >> x) {
    if (s == "deixar") {
      if (gems.size() < n) {
        gems.insert(x);
        suma += x;
      } else {
        if (x > max) {
        }
      }
    } else if (s == "endur") {
      auto it = gems.find(x);
      if (*it <= max) {
        gems.erase(it);
      } else {
      }
    }
    cout << suma << endl;
  }
}
