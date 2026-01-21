import socket
import mysql.connector
import threading
import time

TARGET_USER = "Amir" 

db_config = {
    'host': 'host.docker.internal',
    'user': 'root',
    'password': 'qwerty',
    'database': 'itt440_db',
    'port': 3306
}

def ensure_user_exists():
    try:
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor()
        
        cursor.execute("SELECT user FROM student_table WHERE user = %s", (TARGET_USER,))
        if cursor.fetchone() is None:
            sql = "INSERT INTO student_table (user, points, datetime_stamp) VALUES (%s, 0, NOW())"
            cursor.execute(sql, (TARGET_USER,))
            conn.commit()
            print(f"Server Startup: User '{TARGET_USER}' created in database.")
        else:
            print(f"Server Startup: User '{TARGET_USER}' already exists. Skipping insertion.")
            
        cursor.close()
        conn.close()
    except Exception as e:
        print(f"Startup Database Error: {e}")

def auto_increment_points():
    while True:
        try:
            conn = mysql.connector.connect(**db_config)
            cursor = conn.cursor()
            sql = "UPDATE student_table SET points = points + 1, datetime_stamp = NOW() WHERE user = %s"
            cursor.execute(sql, (TARGET_USER,))
            conn.commit()
            
            if cursor.rowcount > 0:
                print(f"Tick: 1 point added to {TARGET_USER}")
            
            cursor.close()
            conn.close()
        except Exception as e:
            print(f"Auto-update error: {e}")
        
        time.sleep(30)

def start_server():

    ensure_user_exists()

    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.bind(('0.0.0.0', 5001))
    srv.listen(5)
    print(f"Python Server: Monitoring {TARGET_USER} on port 5001")

    threading.Thread(target=auto_increment_points, daemon=True).start()

    while True:
        client_conn, addr = srv.accept()
        client_name = client_conn.recv(1024).decode().strip()
        
        try:
            conn = mysql.connector.connect(**db_config)
            cursor = conn.cursor()
            
            cursor.execute("SELECT points FROM student_table WHERE user = %s", (TARGET_USER,))
            result = cursor.fetchone()
            
            if result:
                current_points = result[0]
                response = f"User: {TARGET_USER} | Points: {current_points}"
            else:
                response = f"Error: {TARGET_USER} not found."
                
            client_conn.send(response.encode())
            cursor.close()
            conn.close()
        except Exception as e:
            print(f"Socket handler error: {e}")
            
        client_conn.close()

if __name__ == "__main__":
    start_server()