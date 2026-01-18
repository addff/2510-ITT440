import socket
import time
import os

# Server configuration from environment variables
SERVER_HOST = os.getenv('SERVER_HOST', 'server3')
SERVER_PORT = int(os.getenv('SERVER_PORT', 5003))

class SocketClient:
    def __init__(self, host=SERVER_HOST, port=SERVER_PORT):
        self.host = host
        self.port = port
        self.socket = None
        
    def connect(self):
        """Connect to the server"""
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.host, self.port))
            print(f"Connected to server {self.host}:{self.port}")
            return True
        except Exception as e:
            print(f"Connection error: {e}")
            return False
    
    def request_data(self):
        """Request latest points and timestamp from server"""
        try:
            # Send request
            self.socket.send("get_data".encode('utf-8'))
            
            # Receive response
            response = self.socket.recv(1024).decode('utf-8')
            print(f"Response: {response}")
            
            return response
        except Exception as e:
            print(f"Request error: {e}")
            return None
    
    def close(self):
        """Close connection"""
        if self.socket:
            try:
                self.socket.send("quit".encode('utf-8'))
            except:
                pass
            self.socket.close()
            print("Connection closed")
    
    def run(self):
        """Run the client - request data every 10 seconds"""
        # Wait for server to be ready
        time.sleep(10)
        
        while True:
            if not self.socket or self.socket.fileno() == -1:
                print("Attempting to connect to server...")
                if not self.connect():
                    print("Failed to connect. Retrying in 5 seconds...")
                    time.sleep(5)
                    continue
            
            try:
                print(f"\n[{time.strftime('%Y-%m-%d %H:%M:%S')}] Requesting data from server...")
                self.request_data()
                
                # Wait 10 seconds before next request
                time.sleep(10)
                
            except KeyboardInterrupt:
                print("\nShutting down client...")
                break
            except Exception as e:
                print(f"Error: {e}")
                print("Reconnecting...")
                time.sleep(5)
                
        self.close()

if __name__ == "__main__":
    client = SocketClient()
    client.run()
