#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    set<string> has;
    set<pair<int, string>> had;
    string word;
    int i = 1;
    bool quit = false, first = true;

    cin >> word;
    while (not quit) {
        while (word != "END" and word != "QUIT") {
            if (!has.count(word)) {
                has.insert(word);
                had.erase(make_pair(word.length(), word));
            } 
            else {
                has.erase(word);
                had.insert(make_pair(word.length(), word));
            }
            cin >> word;
        }

        if (!first) cout << endl;
        first = false;

        cout << "GAME #" << i << endl << "HAS:" << endl;

        for (string elem : has) cout << elem << endl;

        cout << endl << "HAD:" << endl;
        if (!had.empty()) for (auto it = had.begin(); it != had.end(); ++it) cout << it->second << endl;
        
        ++i; 
        has.erase(has.begin(), has.end());
        had.erase(had.begin(), had.end());

        if (word == "QUIT") quit = true;
        else cin >> word;
    }
}