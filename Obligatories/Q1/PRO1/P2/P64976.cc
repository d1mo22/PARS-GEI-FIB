#include <iostream>
using namespace std;

int main () {
   int n;
   int m = 1;
   cin >> n;
   while (m <= n){
    cout << n << " x " << m << " = " << n*m << endl;
    ++m;
   }   
}