import socket
from TimpMessage import TimpMessage, MessageType, Status
from PyQt4.QtCore import QObject, SIGNAL
from DatabaseConnector import DatabaseConnector
from OnlineUsers import OnlineUsers
from OnlineClient import OnlineClient
import datetime

class ServerMessageExchanger(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.authenticated = False
        self.dbConnector = DatabaseConnector()
        self.cseq = 1

    def setSocket(self, sock):
        self.socket = sock

    def processMessage(self, message):
        print "Processing message " + str(message)
        if not self.authenticated:
            self.tryAuthenticate(message)
        else:
            if message.type() is MessageType.GET_BUDDYLIST:
                pass
            elif message.type is MessageType.STATUS_REQUEST:
                pass
            elif message.type() is MessageType.USER_STATUS:
                self.processUserStatusChange(message)
            elif message.type() is MessageType.GET_BUDDYLIST:
                pass
            elif message.type() is MessageType.PUSH_BUDDYLIST:
                pass
            elif message.type() is MessageType.TEXT_MESSAGE:
                pass
            elif message.type() is MessageType.CATALOG_REQUEST:
                self.returnCatalogResults(message)
            elif message.type() is MessageType.FINISH:
                self.finishClient(message)
            else:
                pass


    def tryAuthenticate(self, firstMessage):
        if firstMessage.type() is MessageType.AUTHENTICATE:
            self.authenticateClient(firstMessage)
        elif firstMessage.type() is MessageType.CREATE_ACCOUNT:
            self.createNewClientAccount(firstMessage)
        else:
            msgCseq = firstMessage.cseq()
            errorString = "User not authenticated"
            notOkMessage = self.createNotOkMessage(msgCseq, "", errorString)
            self.sendMessage(notOkMessage)

    def authenticateClient(self, authMessage):
        username = authMessage.getUsername()
        password = authMessage.getPassword()
        msgCseq = authMessage.cseq()
        authSuccess = self.dbConnector.authUser(username, password)
        if authSuccess:
            successMessage = self.createSuccessMessage(msgCseq)
            self.sendMessage(successMessage)
            self.authenticated = True
            onlineClient = OnlineClient(username, self.socket)
            OnlineUsers.addUser(onlineClient)
        else:
            errorString = "Authentication failed"
            notOkMessage = self.createNotOkMessage(msgCseq, username, errorString)
            self.sendMessage(notOkMessage)

    def createNewClientAccount(self, newAccountMessage):
        username = newAccountMessage.getUsername()
        password = newAccountMessage.getPassword()
        msgCseq = newAccountMessage.cseq()
        createSuccess = self.dbConnector.createAccount(username, password)
        if createSuccess:
            successMessage = self.createSuccessMessage(msgCseq)
            self.sendMessage(successMessage)
        else:
            errorString = "Registration failed"
            notOkMessage = self.createNotOkMessage(msgCseq, username, errorString)
            self.sendMessage(notOkMessage)

    def processUserStatusChange(self, message):
        username = message.getUsername()
        status = message.getValueOfParameter("NewStatus")
        statusDesc = message.getValueOfParameter("StatusDesc")
        usersToNotify = self.dbConnector.getUsersToNotify()
        for user in usersToNotify:
            if OnlineUsers.isOnline(user):
                if status == "Invisible":
                    statusMessage = self.createUserStatusMessage(username, "Offline", statusDesc)
                else:
                    statusMessage = self.createUserStatusMessage(username, status, statusDesc)
                userSocket = OnlineUsers.getSocket(user)
                userSocket.send(statusMessage)
        self.processStatus(username, status, statusDesc)

    def processStatus(self, username, status, desc):
        isOnline = OnlineUsers.isOnline(username)
        if status == "Offline":
            if isOnline:
                OnlineUsers.removeUser(username)
            self.dbConnector.setStatusDesc(username, desc)
        else:
            if not isOnline:
                OnlineUsers.addUser(username)

    def returnCatalogResults(self, message):
        phrase = message.getValueOfParameter("Phrase")
        cseq = message.cseq()
        results = self.dbConnector.searchPhrase(phrase)
        responseMessage = self.createSuccessMessage(cseq)
        responseMessage += "\r\n"
        responseMessage += str(results)
        responseMessage += "\r\n"
        self.sendMessage(responseMessage)

    def finishClient(self, message):
        print("Client finished")

    def createUserStatusMessage(self, sender, status, desc):
        messageText = "USER_STATUS * TIMP 0.9\r\n"
        messageText += self.getDateLine()
        messageText += self.getCSeqLine()
        messageText += "Sender: " + sender + "\r\n"
        messageText += "NewStatus: " + status + "\r\n"
        messageText += "StatusDesc: " + desc + "\r\n"
        return messageText

    def sendMessage(self, message):
        print "Sending message from exchanger:" + str(message)
        self.socket.send(str(message))

    def createSuccessMessage(self, cseq):
        messageText = "SUCCESS * TIMP 0.9\r\n"
        messageText += self.getDateLine()
        messageText += "CSeq: " + str(cseq) + "\r\n"
        return messageText

    def createNotOkMessage(self, cseq, receiver, errorString=None):
        if errorString is None:
            messageText = "NOT_OK * TIMP 0.9\r\n"
        else:
            messageText = "NOT_OK * " + errorString + " * TIMP 0.9\r\n"
        messageText += self.getDateLine()
        messageText += "CSeq: " + str(cseq) + "\r\n"
        messageText += "Receiver: " + receiver + "\r\n"
        return messageText

    def getDateLine(self):
        currentDate = datetime.datetime.now().strftime("%I:%M%p, %B %d %Y")
        dateLine = "Date: "+ currentDate + "\r\n"
        return dateLine

    def getCSeqLine(self):
        cseqLine = "CSeq: " + str(self.cseq) + "\r\n"
        self.cseq += 1
        return cseqLine