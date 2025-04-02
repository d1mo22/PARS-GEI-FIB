
symbolicOutput(0).  % set to 1 for DEBUGGING: to see symbolic output only; 0 otherwise.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% A county council wants to organize the night guard shifts of the pharmacies
%% in the county, for a period of N nights. Each pharmacy is located in one of
%% the C cities of the county. The distance between each city is known.
%% Restrictions:
%% a) there must be at least MinPh pharmacies on duty every night
%% b) each pharmacy has a list of nights when it cannot be on duty
%% c) no pharmacy can be on duty three consecutive nights
%% d) no pharmacy can do more than MaxN nights on duty in the total of N nights
%% e) pharmacies in the same city cannot be on duty in the same night
%% f) every night there must be some on-duty pharmacy strictly less than K Km from any city
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%% Begin example input %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

numNights(14).
numCities(6).
minPharmaciesOnDuty(3).   % there must be at least this number of pharmacies on duty every night
maxNightsOnDuty(5).       % no pharmacy can be on duty more than these nights

% pharmacyInfo(idPharm, idCity, blockedNights)
pharmacyInfo(ph1,  1, [1,3,9]).
pharmacyInfo(ph2,  1, [2,3,9,10]).
pharmacyInfo(ph3,  2, [1,4]).
pharmacyInfo(ph4,  3, [4,9]).
pharmacyInfo(ph5,  3, [1,2,4]).
pharmacyInfo(ph6,  3, [3,5,7,9]).
pharmacyInfo(ph7,  4, [2,11,12]).
pharmacyInfo(ph8,  4, [7,8,14]).
pharmacyInfo(ph9,  5, [1]).
pharmacyInfo(ph10, 5, [2]).
pharmacyInfo(ph11, 6, [3]).

%% distance matrix between cities. For example, the distance between cities 1 and 3 is 75 km
distances([[  0,  20,  75,  45, 200, 210, 220],
/*1*/	     [ 20,   0,   5,  15, 210, 215, 215],
/*2*/	     [ 75,   5,   0,  20, 150, 180, 170],
/*3*/	     [ 45,  15,  20,   0, 200, 205, 200],
/*4*/	     [200, 210, 150, 200,   0,  10,  20],
/*5*/	     [210, 215, 180, 205,  10,   0,  10],
/*6*/	     [220, 215, 170, 200,  20,  10,   0] ]).
nearbyDistance(25).   % there must be an on-call pharmacy at a distance strictly smaller
                      % than these kilometers from any city

%%%%%%% End example input %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% A possible example of correct output: %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% night 1 : [ ph2-c1 ph7-c4 ph11-c6 ]
%% night 2 : [ ph3-c2 ph4-c3 ph9-c5 ]
%% night 3 : [ ph3-c2 ph4-c3 ph10-c5 ]
%% night 4 : [ ph1-c1 ph7-c4 ph11-c6 ]
%% night 5 : [ ph2-c1 ph4-c3 ph11-c6 ]
%% night 6 : [ ph1-c1 ph5-c3 ph8-c4 ph10-c5 ]
%% night 7 : [ ph2-c1 ph5-c3 ph7-c4 ph11-c6 ]
%% night 8 : [ ph1-c1 ph6-c3 ph7-c4 ph9-c5 ]
%% night 9 : [ ph3-c2 ph5-c3 ph8-c4 ph10-c5 ]
%% night 10 : [ ph1-c1 ph6-c3 ph8-c4 ph9-c5 ]
%% night 11 : [ ph2-c1 ph6-c3 ph11-c6 ]
%% night 12 : [ ph1-c1 ph5-c3 ph8-c4 ph9-c5 ]
%% night 13 : [ ph3-c2 ph6-c3 ph8-c4 ph10-c5 ]
%% night 14 : [ ph2-c1 ph3-c2 ph6-c3 ph7-c4 ph10-c5 ]

%% pharmacy ph1 nights :  4 6 8 10 12
%% pharmacy ph2 nights :  1 5 7 11 14
%% pharmacy ph3 nights :  2 3 9 13 14
%% pharmacy ph4 nights :  2 3 5
%% pharmacy ph5 nights :  6 7 9 12
%% pharmacy ph6 nights :  8 10 11 13 14
%% pharmacy ph7 nights :  1 4 7 8 14
%% pharmacy ph8 nights :  6 9 10 12 13
%% pharmacy ph9 nights :  2 8 10 12
%% pharmacy ph10 nights :  3 6 9 13 14
%% pharmacy ph11 nights :  1 4 5 7 11

%% city 1 nearby cities: [2]
%% city 2 nearby cities: [1,3,4]
%% city 3 nearby cities: [2,4]
%% city 4 nearby cities: [2,3]
%% city 5 nearby cities: [6]
%% city 6 nearby cities: [5]

%% night 1 unattended cities: [ ]
%% night 2 unattended cities: [ ]
%% night 3 unattended cities: [ ]
%% night 4 unattended cities: [ ]
%% night 5 unattended cities: [ ]
%% night 6 unattended cities: [ ]
%% night 7 unattended cities: [ ]
%% night 8 unattended cities: [ ]
%% night 9 unattended cities: [ ]
%% night 10 unattended cities: [ ]
%% night 11 unattended cities: [ ]
%% night 12 unattended cities: [ ]
%% night 13 unattended cities: [ ]
%% night 14 unattended cities: [ ]


%%%%%%% Some helpful definitions to make the code cleaner: ====================================

night(N):- numNights(NN), between(1,NN,N).
city(C):- numCities(NC), between(1,NC,C).
pharmacy(Ph) :- pharmacyInfo(Ph, _, _).
pharmacyInCity(Ph,C):- pharmacyInfo(Ph,C,_).
pharmacyBlockedNight(Ph,N):- pharmacyInfo(Ph,_,L), member(N,L).
pharmaciesInSameCity(Ph1,Ph2):- pharmacyInCity(Ph1,C), pharmacyInCity(Ph2,C), Ph1 \= Ph2.

threeConsecutiveNights(N1,N2,N3) :- night(N1), N2 is N1+1, night(N2), N3 is N2+1, night(N3).

distanceCities(C1,C2,Km) :- city(C1), city(C2), distances(MD), nth1(C1, MD, Row), nth1(C2, Row, Km).
nearbyPharmacies(Ph,LPh):-  pharmacyInCity(Ph,C), nearbyDistance(Km),
			    findall(Ph1, (pharmacyInCity(Ph1,C1), Ph1 \= Ph, distanceCities(C,C1,Km1), Km1 < Km), LPh).
nearbyCities(C,LC):- city(C), nearbyDistance(Km),
		     findall(C1, (distanceCities(C,C1,Km1), C1 \= C, Km1 < Km), LC).

%%%%%%% End helpful definitions ===============================================================


%%%%%%%  1. Declare SAT variables to be used: =================================================

satVariable( phn(Ph,N) ):- pharmacy(Ph), night(N).  % means "pharmacy Ph is on duty on night N"
% It is NOT MANDATORY, but you may want to introduce some other variable
% for making the cardinality constraints smaller


%%%%%%%  2. Clause generation for the SAT solver: =============================================

writeClauses:-
    minimunOnDutyPharmaciesEachNight, % to be done
    blockedNights,                    % to be done
    noThreeConsecutiveNights,         % to be done
    maxOnDutyNights,                  % to be done 
    noTwoPharmaciesInSameCity,        % to be done
    nearbyOnDutyPharmacies,           % to be done
    true,!.
writeClauses:- told, nl, write('writeClauses failed!'), nl, nl, halt.

% a) there must be at least MinPh pharmacies on duty every night
minimunOnDutyPharmaciesEachNight:- 
      night(N),
      findall(phn(Ph,N), pharmacy(Ph), L),
      minPharmaciesOnDuty(MinPh),
      atLeast(MinPh,L),
      fail.
minimunOnDutyPharmaciesEachNight.

% b) each pharmacy has a list of nights when it cannot be on duty
blockedNights:- 
      pharmacyBlockedNight(Ph,N),
      writeOneClause([-phn(Ph,N)]),      
      fail.
blockedNights.

% c) no pharmacy can be on duty three consecutive nights
noThreeConsecutiveNights:- 
      pharmacy(Ph),
      threeConsecutiveNights(N,N1,N2),
      writeOneClause([-phn(Ph,N), -phn(Ph,N1), -(phn(Ph,N2))]),
      fail.
noThreeConsecutiveNights.

% d) no pharmacy can do more than MaxN nights on duty in the total of N nights
maxOnDutyNights:- 
      pharmacy(Ph),
      findall(phn(Ph,N), night(N), L),
      maxNightsOnDuty(MaxN),
      atMost(MaxN, L),
      fail.
maxOnDutyNights.
    
% e) pharmacies in the same city cannot be on duty in the same night
noTwoPharmaciesInSameCity:- 
      pharmaciesInSameCity(Ph1,Ph2),
      night(N),
      writeOneClause([-phn(Ph1,N), -phn(Ph2,N)]),
      fail.
noTwoPharmaciesInSameCity.

% f) every night there must be some on-duty pharmacy less than K Km from any city
nearbyOnDutyPharmacies:- 
      night(N), pharmacy(Ph),
      nearbyPharmacies(Ph, LPh),
      findall(phn(Ph1,N), member(Ph1, LPh), L),
      writeOneClause([phn(Ph,N)|L]),
      fail.
nearbyOnDutyPharmacies.


%%%%%%%  3. DisplaySol: this predicate displays a given solution M: ===========================

% displaySol(M):- nl, write(M), nl, nl, fail.
displaySol(M):- night(N), nl, write('night '), write(N), write(' : ['), writePharmacies(N,M), write(' ]'), fail.
displaySol(M):- nl, pharmacy(Ph), nl, write('pharmacy '), write(Ph),  write(' nights : '), writeNights(Ph,M), fail.
displaySol(_):- nl, city(C), nl, write('city '), write(C),  write(' nearby cities: '), nearbyCities(C,LC), sort(LC,LC1), write(LC1), fail.
displaySol(M):- nl, night(N), nl, write('night '), write(N), write(' unattended cities: '), writeUnattendedCities(N,M), fail.
displaySol(_).

writePharmacies(N,M):- pharmacy(Ph), member(phn(Ph,N), M), write(' '), pharmacyInCity(Ph,C),
		       write(Ph), write('-c'), write(C), fail.
writePharmacies(_,_).

writeNights(Ph,M):- night(N), member(phn(Ph,N), M), write(' '), write(N), fail.
writeNights(_,_).

writeUnattendedCities(N,M):- write('[ '), city(C), unattendedCity(N,C,M), write(C), write(' '), fail.
writeUnattendedCities(_,_):- write(']').

unattendedCity(N,C,M):- nearbyCities(C,LC),
			findall( Ph, (member(C1,[C|LC]), pharmacyInCity(Ph,C1)), LPh ),
			noPharmacyOnDuty(N,LPh,M).

noPharmacyOnDuty(N,LPh,M):- member(Ph,LPh), member(phn(Ph,N),M), !, fail.
noPharmacyOnDuty(_,_,_).


%%%%%%% =======================================================================================



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Everything below is given as a standard library, reusable for solving
%%    with SAT many different problems.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% Cardinality constraints on arbitrary sets of literals Lits: ===========================

exactly(K,Lits):- symbolicOutput(1), write( exactly(K,Lits) ), nl, !.
exactly(K,Lits):- atLeast(K,Lits), atMost(K,Lits),!.

atMost(K,Lits):- symbolicOutput(1), write( atMost(K,Lits) ), nl, !.
atMost(K,Lits):-   % l1+...+ln <= k:  in all subsets of size k+1, at least one is false:
      negateAll(Lits,NLits),
      K1 is K+1,    subsetOfSize(K1,NLits,Clause), writeOneClause(Clause),fail.
atMost(_,_).

atLeast(K,Lits):- symbolicOutput(1), write( atLeast(K,Lits) ), nl, !.
atLeast(K,Lits):-  % l1+...+ln >= k: in all subsets of size n-k+1, at least one is true:
      length(Lits,N),
      K1 is N-K+1,  subsetOfSize(K1, Lits,Clause), writeOneClause(Clause),fail.
atLeast(_,_).

negateAll( [], [] ).
negateAll( [Lit|Lits], [NLit|NLits] ):- negate(Lit,NLit), negateAll( Lits, NLits ),!.

negate( -Var,  Var):-!.
negate(  Var, -Var):-!.

subsetOfSize(0,_,[]):-!.
subsetOfSize(N,[X|L],[X|S]):- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ):-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).


%%%%%%% Express equivalence between a variable and a disjunction or conjunction of literals ===

% Express that Var is equivalent to the disjunction of Lits:
expressOr( Var, Lits ):- symbolicOutput(1), write( Var ), write(' <--> or('), write(Lits), write(')'), nl, !.
expressOr( Var, Lits ):- member(Lit,Lits), negate(Lit,NLit), writeOneClause([ NLit, Var ]), fail.
expressOr( Var, Lits ):- negate(Var,NVar), writeOneClause([ NVar | Lits ]),!.

%% expressOr(a,[x,y]) genera 3 clausulas (como en la Transformación de Tseitin):
%% a == x v y
%% x -> a       -x v a
%% y -> a       -y v a
%% a -> x v y   -a v x v y

% Express that Var is equivalent to the conjunction of Lits:
expressAnd( Var, Lits) :- symbolicOutput(1), write( Var ), write(' <--> and('), write(Lits), write(')'), nl, !.
expressAnd( Var, Lits):- member(Lit,Lits), negate(Var,NVar), writeOneClause([ NVar, Lit ]), fail.
expressAnd( Var, Lits):- findall(NLit, (member(Lit,Lits), negate(Lit,NLit)), NLits), writeOneClause([ Var | NLits]), !.


%%%%%%% main: =================================================================================

main:-  symbolicOutput(1), !, writeClauses, halt.   % print the clauses in symbolic form and halt Prolog
main:-  initClauseGeneration,
        tell(clauses), writeClauses, told,          % generate the (numeric) SAT clauses and call the solver
        tell(header),  writeHeader,  told,
        numVars(N), numClauses(C),
        write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
        shell('cat header clauses > infile.cnf',_),
        write('Calling solver....'), nl,
        shell('kissat -v infile.cnf > model', Result),  % if sat: Result=10; if unsat: Result=20.
        treatResult(Result),!.

treatResult(20):- write('Unsatisfiable'), nl, halt.
treatResult(10):- write('Solution found: '), nl, see(model), symbolicModel(M), seen, displaySol(M), nl,nl,halt.
treatResult( _):- write('cnf input error. Wrote anything strange in your cnf?'), nl,nl, halt.


initClauseGeneration:-  %initialize all info about variables and clauses:
        retractall(numClauses(   _)),
        retractall(numVars(      _)),
        retractall(varNumber(_,_,_)),
        assert(numClauses( 0 )),
        assert(numVars(    0 )),     !.

writeOneClause([]):- symbolicOutput(1),!, nl.
writeOneClause([]):- countClause, write(0), nl.
writeOneClause([Lit|C]):- w(Lit), writeOneClause(C),!.
w(-Var):- symbolicOutput(1), satVariable(Var), write(-Var), write(' '),!.
w( Var):- symbolicOutput(1), satVariable(Var), write( Var), write(' '),!.
w(-Var):- satVariable(Var),  var2num(Var,N),   write(-), write(N), write(' '),!.
w( Var):- satVariable(Var),  var2num(Var,N),             write(N), write(' '),!.
w( Lit):- told, write('ERROR: generating clause with undeclared variable in literal '), write(Lit), nl,nl, halt.


% given the symbolic variable V, find its variable number N in the SAT solver:
:-dynamic(varNumber / 3).
var2num(V,N):- hash_term(V,Key), existsOrCreate(V,Key,N),!.
existsOrCreate(V,Key,N):- varNumber(Key,V,N),!.                            % V already existed with num N
existsOrCreate(V,Key,N):- newVarNumber(N), assert(varNumber(Key,V,N)), !.  % otherwise, introduce new N for V

writeHeader:- numVars(N),numClauses(C), write('p cnf '),write(N), write(' '),write(C),nl.

countClause:-     retract( numClauses(N0) ), N is N0+1, assert( numClauses(N) ),!.
newVarNumber(N):- retract( numVars(   N0) ), N is N0+1, assert(    numVars(N) ),!.

% Getting the symbolic model M from the output file:
symbolicModel(M):- get_code(Char), readWord(Char,W), symbolicModel(M1), addIfPositiveInt(W,M1,M),!.
symbolicModel([]).
addIfPositiveInt(W,L,[Var|L]):- W = [C|_], between(48,57,C), number_codes(N,W), N>0, varNumber(_,Var,N),!.
addIfPositiveInt(_,L,L).
readWord( 99,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ c
readWord(115,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ s
readWord(-1,_):-!, fail. %end of file
readWord(C,[]):- member(C,[10,32]), !. % newline or white space marks end of word
readWord(Char,[Char|W]):- get_code(Char1), readWord(Char1,W), !.

%%%%%%% =======================================================================================
