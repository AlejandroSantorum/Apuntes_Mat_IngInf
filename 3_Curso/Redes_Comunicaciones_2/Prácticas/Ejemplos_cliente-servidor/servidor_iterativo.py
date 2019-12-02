# -*- coding: utf-8 -*-
import socket, threading, datetime

bind_ip = '0.0.0.0'
bind_port = 9999

# Creamos el socket...
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Lo asociamos a la IP y puerto correctos...
server.bind((bind_ip, bind_port))
# Y decimos al SO que atienda por nosotros hasta 5 conexiones
server.listen(5)

print 'Escuchando en {}:{}'.format(bind_ip, bind_port) 

while True:
    # Aceptamos una conexión (bloqueante)
    client_socket, address = server.accept()
    print 'Conexion entrante de {}:{}'.format(address[0], address[1])

    request = client_socket.recv(1024)
    client_socket.send('ACK!')
    # Ojo! Podemos entrar en estado TIME_WAIT
    client_socket.close()
