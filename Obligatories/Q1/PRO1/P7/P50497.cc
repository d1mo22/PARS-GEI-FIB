#include <iostream>
#include <string>
using namespace std;

//It is a palindrome?

bool is_palindrome(const string& s) {
  int i, j;
  i = 0;
  j = s.size() - 1;
  bool palin = true;

  while(i < j and palin) {
    palin = (s[i] == s[j]);
    ++i;
    --j;
  }
  return palin;
}


int main() {
    string s;
    while (cin >> s) {
      cout << is_palindrome(s) << endl;
      int n = s.size();
      if (n > 100) {
        char c = s[0];
        s[0] = 'a';
        for (int rep = 1000; rep > 0; --rep) cout << is_palindrome(s) << endl;
        s[0] = c;

        c = s[1];
        s[1] = 'a';
        for (int rep = 1000; rep > 0; --rep) cout << is_palindrome(s) << endl;
        s[1] = c;

        c = s[3];
        s[3] = 'a';
        for (int rep = 1000; rep > 0; --rep) cout << is_palindrome(s) << endl;
        s[3] = c;

        c = s[n-1];
        s[n-1] = 'a';
        for (int rep = 1000; rep > 0; --rep) cout << is_palindrome(s) << endl;
        s[n-1] = c;

        c = s[n-2];
        s[n-2] = 'a';
        for (int rep = 1000; rep > 0; --rep) cout << is_palindrome(s) << endl;
        s[n-2] = c;

        c = s[n-7];
        s[n-7] = 'a';
        for (int rep = 1000; rep > 0; --rep) cout << is_palindrome(s) << endl;
        s[n-7] = c;
      }
    }
}
