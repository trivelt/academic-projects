#!/usr/bin/python
import socket
import sys
from os import path
sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )
from MessagesStack import MessagesStack
from TimpMessage import TimpMessage
from ServerMessageExchanger import ServerMessageExchanger
import threading
from PyQt4.QtCore import QObject, SIGNAL

class MessagesReader(threading.Thread, QObject):
    def __init__(self, sock, exchanger):
        QObject.__init__(self)
        threading.Thread.__init__(self)
        self.socket = sock
        self.messageExchanger = exchanger
        self.messageExchanger.setSocket(sock)
        #self.connect(self.messageExchanger, SIGNAL("sendMessage(QString)"), self.sendMessage1)

    def run(self):
        self.stopped = False
        while not self.stopped:
            self.socket.settimeout(1)
            try:
                data = self.socket.recv(4096)
                if data:
                    print "Received data = " + str(data)
                    data = str(data)
                    lines = data.split("\r\n")
                    print( "Splitted = ")
                    print lines
                    MessagesStack.push(TimpMessage(data))
                    self.messageExchanger.processMessage(TimpMessage(data))
                    print MessagesStack.messages
            except:
                pass

    def sendMessage1(self, message):
        print "Sending message " + str(message)
        self.socket.send(str(message))

    def stop(self):
        self.stopped = True

class ServerMain:
    def __init__(self):
        self.tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.tcpSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
    def listen(self, port):
        self.tcpSocket.bind(("localhost", port))        
        self.tcpSocket.listen(5)
        print("Listining started at localhost:" + str(port))
        while True:
            (client, address) = self.tcpSocket.accept()
            print client
            self.addClientSocket(client)
        
    def addClientSocket(self, clientSocket):
        serverMsgExchanger = ServerMessageExchanger()
        msgReader = MessagesReader(clientSocket, serverMsgExchanger)
        msgReader.start()
        
    def stop(self):
        self.tcpSocket.close()
        
        
server = ServerMain()
try:
    server.listen(7777)
except (KeyboardInterrupt, SystemExit):
    server.stop()
    exit()
#server.stop()


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
# Sender: MyUserName\r\n
# Receiver: otherUserName\r\n
# MessageId: id\r\n
# Content-Length: length\r\n\r\n
# MESSAGE CONTENT\r\n
#
#
# Wiadomosc do serwera o zmianie wlasnego statusu
# USERSTATUS * TIMP 0.9\r\n
# Date: unixTime\r\n
# Sender: MyUserName\r\n
# NewStatus: status\r\n
#
#
# Wiadomosc od serwera o zmianie statusu znajomego
# BUDDYSTATUS * TIMP 0.9\r\n
# Date: unixTime\r\n
# StatusChanger: UserName\r\n
# NewStatus: status\r\n
#
#
# Aktualizacja listy znajomych (do serwera)
#
#
#
#
# Pobranie listy znajomych (z serwera)
#
#
#
#
# Zalozenie konta na serwerze
#
#
#
# Autentyfikacja przy logowaniu
#
#
#
# OK (potwierdzenie od serwera)
#
#
# NOT OK (NOT AUTHENTICATED, od serwera)
###################
