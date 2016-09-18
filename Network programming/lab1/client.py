#!/usr/bin/python
import socket
import sys

if len(sys.argv) != 3:
    raise Exception("Zla liczba argumentow")
ip = str(sys.argv[1])
port = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.connect((ip, port))
except socket.error as e:
    print "Nie mozna polaczyc sie z serwerem: " + str(e[1])
    raise SystemExit

inp = raw_input("Podaj wiadomosc do wyslania: ")
msg = str(inp)
print "Client: " + str(msg)

try:
    s.send(msg)
except socket.error as e:
    print "Nie udalo sie wyslac wiadomosci: " + str(e[1])

try:
    data = s.recv(1024)
    print "Server: " + str(data)
except socket.error as e:
    print "Nie odebrano odpowiedzi od serwera: " + str(e[1])

s.close()
