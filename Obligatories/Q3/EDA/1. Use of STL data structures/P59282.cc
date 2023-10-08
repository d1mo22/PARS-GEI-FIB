#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> numbers;
    string action;
    int num, max;
    double sum = 0;
    cout.setf(ios::fixed);
    cout.precision(4);

    while (cin >> action) {
        if (action == "number") {
            cin >> num;
            sum += num;
            if (numbers.empty()) max = num;
            else if (num > max) max = num;
            numbers.push(num);    
        }
        else if (not numbers.empty() and action == "delete")  {
            sum -= numbers.top();
            numbers.pop();
        } 


        if (numbers.empty()) cout << "no elements" << endl;
        else {
           cout << "minimum: " << numbers.top() << 
           ", maximum: " << max << 
           ", average: " << sum/numbers.size() << endl; 
        }
    }
}