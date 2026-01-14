import socket
import threading
import time
from datetime import datetime
import mysql.connector

# Database connection
db = mysql.connector.connect(
    host="mysql", 
    user="root",
    password="rootpassword",
    database="pointsdb"
)
cursor = db.cursor()

USER = "python_user"

# Socket setup
HOST = "py-server"
PORT = 5002

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

def update_points():
    while True:
        now = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        cursor.execute(
            "UPDATE points_table SET points = points + 1, datetime_stamp = %s WHERE user = %s",
            (now, USER)
        )
        db.commit()
        time.sleep(30)

# Start updater thread
threading.Thread(target=update_points, daemon=True).start()

print("Python server running...")

while True:
    conn, addr = server_socket.accept()
    cursor.execute("SELECT points, datetime_stamp FROM points_table WHERE user = %s", (USER,))
    points, ts = cursor.fetchone()
    response = f"Points: {points}, Last update: {ts}"
    conn.send(response.encode())
    conn.close()
