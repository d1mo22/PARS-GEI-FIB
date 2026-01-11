CREATE TABLE Grup (
 nom varchar(1) ,
 monitor varchar(1) ,
 CONSTRAINT Grup_PK PRIMARY KEY (nom));
 
 CREATE TABLE Noi (
 Grup_nom varchar(1)  NOT NULL,
 nom varchar(1) ,
 edat varchar(1) ,
 Mascota_nom varchar(1),
 CONSTRAINT Noi_FK_Grup FOREIGN KEY (Grup_nom) REFERENCES Grup(nom),
 CONSTRAINT Noi_PK PRIMARY KEY (nom),
 CONSTRAINT Noi_UNIQUE UNIQUE (Mascota_nom));
 
 CREATE TABLE Amics (
 Noi1_nom varchar(1) NOT NULL,
 Noi2_nom varchar(1) NOT NULL,
 CONSTRAINT Amics1_FK_Noi FOREIGN KEY (Noi1_nom) REFERENCES Noi(nom),
 CONSTRAINT Amics2_FK_Noi FOREIGN KEY (Noi2_nom) REFERENCES Noi(nom),
 CONSTRAINT Amics_PK PRIMARY KEY (Noi1_nom, Noi2_nom),
CONSTRAINT Amics_check CHECK(Noi1_nom<>Noi2_nom));
 
 CREATE TABLE Incompatibles (
 Mascota1_nom varchar(1) NOT NULL,
 Mascota2_nom varchar(1) NOT NULL,
 CONSTRAINT Incompatibles1_FK_Mascota FOREIGN KEY (Mascota1_nom) REFERENCES Noi(Mascota_nom),
 CONSTRAINT Incompatibles2_FK_Mascota FOREIGN KEY (Mascota2_nom) REFERENCES Noi(Mascota_nom),
 CONSTRAINT Incompatibles_PK PRIMARY KEY (Mascota1_nom, Mascota2_nom),
CONSTRAINT incompatibles_check CHECK (Mascota1_nom<>Mascota2_nom) );
