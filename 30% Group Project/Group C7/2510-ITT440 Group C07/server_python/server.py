import socket
import mysql.connector
import threading
import time

DB_CONFIG = {
    "host": "mysql-db",
    "user": "root",
    "password": "adminpass",
    "database": "socket_db"
}


def update_loop():
    target_user = 'PyUser1' 
    
    while True:
        try:
            db = mysql.connector.connect(**DB_CONFIG)
            cursor = db.cursor()
            
            
            query = f"INSERT INTO scores (user, points) VALUES ('{target_user}', 1) " \
                    f"ON DUPLICATE KEY UPDATE points = points + 1, datetime_stamp = NOW()"
            
            cursor.execute(query)
            db.commit()
            db.close()
            print(f"Python Server 1: Points increased for {target_user}")
        except Exception as e:
            print(f"DB Update Error: {e}")
        time.sleep(30)

threading.Thread(target=update_loop, daemon=True).start()

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('0.0.0.0', 5001))
server.listen(5)
print("Python Server 1 listening on Port 5001 (User: PyUser1)...")

while True:
    conn, addr = server.accept()
    data = conn.recv(1024).decode()
    if data == "GET_SCORE":
        try:
            db = mysql.connector.connect(**DB_CONFIG)
            cursor = db.cursor()
            
          
            cursor.execute("SELECT user, points, datetime_stamp FROM scores WHERE user = 'PyUser1'")
            
            row = cursor.fetchone()
            
            if row:
                final_response = f"User: {row[0]} | Points: {row[1]} | Last Update: {row[2]}"
            else:
                final_response = "Data not found for PyUser1"
            
            conn.send(final_response.encode())
            db.close()
        except Exception as e:
            print(f"Socket Fetch Error: {e}")
            conn.send(b"Server Error")
            
    conn.close()
