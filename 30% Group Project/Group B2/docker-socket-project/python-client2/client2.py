import socket
import time

SERVER_HOST = "python-server2"
SERVER_PORT = 8085

def connect_to_server():
    """Connect to Python socket server and request points"""
    try:
        # Create socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        # Connect to server
        client_socket.connect((SERVER_HOST, SERVER_PORT))
        print(f"Connected to Python Server at {SERVER_HOST}:{SERVER_PORT}")
        
        # Send request
        request = "GET_POINTS"
        client_socket.send(request.encode('utf-8'))
        print(f"Request sent: {request}")
        
        # Receive response
        response = client_socket.recv(1024).decode('utf-8')
        print(f"Server Response: {response}")
        
        # Close connection
        client_socket.close()
        
    except ConnectionRefusedError:
        print("Connection refused. Make sure the server is running.")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    # Wait a moment for server to start
    time.sleep(15)
    connect_to_server()
