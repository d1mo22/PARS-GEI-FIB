
numEvents(15).
numDays(4).
numModerators(4).
maxEventsPerDay(4).
maxDaysPerModerator(2).

%event( id, listPossibleModerators, listPossibleDays).
event(1, [  2  ,4],[  2    ]).
event(2, [1,  3  ],[1,2,  4]).
event(3, [1,2  ,4],[    3  ]).
event(4, [1,  3,4],[1,2,  4]).
event(5, [  2,3,4],[1,  3,4]).
event(6, [    3,4],[1,2,3  ]).
event(7, [1,2    ],[1,2,  4]).
event(8, [1,2  ,4],[    3,4]).
event(9, [  2,3  ],[1,2,3  ]).
event(10,[    3,4],[1,2,  4]).
event(11,[1,2  ,4],[1,2,3  ]).
event(12,[  2,3  ],[    3,4]).
event(13,[1,  3,4],[1,2    ]).
event(14,[  2,3  ],[1,  3,4]).
event(15,[  2  ,4],[  2,3  ]).

