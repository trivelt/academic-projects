#!/usr/bin/python

import socket
import sys
import threading
from struct import *

class TCPportScanner(threading.Thread):
    def __init__(self, port):
        threading.Thread.__init__(self)
        self.port = port

    def run(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            s.connect((address, self.port))
            print "Port " + str(self.port) + " is open"
        except Exception:
            pass

class ICMPReceiver(threading.Thread):
    def __init__(self, UDPport):
        threading.Thread.__init__(self)
        self.udpPort = UDPport
    def run(self):
        s = socket.socket(socket.AF_INET,socket.SOCK_RAW,socket.IPPROTO_ICMP)
        s.setsockopt(socket.SOL_IP, socket.IP_HDRINCL, 1)
        s.settimeout(1)
        n = 100
        nodata = True
        try:
            while n:
                data, addr = s.recvfrom(4096)
                if data:
                    nodata = False
                    s.close()
                    return
                n -= 1
        except Exception:
            s.close()
            if nodata:
                print "\nPort " + str(self.udpPort) + " opened"


class UDPRemotePortScannerUsingICMP():
    def __init__(self, port):
        self.port = port

    def start(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.settimeout(0.1)
        try:
            icr = ICMPReceiver(self.port)
            icr.start()
            s.sendto("ping", (address, self.port))
            rcv = s.recvfrom(512)
        except Exception as e:
            pass
            #print "Port " + str(self.port) + " is open\t"


class UDPLocalPortScannerByOpening:
    def __init__(self, port):
        self.port = port

    def start(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        try:
            s.bind(("localhost", self.port))
            s.close()
        except Exception as e:
            print "Port " + str(self.port) + " is open\t"


class UDPLocalPortScannerBySending:
    def __init__(self, port):
        self.port = port

    def start(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        try:
            s.sendto("ping", ("localhost", self.port))
            s.settimeout(0.01)
            s.recvfrom(1024)
            s.close()
            print "Port " + str(self.port) + " is open\t"
        except Exception as e:
            pass

if len(sys.argv) != 5:
    raise Exception("Zla liczba argumentow.\n "
    "Prawidlowe wywolanie to ./program <adres> <protokol> <port1> <port2>")

address = str(sys.argv[1])
protocol = str(sys.argv[2])
port1 = int(sys.argv[3])
port2 = int(sys.argv[4])
listOfPorts = range(port1,port2+1)

if protocol == "tcp":
    print("TCP ports scanning:")
    for port in listOfPorts:
        scn = TCPportScanner(port)
        scn.start()

elif protocol == "udp":
    print("UDP ports scanning:")
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    for port in listOfPorts:
        if address == "localhost":
            scn = UDPLocalPortScannerByOpening(port)
            scn.start()
        else:
            scn = UDPRemotePortScannerUsingICMP(port)
            scn.start()

print "Ports in range " + str(port1) + "-" + str(port2) + " were scanned"

