%%%%%%% begin puzzle 3x4 UNSAT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% grid(NR,NC): the tatamibari puzzle has NR rows and NC columns
grid(3,4).

% coordinates [I,J] mean: symbol at row I (1 <= I <= NR), column J (1 <= J <= NC)
horizontal([[1,3],[2,4]]).    % location of the – symbols
vertical([[3,1]]).            % location of the | symbols
cross([[1,1]]).               % location of the + symbols

%    Input (unsatisfiable)   This is NOT a valid solution because
%    (dots represent         four pieces may never share the same corner
%    empty cells)
%
%      1 2 3 4                 1 2 3 4
%    1 + · – ·               1 a b b b
%    2 · · · –               2 c d d d
%    3 | · · ·               3 c d d d

%%%%%%% end puzzle 3x4 UNSAT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
