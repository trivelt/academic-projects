USE timp;
#INSERT INTO Auth VALUES("root", "toor");
#INSERT INTO Auth VALUES("ola", "azor");
#INSERT INTO Auth VALUES("Jacek1999", "secretP$wd");

INSERT INTO Buddies VALUES("ola", "Jacek1999");
INSERT INTO Buddies VALUES("ola", "root");
INSERT INTO Buddies VALUES("Jacek1999", "ola");
INSERT INTO Buddies VALUES("root", "Jacek1999");

INSERT INTO BuddiesPseudonims VALUES("ola", "Jacek1999", "Jacus");
INSERT INTO BuddiesPseudonims VALUES("ola", "root", "admin");
INSERT INTO BuddiesPseudonims VALUES("Jacek1999", "ola", "Olka");
INSERT INTO BuddiesPseudonims VALUES("root", "Jacek1999", "JackSparrow");

INSERT INTO OfflineStatuses VALUES("ola", "Goodbye, Blue Sky...");
INSERT INTO OfflineStatuses VALUES("root", "SOA #2, hehe")

INSERT INTO OfflineMessages VALUES("ola", "TEXT_MESSAGE * TIMP 0.9\r\nDate: unixTime\r\nCSeq: 51\r\nSender: MyUserName\r\nReceiver: otherUserName\r\nMessageId: 921\r\nContent-Length: 24\r\n\r\nMESSAGE CONTENT Test1234\r\n");
