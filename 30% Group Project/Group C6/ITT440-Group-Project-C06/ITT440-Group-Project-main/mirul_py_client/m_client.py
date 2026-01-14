import socket

# Server details - MUST match the service name in docker-compose.yml
HOST = "mirul_py_server" 
# Port must match the server's internal port
PORT = 5005

try:
    # Connect to server
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        # Requirement: Client asks for the latest point from server
        data = s.recv(1024)  # receive response from server
        print("Server response:", data.decode())
except ConnectionRefusedError:
    print("Error: Could not connect to mirul_py_server. Is it running?")
except Exception as e:
    print(f"An error occurred: {e}")
