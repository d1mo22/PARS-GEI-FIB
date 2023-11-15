#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

const int ROWS = 100; // Número de filas en el laberinto
const int COLS = 100; // Número de columnas en el laberinto

// Función para imprimir el laberinto
void printMaze(const vector<vector<char> >& maze) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

void newMaze(vector<vector<char>>& maze) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            maze[i][j] = 'X';
        }
    }
}

// Función para generar el laberinto con camino
void generateMaze(vector<vector<char> >& maze, int startRow, int startCol, int endRow, int endCol) {
    // Inicializar el generador de números aleatorios
    srand(static_cast<unsigned>(time(0)));

    // Inicializar el laberinto con 'X'
    for (int i = 0; i <= ROWS; ++i) {
        vector<char> row;
        for (int j = 0; j <= COLS; ++j) {
            row.push_back('X');
        }
        maze.push_back(row);
    }

    // Establecer la posición de inicio y fin del laberinto
    maze[startRow][startCol] = '.';

    // Generar caminos aleatorios en el laberinto
    for (int i = 0; i < ROWS * COLS - 10; ++i) {
        int row = rand() % (ROWS - 2) + 1; // Generar una fila aleatoria, evitando el borde
        int col = rand() % (COLS - 2) + 1; // Generar una columna aleatoria, evitando el borde

        // Establecer el camino en la posición aleatoria
        maze[row][col] = '.';
    }
    maze[endRow][endCol] = 't';
}

// Función para verificar la conectividad usando DFS
bool isPathExistsDFS(const vector<vector<char> >& maze, int startRow, int startCol, int endRow, int endCol) {
    vector<vector<bool> > visited(ROWS, vector<bool>(COLS, false));
    stack<pair<int, int> > s;
    s.push(make_pair(startRow, startCol));

    while (!s.empty()) {
        int currentRow = s.top().first;
        int currentCol = s.top().second;
        s.pop();

        if (currentRow == endRow && currentCol == endCol) {
            return true; // Se encontró un camino
        }

        if (currentRow < 0 || currentRow >= ROWS || currentCol < 0 || currentCol >= COLS || maze[currentRow][currentCol] == 'X' || visited[currentRow][currentCol]) {
            continue;
        }

        visited[currentRow][currentCol] = true;

        // Agregar vecinos
        s.push(make_pair(currentRow - 1, currentCol));
        s.push(make_pair(currentRow + 1, currentCol));
        s.push(make_pair(currentRow, currentCol - 1));
        s.push(make_pair(currentRow, currentCol + 1));
    }

    return false; // No hay camino
}

int main() {
    // Crear el laberinto
    vector<vector<char> > maze;

    // Generar el laberinto con camino
    generateMaze(maze, 1, 1, ROWS - 2, COLS - 2);
    while(!isPathExistsDFS(maze, 1, 1, ROWS - 2, COLS - 2)) {
        newMaze(maze);
        generateMaze(maze, 1, 1, ROWS - 2, COLS - 2);
    } 
    // Imprimir el laberinto
    printMaze(maze);
    return 0;
}
