#!/usr/bin/python

import socket
import os
from time import sleep

class fileServer:
    dirPath = "/home/michalec/Pobrane"
    cmdPort = 7777
    transferPort = 8888
    cmdSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def listFiles(self):
        lsResult = "List of files in directory " + str(self.dirPath) + ":\n"
        print "Klient zazadal listy plikow na serwerze"
        for file in next(os.walk(self.dirPath))[2]:
            lsResult += "* " + file + "\n"
        self.client.send(lsResult)


    def sendFile(self, filename):
        fullPath = self.dirPath + "/" + filename
        if not os.path.isfile(fullPath):
            self.client.send("Error 01: File not found\n")
            return
        print "Wysylanie pliku " + str(filename) + " na porcie " + str(self.transferPort)
        self.client.send(str("port " + str(self.transferPort)))
        self.transferData(fullPath, filename)

    def transferData(self, path, filename):
        self.transferSocket =  socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.transferSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.transferSocket.bind(("localhost", self.transferPort))
        self.transferSocket.listen(2)
        sleep(1)
        try:
            clientCon, addr = self.transferSocket.accept()
            f = open(path, "r")
            fileSize =  str(os.stat(path).st_size)
            clientCon.send(filename)
            sleep(0.5)
            clientCon.send(fileSize)
            while True:
                readData = f.read(1024)
                clientCon.send(readData)
                if readData == '':
                    break
        except(Exception):
            print "Nie udalo sie wyslac pliku"


    def processCommand(self, data):
        #print "Received data=" + str(data)
        if data == "ls":
            self.listFiles()
        elif data.startswith("get "):
            self.sendFile(data[4:])
        else:
            self.client.send("Nieznane polecenie\n")
            print "Klient wykonal bledne polecenie"

    def run(self):
        self.cmdSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.cmdSocket.bind(("localhost", self.cmdPort))
        self.cmdSocket.listen(4)
        print "Listining started on port " + str(self.cmdPort)

        while True:
            (self.client, self.address) = self.cmdSocket.accept()
            print "Client " + str(self.address) + " connected"
            self.client.send("Polecenia serwera transferu plikow:\n"
                        "ls - wyswietla liste plikow na serwerze\n"
                        "get PLIK - pobiera plik wskazany przez uzytkownika\n")
            connected = True
            while connected:
                data = self.client.recv(1024).rstrip()
                if data:
                    self.processCommand(data)
                else:
                    print "Client disconnected"
                    connected = False


server = fileServer()
server.run()
