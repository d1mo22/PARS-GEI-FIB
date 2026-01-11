package IA.Azamon;

import aima.search.framework.Successor;
import aima.search.framework.SuccessorFunction;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

/**
 * Esta clase genera los sucesores para explorar el espacio de soluciones utilizando los operadores de swap y move.
 */
public class AzamonSuccesorFunction implements SuccessorFunction {
    public List<Successor> getSuccessors(Object state) {
        ArrayList<Successor> retVal = new ArrayList<>();
        AzamonBoard board = (AzamonBoard) state;
        String s = "";
        DecimalFormat decimalFormat = new DecimalFormat("#.###");
        AzamonHeuristicFunction hf = new AzamonHeuristicFunction();
        int nPackages = board.getNPackages();
        int nOffers = board.getNOffers();

        for (int i = 0; i < nPackages; i++) {
            // Generar todos los posibles estados con swap.
            for (int j = i + 1; j < nPackages; j++) {
                AzamonBoard newBoard = new AzamonBoard(board);
                if (newBoard.swapCompatible(i, j)) {
                    newBoard.swapPaquetes(i, j);
                    double v = hf.getHeuristicValue(newBoard);
                    String format = decimalFormat.format(v);
                    s = "Swap package " + i + " with package " + j + " h= " + v;
                    retVal.add(new Successor(s, newBoard));
                }
            }
            // Nodos generados por el move
            for (int j = 0; j < nOffers; j++) {
                AzamonBoard newBoard = new AzamonBoard(board);
                if (newBoard.compatible(i, j)) {
                    newBoard.moverPaquete(i, j);
                    double v = hf.getHeuristicValue(newBoard);
                    String format = decimalFormat.format(v);
                    s = "Move package " + i + " to offer " + j + " h= " + v;
                    retVal.add(new Successor(s , newBoard));
                }
            }
        }
        return retVal;
    }
}