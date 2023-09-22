#include <iostream>
#include <vector>
using namespace std;

typedef vector< vector<char> > Matriu;

void convertir_majuscules(Matriu& resultat, int i, int j, int l_paraula, 
bool vertical, bool horitzontal, bool diagonal) {
    if (vertical) {
        for (int k = 0; k < l_paraula; ++k) {
            char lletra = resultat[i+k][j];
            if (lletra >= 'a' and lletra <= 'z') {
                resultat[i+k][j] = lletra - ('a' -'A');
            }
        }
    }

    if (horitzontal) {
        for (int k = 0; k < l_paraula; ++k) {
            char lletra = resultat[i][j+k];
            if (lletra >= 'a' and lletra <= 'z') {
                resultat[i][j+k] = lletra - ('a' -'A');
            }
        }
    }
    if (diagonal) {
        for (int k = 0; k < l_paraula; ++k) {
            char lletra = resultat[i+k][j+k];
            if (lletra >= 'a' and lletra <= 'z') {
                resultat[i+k][j+k] = lletra - ('a' -'A');
            }
        }
    }
}

void resoldre_paraula(const Matriu& sopa, Matriu& resultat, int f, int c,
string paraula) {
    char inicial = paraula[0];
    int l_paraula = paraula.length();

    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < c; ++j) {
            bool vertical = true;
            bool horitzontal = true;
            bool diagonal = true;
            
            if (inicial == sopa[i][j]) {
                for (int k = 1; k < l_paraula; ++k) {
                    if (vertical and (i+k >= f or paraula[k] != sopa[i+k][j]))
                    vertical = false;
                    if (horitzontal and (j+k >= c or paraula[k] != sopa[i][j+k]))
                    horitzontal = false;
                    if (diagonal and (i+k >= f or j+k >= c or paraula[k] !=sopa[i+k][j+k])) 
                    diagonal = false;
                }
                if (vertical or horitzontal or diagonal)
                convertir_majuscules(resultat, i, j, l_paraula, vertical, horitzontal, diagonal);
            } 
        }
    } 
}

Matriu entrar_matriu(int f, int c) {
    Matriu m(f, vector<char>(c));
    for (int i = 0; i < f; ++i) {
        int j = 0;
        while (j < c) {
            char a;
            cin >> a;
            if (a != ' ') {
            m[i][j] = a;
            ++j; 
            }
        } 
    }
    return m; 
}

int main() {
    int x;
    bool primer = true;
    while (cin >> x) {
        int f, c;
        cin >> f >> c;
        vector<string> paraules(x);
        for (int i = 0; i < x; ++i) cin >> paraules[i];
        Matriu sopa = entrar_matriu(f, c);
        Matriu resultat = sopa;
        for (int i = 0; i < x; ++i) {
            resoldre_paraula(sopa, resultat, f, c, paraules[i]);
        }
        if (not primer) cout << endl;
        else primer = false;
        for (int i = 0; i < f; ++i) {
            cout << resultat[i][0];
            for (int j = 1; j < c; ++j) {
                cout << ' ' << resultat[i][j];
            }
            cout << endl;
        }
} }