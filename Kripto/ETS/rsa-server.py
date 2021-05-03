import socket
from time import sleep

from Crypto.Util.number import *
from Crypto import Random
import Crypto
import libnum
import sys

def server_program():
    # get the hostname
    host = socket.gethostname()
    port = 5000  # initiate port no above 1024

    server_socket = socket.socket()  # get instance
    # look closely. The bind() function takes tuple as argument
    server_socket.bind((host, port))  # bind host address and port together

    # configure how many client the server can listen simultaneously
    server_socket.listen(2)
    conn, address = server_socket.accept()  # accept new connection
    print("Connection from: " + str(address))
    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        c=''
        c = conn.recv(1024).decode()
        res=''
        res = conn.recv(1024).decode()
        if not c:
            # if data is not received break
            break
        if not res:
            # if data is not received break
            break        
        print("=========================================================")
        print("Chiper: " + str(c) + "\n")
        print("Dechiper: " + long_to_bytes(res).decode())

    conn.close()  # close the connection


if __name__ == '__main__':
    server_program()
