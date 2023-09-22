#include <iostream>
using namespace std;

//Identifica la lletra, si es Majuscula o minuscula
// i també consonant o bocal

int main () {
    char c;
    cin >> c;

    if (c >= 'A' and c <= 'Z'){
        cout << "uppercase" << endl;
    }
    else if (c >= 'a' and c <= 'z'){
        cout << "lowercase" << endl;
    }
    if (c == 'a' or c == 'A' or c == 'e' or c == 'E'
    or c == 'i' or c == 'I' or c == 'o' or c == 'O' 
    or c == 'u' or c == 'U') cout << "vowel" << endl;
    else cout << "consonant" << endl;
}