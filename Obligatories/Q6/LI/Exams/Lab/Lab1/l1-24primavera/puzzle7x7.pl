%%%%%%% begin puzzle 7x7 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% grid(NR,NC): the tatamibari puzzle has NR rows and NC columns
grid(7,7).

% coordinates [I,J] mean: symbol at row I (1 <= I <= NR), column J (1 <= J <= NC)
horizontal([[1,5],[2,5],[4,2],[5,3],[5,5],[7,3],[7,6]]).    % location of the – symbols
vertical([[1,6],[2,1],[2,7],[6,6]]).                        % location of the | symbols
cross([[1,1],[2,2],[4,6],[7,5]]).                           % location of the + symbols

%    Input (15 symbols)   Solution for input                   Regions (upper left cell coordinates,
%    (dots represent      (regions are described by cells      height, width, and letter)
%    empty cells)         containing the same letter)
%
%      1 2 3 4 5 6 7        1 2 3 4 5 6 7                       1. r(1,1,1,1)  a
%    1 + · · · – | ·      1 a b b c c d e                       2. r(1,2,2,2)  b
%    2 | + · · – · |      2 f b b g g d e                       3. r(1,4,1,2)  c
%    3 · · · · · · ·      3 f h h h i i e                       4. r(1,6,2,1)  d
%    4 · – · · · + ·      4 f h h h i i e                       5. r(1,7,6,1)  e
%    5 · · – · – · ·      5 j j j k k l e                       6. r(2,1,3,1)  f
%    6 · · · · · | ·      6 j j j m m l e                       7. r(2,4,1,2)  g
%    7 · · – · + – ·      7 n n n m m o o                       8. r(3,2,2,3)  h
%                                                               9. r(3,5,2,2)  i
%                                                              10. r(5,1,2,3)  j
%                                                              11. r(5,4,1,2)  k
%                                                              12. r(5,6,2,1)  l
%                                                              13. r(6,4,2,2)  m
%                                                              14. r(7,1,1,3)  n
%                                                              15. r(7,6,1,2)  o

%%%%%%% end puzzle 7x7 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
