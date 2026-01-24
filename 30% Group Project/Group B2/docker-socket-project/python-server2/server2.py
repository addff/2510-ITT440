import socket
import time
import threading
import mysql.connector
from datetime import datetime

# Database configuration
DB_CONFIG = {
    'host': 'database',
    'user': 'root',
    'password': 'rootpassword',
    'database': 'socket_db'
}

PORT = 8085
USERNAME = "python_user2"

def update_database_points():
    """Update points for python_user2 every 30 seconds"""
    while True:
        try:
            conn = mysql.connector.connect(**DB_CONFIG)
            cursor = conn.cursor()
            
            query = """
            UPDATE user_points 
            SET points = points + 1, datetime_stamp = NOW() 
            WHERE user = %s
            """
            
            cursor.execute(query, (USERNAME,))
            conn.commit()
            print(f"Updated points for {USERNAME} at {datetime.now()}")
            
            cursor.close()
            conn.close()
        except Exception as e:
            print(f"Database update error: {e}")
        
        time.sleep(30)

def get_latest_points():
    """Get latest points from database"""
    try:
        conn = mysql.connector.connect(**DB_CONFIG)
        cursor = conn.cursor()
        
        query = """
        SELECT points, datetime_stamp 
        FROM user_points 
        WHERE user = %s
        """
        
        cursor.execute(query, (USERNAME,))
        result = cursor.fetchone()
        
        cursor.close()
        conn.close()
        
        if result:
            return f"User: {USERNAME}, Points: {result[0]}, Last Updated: {result[1]}"
        else:
            return f"No data found for {USERNAME}"
            
    except Exception as e:
        return f"Error: {str(e)}"

def handle_client(client_socket):
    """Handle client requests"""
    try:
        request = client_socket.recv(1024).decode('utf-8')
        
        if "GET_POINTS" in request:
            response = get_latest_points()
            client_socket.send(response.encode('utf-8'))
        else:
            client_socket.send(b"Invalid request")
            
    except Exception as e:
        print(f"Client handling error: {e}")
    finally:
        client_socket.close()

def start_server():
    """Start the socket server"""
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(('0.0.0.0', PORT))
    server.listen(5)
    
    print(f"Python Server listening on port {PORT}")
    
    # Start periodic update thread
    update_thread = threading.Thread(target=update_database_points, daemon=True)
    update_thread.start()
    
    # Accept client connections
    while True:
        client_socket, addr = server.accept()
        print(f"Connection from {addr}")
        
        client_thread = threading.Thread(target=handle_client, args=(client_socket,))
        client_thread.start()

if __name__ == "__main__":
    start_server()
