package IA.ProbIA5;

import java.util.Arrays;

/**
 * Created by bejar on 17/01/17.
 */
public class ProbIA5Board {
    /* Class independent from AIMA classes
       - It has to implement the state of the problem and its operators
     *

    /* State data structure
        vector with the parity of the coins (we can assume 0 = heads, 1 = tails
     */

    private int [] board;
    private static int [] solution;

    /* Constructor */
    public ProbIA5Board(int []init, int[] goal) {

        board = new int[init.length];
        solution = new int[init.length];

        for (int i = 0; i< init.length; i++) {
            board[i] = init[i];
            solution[i] = goal[i];
        }

    }

    /* vvvvv TO COMPLETE vvvvv */
    public void flip_it(int i){
        // flip the i-th coin
        board[i] = 1 - board[i];
    }

    /* Heuristic function */
    public double heuristic(){
        int h = 0;
        for (int i = 0; i < board.length; i++) {
            if (board[i] != solution[i]) h++;
        }
        return h;
    }

     /* Goal test */
     public boolean is_goal(){
         // compute if board = solution
         return Arrays.equals(board, solution);
     }

     /* auxiliary functions */

     // Some functions will be needed for creating a copy of the state

    /* ^^^^^ TO COMPLETE ^^^^^ */

    public ProbIA5Board copy(){
        int [] new_board = new int[board.length];
        for (int i = 0; i < board.length; i++) {
            new_board[i] = board[i];
        }
        return new ProbIA5Board(new_board, solution);
    }

    public int getLength(){
        return board.length;
    }

}
