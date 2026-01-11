 CREATE TABLE Esplai (
 Nom VARCHAR(1) ,
 Adreca VARCHAR(1) ,
 CONSTRAINT Esplai_PK PRIMARY KEY (Nom));
 
 CREATE TABLE Jornada (
 Data VARCHAR(1) ,
 SortSol VARCHAR(1) ,
 PostaSol VARCHAR(1) ,
 CONSTRAINT Jornada_PK PRIMARY KEY (Data));
 
 CREATE TABLE Noi (
 Nom VARCHAR(1) ,
 Cognom1 VARCHAR(1) ,
 Cognom2 VARCHAR(1) ,
 Edat VARCHAR(1) ,
 CONSTRAINT Noi_PK PRIMARY KEY (Cognom2,  Nom,  Cognom1));
 
 CREATE TABLE Tanda (
 Ident VARCHAR(1) ,
 Esplai_PK_Nom VARCHAR(1) ,
 CONSTRAINT Tanda_FK_EsplaiPK FOREIGN KEY (Esplai_PK_Nom) REFERENCES Esplai(Nom),
 CONSTRAINT Tanda_PK PRIMARY KEY (Ident,  Esplai_PK_Nom));
 
 CREATE TABLE Calendari (
 Jornada_Data VARCHAR(1),
 Tanda_Ident VARCHAR(1),
 Tanda_Esplai_PK_Nom VARCHAR(1),
 CONSTRAINT Calendari_FK_Jornada FOREIGN KEY (Jornada_Data) REFERENCES Jornada(Data),
 CONSTRAINT Calendari_FK_Tanda FOREIGN KEY (Tanda_Ident, Tanda_Esplai_PK_Nom) REFERENCES Tanda(Ident, Esplai_PK_Nom),
 CONSTRAINT Calendari_PK PRIMARY KEY (Jornada_Data, Tanda_Ident, Tanda_Esplai_PK_Nom));
 
 CREATE TABLE Membre (
 Noi_Cognom2 VARCHAR(1),
 Noi_Nom VARCHAR(1),
 Noi_Cognom1 VARCHAR(1),
 Tanda_Ident VARCHAR(1),
 Tanda_Esplai_PK_Nom VARCHAR(1) NOT NULL,
 CONSTRAINT Membre_FK_Noi FOREIGN KEY (Noi_Cognom2, Noi_Nom, Noi_Cognom1) REFERENCES Noi(Cognom2, Nom, Cognom1),
 CONSTRAINT Membre_FK_Tanda FOREIGN KEY (Tanda_Ident, Tanda_Esplai_PK_Nom) REFERENCES Tanda(Ident, Esplai_PK_Nom),
 CONSTRAINT Membre_PK PRIMARY KEY (Noi_Cognom2, Noi_Nom, Noi_Cognom1, Tanda_Ident, Tanda_Esplai_PK_Nom));
 
 CREATE TABLE Sortida (
 Tanda_Ident VARCHAR(1) NOT NULL,
 Tanda_Esplai_PK_Nom VARCHAR(1) NOT NULL,
 Jornada_Data VARCHAR(1) NOT NULL,
 Noi_Cognom2 VARCHAR(1) NOT NULL,
 Noi_Nom VARCHAR(1) NOT NULL,
 Noi_Cognom1 VARCHAR(1) NOT NULL,
 CONSTRAINT Sortida_FK_Calendari FOREIGN KEY (Jornada_Data, Tanda_Ident, Tanda_Esplai_PK_Nom) REFERENCES Calendari(Jornada_Data, Tanda_Ident, Tanda_Esplai_PK_Nom),
 CONSTRAINT Sortida_FK_Membre FOREIGN KEY (Noi_Cognom2, Noi_Nom, Noi_Cognom1, Tanda_Ident, Tanda_Esplai_PK_Nom) REFERENCES Membre(Noi_Cognom2, Noi_Nom, Noi_Cognom1, Tanda_Ident, Tanda_Esplai_PK_Nom),
 CONSTRAINT Sortida_PK PRIMARY KEY (Jornada_Data, Noi_Cognom2, Noi_Nom, Noi_Cognom1));
