from PyQt4.QtCore import SIGNAL, QObject
import datetime
from ClientInfo import ClientInfo

class ClientMessageExchanger(QObject):
    cseq = 1

    def __init__(self):
        QObject.__init__(self)

    def processMessage(self, message):
        print "Emmiting msg=" + str(message)
        self.emit(SIGNAL("sgb(QString)"), str(message))

    @staticmethod
    def createRegisterMessage(username, password):
        messageText = "CREATE_ACCOUNT * TIMP 0.9\r\n"
        messageText += ClientMessageExchanger.getDateLine()
        messageText += ClientMessageExchanger.getCSeqLine()
        messageText += "Username: " + username + "\r\n"
        messageText += "Password: " + password + "\r\n"
        return messageText

    @staticmethod
    def createAuthMessage(username, password):
        messageText = "AUTHENTICATE * TIMP 0.9\r\n"
        messageText += ClientMessageExchanger.getDateLine()
        messageText += ClientMessageExchanger.getCSeqLine()
        messageText += "Username: " + username + "\r\n"
        messageText += "Password: " + password + "\r\n"
        return messageText

    @staticmethod
    def createStatusChangeMessage(newStatus, statusDesc):
        messageText = "USER_STATUS * TIMP 0.9\r\n"
        messageText += ClientMessageExchanger.getDateLine()
        messageText += ClientMessageExchanger.getCSeqLine()
        messageText += "Sender: " + ClientInfo.username + "\r\n"
        messageText += "NewStatus: " + newStatus + "\r\n"
        messageText += "StatusDesc: " + statusDesc + "\r\n"
        return messageText

    @staticmethod
    def createBuddyStatusRequestMessage(buddy):
        pass

    @staticmethod
    def createPushBuddylistMessage(buddylist):
        pass

    @staticmethod
    def createGetBuddylistMessage():
        messageText = "GET_BUDDYLIST * TIMP 0.9\r\n"
        messageText += ClientMessageExchanger.getDateLine()
        messageText += ClientMessageExchanger.getCSeqLine()
        messageText += "Sender: " + ClientInfo.username + "\r\n"
        return messageText

    @staticmethod
    def createTextMessage(receiver, msgText):
        pass

    @staticmethod
    def createFinishMessage():
        messageText = "FINISH * TIMP 0.9\r\n"
        messageText += ClientMessageExchanger.getDateLine()
        messageText += ClientMessageExchanger.getCSeqLine()
        messageText += "Sender: " + ClientInfo.username + "\r\n"
        return messageText

    @staticmethod
    def createCatalogRequestMessage(searchPhrase):
        messageText = "CATALOG_REQUEST * TIMP 0.9\r\n"
        messageText += ClientMessageExchanger.getDateLine()
        messageText += ClientMessageExchanger.getCSeqLine()
        messageText += "Phrase: " + searchPhrase + "\r\n"
        return messageText

    @staticmethod
    def getDateLine():
        currentDate = datetime.datetime.now().strftime("%I:%M%p, %B %d %Y")
        dateLine = "Date: "+ currentDate + "\r\n"
        return dateLine

    @staticmethod
    def getCSeqLine():
        cseqLine = "CSeq: " + str(ClientMessageExchanger.cseq) + "\r\n"
        ClientMessageExchanger.cseq += 1
        return cseqLine