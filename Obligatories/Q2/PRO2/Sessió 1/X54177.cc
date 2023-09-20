#include <iostream>
using namespace std;

int main()
{

  int x, y, n; 
  int sum = 0;
  cin >> n >> x;
  for (int i = 1; i <= n; ++i) {
    while (cin >> y and y != x) {
      sum += y;
    }
    string s;
    getline(cin,s);
    cout << "La suma de la secuencia " << i << " es " << sum << endl;
    sum = 0;
    }
}