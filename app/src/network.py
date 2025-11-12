import socket

s = socket.socket()
s.bind(('0.0.0.0', 8090))
s.listen(0)

#wait for an incomming connection
client, address = s.accept()

while True:
    content = client.recv(32)

    if (len(content) == 0):
        break
    else:
        print(content)

client.close()
print("Closed connection")