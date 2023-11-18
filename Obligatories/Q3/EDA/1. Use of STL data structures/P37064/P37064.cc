#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    set<string> words;
    auto mediana = words.end();
    string word;
    bool imparell = 0;
    while (cin >> word and word != "END") {
        auto it = words.insert(word).first;
        imparell = not imparell;
        if (mediana == words.end()) mediana = it;
        else if (imparell and word > *mediana) ++mediana;
        else if (not imparell and word < *mediana) --mediana;
        cout << *mediana << endl;

    }
}