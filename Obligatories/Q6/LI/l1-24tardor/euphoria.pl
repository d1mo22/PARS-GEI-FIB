%% ----------- [5 points] ---------- %%

symbolicOutput(0).  % set to 1 for DEBUGGING: to see symbolic output only; 0 otherwise.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*

Euphoria is a song contest in the Catalan TV station. At the end of
the season, a final concert is organized where the participants sing
their best songs from the programme. Your goal is to choose the songs
and to decide their order in the concert.

Each song has a *score*, based on the votes of the audience. The
higher the score, the more popular the song is. Songs have another
attribute, which we will refer to as their *type*: a song may be
a *dance* song        (the audience is expected to dance wildly); or
a *flashlight* song   (the audience is expected to turn on the flashlight
                       of their cell phones and wave them); or
a *regular* song      (anything else).

Songs are identified by consecutive natural numbers starting from 1.
The input gives, for each song: its identifier, its title, its score,
its type, and the programme participant who sings it.

The following constraints should be met. 
- First of all, the concert
should consist of the specified number of songs. Of course, songs
cannot be repeated. 
- Secondly, to keep the audience's spirits high, the
score of the songs along the concert should never decrease. 
- In the third place, nobody can sing two songs in a row. 
- Morever, each of theprogramme participants has to sing at least one song. 
- Also, there is a minimum on the number of dance songs and flashlight songs in the
concert. 
- Finally, in a window of consecutive songs of the specified length, there can be at most one dance song; 
and similarly for flashlight songs.

*/
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%% begin example %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% numberOfSongsForConcert(N):
% N songs are sung in the concert.
% numberOfSongsForConcert(20).

% % minNumberOfSongsOfType(M, T):
% % in the concert there are at least M songs of type T.
% minNumberOfSongsOfType(3,      dance).
% minNumberOfSongsOfType(3, flashlight).

% % inWindowOfThisSizeAtMostOneOfType(W, T):
% % in a window of W consecutive song slots, at most one is of type T.
% inWindowOfThisSizeAtMostOneOfType(4,      dance).
% inWindowOfThisSizeAtMostOneOfType(4, flashlight).

% %%    Id                             Title   Score          Type     Participant
% data(  1,                    'Tu es foutu',      8,      regular,        'Julien').
% data(  2,            'Great balls of fire',      7,        dance,        'Julien').
% data(  3,                        'Bon dia',      6,        dance,        'Julien').
% data(  4,            'Baby don\'t hurt me',      6,      regular,        'Julien').
% data(  5,                         'Corren',      5,      regular,         'Lluís').
% data(  6,                       'Bailoteo',      7,        dance,         'Lluís').
% data(  7,                   'Lose control',      6,      regular,         'Lluís').
% data(  8,                       'Wa yeah!',      8,        dance,         'Lluís').
% data(  9,                    'Blank space',      7,      regular,         'Maria').
% data( 10,                       'Symphony',      8,      regular,         'Maria').
% data( 11,                          'Creep',      9,   flashlight,         'Maria').
% data( 12,            'The show must go on',      8,   flashlight,         'Maria').
% data( 13,                           'Torn',      7,      regular,         'Misty').
% data( 14,                       'Diamonds',      8,      regular,         'Misty').
% data( 15,                  'Eternal flame',      9,   flashlight,         'Misty').
% data( 16,                 'Girl gone wild',      6,      regular,         'Misty').
% data( 17,                        'Valerie',      6,      regular,       'Valeria').
% data( 18,                           'Lobo',      7,      regular,       'Valeria').
% data( 19,                  'Els teus ulls',      6,   flashlight,       'Valeria').
% data( 20,                            'SOS',      6,      regular,       'Fredrik').
% data( 21,                   'Grande amore',      7,      regular,       'Fredrik').
% data( 22,               'Nothing compares',      8,   flashlight,     'Xavi Noms').
% data( 23,                    'A poc a poc',      7,      regular,     'Xavi Noms').
% data( 24,            'Million dollar baby',      6,      regular, 'Aina Da Silva').
% data( 25,       'Dancing in the Moonlight',      5,      regular, 'Aina Da Silva').
% data( 26,                     'Chandelier',      6,      regular,         'Lluna').
% data( 27,                     'Girlfriend',      5,      regular,         'Lluna').
% data( 28,                     'Tant de bo',      6,      regular,          'Bita').
% data( 29,                      'Rich girl',      5,      regular,          'Bita').
% data( 30,                      'La platja',      6,        dance,   'Pau Culleré').
% data( 31, 'La petita rambla del poble-sec',      5,      regular,        'Rangel').
% data( 32,                      'I love it',      4,      regular,           'Yuk').
% data( 33,              'Paraules paraules',      3,      regular,        'Dounia').
% data( 34,                   'La meva sort',      3,      regular,        'Tamara').
% data( 35,                'Blinding lights',      2,      regular,          'Hugo').

%%%%%%% end example %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% Some helpful definitions to make the code cleaner: ====================================

slot(I) :- numberOfSongsForConcert(N), between(1, N, I).
song(J) :- data(J, _, _, _, _).

songParticipant(J, P) :- data(J, _, _, _, P).
songScore(J, S)       :- data(J, _, S, _, _).
songType(J, T)        :- data(J, _, _, T, _).

participant(P) :- findall(X, songParticipant(_, X), L), sort(L, S), member(P, S).

%%%%%%% End helpful definitions ===============================================================


%%%%%%%  1. SAT Variables: ====================================================================

satVariable( x(I, J) ) :- slot(I), song(J).  % in the I-th slot song J is sung.


%%%%%%%  2. Clause generation for the SAT solver: =============================================

writeClauses :-
    everySlotExactlyOneSong,        % at every slot exactly 1 song is sung
    everySongAtMostOneSlot,         % songs cannot be repeated
    scoreNeverDecreases,            % (*1) the score of songs along the concert never decreases DONE
    noParticipantSings2SongsInARow, % (*2) nobody can sing 2 songs in a row DONE
    everyParticipantAtLeastOneSong, % (*3) every participant sings at least 1 song DONE
    enoughSongsOfEachType,          % (*4) minimum number of dance/flashlight songs is respected DONE
    atMostOneOfThisTypeInAWindow,   % (*5) in window of consecutive songs at most 1 of type dance/flashlight
    true, !.
writeClauses :- told, nl, write('writeClauses failed!'), nl, nl, halt.

everySlotExactlyOneSong :-
    slot(I),
    findall(x(I, J), song(J), Lits),
    exactly(1, Lits),
    fail.
everySlotExactlyOneSong.

everySongAtMostOneSlot :-
    song(J),
    findall(x(I, J), slot(I), Lits),
    atMost(1, Lits),
    fail.
everySongAtMostOneSlot.

%% TO BE COMPLETED: (*1)-(*5): <<<<<<<<<<
scoreNeverDecreases :-
    slot(I),
    I1 is I+1, 
    slot(I1),
    songScore(JA, SA), 
    songScore(JB,SB), 
    SA > SB,
    writeOneClause([-x(I,JA), -x(I1,JB)]),
    fail.
scoreNeverDecreases.

noParticipantSings2SongsInARow :-
    slot(I0),
    I1 is I0+1,
    slot(I1),
    songParticipant(JA, P),
    songParticipant(JB, P),
    writeOneClause([-x(I0,JA), -x(I1,JB)]),
    fail.
noParticipantSings2SongsInARow.

everyParticipantAtLeastOneSong :-
    participant(P),
    findall(x(I,J), (slot(I), songParticipant(J,P)),L),
    atLeast(1,L), % writeOneClause(Lits),
    fail.
everyParticipantAtLeastOneSong.

enoughSongsOfEachType :-
    minNumberOfSongsOfType(N, T),
    findall(x(I,J), (slot(I), songType(J, T)), Lits),
    atLeast(N,Lits),
    fail.
enoughSongsOfEachType.

atMostOneOfThisTypeInAWindow :-
    inWindowOfThisSizeAtMostOneOfType(W,T),
    slot(I0),
    I1 is I0+W,
    slot(I1),
    findall(x(I,J), (slot(I), between(I0,I1,I), songType(J,T)), Lits),
    atMost(1, Lits),
    fail.
atMostOneOfThisTypeInAWindow.

%%%%%%%  3. DisplaySol: show the solution. Here M contains the literals that are true in the model:

print_with_leading_zero(N) :- format('~|~`0t~d~2+', [N]).
print_left_aligned(S, W) :-   format('~|~w~t~*+', [S, W]).


%% displaySol(M) :- nl, sort(M,M1), write(M1), nl, nl, fail.
displaySol(M) :-
    slot(I),
    write('Song #'), print_with_leading_zero(I), write(' by\t'),
    member(x(I,J), M),
    data(J, Title, Score, Type, Participant),
    print_left_aligned(Participant, 15),
    print_left_aligned(Title,       35),
    print_left_aligned(Score,        5),
    print_left_aligned(Type,        10),
    nl,
    fail.
displaySol(_).

%%%%%%% =======================================================================================



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Everything below is given as a standard library, reusable for solving
%%    with SAT many different problems.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% Cardinality constraints on arbitrary sets of literals Lits: ===========================

exactly(K,Lits) :- symbolicOutput(1), write( exactly(K,Lits) ), nl, !.
exactly(K,Lits) :- atLeast(K,Lits), atMost(K,Lits),!.

atMost(K,Lits) :- symbolicOutput(1), write( atMost(K,Lits) ), nl, !.
atMost(K,Lits) :-   % l1+...+ln <= k:  in all subsets of size k+1, at least one is false:
      negateAll(Lits,NLits),
      K1 is K+1,    subsetOfSize(K1,NLits,Clause), writeOneClause(Clause),fail.
atMost(_,_).

atLeast(K,Lits) :- symbolicOutput(1), write( atLeast(K,Lits) ), nl, !.
atLeast(K,Lits) :-  % l1+...+ln >= k: in all subsets of size n-k+1, at least one is true:
      length(Lits,N),
      K1 is N-K+1,  subsetOfSize(K1, Lits,Clause), writeOneClause(Clause),fail.
atLeast(_,_).

negateAll( [], [] ).
negateAll( [Lit|Lits], [NLit|NLits] ) :- negate(Lit,NLit), negateAll( Lits, NLits ),!.

negate( -Var,  Var) :- !.
negate(  Var, -Var) :- !.

subsetOfSize(0,_,[]) :- !.
subsetOfSize(N,[X|L],[X|S]) :- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ) :-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).


%%%%%%% Express equivalence between a variable and a disjunction or conjunction of literals ===

% Express that Var is equivalent to the disjunction of Lits:
expressOr( Var, Lits ) :- symbolicOutput(1), write( Var ), write(' <--> or('), write(Lits), write(')'), nl, !.
expressOr( Var, Lits ) :- member(Lit,Lits), negate(Lit,NLit), writeOneClause([ NLit, Var ]), fail.
expressOr( Var, Lits ) :- negate(Var,NVar), writeOneClause([ NVar | Lits ]),!.

%% expressOr(a,[x,y]) genera 3 clausulas (como en la Transformación de Tseitin):
%% a == x v y
%% x -> a       -x v a
%% y -> a       -y v a
%% a -> x v y   -a v x v y

% Express that Var is equivalent to the conjunction of Lits:
expressAnd( Var, Lits) :- symbolicOutput(1), write( Var ), write(' <--> and('), write(Lits), write(')'), nl, !.
expressAnd( Var, Lits) :- member(Lit,Lits), negate(Var,NVar), writeOneClause([ NVar, Lit ]), fail.
expressAnd( Var, Lits) :- findall(NLit, (member(Lit,Lits), negate(Lit,NLit)), NLits), writeOneClause([ Var | NLits]), !.


%%%%%%% main: =================================================================================

main :- current_prolog_flag(os_argv, Argv),
        nth0(1, Argv, InputFile),
        main(InputFile), !.
main :-  write('Usage: $ ./<executable> <example>          or ?- main(<example>).'), nl, halt.

main(InputFile) :-
        symbolicOutput(1), !,
        consult(InputFile),
        writeClauses, halt.   % print the clauses in symbolic form and halt Prolog
main(InputFile):-
        consult(InputFile),
        initClauseGeneration,
        tell(clauses), writeClauses, told,          % generate the (numeric) SAT clauses and call the solver
        tell(header),  writeHeader, told,
        numVars(N), numClauses(C),
        write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
        shell('cat header clauses > infile.cnf',_),
        write('Calling solver....'), nl,
        shell('kissat -v infile.cnf > model', Result),  % if sat: Result=10; if unsat: Result=20.
        treatResult(Result),!.

treatResult(20) :- write('Unsatisfiable'), nl, halt.
treatResult(10) :- write('Solution found: '), nl, see(model), symbolicModel(M), seen, displaySol(M), nl,nl,halt.
treatResult( _) :- write('cnf input error. Wrote anything strange in your cnf?'), nl,nl, halt.


initClauseGeneration :-  %initialize all info about variables and clauses:
        retractall(numClauses(   _)),
        retractall(numVars(      _)),
        retractall(varNumber(_,_,_)),
        assert(numClauses( 0 )),
        assert(numVars(    0 )),     !.

writeOneClause([]) :- symbolicOutput(1),!, nl.
writeOneClause([]) :- countClause, write(0), nl.
writeOneClause([Lit|C]) :- w(Lit), writeOneClause(C),!.
w(-Var) :- symbolicOutput(1), satVariable(Var), write(-Var), write(' '),!.
w( Var) :- symbolicOutput(1), satVariable(Var), write( Var), write(' '),!.
w(-Var) :- satVariable(Var),  var2num(Var,N),   write(-), write(N), write(' '),!.
w( Var) :- satVariable(Var),  var2num(Var,N),             write(N), write(' '),!.
w( Lit) :- told, write('ERROR: generating clause with undeclared variable in literal '), write(Lit), nl,nl, halt.


% given the symbolic variable V, find its variable number N in the SAT solver:
:- dynamic(varNumber / 3).
var2num(V,N) :- hash_term(V,Key), existsOrCreate(V,Key,N),!.
existsOrCreate(V,Key,N) :- varNumber(Key,V,N),!.                            % V already existed with num N
existsOrCreate(V,Key,N) :- newVarNumber(N), assert(varNumber(Key,V,N)), !.  % otherwise, introduce new N for V

writeHeader :- numVars(N),numClauses(C), write('p cnf '),write(N), write(' '),write(C),nl.

countClause :-     retract( numClauses(N0) ), N is N0+1, assert( numClauses(N) ),!.
newVarNumber(N) :- retract( numVars(   N0) ), N is N0+1, assert(    numVars(N) ),!.

% Getting the symbolic model M from the output file:
symbolicModel(M) :- get_code(Char), readWord(Char,W), symbolicModel(M1), addIfPositiveInt(W,M1,M),!.
symbolicModel([]).
addIfPositiveInt(W,L,[Var|L]) :- W = [C|_], between(48,57,C), number_codes(N,W), N>0, varNumber(_,Var,N),!.
addIfPositiveInt(_,L,L).
readWord( 99,W) :- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ c
readWord(115,W) :- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ s
readWord( -1,_) :-!, fail. %end of file
readWord(C, []) :- member(C,[10,32]), !. % newline or white space marks end of word
readWord(Char,[Char|W]) :- get_code(Char1), readWord(Char1,W), !.

%%%%%%% =======================================================================================
