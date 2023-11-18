#include <iostream>
#include <string>
#include <queue>
using namespace std;

string s;

struct comp {
    bool operator()(const string& a, const string& b) {
        if (a.length() == b.length()) {
            string new_char = s.substr(0, a.length());
            if (a == new_char) return false;
            if (b == new_char) return true;
            if (a < b) {
                if (a < new_char and b > new_char) return true;
                return false;
            }
            else {
                if (a > new_char and b < new_char) return false;
                return true;
            }
        }
        else return a.length() > b.length();
    }
};

int main() {
    while (cin >> s) {
        priority_queue<string, vector<string>, comp> espera; 
        string id;
        char accio;
        int tiquets = 0;
        while (cin >> accio and accio != 'E') {
            if (accio == 'S') {
                cin >> id;
                espera.push(id);
            }
            else if (accio == 'T') ++tiquets;

            while (tiquets > 0 and (!espera.empty())) {
                cout << espera.top() << endl;
                espera.pop();
                --tiquets;
            }
        }
        cout << tiquets << " ticket(s) left" << endl;
        cout << espera.size() << " supporter(s) with no ticket" << endl << endl;
    }
     
}