#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

const int ROWS = 100; // Número de filas en el laberinto
const int COLS = 100; // Número de columnas en el laberinto

int findSymbolBFSWithPathLength(const vector<vector<char>>& maze, int startRow, int startCol, char symbol) {
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
    queue<pair<int, int>> q;
    int pathLength = 0;

    q.push(make_pair(startRow, startCol));

    while (!q.empty()) {
        int currentRow = q.front().first;
        int currentCol = q.front().second;
        q.pop();

        pathLength++;

        if (maze[currentRow][currentCol] == symbol) {
            return pathLength; // Se encontró el símbolo 't', devuelve la longitud del camino
        }

        if (currentRow < 0 || currentRow >= ROWS || currentCol < 0 || currentCol >= COLS || maze[currentRow][currentCol] == 'X' || visited[currentRow][currentCol]) {
            pathLength--;
            continue;
        }

        visited[currentRow][currentCol] = true;

        // Agregar vecinos
        q.push(make_pair(currentRow - 1, currentCol));
        q.push(make_pair(currentRow + 1, currentCol));
        q.push(make_pair(currentRow, currentCol - 1));
        q.push(make_pair(currentRow, currentCol + 1));
    }

    return -1; // No se encontró el símbolo 't', devuelve -1
}

void readMaze(vector<vector<char>>& maze) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cin >> maze[i][j];
        }
    }
}

void printMaze(const vector<vector<char> >& maze) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    // Crear el laberinto
    vector<vector<char> > maze(ROWS,vector<char>(COLS));
    readMaze(maze);

    // Llamada a la función BFS para encontrar 't' con longitud del camino
    int lengthBFS = findSymbolBFSWithPathLength(maze, 1, 1, 't');
    if (lengthBFS != -1) {
        cout << "Se encontró el símbolo 't' usando BFS. Longitud del camino: " << lengthBFS << endl;
    } else {
        cout << "No se encontró el símbolo 't' usando BFS." << endl;
    }
}