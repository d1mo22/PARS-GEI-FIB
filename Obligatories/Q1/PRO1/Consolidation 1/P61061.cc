#include <iostream>
using namespace std;

int main() {
    int n;
    int sum = 1;

    while (cin >> n) {
        
        if (n/10 == 0){
            cout << "The product of the digits of " << n << " is " 
            << n << "." << endl;
            cout << "----------" << endl; 
        } 
        
        else {
            while (n/10 != 0) {
            
                for (int i = n; i > 0; i /= 10) sum *= i%10;
                cout << "The product of the digits of " << n << " is " 
                << sum << "." << endl;
            
                if (sum/10 == 0) cout << "----------" << endl;
            
                n = sum;
                sum = 1;
            }
        }
    }
}