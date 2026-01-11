create table pais
(paisAg char(1) PRIMARY KEY,
pib char(1));

CREATE TABLE agencies
(ag char(1) PRIMARY KEY,
paisAg char(1),
FOREIGN KEY (paisAg) REFERENCES pais);

create table deute
(paisD char(1),
paisAc char(1),
deute char(1),
PRIMARY KEY (paisD,paisAc));

create table r
(ag char(1),
paisD char(1),
paisAc char(1),
PRIMARY KEY(ag,paisD,paisAc),
FOREIGN KEY (ag) REFERENCES agencies,
FOREIGN KEY (paisD,paisAc) REFERENCES deute);