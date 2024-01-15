#include <iostream>
#include <map>
using namespace std;

struct Info {
  string code;
  int price;
};

int main() {
  map<int, Info> M;
  char c;
  while (cin >> c) {
    if (c == 'n') {
      cout << "num: " << M.size() << endl;
    }

    else if (c == 'u') {
      string code;
      int length, price;
      cin >> code >> length >> price;
      M[length] = {code, price};
    }

    else if (c == 'q') {
      int length;
      cin >> length;
      auto it = M.find(length);
      cout << (it == M.end() ? -1 : it->second.price) << endl;
    }

    else if (c == 'p') {
      cout << string(10, '-') << endl;
      for (pair<int, Info> p : M) {
        cout << p.second.code << " " << p.first << " " << p.second.price
             << endl;
      }
      cout << string(10, '*') << endl;
    }

    else { // c == 's'
      if (M.size() < 2)
        cout << "no" << endl;
      else {
        auto it = M.begin();
        ++it;
        cout << it->second.code << " " << it->first << " " << it->second.price
             << endl;
      }
    }
  }
}
