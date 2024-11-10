#include "BinTreeIOEst.hh"
#include <iostream>
using namespace std;

int find(const BinTree<Estudiant>& a, int dni, int& mark) {
    if (not a.empty()) {
        if (a.value().consultar_DNI() == dni) {
            if (a.value().te_nota()) mark = a.value().consultar_nota();
            else mark = -1;
            return 0;
        }
        int left = find(a.left(), dni, mark);
        int mark2;
        int right = find(a.right(), dni, mark2);
        if (left != -1 and right != -1) {
            if (left <= right) return left + 1;
            else {
                mark = mark2;
                return right + 1;
            }
        } 
        if (left != -1) return left + 1;
        else if (right != -1) {
            mark = mark2;
            return right + 1;
        }
    }
    return -1;
}

int main() {
    BinTree<Estudiant> a;
    read_bintree_est(a);
    
    int dni, mark;
    while (cin >> dni) {
        int dist = find(a, dni, mark);
        if (dist != -1) {
            if (mark != -1) cout << dni << " " << dist << " " << mark << endl;
            else cout << dni << " " << dist << " " << -1 << endl;
        } else cout << dni << " " << -1 << endl;
    }
}

/*
1 2 
2 3
4 1
0 0
0 0
4 5
5 2
0 0
0 0
0 0
3 4
1 3
0 0
0 0
5 1
0 0
0 0
1
2
3
4
5
6
*/
