#!/usr/bin/python
import socket
import sys
import threading

class MathServer():
    def __init__(self):
        pass

    def getResponse(self, data):
        self.data = data
        self.data = self.data.rstrip()
        print "Recveived data=" + str(data)
        try:
            #resp = evalTools.eval_expr(str(data))
            resp = eval(str(data))
            resp = str(resp)
        except Exception:
            resp = "Wrong expression"
        print "Response=" + resp
        return resp


class TcpClient(threading.Thread):
    def __init__(self, sock):
        threading.Thread.__init__(self)
        self.socket = sock

    def run(self):
        print "TcpClient run"
        mathServer = MathServer()
        while True:
            data = self.socket.recv(4096)
            response = mathServer.getResponse(data)
            try:
                self.socket.send(response)
            except Exception:
                self.socket.close()
                break

class UdpClient(threading.Thread):
    def __init__(self, firstData, serverSocket, clientAddress):
        threading.Thread.__init__(self)
        self.data = firstData
        self.serverSocket = serverSocket
        self.client = clientAddress

    def run(self):
        print "UdpClient run"
        mathServer = MathServer()
        response = mathServer.getResponse(self.data)

        self.serverSocket.sendto(response, self.client)


class TcpMathServer(threading.Thread):
    def __init__(self, port):
        threading.Thread.__init__(self)
        self.tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.tcpSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.tcpSocket.bind(("localhost", port))

    def run(self):
        print "Tcp server run"
        self.tcpSocket.listen(5)
        while True:
            (client, address) = self.tcpSocket.accept()
            mathServer = TcpClient(client)
            mathServer.start()


class UdpMathServer(threading.Thread):
    def __init__(self, port):
        threading.Thread.__init__(self)
        self.udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.udpSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.udpSocket.bind(("localhost", port))

    def run(self):
        print "UdpServer run"
        while True:
            (data, client) = self.udpSocket.recvfrom(4096)
            mathServer = UdpClient(data, self.udpSocket, client)
            mathServer.start()



if len(sys.argv) != 2:
    raise Exception("Zla liczba argumentow")
port = int(sys.argv[1])


tcpServer = TcpMathServer(port)
udpServer = UdpMathServer(port)
tcpServer.start()
udpServer.start()
