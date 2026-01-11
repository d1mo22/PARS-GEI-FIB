
% example: 4 gangsters are needed for killing on hour 1, one gangster on hour 2, two gangsters on hour 3, etc.
gangstersNeeded( killing,       [4,1,2,4,2,1,1,4,1,1,3,2,4,2,1,2,1,3,2,3,4,1,3,1,2,3,1,3,4,3,2,3,4,2,3,1,4,4,1,4,2,2,1,4,3,3,3,2,2,3,4,4,1,3,3,3,4,4,1,1,2,3,3,3,3,2,1,3,1,1,3,2] ).
gangstersNeeded( countingMoney, [1,2,1,3,1,4,3,1,3,1,4,3,2,2,1,2,1,2,1,1,2,1,2,1,1,3,1,2,2,4,3,2,4,4,4,1,2,4,4,2,4,4,4,3,2,2,1,3,2,1,3,3,2,3,3,3,1,4,1,1,3,1,2,3,3,1,4,4,3,3,2,1] ).
gangstersNeeded( politics,      [2,4,2,1,1,1,4,1,1,4,1,3,2,4,1,1,4,1,4,3,1,3,2,4,4,2,4,2,1,1,4,3,1,2,2,2,1,1,3,1,1,1,2,2,4,1,1,3,4,4,2,3,2,4,3,1,1,1,3,4,2,2,4,4,3,1,1,2,1,4,3,2] ).

gangsters([g01,g02,g03,g04,g05,g06,g07,g08,g09,g10,g11,g12]).

notAvailable(g01,[6,13,14,16,21,35,37,41,59]).
notAvailable(g02,[14,34,40,45,48,52,58,65,70,72]).
notAvailable(g03,[8,11,13,27,30,38,50,51,70]).
notAvailable(g04,[4,12,16,17,26,30,42,45,48,55,71]).

maxTwoTaskGangsters([g01,g02,g04,g06,g07]).

notAllowedTask(g09, politics).
notAllowedTask(g10, politics).
notAllowedTask(g11, politics).
notAllowedTask(g12, politics).

initialMaxConsecutive(20).
