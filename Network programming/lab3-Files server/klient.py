#!/usr/bin/python

import socket
from time import sleep

class fileClient:
    cmdSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def getFile(self, port):
        print "Pobieranie pliku na porcie " + str(port)
        self.transferSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sleep(0.5)	
        self.transferSocket.connect(("localhost", port))

        filename = self.transferSocket.recv(512)
        fileSize = self.transferSocket.recv(100)
        fileSize = int(fileSize)
        recvBytes = 0

        print "filename=" + str(filename) + ", size=" + str(fileSize)

        f = open(filename, "w")

        while recvBytes < fileSize:
            data = self.transferSocket.recv(1024)
            if data:
                recvBytes += 1024
                f.write(data)
                #print "received =" + str(data)
        f.close()


    def run(self):
        self.cmdSocket.connect(("localhost", 7777))

        while True:
            data = self.cmdSocket.recv(8192)
            if data:
                if data.startswith("port "):
                    self.getFile(int(data[5:]))
                else:
                    print data

            cmd = raw_input("$: ")
            cmd = str(cmd)
            self.cmdSocket.send(cmd)

client = fileClient()
client.run()
