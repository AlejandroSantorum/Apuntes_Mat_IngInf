import socket

serverName = '192.168.1.39'
serverPort = 9999
sentence = b"Los que van a morir, te saludan!!!!"

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((serverName,serverPort))
	
client_socket.send(sentence)
modifiedSentence = client_socket.recv(1024)
print('Desde el servidor:', modifiedSentence)

client_socket.close()