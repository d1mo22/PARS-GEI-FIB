create table productes
(idProducte char(9),
nom char(20),
mida char(20),
preu integer check(preu>0),
primary key (idProducte),
unique (nom,mida));

create table domicilis
(numTelf char(9),
nomCarrer char(20),
numCarrer integer check(numCarrer>0),
pis char(2),
porta char(2),
primary key (numTelf));

create table comandes
(numComanda integer check(numComanda>0),
instantFeta integer not null check(instantFeta>0),
instantServida integer check(instantServida>0),
numTelf char(9),
import integer check(import>0),
primary key (numComanda),
foreign key (numTelf) references domicilis,
check (instantServida>instantFeta));

create table liniesComandes
(numComanda integer,
idProducte char(9),
quantitat integer check(quantitat>0),
primary key(numComanda,idProducte),
foreign key (numComanda) references comandes,
foreign key (idProducte) references productes);

insert into productes values ('p111', '4 formatges', 'gran', 21); 
  
insert into domicilis values ('934131415', 'pont', 47, '4', '2');

insert into comandes values (110, 1091, 1101, '934131415', 42);

insert into liniesComandes values (110, 'p111', 2);

-- Doneu una sentència SQL per obtenir, de cada producte, quants productes diferents formen part de les comandes en què apareix el producte. Tingueu en compte que:
-- Si un producte no ha estat demanat en cap comanda, ha de sortir amb el comptador 0.
-- En el resultat de la consulta ha de sortir el identificador del producte i la quantitat demanada. Ordeneu el resultat per identificador de producte.

SELECT p.idProducte, COUNT(DISTINCT l2.idProducte) as Count
FROM productes p
LEFT JOIN liniesComandes l1 ON p.idProducte = l1.idProducte
LEFT JOIN liniesComandes l2 ON l1.numComanda = l2.numComanda
GROUP BY p.idProducte
ORDER BY p.idProducte;



