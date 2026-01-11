% [ [1,A1,B1,C1,D1,E1],[2,A2,B2,C2,D2,E2], [3,A3,B3,C3,D3,E3], [4,A4,B4,C4,D4,E4],[5,A5,B5,C5,D5,E5] ]
solucio(L):-
    L = [ [1,_,_,_,_,_],[2,_,_,_,_,_], [3,_,_,_,_,_], [4,_,_,_,_,_],[5,_,_,_,_,_] ],
    % [numcasa,color,professio,animal,beguda,pais]
    member([_,vermella,_, _,_,peru], L),   % 1- El que viu a la casa vermella es del Peru
    member([_,_,_,gos,_,frances], L),      % 2- Al frances li agrada el gos
    member([_,_,pintor,_,_,japones], L),   % 3- El pintor es japones
    member([_,_,_,_,rom,xines], L),        % 4- Al xines li agrada el rom
    member([1,_,_,_,_,hongares], L),       % 5- L'hongares viu en la primera casa
    member([_,verda,_,_,conyac,_], L),     % 6- Al de la casa verda li agrada el conyac
    member([X1,verda,_,_,_,_], L),          % 7- La casa verda esta just a la esquerra de la blanca
    member([Y1,blanca,_,_,_,_], L),
    X1 is Y1 - 1, %, Y > 0, Y < 6,
    member([_,_,escultor,caragols,_,_], L), % 8- L’escultor cria caragols
    member([_,groga,actor,_,_,_], L),       % 9- El de la casa groga es actor
    member([3,_,_,_,cava,_], L),            % 10- El de la tercera casa beu cava
    member([X2,_,actor,_,_,_], L),          % 11- El que viu al costat de l’actor te un cavall
    (Y2 is X2-1; Y2 is X2+1),
    member([Y2,_,_,cavall,_,_], L),
    member([X3,blau,_,_,_,_], L),           % 12- L’hongares viu al costat de la casa blava
    (Y3 is X3-1; Y3 is X3+1),
    member([Y3,_,_,_,_,hongares], L),
    member([_,_,notari,_,whisky,_], L),     % 13- Al notari l’agrada el whisky
    member([X4,_,metge,_,_,_], L),          % 14- El que viu al costat del metge te un esquirol
    (Y4 is X4-1; Y4 is X4+1),
    member([Y4,_,_,esquirol,_,_], L),
    not(member([_,_,_,gat,cervesa,_], L)),   % 15- El que te un gat no es a qui agrada la cervesa
    write(L), nl, fail.