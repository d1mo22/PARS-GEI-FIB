#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> matrix;
typedef vector<int> VI;
typedef vector<VI> VVB;

VVB cols, rows, sq;
matrix sudoku(9, vector<char>(9));

void print() {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j)
        cout << (j ? " " : "") << sudoku[i][j];
        cout << endl;
    }
}

bool solucio(int idx, matrix& sudoku, const vector<pair<int,int>>& punts) {
    if (idx == punts.size()) {
        print();
        return true;
    }

    else {
        for (int i = 1; i < 10; ++i) {
            int x = punts[idx].first;
            int y = punts[idx].second;
            int z = (x/3)*3 + y/3;
            if (!cols[y][i] and !rows[x][i] and !sq[z][i]) {
                cols[y][i] = rows[x][i] = sq[z][i] = true;
                sudoku[x][y] = i + '0';
                if (solucio(idx+1, sudoku, punts)) return true;
                cols[y][i] = rows[x][i] = sq[z][i] = false;
            }
        }
        return false;
    }
}

int main() {
    int n; cin >> n;
    cout << n << endl;
    while (n--) {
        cout << endl;
        vector<pair<int,int>> punts;
        cols = rows = sq = VVB(10, VI(10, false));
        for (int i = 0; i < 9; ++i) 
            for (int j = 0; j < 9; ++j) {
                char c; cin >> c;
                if (c == '.') punts.push_back({i, j});
                else {
                    int x = c - '0';
                    int quadrat = (i/3)*3 + j/3;
                    if (!cols[j][x] and !rows[i][x] and !sq[quadrat][x]) {
                        cols[j][x] = rows[i][x] = sq[quadrat][x] = true;
                    }
                }
                sudoku[i][j] = c;
            }
        solucio(0, sudoku, punts);
    }
}