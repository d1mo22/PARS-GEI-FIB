#include <iostream>
#include <stack>
using namespace std;


int main() {
    stack<char> pila;
    char c;
    cin >> c;
    bool correcte = true;
    int i = 0;
    while (correcte and c != '.') {
       if (c == '(' or c == '[') pila.push(c);
       else {
           if (pila.empty()) correcte = false;
           else if ((pila.top() == '(' and c == ')') or 
           (pila.top() == '[' and c == ']')) pila.pop();
           else correcte = false;
        } 
       cin >> c;
       ++i;
    }
    
    if (pila.empty() and correcte) cout << "Correcte" << endl;
    else cout <<"Incorrecte " << i << endl;


    /*int tamany = pila.size();
    for (int i = 0; i < tamany; ++i) {
        cout << pila.top();
        pila.pop();
    }
    cout << endl;*/
}