#include <iostream>
using namespace std;

int main () {
    char c;
    bool found = false;
    bool a = false;

    while (not found and cin >> c){    
        while (c != '.'){
            if (c == 'a') a = true;
            cin >> c;  
            if (c == '.') found = true;
      }
      if (a == 1) cout << "yes" << endl;
      else cout << "no" << endl;
    }
}

/*
int main() {
    char c;
    cin >> c;
    while (c != '.' and c != 'a') cin >> c
    if (c == 'a') cout << "yes" << endl;
    else cout << "no" << endl;
}
*/