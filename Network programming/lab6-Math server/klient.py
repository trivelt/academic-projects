#!/usr/bin/python
import socket
import sys

if len(sys.argv) != 4:
    raise Exception("Zla liczba argumentow")
ip = str(sys.argv[1])
port = int(sys.argv[2])
protocol = str(sys.argv[3])

if protocol != "tcp" and protocol != "udp":
    print "Nieprawidlowy argument. Protokol: udp/tcp"
    sys.exit()

if protocol == "tcp":
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
else:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.connect((ip, port))
print("Wpisuj dzialania matematyczne do obliczenia. Aby zakonczysz wpisz /exit")

while True:
    inp = raw_input("$: ")
    msg = str(inp)
    if msg == "/exit":
        s.close()
        sys.exit()
    s.send(msg)
    rsp = s.recv(4098)
    print("$$: " + str(rsp))
