import socket
import threading
import sys
from os import path
sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )
from TimpMessage import TimpMessage, Status
from MessagesStack import MessagesStack
from ClientMessageExchanger import ClientMessageExchanger
from PyQt4.QtCore import QObject
from PyQt4.Qt import SIGNAL
from ClientInfo import ClientInfo
import time

class MessagesReader(threading.Thread):
    def __init__(self, sock, exchanger):
        threading.Thread.__init__(self)
        self.socket = sock
        self.messageExchanger = exchanger

    def run(self):
        self.stopped = False
        while not self.stopped:
            self.socket.settimeout(1)
            try:
                data = self.socket.recv(4096)
                if data:
                    print "Received data = " + str(data)
                    MessagesStack.push(TimpMessage(data))
                    self.messageExchanger.processMessage(TimpMessage(data))
                    print MessagesStack.messages
            except:
                pass

    def stop(self):
        self.stopped = True

class ClientMain(QObject):
    def __init__(self):
        QObject.__init__(self)
        self.loggedIn = False
        self.serverAddress = "localhost"
        self.serverPort = 7777
        self.clientSocket = None
        self.msgReader = None

        self.messageExchanger = ClientMessageExchanger()
        self.connect(self.messageExchanger, SIGNAL("sgb(QString)"), self.tstSigB)
        self.connect(self.messageExchanger, SIGNAL("sga()"), self.tstSig)

    def connectToServer(self):
        self.clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.clientSocket.connect((self.serverAddress, self.serverPort))
        self.msgReader = MessagesReader(self.clientSocket, self.messageExchanger)
        self.msgReader.start()

    def disconnectFromServer(self):
        print("Trying to disconnect from the server")
        if self.loggedIn == True:
            print("Sending FINISH message")
            finishMessage = ClientMessageExchanger.createFinishMessage()
            self.sendMessage(finishMessage)
        if self.clientSocket is not None:
            print("Closing client socket")
            self.clientSocket.close()
        if self.msgReader is not None:
            print("Stopping msgReader")
            self.msgReader.stop()
        del self.clientSocket
        del self.msgReader

    def sendMessage(self, text):
        self.clientSocket.send(str(text))

    def updateStatuses(self):
        statusChangeNotify = ClientMessageExchanger.createStatusChangeMessage(ClientInfo.getStatus(), statusDesc="")
        self.sendMessage(statusChangeNotify)

        getListMessage = ClientMessageExchanger.createGetBuddylistMessage()
        self.sendMessage(getListMessage)
        requestCseq = TimpMessage(getListMessage).cseq()
        time.sleep(1)
        getListResponse = MessagesStack.getResponseMessageByCseq(requestCseq)
        self.fillBuddyList(getListResponse)

    def fillBuddyList(self, getListResponse):
        pass

    def tstSig(self):
        print "YEEEEAH!"

    def tstSigB(self):
            print "YEEEEAHBBBBBBBBBB!"