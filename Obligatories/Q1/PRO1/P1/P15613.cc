#include <iostream>
using namespace std;

//Termometre

int main () {
    int x;
    cin >> x;

    if (x >= 100) {
        cout << "it's hot" << endl;
        cout << "water would boil" << endl;
    }
    else if (x > 30) {
        cout << "it's hot" << endl;
    }
    else if (x <= 0){
        cout << "it's cold" << endl;
        cout << "water would freeze" << endl;
    }
    else if (x < 10) {
        cout << "it's cold" << endl;
    }
    
    else cout << "it's ok" << endl;
}