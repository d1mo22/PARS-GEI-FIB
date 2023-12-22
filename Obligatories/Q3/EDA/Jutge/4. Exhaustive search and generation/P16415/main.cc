#include <iostream>
#include <vector>
using namespace std;

int diagonal1(int i, int j) {return i+j;}

int diagonal2(int i, int j, int n) {return i-j+n-1;}

int reines(int i, int n,vector<int>& t,vector<int>&mc,vector<int>&md1,vector<int>&md2) {
    if (i == n) return 1;
    else {
        int resultats = 0;
        for (int j = 0; j < n; ++j) {
            if(!mc[j] and !md1[diagonal1(i,j)] and !md2[diagonal2(i,j,n)]) {
                t[i] = j;
                mc[j] = md1[diagonal1(i,j)] = md2[diagonal2(i,j,n)] = true;
                resultats += reines(i+1, n, t, mc, md1, md2);
                mc[j] = md1[diagonal1(i,j)] = md2[diagonal2(i,j,n)] = false;
            }
        }
        return resultats;
    }    

}

int main() {
    int n; cin >> n;
    vector<int> t(n);
    vector<int> mc(n, false);
    vector<int> md1(2*n-1, false), md2(2*n-1, false);
    cout << reines(0, n, t, mc, md1, md2) << endl;
}