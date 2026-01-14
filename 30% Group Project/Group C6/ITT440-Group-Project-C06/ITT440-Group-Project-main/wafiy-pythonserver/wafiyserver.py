import socket
import threading
import time
from datetime import datetime
import mysql.connector

DB_CONFIG = {
    "host": "mysql",
    "user": "root",
    "password": "rootpassword",
    "database": "pointsdb"
}

USER = "wafiy_user"
PORT = 8080


def connect_to_db():
    while True:
        try:
            print("Connecting to MySQL...", flush=True)
            conn = mysql.connector.connect(**DB_CONFIG)
            print("MySQL Connected!", flush=True)
            return conn
        except mysql.connector.Error as err:
            print(f"Database not ready yet... ({err})", flush=True)
            time.sleep(2)


def update_points():
    while True:
        try:
            conn = connect_to_db()
            cursor = conn.cursor()

            while True:
                now = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                cursor.execute(
                    "UPDATE points_table SET points = points + 1, datetime_stamp = %s WHERE user = %s",
                    (now, USER)
                )
                conn.commit()
                print(f"Points updated for {USER} at {now}", flush=True)
                time.sleep(30)

        except Exception as e:
            print(f"DB error, reconnecting... {e}", flush=True)
            time.sleep(5)


# Start background updater
threading.Thread(target=update_points, daemon=True).start()

# TCP socket server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("0.0.0.0", PORT))
server.listen()

print(f"wafiy Python server running on port {PORT}...", flush=True)

while True:
    client, addr = server.accept()
    try:
        conn = connect_to_db()
        cursor = conn.cursor()
        cursor.execute("SELECT points, datetime_stamp FROM points_table WHERE user = %s", (USER,))
        result = cursor.fetchone()

        if result:
            points, ts = result
            response = f"User: {USER}, Points: {points}, Last update: {ts}"
        else:
            response = f"User {USER} not found in database."

        client.send(response.encode())
        conn.close()

    except Exception as e:
        client.send(f"Error: {e}".encode())

    client.close()
