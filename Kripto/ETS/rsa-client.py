import socket
from time import sleep

from Crypto.Util.number import *
from Crypto import Random
import Crypto
import libnum
import sys


def client_program():
    host = socket.gethostname()  # as both code is running on same pc
    port = 5000  # socket server port number

    client_socket = socket.socket()  # instantiate
    client_socket.connect((host, port))  # connect to the server
    
    i = 1
    print("=========================================================")
    print("#%d" % (i))
    print("Masukkan pesan:")
    message = input("-> Pesan: ")  # take input
    print("\nMasukkan panjang bit: ( 60/80/128/256/512/1024 ) ")
    bits = int(input("-> Bit: "))  # again take input
    print("\n")

    # RSA ALGORITHM

    p = Crypto.Util.number.getPrime(bits, randfunc=Crypto.Random.get_random_bytes)
    q = Crypto.Util.number.getPrime(bits, randfunc=Crypto.Random.get_random_bytes)

    n = p*q
    PHI=(p-1)*(q-1)

    e=65537
    d=libnum.invmod(e,PHI)

    m = bytes_to_long(message.encode('utf-8'))

    c=pow(m,e, n)
    res=pow(c,d ,n)    

    while message.lower().strip() != 'bye':
        client_socket.send(str(c).encode())  # send message
        sleep(1)
        client_socket.send(str(res).encode())  # send message
        sleep(1)

        i+=1
        print("=========================================================")
        print("#%d" % (i))
        print("Masukkan pesan:")
        message = input("-> Pesan: ")  # take input
        print("\nMasukkan panjang bit: ( 60/80/128/256/512/1024 ) ")
        bits = int(input("-> Bit: "))  # again take input

        # RSA ALGORITHM
        p = Crypto.Util.number.getPrime(bits, randfunc=Crypto.Random.get_random_bytes)
        q = Crypto.Util.number.getPrime(bits, randfunc=Crypto.Random.get_random_bytes)

        n = p*q
        PHI=(p-1)*(q-1)

        e=65537
        d=libnum.invmod(e,PHI)

        m = bytes_to_long(message.encode('utf-8'))

        c=pow(m,e, n)
        res=pow(c,d ,n) 

    client_socket.close()  # close the connection


if __name__ == '__main__':
    client_program()
