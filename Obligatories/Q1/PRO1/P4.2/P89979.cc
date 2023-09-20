#include <iostream>
using namespace std;

int main() {
    //Declaro la varialbe de la linea (n), un bool para saber si ya
    //he encontrado la linea, dos string para hacer la busqueda por
    //ventana y un contador para saber que linea es.
    int n;
    bool found = false;
    string a, b;
    int i = 0;
    //Siempre y cuando me entren valores numericos y no haya encontrado
    //La linea en orden
    while (cin >> n and not found) {
        //Leo la primer string y defino un booleano de orden que es true
        cin >> a;
        bool order = true;
        //Hago un bucle que me le las siguientes palabras y si la siguiente
        //palabra es mayor que la anterior orden es falso y found tambien
        for (int j = 0; j < n - 1; ++j) {
            cin >> b;
            if (b < a) order = false;
            a = b;
        }
        found = order;
        ++i;
    }
    if (found) cout << "The first line in increasing order is " <<
    i << "." << endl;
    else cout << "There is no line in increasing order." << endl;
}
