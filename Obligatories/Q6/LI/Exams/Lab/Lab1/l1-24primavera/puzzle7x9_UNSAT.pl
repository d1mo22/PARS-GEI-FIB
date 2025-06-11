%%%%%%% begin puzzle 7x9 UNSAT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% grid(NR,NC): the tatamibari puzzle has NR rows and NC columns
grid(7,9).

% coordinates [I,J] mean: symbol at row I (1 <= I <= NR), column J (1 <= J <= NC)
horizontal([[1,8],[2,3],[5,8],[7,4],[7,7]]).    % location of the – symbols
vertical([[2,9],[3,1],[3,5],[3,7],[5,1]]).      % location of the | symbols
cross([[1,2],[1,4],[4,6],[5,3],[7,5]]).         % location of the + symbols

%     Input (15 symbols)     NO solution exists!
%     (dots represent
%      empty cells)
%
%       1 2 3 4 5 6 7 8 9
%     1 · + · + · · · – ·
%     2 · · – · · · · · |
%     3 | · · · | · | · ·
%     4 · · · · · + · · ·
%     5 | · + · · · · – ·
%     6 · · · · · · · · ·
%     7 · · · – + · – · ·
%
%

%%%%%%% end puzzle 7x9 UNSAT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
