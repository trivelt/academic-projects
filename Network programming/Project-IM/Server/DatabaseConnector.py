import MySQLdb as mdb

class DatabaseConnector:
    def __init__(self):
        self.con = mdb.connect("localhost", "root", "toor", "timp")
        self.cur = self.con.cursor()

    def authUser(self, username, password):
        query = "SELECT login, password FROM Auth WHERE login='" + str(username) + "'"
        self.cur.execute(query)
        result = self.cur.fetchone()
        if result is None:
            return False
        loginFromDb = result[0]
        passwordFromDb = result[1]
        if username == loginFromDb and password == passwordFromDb:
            return True
        else:
            return False

    def createAccount(self, username, password):
        if username == "" or password == "":
            return False
        query = "SELECT login FROM Auth WHERE login='" + str(username) + "'"
        self.cur.execute(query)
        result = self.cur.fetchall()
        if len(result) > 0:
            return False
        query = "INSERT INTO Auth VALUES ('" + str(username) + "', '"
        query += str(password) + "')"
        self.cur.execute(query)
        self.con.commit()
        return True

    def searchPhrase(self, phrase):
        query = "SELECT login FROM Auth WHERE login LIKE CONCAT('%', '" + str(phrase) + "', '%')"
        self.cur.execute(query)
        result = self.cur.fetchall()
        resultList = list()
        for name in result:
            resultList.append(name[0])
        return resultList

    def getBuddyList(self, username):
        buddyList = list()
        query = "SELECT buddyname FROM Buddies WHERE username='" + str(username) + "'"
        self.cur.execute(query)
        buddies = self.cur.fetchall()
        for buddy in buddies:
            buddyName = buddy[0]
            buddyPseudonim = self.getPseudonim(username, buddyName)
            buddyEntry = [buddyName, buddyPseudonim]
            buddyList.append(buddyEntry)
        return buddyList

    def getPseudonim(self, username, buddyname):
        query = "SELECT pseudonim FROM BuddiesPseudonims WHERE username='" + str(username) + "'"
        query += " and buddyname='" + str(buddyname) + "'"
        self.cur.execute(query)
        pseudonim = self.cur.fetchone()
        if pseudonim is None:
            return buddyname
        else:
            return pseudonim[0]

    def updateBuddyList(self, username, buddyList):
        buddyListDict = self.createBuddyDict(buddyList)
        buddyDbDict = self.createBuddyDict(self.getBuddyList(username))

        buddiesFromDb = set(buddyDbDict.keys())
        currentBuddies = set(buddyListDict.keys())

        newBuddies = currentBuddies - buddiesFromDb
        buddiesToRemove = buddiesFromDb - currentBuddies

        self.addNewBuddies(username, newBuddies, buddyListDict)
        self.removeOldBuddies(username, buddiesToRemove)

        updatedBuddies = self.createBuddyDict(self.getBuddyList(username))
        buddiesDbPseudos = set(updatedBuddies.values())
        currentBuddiesPseudos = set(buddyListDict.values())
        changedPseudos = currentBuddiesPseudos - buddiesDbPseudos
        for pseudo in changedPseudos:
            name = self.findNameForPseudo(buddyListDict, pseudo)
            queryPseudo = "UPDATE BuddiesPseudonims SET pseudonim='" + str(pseudo) + "'"
            queryPseudo += " WHERE username='"+str(username)+"' AND buddyname='"+str(name)+"'"
            self.cur.execute(queryPseudo)
        self.con.commit()

    def findNameForPseudo(self, buddiesDict, searchedPseudo):
        for name, pseudo in buddiesDict.items():
            if pseudo == searchedPseudo:
                return name
        return None

    def createBuddyDict(self, buddyList):
        buddyDict = dict()
        for buddy in buddyList:
            name = buddy[0]
            pseudo = buddy[1]
            buddyDict[name] = pseudo
        return buddyDict

    def addNewBuddies(self, username, newBuddies, buddyListDict):
        for buddy in newBuddies:
            queryBuddy = "INSERT INTO Buddies VALUES('" + str(username) + "','"
            queryBuddy += str(buddy) + "')"
            self.cur.execute(queryBuddy)

            pseudo = buddyListDict[buddy]
            queryPseudo = "INSERT INTO BuddiesPseudonims VALUES('" + str(username) + "','"
            queryPseudo += str(buddy) + "','" + str(pseudo) + "')"
            self.cur.execute(queryPseudo)

    def removeOldBuddies(self, username,buddiesToRemove):
        for buddy in buddiesToRemove:
            queryBuddy = "DELETE FROM Buddies WHERE username='"+ str(username)
            queryBuddy += "' AND buddyname='" + str(buddy) + "'"
            self.cur.execute(queryBuddy)

            queryPseudo = "DELETE FROM BuddiesPseudonims WHERE username='"+ str(username)
            queryPseudo += "' and buddyname='" + str(buddy) + "'"
            self.cur.execute(queryPseudo)

    def getUsersToNotify(self, username):
        usersList = list()
        query = "SELECT username FROM Buddies WHERE buddyname='" + str(username) + "'"
        self.cur.execute(query)
        users = self.cur.fetchall()
        for user in users:
            name = user[0]
            usersList.append(name)
        return usersList

    def getStatusDesc(self, username):
        query = "SELECT statusDesc from OfflineStatuses WHERE username='" + str(username) + "'"
        self.cur.execute(query)
        status = self.cur.fetchone()
        if status is None:
            return ""
        else:
            return status[0]

    def setStatusDesc(self, username, desc):
        queryDelete =  "DELETE FROM OfflineStatuses WHERE username='" + str(username) + "'"
        queryInsert = "INSERT INTO OfflineStatuses VALUES('" + str(username) + "','" + str(desc) + "')"
        self.cur.execute(queryDelete)
        self.cur.execute(queryInsert)
        self.con.commit()


    def getOfflineMessages(self, username):
        messagesList = list()
        querySelect = "SELECT msgText FROM OfflineMessages WHERE receiver='" + str(username) + "'"
        self.cur.execute(querySelect)
        messages = self.cur.fetchall()
        for message in messages:
            msgText = message[0]
            messagesList.append(msgText)
        queryDelete = "DELETE FROM OfflineMessages WHERE receiver='" + str(username) + "'"
        self.cur.execute(queryDelete)
        self.con.commit()
        return messagesList

    def putOfflineMessage(self, username, message):
        query = "INSERT INTO OfflineMessages VALUES('" + str(username) + "','" + str(message) + "')"
        self.cur.execute(query)
        self.con.commit()


dC = DatabaseConnector()
print "createAccount(Ola): " + str(dC.createAccount("ola", "adadad"))
print dC.createAccount("Adam", "")
print dC.createAccount("Michal239", "haslo2392")

print "\nauthUser(ola): " + str(dC.authUser("ola", "adadad"))
print dC.authUser("ola", "azor")
print dC.authUser("Michal239", "haslo2392")
print dC.authUser("noUser", "X")

dC.updateBuddyList("ola", [["Jacek1999", "Jacus:)"], ["root", "adminek"]])
print "getBuddyList(ola): " + str(dC.getBuddyList("ola"))
print "getBuddyList(Jacek1999): " + str(dC.getBuddyList("Jacek1999"))

print dC.getUsersToNotify("Jacek1999")
print dC.getUsersToNotify("noUser")

dC.setStatusDesc("ola", "Goodbye, Blue Sky...")
print dC.getStatusDesc("ola")
print dC.getStatusDesc("root")
print dC.getStatusDesc("noUser")

#print dC.putOfflineMessage("Jacek1999", "ABCD")
print dC.getOfflineMessages("Jacek1999")

print "Search phrase: " + str(dC.searchPhrase("o"))