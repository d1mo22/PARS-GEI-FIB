import nashpy as nash
import numpy as np


def prob_2():
    fila = np.array([
        [-1, 2],
        [1, 0]
    ])
    columna = np.array([
        [-1, 1],
        [2, 0]
    ])
    return fila, columna


def prob_3():
    fila = np.array([
        [2, 0],
        [0, 1]
    ])
    columna = np.array([
        [2, 0],
        [0, 1]
    ])
    return fila, columna


def prob_4():
    fila = np.array([
        [5, -5],
        [2, 0]
    ])
    columna = np.array([
        [5, 2],
        [-5, 0]
    ])
    return fila, columna


def prob_5():
    fila = np.array([
        [1, 3],
        [4, 0]
    ])
    columna = np.array([
        [-1, 0],
        [2, -1]
    ])
    return fila, columna


def prob_6():
    fila = np.array([
        [1, -2, 0],
        [-2, 1, 0],
        [0, 0, 1]
    ])
    columna = np.array([
        [-2, 1, 0],
        [1, -2, 0],
        [0, 0, 1]
    ])
    return fila, columna


if __name__ == '__main__':
    problem_functions = {
        '2': prob_2,
        '3': prob_3,
        '4': prob_4,
        '5': prob_5,
        '6': prob_6
    }
    x = input("Introduce el numero del problema (2-6): ")
    A, B = problem_functions[x]()
    game = nash.Game(A, B)

    equilibrios = game.support_enumeration()

    for i, eq in enumerate(equilibrios):
        is_mixed_j1 = np.any((eq[0] > 0) & (eq[0] < 1))
        is_mixed_j2 = np.any((eq[1] > 0) & (eq[1] < 1))
        is_mixed = is_mixed_j1 or is_mixed_j2

        print(f"\nEquilibrio {i+1}:")

        if is_mixed:
            print("Tipo: Estrategia Mixta")
        else:
            print("Tipo: Estrategia Pura")

        print("Estrategia Jugador 1:", eq[0])
        print("Estrategia Jugador 2:", eq[1])

        utilidad_j1 = eq[0] @ A @ eq[1]
        utilidad_j2 = eq[0] @ B @ eq[1]
        print(f"Utilidad esperada - Jugador 1: {utilidad_j1:.4f}")
        print(f"Utilidad esperada - Jugador 2: {utilidad_j2:.4f}")
