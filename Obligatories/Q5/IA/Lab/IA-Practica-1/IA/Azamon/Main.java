package IA.Azamon;

import aima.search.framework.Problem;
import aima.search.framework.Search;
import aima.search.framework.SearchAgent;
import aima.search.informed.HillClimbingSearch;
import aima.search.informed.SimulatedAnnealingSearch;

import java.util.List;
import java.util.Scanner;
import java.util.Properties;

/**
 * Clase principal para resolver la práctica de búsqueda local, Ázamon.
 */
public class Main {
    // Variables de configuración para el problema
    static int numPaquetes = 100;
    static float proporcionPaquetes = 1.2f;
    static int seed = 1234;
    static int estadoInicial = 0;
    static int heuristico = 1;
    static int debugMode = 0;
    static int algoritmo = 1;
    static double happinessConstant = 1;

    /**
     * Muestra un menú para que el usuario seleccione los parámetros de configuración.
     */
    static void menuInicial() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("¿Qué seed quieres?");
        seed = scanner.nextInt();

        System.out.println("Estado inicial 0 (ordenar por prioridad) o 1 (ordenar por paquetes por peso y ofertas por ratio precio/capacidad)");
        estadoInicial = scanner.nextInt();

        System.out.println("¿Qué heurístico quieres usar?\n (1) Precio\n (2) Precio+Felicidad");
        heuristico = scanner.nextInt();

        if (heuristico == 2) {
            System.out.println("¿Qué proporción de felicidad quieres?");
            happinessConstant = scanner.nextDouble();
        }

        System.out.println("¿Quieres debuggear?\n (1) Si\n (2) No");
        debugMode = scanner.nextInt();

        System.out.println("Algoritmo a usar:\n (1) Hill Climbing\n (2) Simulated Annealing");
        algoritmo = scanner.nextInt();


    }

    /**
     * Método principal que inicializa el problema.
     *
     * @param args argumentos de la línea de comandos (no utilizados).
     */
    public static void main(String[] args) {
        menuInicial();

        Paquetes listaPaquetes = new Paquetes(numPaquetes, seed);
        Transporte listaTransporte = new Transporte(listaPaquetes, proporcionPaquetes, seed);
        AzamonBoard azamonBoard = new AzamonBoard(listaPaquetes, listaTransporte, estadoInicial);
        azamonBoard.setHappinessConstant(happinessConstant);

        switch(algoritmo) {
            case 1:
                if (heuristico == 1)
                    HillClimbing(azamonBoard, debugMode);

                else
                    HillClimbingHappiness(azamonBoard, debugMode);

            break;

            case 2:
                if (heuristico == 1)
                    simulatedAnnealing(azamonBoard, debugMode, 10000, 1, 0.01);
                else
                    simulatedAnnealingHappiness(azamonBoard, debugMode, 10000, 1, 0.01);
                break;

            default:
                System.out.println("Argumento para algoritmo no válido.");
        }
    }

    /**
     * Ejecuta el algoritmo de Hill Climbing utilizando el heurístico de precio.
     *
     * @param board Estado inicial del problema.
     * @param debug Modo debug (1 para activar, 0 para desactivar).
     */
    private static void HillClimbing(AzamonBoard board, int debug) {
        System.out.println("\nHill Climbing");

        try {
            long time = System.currentTimeMillis();

            Problem problem = new Problem(board, new AzamonSuccesorFunction(), new AzamonGoalTest(), new AzamonHeuristicFunction());
            Search search = new HillClimbingSearch();
            SearchAgent agent = new SearchAgent(problem, search);
            AzamonBoard newBoard = (AzamonBoard) search.getGoalState();
            time = System.currentTimeMillis() - time;
            newBoard.printState();
            printInstrumentation(agent.getInstrumentation());
            System.out.printf("Precio total: %.3f\n", newBoard.getTotalPrice());
            if (debug == 1) {
                printActions(agent.getActions());
                printInstrumentation(agent.getInstrumentation());
                newBoard.printState();
            }
            System.out.println("Tiempo de ejecucion: " + time + "ms\n");

        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Ejecuta el algoritmo de Hill Climbing utilizando el heurístico de precio + felicidad.
     *
     * @param board Estado inicial del problema.
     * @param debug Modo debug (1 para activar, 0 para desactivar).
     */
    private static void HillClimbingHappiness(AzamonBoard board, int debug) {
        System.out.println("\nHill Climbing Happiness");
        try {
            long time = System.currentTimeMillis();
            Problem problem = new Problem(board, new AzamonSuccesorFunction(), new AzamonGoalTest(), new AzamonHeuristicFunctionHappiness());
            Search search = new HillClimbingSearch();
            SearchAgent agent = new SearchAgent(problem, search);
            time = System.currentTimeMillis() - time;
            double happiness = ((AzamonBoard) search.getGoalState()).getHappinessConstant();
            AzamonBoard newBoard = (AzamonBoard) search.getGoalState();

            System.out.printf("Precio: %.3f\n", newBoard.getHappinessPrice());

            printInstrumentation(agent.getInstrumentation());
            if (debug == 1) {
                printActions(agent.getActions());
                printInstrumentation(agent.getInstrumentation());
                newBoard.printState();
            }
            System.out.println("Tiempo de ejecucion: " + time + "ms\n");
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Ejecuta el algoritmo de Simulated Annealing utilizando el heurístico de precio.
     *
     * @param board Estado inicial del problema.
     * @param debug Modo debug (1 para activar, 0 para desactivar).
     * @param steps Número de pasos.
     * @param k Parámetro k del algoritmo.
     * @param l Parámetro lambda del algoritmo.
     */
    private static void simulatedAnnealing(AzamonBoard board, int debug, int steps, int k, double l) {
        try {
            long timeInitial = System.currentTimeMillis();

            Problem p = new Problem(board, new AzamonSuccesorFunction(), new AzamonGoalTest(), new AzamonHeuristicFunction());
            Search search = new SimulatedAnnealingSearch(steps, 100, k, l);
            SearchAgent agent = new SearchAgent(p, search);
            AzamonBoard newBoard = (AzamonBoard) search.getGoalState();

            long timeFinal = System.currentTimeMillis();

            printInstrumentation(agent.getInstrumentation());
            if (debug == 1) {
                printActions(agent.getActions());
                newBoard.printState();
            }

            System.out.printf("Precio total: %.2f\n", newBoard.getTotalPrice());
            System.out.println("Time elapsed: " + (timeFinal - timeInitial) + "ms");


        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Ejecuta el algoritmo de Simulated Annealing utilizando el heurístico de precio.
     *
     * @param board Estado inicial del problema.
     * @param debug Modo debug (1 para activar, 0 para desactivar).
     * @param steps Número de pasos.
     * @param k Parámetro k del algoritmo.
     * @param l Parámetro lambda del algoritmo.
     */
    private static void simulatedAnnealingHappiness(AzamonBoard board, int debug, int steps, int k, double l) {
        try {
            long timeInitial = System.currentTimeMillis();

            Problem p = new Problem(board, new AzamonSuccesorFunction(), new AzamonGoalTest(), new AzamonHeuristicFunctionHappiness());
            Search search = new SimulatedAnnealingSearch(steps, 100, k, l);
            SearchAgent agent = new SearchAgent(p, search);
            AzamonBoard newBoard = (AzamonBoard) search.getGoalState();

            long timeFinal = System.currentTimeMillis();

            printInstrumentation(agent.getInstrumentation());
            if (debug == 1) {
                printActions(agent.getActions());
                newBoard.printState();
            }

            System.out.printf("Precio: %.2f\n", newBoard.getHappinessPrice());
            System.out.println("Time elapsed: " + (timeFinal - timeInitial) + "ms");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //Funcion que imprime los pasos que ha seguido el algoritmo
    private static void printInstrumentation(Properties properties) {
        for (Object o : properties.keySet()) {
            String key = (String) o;
            String property = properties.getProperty(key);
            System.out.println(key + " : " + property);
        }
    }

    private static void printActions(List actions) {
        for (Object o : actions) {
            String action = (String) o;
            System.out.println(action);
        }
    }
}