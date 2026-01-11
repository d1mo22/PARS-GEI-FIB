
numWorkers(20).
numTeams(5).    % exact number of teams needed
minSize(3).     % min size of any team
maxSize(6).     % max size of any team
maxScore(14).   % two workers whose scores sum more than 14 cannot go together

% score(workerId, score)
score( 1, 2).
score( 2, 6).
score( 3, 3).
score( 4, 4).
score( 5, 6).
score( 6, 10).
score( 7, 2).
score( 8, 1).
score( 9, 4).
score(10, 2).
score(11, 7).
score(12, 9).
score(13, 3).
score(14, 4).
score(15, 9).
score(16, 1).
score(17, 3).
score(18, 8).
score(19, 2).
score(20, 1).

