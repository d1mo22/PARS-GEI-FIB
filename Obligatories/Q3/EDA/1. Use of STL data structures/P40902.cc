#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    map<string, int> players;
    string name, action;
    int value;
    while (cin >> name >> action) {
        if (action == "enters") {
            if (players.find(name) == players.end()) players[name] = 0;
            else cout << name << " is already in the casino" << endl;
        }
        else if (action == "wins") {
            cin >> value;
            if (players.find(name) != players.end()) players[name] += value; 
            else cout << name << " is not in the casino" << endl;
        }
        else if (action == "leaves") {
            if (players.find(name) != players.end()) {
                cout << name << " has won " << players[name] << endl;
                players.erase(name);
            } 
            else cout << name << " is not in the casino" << endl;
        }
    }
    cout << "----------" << endl;
    for (pair<string, int> x: players) {
        cout << x.first << " is winning " << x.second << endl;
    }

}