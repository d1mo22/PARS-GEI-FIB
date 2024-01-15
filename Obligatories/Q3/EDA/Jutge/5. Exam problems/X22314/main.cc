#include <iostream>
#include <map>
#include <utility>
using namespace std;

int main() {
  map<string, int> M;
  char c;
  while (cin >> c) {
    if (c == 'N') {
      cout << "number: " << M.size() << endl;
    }

    else if (c == 'D') {
      string nif;
      int money;
      cin >> nif >> money;
      M[nif] += money;
    }

    else if (c == 'Q') {
      string nif;
      cin >> nif;
      auto it = M.find(nif);
      if (it == M.end())
        cout << -1 << endl;
      else
        cout << it->second << endl;
    }

    else if (c == 'P') {
      bool primer = true;
      for (pair<string, int> p : M) {
        if ((p.first[7] - '0') % 2 == 0) {
          if (primer) {
            primer = false;
          } else {
            cout << " ";
          }
          cout << p.first;
        }
      }
      cout << endl;
    }

    else { // c == 'L'
      if (M.size() == 0)
        cout << "NO LAST NIF" << endl;
      else {
        auto it = M.end();
        --it;
        cout << it->first << " " << it->second << endl;
      }
    }
  }
}
