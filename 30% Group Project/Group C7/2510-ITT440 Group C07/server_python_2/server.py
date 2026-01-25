import socket
import mysql.connector
import threading
import time

db_config = {
    'host': 'mysql-db',
    'user': 'root',
    'password': 'adminpass',
    'database': 'socket_db'
}


def update_points():
    
    target_user = "PyUser2"
    
    while True:
        try:
            conn = mysql.connector.connect(**db_config)
            cursor = conn.cursor()
            
      
            cursor.execute("""
                INSERT INTO scores (user, points) VALUES (%s, 1)
                ON DUPLICATE KEY UPDATE points = points + 1, datetime_stamp = NOW()
            """, (target_user,))
            
            conn.commit()
            conn.close()
            print(f"Python Server 2: Points increased for {target_user}")
        except Exception as e:
            print(f"DB Error in background loop: {e}")
        time.sleep(30)


threading.Thread(target=update_points, daemon=True).start()


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('0.0.0.0', 5003)) 
server.listen(5)
print("Python Server 2 listening on Port 5003 (User: PyUser2)...")

while True:
    client, addr = server.accept()
    try:
        data = client.recv(1024).decode()
        if data == "GET_SCORE":
            conn = mysql.connector.connect(**db_config)
            cursor = conn.cursor()
            
          
            cursor.execute("SELECT user, points, datetime_stamp FROM scores WHERE user = %s", ("PyUser2",))
            row = cursor.fetchone()
            
            if row:
                response = f"User: {row[0]} | Points: {row[1]} | Last Update: {row[2]}"
            else:
                response = "No PyUser2 data found in database."
                
            client.send(response.encode())
            conn.close()
    except Exception as e:
        print(f"Error handling client: {e}")
    finally:
        client.close()
