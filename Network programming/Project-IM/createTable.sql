CREATE DATABASE timp DEFAULT CHARACTER SET utf8 COLLATE utf8_polish_ci;
USE timp;

CREATE TABLE Auth (
login VARCHAR(100),
password VARCHAR(100)
);

CREATE TABLE Buddies (
username VARCHAR(100),
buddyname VARCHAR(100)
);

CREATE TABLE BuddiesPseudonims (
username VARCHAR(100),
buddyname VARCHAR(100),
pseudonim VARCHAR(100)
);

CREATE TABLE OfflineMessages (
receiver VARCHAR(100),
msgText TEXT
);

CREATE TABLE OfflineStatuses (
username VARCHAR(100),
statusDesc TEXT
);
