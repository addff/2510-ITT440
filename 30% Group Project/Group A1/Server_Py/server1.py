import socket
import mysql.connector
import threading
import time
import os
from datetime import datetime
from http.server import HTTPServer, BaseHTTPRequestHandler
import json

# Database configuration from environment variables
DB_CONFIG = {
    'host': os.getenv('DB_HOST', 'database'),
    'user': os.getenv('DB_USER', 'dbuser'),
    'password': os.getenv('DB_PASSWORD', 'dbpassword'),
    'database': os.getenv('DB_NAME', 'network_project')
}

SERVER_PORT = int(os.getenv('SERVER_PORT', 5001))
USER_NAME = os.getenv('USER_NAME', 'Afif')

# Global control variable
update_paused = False

class SocketServer:
    def __init__(self, host='0.0.0.0', port=SERVER_PORT):
        self.host = host
        self.port = port
        self.socket = None
        self.running = True
        
    def connect_to_database(self):
        """Establish connection to MySQL database"""
        try:
            conn = mysql.connector.connect(**DB_CONFIG)
            return conn
        except mysql.connector.Error as err:
            print(f"Database connection error: {err}")
            return None
    
    def update_user_points(self):
        """Automatically update user points every 30 seconds"""
        global update_paused
        while self.running:
            try:
                # Check if updates are paused
                if not update_paused:
                    conn = self.connect_to_database()
                    if conn:
                        cursor = conn.cursor()
                        
                        # Increase points by 10 for this user
                        query = """
                            UPDATE user_tracking 
                            SET points = points + 10, 
                                datetime_stamp = NOW() 
                            WHERE user = %s
                        """
                        cursor.execute(query, (USER_NAME,))
                        conn.commit()
                        
                        # Fetch updated values
                        cursor.execute(
                            "SELECT user, points, datetime_stamp FROM user_tracking WHERE user = %s", 
                            (USER_NAME,)
                        )
                        result = cursor.fetchone()
                        
                        if result:
                            print(f"[{datetime.now()}] Updated {result[0]}: Points={result[1]}, Time={result[2]}")
                        
                        cursor.close()
                        conn.close()
                else:
                    print(f"[{datetime.now()}] Updates paused for {USER_NAME}")
                    
            except Exception as e:
                print(f"Error updating points: {e}")
            
            # Wait 30 seconds before next update
            time.sleep(30)
    
    def get_user_data(self):
        """Retrieve current user data from database"""
        try:
            conn = self.connect_to_database()
            if conn:
                cursor = conn.cursor()
                cursor.execute(
                    "SELECT user, points, datetime_stamp FROM user_tracking WHERE user = %s", 
                    (USER_NAME,)
                )
                result = cursor.fetchone()
                cursor.close()
                conn.close()
                
                if result:
                    return f"User: {result[0]} | Points: {result[1]} | Last Update: {result[2]}"
                else:
                    return "No data found"
        except Exception as e:
            return f"Error: {e}"
    
    def handle_client(self, client_socket, address):
        """Handle client requests"""
        print(f"Client connected from {address}")
        
        try:
            while True:
                # Receive request from client
                data = client_socket.recv(1024).decode('utf-8')
                
                if not data or data.lower() == 'quit':
                    print(f"Client {address} disconnected")
                    break
                
                print(f"Received request from {address}: {data}")
                
                # Get data from database and send to client
                if data.lower() == 'get_data':
                    response = self.get_user_data()
                    client_socket.send(response.encode('utf-8'))
                else:
                    client_socket.send("Invalid command. Use 'get_data' or 'quit'".encode('utf-8'))
                    
        except Exception as e:
            print(f"Error handling client {address}: {e}")
        finally:
            client_socket.close()
    
    def start(self):
        """Start the socket server"""
        # Create socket
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        try:
            self.socket.bind((self.host, self.port))
            self.socket.listen(5)
            print(f"Server started on {self.host}:{self.port}")
            print(f"Managing user: {USER_NAME}")
            
            # Start database update thread
            update_thread = threading.Thread(target=self.update_user_points, daemon=True)
            update_thread.start()
            
            # Accept client connections
            while self.running:
                try:
                    client_socket, address = self.socket.accept()
                    client_thread = threading.Thread(
                        target=self.handle_client, 
                        args=(client_socket, address),
                        daemon=True
                    )
                    client_thread.start()
                except KeyboardInterrupt:
                    print("\nShutting down server...")
                    self.running = False
                    break
                    
        except Exception as e:
            print(f"Server error: {e}")
        finally:
            if self.socket:
                self.socket.close()

if __name__ == "__main__":
    # Start control HTTP server in separate thread
    class ControlHandler(BaseHTTPRequestHandler):
        def do_POST(self):
            global update_paused
            if self.path == '/toggle':
                update_paused = not update_paused
                status = "paused" if update_paused else "active"
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps({'status': status}).encode())
                print(f"[Control] Updates {status} for {USER_NAME}")
            elif self.path == '/status':
                status = "paused" if update_paused else "active"
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps({'status': status}).encode())
            else:
                self.send_response(404)
                self.end_headers()
        
        def log_message(self, format, *args):
            pass  # Suppress HTTP logs
    
    def run_control_server():
        control_port = SERVER_PORT + 1000  # 6001, 6002, 6003
        control_server = HTTPServer(('0.0.0.0', control_port), ControlHandler)
        print(f"Control server started on port {control_port}")
        control_server.serve_forever()
    
    control_thread = threading.Thread(target=run_control_server, daemon=True)
    control_thread.start()
    
    # Wait for database to be ready
    time.sleep(5)
    
    server = SocketServer()
    server.start()
