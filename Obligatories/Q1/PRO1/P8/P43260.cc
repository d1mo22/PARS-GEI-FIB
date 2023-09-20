#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

void spaces(int n){
  for (int i = 0; i < n; ++i) cout << ' ';
}

string spaces_string(int n){
  string s = "";
  for (int i = 0; i < n; ++i) s += " ";
  return s;
}

vector<string> creu(int n, const int& N){
  if (n == 1){
    vector<string> v(3);
    v[0] = " | ";
    v[1] = "-O-";
    v[2] = " | ";
    if (N == 1){
      for (int i = 0; i < 3; ++i){
        cout << "|";
        cout << v[i];
        cout << "|";
        cout << endl;
      }
      return v;
    }
    else return v;
  }
  else{
    vector<string> v(pow(3,n));
    vector<string> v_anterior = creu(n-1,N);
    int m = v_anterior.size();
    
    //part superior
    int p = v_anterior[0].size();
    for (int i = 0; i < m; ++i){
      v[i] = spaces_string(p);
      v[i] += v_anterior[i];
      v[i] += spaces_string(p);
    }
    //part del mig
    for (int i = m; i < 2*m; ++i){
      for (int j = 0; j < 3; ++j){
        v[i] += v_anterior[i-m];
      }
    }
    //part inferior
    for (int i = 2*m; i < 3*m; ++i){
      v[i] = spaces_string(p);
      v[i] += v_anterior[i-2*m];
      v[i] += spaces_string(p);
    }
    
    if (n == N){ //imprimir
      int k = v.size();
      for (int i = 0; i < k; ++i){
        cout << '|';
        spaces((pow(3,n)-v[i].size())/2);
        cout << v[i];
        spaces((pow(3,n)-v[i].size())/2);
        cout << '|';
        cout << endl;
      }
      return v;
    }else{ //retornar
      return v;
    }
  }
}

int main() {
  int n;
  cin >> n;
  vector<string> v = creu(n,n);
}