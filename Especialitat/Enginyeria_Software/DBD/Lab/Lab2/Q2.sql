CREATE TABLE Bicicleta (
 id VARCHAR(1) ,
 CONSTRAINT Bicicleta_PK PRIMARY KEY (id));
 
 CREATE TABLE corredorM (
 club VARCHAR(1) ,
 federacio VARCHAR(1) ,
 Corredor_id VARCHAR(1) ,
 CONSTRAINT M_PK PRIMARY KEY (Corredor_id));
 
 CREATE TABLE corredorC (
 edat VARCHAR(1) ,
 pes VARCHAR(1) ,
 alt VARCHAR(1) ,
 Corredor_id VARCHAR(1) ,
 CONSTRAINT C_PK PRIMARY KEY (Corredor_id));
 
 CREATE TABLE Usa (
 C_Corredor_id VARCHAR(1) NOT NULL,
 Bicicleta_id VARCHAR(1),
 CONSTRAINT Usa_FK_C FOREIGN KEY (C_Corredor_id) REFERENCES corredorC(Corredor_id),
 CONSTRAINT Usa_FK_Bicicleta FOREIGN KEY (Bicicleta_id) REFERENCES Bicicleta(id),
 CONSTRAINT Usa_PK PRIMARY KEY (Bicicleta_id));
