import os
import socket
import mysql.connector
import threading
import time

#for db connection
DB_HOST = os.getenv('DB_HOST', 'mysql')
DB_USER = os.getenv('DB_USER', 'root')
DB_PASS = os.getenv('DB_PASS', 'root')
DB_NAME = os.getenv('DB_NAME', 'itt440_db')
MY_USER = os.getenv('USER_NAME', 'py_ayu_1')
PORT = int(os.getenv('SERVER_PORT', 4001))


#trying db connection
def get_db_connection():
    while True:
        try:
            return mysql.connector.connect(
                host=DB_HOST,
                user=DB_USER,
                password=DB_PASS,
                database=DB_NAME
            )
        except mysql.connector.Error as e:
            print(f"DB not ready yet: {e}. Retrying in 5 seconds")
            time.sleep(5)


def update_points_loop():
    while True:
        try:
            conn = get_db_connection()
            cursor = conn.cursor()
            query = "UPDATE Star_point SET points = points + 1, datetime_stamp = NOW() WHERE user = %s"
            cursor.execute(query, (MY_USER,))
            conn.commit()
            print(f"[{time.ctime()}] Points increased for {MY_USER}")
            cursor.close()
            conn.close()
        except Exception as e:
            print(f"DB Error in update loop: {e}")

        time.sleep(30)


def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', PORT))
    server.listen(5)
    print(f"Server {MY_USER} listening on port {PORT}...")

    while True:
        client_sock, addr = server.accept()
        try:
            conn = get_db_connection()
            cursor = conn.cursor()
            cursor.execute(
                "SELECT user, points, datetime_stamp FROM Star_point WHERE user = %s",
                (MY_USER,)
            )
            row = cursor.fetchone()

            if row:
                response = f"User: {row[0]} | Points: {row[1]} | Updated: {row[2]}"
            else:
                response = "User not found."

            cursor.close()
            conn.close()
        except Exception as e:
            response = f"Server DB error: {e}"

        client_sock.send(response.encode())
        client_sock.close()


if __name__ == "__main__":
    threading.Thread(target=update_points_loop, daemon=True).start()
    start_server()

