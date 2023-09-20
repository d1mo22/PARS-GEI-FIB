#include <iostream>
using namespace std;

int main() {
    string s;

    bool start = false;
    int count = 0;

    while (cin >> s and s != "final") {
        
        if (s == "principi") start = true;
        else if (start) ++count;
    }
    
    if (start and s == "final") cout << count << endl;
    else cout << "sequencia incorrecta" << endl;
    
}