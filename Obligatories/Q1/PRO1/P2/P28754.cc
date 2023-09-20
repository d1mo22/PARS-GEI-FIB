#include <iostream>
using namespace std;

//introduir un numero
//treure en numero al reves en binari

int main () {
    int a;
    cin >> a;
   
    while (a/2 != 0){
    cout << a%2;
    a = a/2;
    }
    cout << a << endl;
}