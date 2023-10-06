#include <iostream>
#include <map>
using namespace std;
const int LIMIT = 100000000;
//Limit plantejat al exercici 10⁸
int main() {
    int x, y, n;
    map<int, int> colatz; 
    //mapa que guarda el valor y la posicio a la sequecia
    while (cin >> x >> y >> n) {
        bool again = false;
        int result = 0;
        while (!again and n <= LIMIT) {
            //comprovem si el valor esta a la sequencia
            if (colatz.find(n) != colatz.end()) {
                //si esta a la sequencia restem les posicions
                result -= colatz[n];
                again = true;
            }
            //Sumem la posicio 
            ++result;
            //Guardem el valor amb la seva posicio
            colatz[n] = result;
            //Calculem el seguent terme
            if (n%2) n = 3*n+y;
            else n = n/2+x;
        }
        //Netejem el mapa
        colatz.clear();
        //Si tenim un cicle imprimim la longitud
        //si no el primer valor en superar el limit
        cout << (again ? result : n) << endl;
    }
}