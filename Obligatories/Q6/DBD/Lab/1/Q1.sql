CREATE TABLE DEPARTAMENTS
         (	NUM_DPT INTEGER,
    NOM_DPT CHAR(20),
    PLANTA INTEGER,
    EDIFICI CHAR(30),
    CIUTAT_DPT CHAR(20),
    PRIMARY KEY (NUM_DPT));

CREATE TABLE PROJECTES
         (	NUM_PROJ INTEGER,
    NOM_PROJ CHAR(10),
    PRODUCTE CHAR(20),
    PRESSUPOST INTEGER,
    PRIMARY KEY (NUM_PROJ));

CREATE TABLE EMPLEATS
         (	NUM_EMPL INTEGER,
    NOM_EMPL CHAR(30),
    SOU INTEGER,
    CIUTAT_EMPL CHAR(20),
    NUM_DPT INTEGER,
    NUM_PROJ INTEGER,
    PRIMARY KEY (NUM_EMPL),
    FOREIGN KEY (NUM_DPT) REFERENCES DEPARTAMENTS (NUM_DPT),
    FOREIGN KEY (NUM_PROJ) REFERENCES PROJECTES (NUM_PROJ));


INSERT INTO  PROJECTES VALUES (1,'IBDTEL','TELEVISIO',1000000);
INSERT INTO  DEPARTAMENTS VALUES (1,'DIRECCIO',10,'PAU CLARIS','BARCELONA');
INSERT INTO  EMPLEATS VALUES (1,'CARME',400000,'MATARO',1,1);
-----------------------------------------
--Proposeu una sentència SQL per obtenir tots els projectes de la base de dades.
--Per cada projecte ha de sortir el número del projecte, el nom del projecte i la quantitat de ciutats en que estan situats els departaments dels empleats que treballen al projecte.
--El resultat ha d'estar ordenat pel número de projecte, el nom de projecte i la quantitat de ciutats.
SELECT p.NUM_PROJ, p.NOM_PROJ, COUNT(DISTINCT d.CIUTAT_DPT) as NUM_CIUTATS
FROM PROJECTES p
LEFT JOIN EMPLEATS e ON p.NUM_PROJ = e.NUM_PROJ
LEFT JOIN DEPARTAMENTS d ON e.NUM_DPT = d.NUM_DPT
GROUP BY p.NUM_PROJ, p.NOM_PROJ
ORDER BY p.NUM_PROJ, p.NOM_PROJ, NUM_CIUTATS;