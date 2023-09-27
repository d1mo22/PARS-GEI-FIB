#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

/*struct comp {
};*/

int main() {
    set<string> logged;
    map<string, int> elo;
    string s;
    while (cin >> s) {
        string player; cin >> player;
        if (s == "LOGIN") {
            if (logged.find(player) == logged.end()) {
                logged.insert(player);
                elo.insert(make_pair(player,1200));
            }
        }
        else if (s == "LOGOUT") {
            logged.erase(player);
        }
        else if (s == "PLAY") {
            string player2; cin >> player2;
            if (logged.find(player) == logged.end() or logged.find(player2) == logged.end()) {
                cout << "player(s) not connected" << endl;
            }
            else {
                elo[player] += 10;
                elo[player2] = max(1200, elo[player2] - 10);
            }
        }
        else {
            cout << player << " " << elo[player] << endl;
        }
    }
    cout << endl << "RANKING" << endl;

    vector<pair<int, string>> ranking;
    for (const auto &it : elo) {
        ranking.emplace_back(-it.second, it.first);
    }
    sort(ranking.begin(), ranking.end());
    for (const auto &it : ranking) cout << it.second << " " << -it.first << endl;

}