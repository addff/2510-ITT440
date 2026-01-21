import socket

SERVER_IP = 'host.docker.internal' 
SERVER_PORT = 5003

def run_client():
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((SERVER_IP, SERVER_PORT))
        
        client_socket.send("get_points".encode())

        response = client_socket.recv(1024).decode()
        
        print("-" * 40)
        print(f"Python Server Response | {response}")
        print("-" * 40)
        
        client_socket.close()
        
    except Exception as e:
        print(f"Connection Error: {e}")

if __name__ == "__main__":
    run_client()