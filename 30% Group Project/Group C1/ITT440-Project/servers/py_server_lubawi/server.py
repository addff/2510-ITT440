import socket
import threading
import mysql.connector
import time
from datetime import datetime
import pytz

PORT = 5004
DB_CONFIG = {
    'host': 'mysql_db',
    'user': 'root',
    'password': 'root123',
    'database': 'itt440_db'
}

# Set Kuala Lumpur timezone
kuala_lumpur = pytz.timezone('Asia/Kuala_Lumpur')

def update_database():
    try:
        conn = mysql.connector.connect(**DB_CONFIG)
        cursor = conn.cursor()
        query = "UPDATE user_points SET points = points + 1, datetime_stamp = NOW() WHERE user = 'lubawi'"
        cursor.execute(query)
        conn.commit()
        cursor.close()
        conn.close()
        
        # Get current KL time
        current_time = datetime.now(kuala_lumpur)
        print(f"[{current_time.strftime('%Y-%m-%d %H:%M:%S')}] Database updated for lubawi")
    except Exception as e:
        print(f"Database update error: {e}")

def handle_client(client_socket):
    try:
        request = client_socket.recv(1024).decode()
        if "GET_POINTS" in request:
            conn = mysql.connector.connect(**DB_CONFIG)
            cursor = conn.cursor()
            cursor.execute("SELECT points FROM user_points WHERE user='lubawi'")
            result = cursor.fetchone()
            cursor.close()
            conn.close()
            
            response = f"Lubawi Points: {result[0]}"
            client_socket.send(response.encode())
        else:
            response = "Send GET_POINTS to get points"
            client_socket.send(response.encode())
    except Exception as e:
        print(f"Client handling error: {e}")
        try:
            error_response = f"Error: {str(e)}"
            client_socket.send(error_response.encode())
        except:
            pass
    finally:
        client_socket.close()

def start_server():
    # Wait for database to be ready
    print("Waiting for database connection...")
    time.sleep(10)
    
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(('0.0.0.0', PORT))
    server.listen(5)
    print(f"Python Server (Lubawi) listening on port {PORT}")
    
    # Start database update thread
    def update_thread():
        while True:
            update_database()
            time.sleep(30)
    
    threading.Thread(target=update_thread, daemon=True).start()
    
    # Handle clients
    while True:
        try:
            client_socket, addr = server.accept()
            print(f"Connection from {addr}")
            client_thread = threading.Thread(target=handle_client, args=(client_socket,))
            client_thread.daemon = True
            client_thread.start()
        except Exception as e:
            print(f"Server accept error: {e}")

if __name__ == "__main__":
    start_server()