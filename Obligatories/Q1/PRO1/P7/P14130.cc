#include <iostream>
#include <vector>
using namespace std;

//Equal to the last one

int equal_to_last_one(const vector<int>& v) {
    int n = v.size();
    int last = v[n - 1];
    int counter = 0;
    
    for (int i = 0; i < n - 1; ++i) {
        if (last == v[i]) ++counter;
    }

    return counter;
}

vector <int> read(int n) {
    vector <int> v(n);
    //Llegim el vector de posisio i
    for (int i = 0; i < n; ++i) cin >> v[i];
    return v;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> numbers = read(n);
    cout << equal_to_last_one(numbers) << endl;

}