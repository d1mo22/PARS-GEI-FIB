#include <iostream>
using namespace std;

int main() {
    string s;
    cin >> s;

    int count = 1;
    int max_count = 1;
    
    string seq;

    while (cin >> seq) {
        
        if (s != seq) count = 0;
        else {
            ++count;
            if (count > max_count) max_count = count;
        }
    }
    
    cout << max_count << endl;
}