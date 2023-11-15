//Caminos de una largada minima
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

const int ROWS = 100; // Número de filas en el laberinto
const int COLS = 100; // Número de columnas en el laberinto

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

// Función para imprimir el laberinto
void printMaze(const vector<vector<char> >& maze) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

//Funcion para generar un laberinto con 'X'
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
    for (int i = 0; i < ROWS; ++i) {
        vector<char> row;
        for (int j = 0; j < COLS; ++j) {
            row.push_back('X');
        }
        maze.push_back(row);
    }

    // Establecer la posición de inicio y fin del laberinto
    maze[startRow][startCol] = 'S';

    // Generar caminos aleatorios en el laberinto
    for (int i = 0; i < (ROWS * COLS) - 10; ++i) {
        int row = rand() % (ROWS - 2) + 1; // Generar una fila aleatoria, evitando el borde
        int col = rand() % (COLS - 2) + 1; // Generar una columna aleatoria, evitando el borde

        // Establecer el camino en la posición aleatoria
        if (maze[row][col] != 'S') maze[row][col]= '.';
    }
    maze[endRow][endCol] = 't';
}

int main() {
    // Crear el laberinto
    vector<vector<char> > maze;
    srand(time(NULL));
    int i_start = rand() % (ROWS - 3) + 1;
    int j_start = rand() % (COLS - 3) + 1;
    int i_end = rand() % (ROWS - 3) + 1;
    int j_end = rand() % (COLS - 3) + 1;
    int i = 0;
    // Generar el laberinto con camino
    generateMaze(maze, i_start, j_start, i_end, j_end);
    while(!isPathExistsDFS(maze,i_start, j_start, i_end, j_end)) {
        srand(time(NULL) + i);
        newMaze(maze);
        i_start = rand() % (ROWS - 3) + 1;
        j_start = rand() % (COLS - 3) + 1;
        i_end = rand() % (ROWS - 3) + 1;
        j_end = rand() % (COLS - 3) + 1;
        generateMaze(maze, i_start, j_start, i_end, j_end);
        ++i;
    } 
    // Imprimir el laberinto
    cout << i_start << " " << j_start << endl;
    printMaze(maze);
    return 0;
}
