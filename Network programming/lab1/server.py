#!/usr/bin/python
import socket
import sys

if len(sys.argv) is not 3:
    raise Exception("Zla liczba argumentow")
port = int(sys.argv[1])
response = str(sys.argv[2])

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("localhost", port))
    s.listen(5)
except socket.error as e:
    print "Server error: " + str(e[1])
    raise SystemExit

while 1:
    try:
        (client, address) = s.accept()
        clientInfo = "(ip="+str(address[0])+" port="+str(address[1])+")"
        data = client.recv(1024)
        print "Client" + clientInfo+":" + str(data)
        client.send("Wiadomosc odebrana\n")
        client.send(response+":"+data)
        client.close()
    except(KeyboardInterrupt, SystemExit):
	s.close()
	print "Server closed"
	sys.exit(0)