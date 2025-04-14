CREATE TABLE families (
    familia CHAR(20),
    reproduccio CHAR(10),
    PRIMARY KEY (familia));

CREATE TABLE peixos (
    especie CHAR(20),
    familia CHAR(20) NOT NULL,
    color CHAR(10) NOT NULL,
    raresa INTEGER,
    PRIMARY KEY (especie),
    UNIQUE (familia, color),
    FOREIGN KEY (familia) REFERENCES families(familia));