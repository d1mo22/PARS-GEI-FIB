#include <iostream>
#include <set>
#include <string>
using namespace std;

typedef long long int lint;

int main() {
  lint suma = 0;
  set<lint> selec;
  set<lint> resta;

  int n;
  cin >> n;
  string s;
  lint x;

  while (cin >> s >> x) {
    if (s == "deixar") {
      if (selec.size() < n) {
        selec.insert(x);
        suma += x;
      } else {
        lint min = *(selec.begin());
        if (min < x) {
          selec.insert(x);
          selec.erase(selec.begin());
          suma = suma + x - min;
          resta.insert(min);
        } else
          resta.insert(x);
      }
    } else {
      if (*(selec.begin()) <= x) {
        selec.erase(x);
        suma -= x;
        if (resta.size() > 0) {
          auto it = resta.end();
          --it;
          selec.insert(*it);
          suma += *it;
          resta.erase(it);
        }
      } else
        resta.erase(x);
    }
    cout << suma << endl;
  }
}
