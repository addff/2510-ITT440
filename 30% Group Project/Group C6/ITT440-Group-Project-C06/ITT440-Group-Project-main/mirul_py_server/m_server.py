import socket
import threading
import time
from datetime import datetime
import mysql.connector

# Database connection
def connect_to_db():
    while True:
        try:
            print("Connecting to MySQL...")
            conn = mysql.connector.connect(
                host="mysql", 
                user="root",
                password="rootpassword",
                database="pointsdb"
            )
            print("MySQL Connected!")
            return conn
        except mysql.connector.Error as err:
            print(f"Database not ready yet... ({err})")
            time.sleep(2)  # Wait 2 seconds before trying again

db = connect_to_db()
cursor = db.cursor()

# CHANGED: Unique user for this specific server
USER = "mirul_py_user" 

# Socket setup
HOST = "0.0.0.0"
# CHANGED: Unique port (Requirements state port > 1024)
PORT = 5005 

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

def update_points():
    while True:
        # Requirement: Update every 30 seconds [cite: 8, 41]
        now = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        cursor.execute(
            "UPDATE points_table SET points = points + 1, datetime_stamp = %s WHERE user = %s",
            (now, USER)
        )
        db.commit()
        time.sleep(30)

# Start updater thread
threading.Thread(target=update_points, daemon=True).start()

print(f"Mirul Python server running on port {PORT}...")

while True:
    conn, addr = server_socket.accept()
    # Requirement: Server must access DB before passing to client [cite: 9, 50]
    cursor.execute("SELECT points, datetime_stamp FROM points_table WHERE user = %s", (USER,))
    result = cursor.fetchone()
    
    if result:
        points, ts = result
        response = f"User: {USER}, Points: {points}, Last update: {ts}"
    else:
        response = f"User {USER} not found in database."
        
    conn.send(response.encode())
    conn.close()
