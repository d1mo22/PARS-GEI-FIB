#include <iostream>
#include <map>
using namespace std;

int main() {
  string op;
  map<string, string> m;
  while (cin >> op) {
    if (op == "info") {
      cout << "PARELLES:" << endl;
      for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second != "" and it->first < it->second)
          cout << it->first << " " << it->second << endl;
      }
      cout << "SOLS:" << endl;
      for (auto it = m.begin(); it != m.end(); ++it) {
        if (it->second == "")
          cout << it->first << endl;
      }
      cout << "----------" << endl;
    } else {
      string x, y;
      cin >> x >> y;
      auto it_x = m.find(x);
      if (it_x == m.end())
        m.insert({x, y});
      else {
        if (it_x->second == "")
          it_x->second = y;
        else {
          auto it1 = m.find(it_x->second);
          it1->second = "";
          it_x->second = y;
        }
      }
      auto it_y = m.find(y);
      if (it_y == m.end())
        m.insert({y, x});
      else {
        if (it_y->second == "")
          it_y->second = x;
        else {
          auto it2 = m.find(it_y->second);
          it2->second = "";
          it_y->second = x;
        }
      }
    }
  }
}
