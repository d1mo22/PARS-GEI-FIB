# Azamon Package Assignment

This project implements a search algorithm to solve a package assignment problem using the Azamon framework. The program allows the user to choose between two algorithms: Hill Climbing and Simulated Annealing.

## Table of Contents

- [Usage](#usage)
- [Algorithms](#algorithms)
    - [Hill Climbing](#hill-climbing)
    - [Simulated Annealing](#simulated-annealing)
- [Classes](#classes)

## Usage
1. Clone the repository:
    ```sh
    git clone https://github.com/d1mo22/IA-Practica-1.git
    ```
   
2. Change to the project directory:
    ```sh
    cd IA-Practica-1
    ```
3. Add execution permissions to the `run` script:
    ```sh
    chmod +x run
    ```

4. Run the `run` script:
    ```sh
    ./run
    ```
   
5. Follow the prompts to select the initial state and the algorithm to use.
6. The program will execute the chosen algorithm and print the total price and execution time.

## Algorithms

### Hill Climbing

The Hill Climbing algorithm is implemented in the `HillClimbing` method

### Simulated Annealing

The Simulated Annealing algorithm is implemented in the `SimulatedAnnealing` method.

## Classes

- **Main**: The entry point of the program. It handles user input and executes the chosen algorithm.
- **AzamonBoard**: Represents the state of the package assignment problem.
- **AzamonSuccesorFunction**: Generates successor states for the Hill Climbing algorithm.
- **AzamonHeuristicFunction**: Evaluates the heuristic value of a state.
- **AzamonHeuristicFunctionHappiness**: Evaluates the heuristic value of a state based on the happiness of the delivery. 
- **AzamonGoalTest**: Checks if a state is a goal state.