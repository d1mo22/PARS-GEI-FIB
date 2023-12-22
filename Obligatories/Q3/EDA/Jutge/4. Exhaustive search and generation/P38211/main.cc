#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> t;
vector<int> mc, md1, md2;

int diagonal1(int i, int j) {return i+j;}
int diagonal2(int i, int j) {return i-j + n-1;}

void escriu() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << (t[i] == j ? 'Q' : '.');
        cout << endl;
    }
}

bool reines(int i) {
    if (i == n) {
        escriu();
        return true;
    }
    else {
        for (int j = 0; j < n; ++j) {
            if (!mc[j] and !md1[diagonal1(i,j)] and !md2[diagonal2(i,j)]) {
                t[i] = j;
                mc[j] = md1[diagonal1(i,j)] = md2[diagonal2(i,j)] = true;
                if (reines(i+1)) return true;
                mc[j] = md1[diagonal1(i,j)] = md2[diagonal2(i,j)] = false;
            }
        }
        return false;
    }
}

int main(){
    cin >> n;
    t = vector<int>(n);
    mc = vector<int>(n, false);
    md1 = md2 = vector<int>(2*n-1, false);
    if (!reines(0)) cout << "NO SOLUTION\n";
}