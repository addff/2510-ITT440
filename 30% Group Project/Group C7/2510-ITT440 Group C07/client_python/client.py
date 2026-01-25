import socket
import time

SERVER_HOST = 'py-server-container'
SERVER_PORT = 5001

def get_score_from_server():
    try:
        
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((SERVER_HOST, SERVER_PORT))
        
        client_socket.send("GET_SCORE".encode())
        
        response = client_socket.recv(1024).decode()
        print(f"Server Response: {response}")
        
        client_socket.close()
    except Exception as e:
        print(f"Connection failed: {e}")

if __name__ == "__main__":
    print("Client started. Requesting score...")
    get_score_from_server()
