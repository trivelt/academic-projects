#!/usr/bin/python
import socket
import sys
import datetime
import struct

def computeTimestamp():
    diff = datetime.datetime.utcnow() - datetime.datetime(1900, 1, 1, 0, 0)
    timestamp = diff.days*24*60*60+diff.seconds
    t = struct.pack("!I", timestamp)
    print "Computed timestamp=" + str(timestamp)
    return t

def computeDaytime():
    now = datetime.datetime.utcnow()
    strNow = now.strftime("%a %b %d %H:%M:%S %Y")
    print("Computed daytime=" + strNow)
    return strNow

if len(sys.argv) < 3:
    raise Exception("Zla liczba argumentow")
mode = str(sys.argv[1])
protocol = str(sys.argv[2])

if len(sys.argv) is 4:
	port = int(sys.argv[3])
else:
	if mode == "time":
		port = 37
	elif mode == "daytime":
		port = 13

if protocol == "tcp":
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
elif protocol == "udp":
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("localhost", port))
print("Service " + mode + " started on port " + str(port))

if protocol == "tcp":
    s.listen(5)
    while 1:
        (client, address) = s.accept()
        print("Client "  + str(address[0]) + ":" + str(address[1]) + " connected")
        if mode == "time":
            client.send(computeTimestamp())
        elif mode == "daytime":
            client.send(computeDaytime())
        client.close()
elif protocol == "udp":
    while 1:
        (data, address) = s.recvfrom(1024)
        if data:
            print("Client "  + str(address[0]) + ":" + str(address[1]) + " connected")
            if mode == "time":
                s.sendto(computeTimestamp(), address)
            elif mode == "daytime":
                s.sendto(computeDaytime(), address)
