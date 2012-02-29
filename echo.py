#!/usr/bin/env python 

""" 
A simple echo server 
""" 

import socket 
import sys

host = '' 
port = 1400
backlog = 5 
size = 1
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.bind((host, port)) 
s.listen(backlog) 
while 1: 
    client, address = s.accept() 
    print 'Connection:', address
    while 1:
        data = client.recv(size)
        if data:
            sys.stdout.write(data)
            client.send(data)
        else:
            break
    client.close()
    print 'Closed'
