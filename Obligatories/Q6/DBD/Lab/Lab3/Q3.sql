CREATE TABLE objects (
id_object NUMBER PRIMARY KEY,
descr_object VARCHAR2(100));

CREATE TABLE peers (
peer_id NUMBER PRIMARY KEY,
peer_url VARCHAR(50) UNIQUE NOT NULL);

CREATE TABLE files (
file_id NUMBER PRIMARY KEY,
file_size NUMBER,
file_extension VARCHAR2(3),
id_object NUMBER REFERENCES objects(id_object));

CREATE TABLE shares (
peer_id NUMBER REFERENCES peers(peer_id),
file_id NUMBER REFERENCES files(file_id),
PRIMARY KEY(peer_id, file_id));