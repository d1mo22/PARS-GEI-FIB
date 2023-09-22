#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Reversing words (2)

vector<string> read(vector<string>& words, int m) {
    for (int j = m - 1; j >= 0; --j) {
        cin >> words[j];
    }
    return words;
}

void reverse_word(const string& s) {
    int n = s.size();
    for (int i = n - 1; i >= 0; --i) cout << s[i];
    cout << endl;
}

void print_reverse(vector<string>& words, int m) {
    for (int i = 0; i < m; ++i) reverse_word(words[i]);
}

int main() {
    string word;
    int m;
    cin >> m;
    vector<string> words(m);
    read(words, m);
    print_reverse(words, m);
}