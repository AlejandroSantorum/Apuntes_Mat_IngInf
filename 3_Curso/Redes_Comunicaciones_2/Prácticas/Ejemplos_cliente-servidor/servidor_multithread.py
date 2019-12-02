import socket
import threading

bind_ip = '0.0.0.0'
bind_port = 9999

# Creamos el socket...
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Lo asociamos a la IP y puerto correctos...
server.bind((bind_ip, bind_port))
# Y decimos al SO que atienda por nosotros hasta 5 conexiones
server.listen(5)

print 'Escuchando en {}:{}'.format(bind_ip, bind_port)


def handle_client_connection(client_socket):
    request = client_socket.recv(1024)
    client_socket.send('ACK!')
    client_socket.close()

while True:
    client_sock, address = server.accept()
    print 'Aceptada conexion de {}:{}'.format(address[0], address[1])
    client_handler = threading.Thread(
        target=handle_client_connection,
        args=(client_sock,)  
    )
    client_handler.start()
