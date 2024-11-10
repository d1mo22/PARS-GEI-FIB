#include "BinTreeIOEst.hh"

// Pre: a és buit; el canal estandar d’entrada conté una seqüència
// de parells <int, double> que representa un arbre binari d’estudiants
// en preordre, on un parell amb l’int = ‘‘marca’’ representa
// un arbre buit
// Post: a conté l’arbre que hi havia al canal estandar d’entrada
void read_bintree_est(BinTree<Estudiant>& a) {
    Estudiant est;
    est.llegir();
    if (est.consultar_DNI() != 0) {
        BinTree<Estudiant> a1;
        BinTree<Estudiant> a2;
        
        read_bintree_est(a1); //left
        read_bintree_est(a2); //right
        a = BinTree<Estudiant>(est, a1, a2);
    }
}

// Pre: a = A
// Post: s’han escrit al canal estandar de sortida els elements
// d’a recorreguts en inordre, a = A
void write_bintree_est(const BinTree<Estudiant>& a) {
    if (not a .empty()) {
        write_bintree_est(a.right());
        a.value().escriure();
        write_bintree_est(a.left());
    }
}

