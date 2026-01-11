%%%%%%% begin puzzle 4x5 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% grid(NR,NC): the tatamibari puzzle has NR rows and NC columns
grid(4,5).

% coordinates [I,J] mean: symbol at row I (1 <= I <= NR), column J (1 <= J <= NC)
horizontal([[1,4]]).        % location of the – symbols
vertical([[4,2]]).          % location of the | symbols
cross([[3,4]]).             % location of the + symbols

%    Input (3 symbols)   Solution for input                   Regions (upper left cell coordinates,
%    (dots represent     (regions are described by cells      height, width, and letter)
%    empty cells)         containing the same letter)
%
%      1 2 3 4 5           1 2 3 4 5                          1. r(1,1,4,2)  a
%    1 · · · – ·         1 a a b b b                          2. r(1,3,1,3)  b
%    2 · · · · ·         2 a a c c c                          3. r(2,3,3,3)  c
%    3 · · · + ·         3 a a c c c
%    4 · | · · ·         4 a a c c c

%%%%%%% end puzzle 4x5 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
