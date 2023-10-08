#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    priority_queue<pair<int,string>> espera; 
    string id;
    int i = 7;
    while (i != 0)  {
        cin >> id;
        espera.push(make_pair(id.length(), id));
        --i;
    }
    while (!espera.empty()) {
        pair<int, string> par = espera.top();
        cout << par.first << " " << par.second << endl;
        espera.pop();
    }
     
}