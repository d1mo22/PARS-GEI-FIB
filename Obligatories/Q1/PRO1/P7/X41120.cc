#include <iostream>
#include <vector>
using namespace std;

vector<int> calcula_cims(const vector<int>& v) {
    int tam_v = v.size();
    vector<int> u;
    for (int i = 1; i < tam_v - 1; ++i) {
        if (v[i] > v[i - 1] && v[i] > v[i + 1]) {
            u.push_back(v[i]);
        }
    }
    return u;
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<int> cims = calcula_cims(v);
    int num_cims = cims.size();
    int ult_cim = cims.empty() ? 0 : cims.back();

    cout << num_cims << ":";
        for (int cim : cims) {
            cout << " " << cim;
        }
    cout << endl;

    bool found_higher = false;
    for (size_t i = 0; i < cims.size(); ++i) {
        if (cims[i] > ult_cim) {
            if (found_higher) {
                cout << " ";
            }
            cout << cims[i];
            found_higher = true;
        }
    }
    if (!found_higher) {
        cout << "-";
    }
    cout << endl;

    return 0;
}