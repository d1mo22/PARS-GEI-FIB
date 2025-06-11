% A matrix which contains zeroes and ones gets "x-rayed" vertically and
% horizontally, giving the total number of ones in each row and column.
% The problem is to reconstruct the contents of the matrix from this
% information. Sample run:
%
%        ?- main.
%            0 0 7 1 6 3 4 5 2 7 0 0
%         0                         
%         0                         
%         8      * * * * * * * *    
%         2      *             *    
%         6      *   * * * *   *    
%         4      *   *     *   *    
%         5      *   *   * *   *    
%         3      *   *         *    
%         7      *   * * * * * *    
%         0                         
%         0                         
%        

:- use_module(library(clpfd)).

example1( [0,0,8,2,6,4,5,3,7,0,0], [0,0,7,1,6,3,4,5,2,7,0,0] ).
example2( [10,4,8,5,6], [5,3,4,0,5,0,5,2,2,0,1,5,1] ).
example3( [11,5,4], [3,2,3,1,1,1,1,2,3,2,1] ).

declareConstraints([],[]).
declareConstraints([RowSum | RowSums], [Row | Rows]) :- 
        sum(Row, #=, RowSum),
        %sum_list(Row, RowSum), 
        declareConstraints(RowSums, Rows). 

matrixByRows(_, [], []).
matrixByRows(S, L, [Row|Rows]):- append(Row,L1,L), length(Row,S), matrixByRows(S,L1,Rows).

main :- example1(RowSums, ColSums),
%1: Variables i domini:	
        length(RowSums, NumRows),
        length(ColSums, NumCols),
        NVars is NumRows*NumCols,
        length(L, NVars),  % generate a list of Prolog vars (their names do not matter)
        L ins 0..1,
%2: Constraints:
        matrixByRows(NumCols, L, MatrixByRows), declareConstraints(RowSums, MatrixByRows),
        transpose(MatrixByRows, MatrixByCols), declareConstraints(ColSums, MatrixByCols),

%3: Labeling:
        label(L),
%4: Escrivim el resultat:
        pretty_print(RowSums, ColSums, MatrixByRows).


pretty_print(_, ColSums, _) :- write('     '), member(S, ColSums), writef('%2r ', [S]), fail.
pretty_print(RowSums, _, M) :- nl, nth1(N, M, Row), nth1(N, RowSums, S), nl, writef('%3r   ', [S]),
                               member(B, Row), wbit(B), fail.
pretty_print(_, _, _)       :- nl.

wbit(1) :- write('*  '), !.
wbit(0) :- write('   '), !.

