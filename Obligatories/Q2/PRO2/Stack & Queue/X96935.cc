#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> p;

    int n, num;
    cin >> n;
    
    for (int i = 0; i < (n+1)/2; ++i) {
        cin >> num;
        p.push(num);
    }
    
    bool palindromic = true;

    if (n%2 == 1) p.pop();
    int i = 0;
    while (palindromic and i < n/2) {
        cin >> num;
        if (num == p.top()) p.pop();
        else palindromic = false;
        ++i;
    }
    cout << (palindromic ? "SI" : "NO") << endl;
}