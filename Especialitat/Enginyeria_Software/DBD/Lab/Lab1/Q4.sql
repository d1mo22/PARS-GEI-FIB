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
insert into domicilis values ('934131414', 'casa', 48, '4', '2');

insert into comandes values (110, 1091, 1101, '934131415', 42);
insert into comandes values (111, 1091, 1101, '934131415', 42);
insert into comandes values (112, 1091, 1101, '934131414', 42);


insert into liniesComandes values (110, 'p111', 2);


SELECT d.NOMCARRER, d.NUMCARRER
FROM DOMICILIS d RIGHT JOIN COMANDES c ON d.NUMTELF = c.NUMTELF
WHERE c.NUMTELF IS NOT NULL OR NOT EXISTS (SELECT *
										   FROM COMANDES c
										   WHERE c.NUMTELF IS NOT NULL) 
GROUP BY d.NOMCARRER , d.NUMCARRER
HAVING MAX(d.NUMTELF)
ORDER BY COUNT(d.NUMTELF) desc, d.NOMCARRER, d.NUMCARRER;

-- NO ESTA ACABAT



 