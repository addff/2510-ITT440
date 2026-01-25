import socket

SERVER_HOST = 'py-server-2-container'
SERVER_PORT = 5003

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    client.connect((SERVER_HOST, SERVER_PORT))
    client.send(b"GET_SCORE")
    response = client.recv(4096).decode()
    print(f"--- Python Server 2 Response ---\n{response}")
except Exception as e:
    print(f"Connection Error: {e}")
finally:
    client.close()
