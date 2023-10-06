#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    string action, word;
    map<string, int> bag;
    while (cin >> action) {
        if (action == "maximum?") {
            if (bag.empty()) cout << "indefinite maximum" << endl;
            else {
                auto it = --bag.end();
                cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
        }
        else if(action == "minimum?") {
            if (bag.empty()) cout << "indefinite minimum" << endl;
            else cout << "minimum: " << bag.begin()->first << ", " << bag.begin()->second << " time(s)" << endl;
        }
        else if (action == "store") {
            cin >> word;
            if (bag.find(word) != bag.end()) ++bag[word];
            else bag[word] = 1;
        }
        else if (action == "delete") {
            cin >> word;
            if (bag[word] > 1) --bag[word];
            else bag.erase(word);
        }
    }
}