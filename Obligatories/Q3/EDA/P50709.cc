#include <iostream>
#include <queue>

using namespace std;

int main() {
    priority_queue<int> pq;
    char op;
    while (cin >> op) {
        if (op == 'S') {
            int value; cin >> value;
            pq.push(value);
        }
        else if (op == 'A') {
            if (pq.empty()) cout << "error!" << endl;
            else cout << pq.top() << endl;
        }
        else if (op == 'R') {
            if (pq.empty()) cout << "error!" << endl;
            else pq.pop();
        }
        else if (op == 'I') {
            int value; cin >> value;
            if (pq.empty()) cout << "error!" << endl;
            else {
                value = pq.top() + value;
                pq.pop();
                pq.push(value);
            }
        }
        else if (op == 'D') {
            int value; cin >> value;
            if (pq.empty()) cout << "error!" << endl;
            else {
                value = pq.top() - value;
                pq.pop();
                pq.push(value);
            }
        }

    }
}