#include "BinTreeIOParInt.hh"

void Nivell(const BinTree<ParInt>& a, int& n, int& company, int& profunditat, int& trobat) 
{
    if (trobat == -1 and not a.empty()) {
        ParInt p = a.value();
        if (p.primer() == n) {
            company = p.segon();
            trobat = profunditat;
        } 
        else {
            ++profunditat;
            Nivell(a.right(), n, company, profunditat, trobat);
            Nivell(a.left(), n, company, profunditat, trobat);
            --profunditat;
        }
    }
}

int main() {
    BinTree<ParInt> a;
    read_bintree_parint(a);
    int n;
    while (cin >> n) {
        int profunditat, company = 0;
        int trobat = -1;
        Nivell(a, n, company, profunditat, trobat);
        if (trobat != -1) cout << n << " " << company << " " << trobat << endl;
        else cout << -1 << endl;
    }
}