import socket
import time
import os

# Get server details from docker-compose environment variables
SERVER_HOST = os.getenv('SERVER_HOST', 'server-python1')
SERVER_PORT = int(os.getenv('SERVER_PORT', 4001))

def request_data():
    print(f"AyuPY_Client... connecting to {SERVER_HOST}:{SERVER_PORT}")
    
    while True:
        try:
            # Create a TCP socket
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.connect((SERVER_HOST, SERVER_PORT))
            
            # Send request to server
            client.send("GET_POINTS".encode())
            
            # Receive and print response
            response = client.recv(1024).decode()
            print(f"[{time.ctime()}] Received from Server: {response}")
            
            client.close()
        except Exception as e:
            print(f"Connection failed: {e}. Retrying in 5 seconds")
            time.sleep(5)
            continue
        
        # Wait 10 seconds before asking again
        time.sleep(10)

if __name__ == "__main__":
    request_data()
