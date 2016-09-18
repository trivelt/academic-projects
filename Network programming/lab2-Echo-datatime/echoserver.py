#!/usr/bin/python
import socket
import sys

if len(sys.argv) < 2:
    raise Exception("Zla liczba argumentow")
protocol = str(sys.argv[1])

if len(sys.argv) == 3:
    port = int(sys.argv[2])
else:
    port = 7

if protocol == "tcp":
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
elif protocol == "udp":
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("localhost", port))
print("Listining on port " + str(port) + " started")

if protocol == "tcp":
    s.listen(5)
    while 1:
        (client, address) = s.accept()
        data = client.recv(1024)
        print "Message received from " + str(address[0]) + ":" + str(address[1]) + ": " + str(data)
        client.send(data)
        print "Sent: " + str(data)
        client.close()

elif protocol == "udp":
    while 1:
        (data, address) = s.recvfrom(1024)
        if data:
            print "Message received from " + str(address[0]) + ":" + str(address[1]) + ": " + str(data)
            s.sendto(data, address)
            print "Sent: " + str(data)
