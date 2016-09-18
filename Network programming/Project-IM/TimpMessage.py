class MessageType:
    TEXT_MESSAGE = 1
    USER_STATUS = 2
    STATUS_REQUEST = 3
    PUSH_BUDDYLIST = 4
    GET_BUDDYLIST = 5
    CREATE_ACCOUNT = 6
    AUTHENTICATE = 7
    SUCCESS = 8
    NOT_OK = 9
    UNKNOWN = 10
    CATALOG_REQUEST = 11
    FINISH = 12

class Status:
    AVAILABLE = 1
    OFFLINE = 2
    AWAY = 3
    INVISIBLE = 4

    @staticmethod
    def toString(status):
        if status is Status.AVAILABLE:
            return "Available"
        elif status is Status.OFFLINE:
            return "Offline"
        elif status is Status.AWAY:
            return "Away"
        elif status is Status.INVISIBLE:
            return "Invisible"


class TimpMessage:
    def __init__(self, message=""):
        self.message = message

    def __repr__(self):
        reprString = "TimpMessage:\n"
        reprString += self.message
        return reprString

    def type(self):
        startLine = self.getLineByNumber(0)
        if "TEXT_MESSAGE" in startLine:
            return MessageType.TEXT_MESSAGE
        elif "USER_STATUS" in startLine:
            return MessageType.USER_STATUS
        elif "STATUS_REQUEST" in startLine:
            return MessageType.STATUS_REQUEST
        elif "PUSH_BUDDYLIST" in startLine:
            return MessageType.PUSH_BUDDYLIST
        elif "GET_BUDDYLIST" in startLine:
            return MessageType.GET_BUDDYLIST
        elif "CREATE_ACCOUNT" in startLine:
            return MessageType.CREATE_ACCOUNT
        elif "AUTHENTICATE" in startLine:
            return MessageType.AUTHENTICATE
        elif "SUCCESS" in startLine:
            return MessageType.SUCCESS
        elif "NOT_OK" in startLine:
            return MessageType.NOT_OK
        elif "CATALOG_REQUEST" in startLine:
            return MessageType.CATALOG_REQUEST
        elif "FINISH" in startLine:
            return MessageType.FINISH
        else:
            return MessageType.UNKNOWN

    def getLineByNumber(self, number):
        lines = self.message.split("\r\n")
        if number < 0 or number >= len(lines):
            return ""
        return lines[number]

    def getLineByText(self, text):
        """Return first line containing text, otherwise empty string"""
        lines = self.message.split("\r\n")
        for line in lines:
            if text in line:
                return line
        return ""

    def cseq(self):
        if self.isValid():
            secondLine = self.getLineByNumber(2)
            return int(secondLine.split(": ")[1])
        else:
            return None

    def isValid(self):
        valid = True
        if not "* TIMP " in self.getLineByNumber(0):
            valid = False
        if not "Date: " in self.getLineByNumber(1):
            valid = False
        if not "CSeq: " in self.getLineByNumber(2):
            valid = False
        if not self.message[-2:] == "\r\n":
            valid = False
        return valid

    def getStatus(self):
        if self.type() is not MessageType.USER_STATUS and \
                        self.type() is not MessageType.BUDDY_STATUS:
            return None
        statusLine = self.getLineByNumber(4)
        statusLine = statusLine.lower()
        if "available" in statusLine:
            return Status.AVAILABLE
        elif "offline" in statusLine:
            return Status.OFFLINE
        elif "away" in statusLine:
            return Status.AWAY
        elif "invisible" in statusLine:
            return Status.INVISIBLE
        else:
            return None

    def getSender(self):
        return self.getValueOfParameter("Sender")

    def getReceiver(self):
        return self.getValueOfParameter("Receiver")

    def getUsername(self):
        return self.getValueOfParameter("Username")

    def getPassword(self):
        return self.getValueOfParameter("Password")

    def getContentLength(self):
        contentLength = self.getValueOfParameter("Content-Length")
        if contentLength is "":
            return 0
        else:
            return int(contentLength)

    def getValueOfParameter(self, parameter):
        parameterLine = self.getLineByText(parameter + ": ")
        if parameterLine is not "":
            partsOfLine = parameterLine.split(": ")
            if len(partsOfLine) > 1:
                return partsOfLine[1]
        return ""

    def getContent(self):
        parts = self.message.split("\r\n\r\n")
        if len(parts) == 2:
            content = parts[1]
            return content[:-2]
        return None

    def hasContent(self):
        return self.getContent() is not None


###################
#
# tcpSocket.accept() -> authenticateClient() [OK]-> addToListOfActiveClients() -> createClientThread()
# tcpSocket.accept() -> authenticateClient() [NOT OK]-> FinishConnection()
#
# clientSocket.
#
#
# Trivelt IM Protocol (TIMP)
#
#
# Wiadomosc do innego uzytkownika:
# MESSAGE * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: id\r\n
# Sender: MyUserName\r\n
# Receiver: otherUserName\r\n
# Content-Length: length\r\n\r\n
# MESSAGE CONTENT\r\n
#
#
# Wiadomosc do serwera o zmianie wlasnego statusu
# USERSTATUS * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: seq\r\n\r\n
# Sender: MyUserName\r\n
# NewStatus: status\r\n
# StatusDesc: desc\r\n
#
#
# Zadanie informacji o statusie znajomego
# STATUS_REQUEST * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: seq\r\n\r\n
# Sender: userName\r\n
# RequestedUser: username\r\n
# NewStatus: status\r\n
# StatusDesc: desc\r\n
#
#
# Aktualizacja listy znajomych (do serwera)
# PUSH_BUDDYLIST * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq = id\r\n
# Sender: userName\r\n
# Content-Length: length\r\n\r\n
# BUDDY_LIST
#
#
#
# Pobranie listy znajomych (z serwera)
# GET_BUDDYLIST * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: seq\r\n\r\n
# Sender: userName\r\n
#
#
#
#
# Zalozenie konta na serwerze
# CREATE_ACCOUNT * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: seq\r\n\r\n
# Username: name\r\n
# Password: pswd\r\n
#
#
#
# Autentyfikacja przy logowaniu
# AUTHENTICATE * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: seq\r\n\r\n
# Username: name\r\n
# Password: pswd\r\n
#
#
#
# SUCCESS (potwierdzenie od serwera)
# SUCCESS * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: seq\r\n\r\n
# Username: name\r\n
# Password: pswd\r\n
# (Content-Length: length\r\n\r\n
# BUDDY_LIST\r\n)
#
#
# NOT OK (NOT AUTHENTICATED, od serwera)
# NOT_OK * ERROR_CODE * TIMP 0.9\r\n
# Date: unixTime\r\n
# CSeq: seq\r\n\r\n
# Username: name\r\n
# Password: pswd\r\n
#
###################
