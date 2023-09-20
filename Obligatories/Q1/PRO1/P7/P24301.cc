#include <iostream>
#include <vector>
using namespace std;


vector<int> concatenation(const vector<int> & V1, const vector<int> & V2) {
  vector<int> V = V1;
  int size = V2.size();
  for (int i = 0; i < size; ++i) V.push_back(V2[i]);
  return V;
}

