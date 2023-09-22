#include <iostream>
using namespace std;

int main (){
    char c;
    int h = 0;
    int v = 0;
    while (cin >> c){
        if (c == 'n') --v;
        else if(c == 's') ++v;
        if (c == 'w') --h;
        else if (c == 'e') ++h;
    }
    if (h > 0 or v > 0) cout << "(" << h << ", " << v << ")" << endl;
    else cout << "(" << h << ", " << v << ")" << endl;
}