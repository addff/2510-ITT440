import socket

# Server details
HOST = "py-server" 
PORT = 5002

# Connect to server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    data = s.recv(1024)  # receive response from server
    print("Server response:", data.decode())
