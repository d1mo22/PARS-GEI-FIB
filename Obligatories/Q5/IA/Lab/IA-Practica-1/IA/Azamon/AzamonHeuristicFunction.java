package IA.Azamon;

import aima.search.framework.HeuristicFunction;

/**
 * Esta clase implementa la función heurística que únicamente tiene en cuenta el coste.
 */
public class AzamonHeuristicFunction implements HeuristicFunction {
    /**
     * Calcula el valor heurístico para el estado pasado por parámetro.
     *
     * @param state el estado actual del tablero de Azamon.
     * @return el valor heurístico en el estado actual.
     */
    public double getHeuristicValue(Object state) {
        AzamonBoard board = (AzamonBoard) state;
        return board.getTotalPrice();
    }
}