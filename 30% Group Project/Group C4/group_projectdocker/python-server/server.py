import mysql.connector
import time
import socket
import threading

PORT = 5002
HOST = '0.0.0.0'

def update_loop():
    while True:
        try:
            conn = mysql.connector.connect(
                host="mysql-db",
                user="py_server",
                password="pypass",
                database="assignmentdb"
            )
            cursor = conn.cursor()
            cursor.execute(
                "UPDATE points_table SET points = points + 1, last_update = NOW() WHERE user='user_py'"
            )
            conn.commit()
            print(f"[{time.strftime('%H:%M:%S')}] Points updated for user_py.")
        except Exception as e:
            print("Update failed:", e)
        finally:
            cursor.close()
            conn.close()
        time.sleep(30)

def handle_client(client_socket):
    conn = mysql.connector.connect(
        host="mysql-db",
        user="py_server",
        password="pypass",
        database="assignmentdb"
    )
    cursor = conn.cursor()

    cursor.execute("SELECT points, last_update FROM points_table WHERE user='user_py'")
    result = cursor.fetchone()

    conn.close()

    if result:
        response = f"Total user_py points: {result[0]} (updated at {result[1]})\n"
        client_socket.send(response.encode())
        print(f"Sent to client: {response.strip()}")
    else:
        client_socket.send(b"User not found.\n")

    client_socket.close()

print(f"Python server listening on port {PORT}")
threading.Thread(target=update_loop, daemon=True).start()

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(5)

while True:
    client_socket, addr = server_socket.accept()
    print("Client connected!")
    threading.Thread(target=handle_client, args=(client_socket,), daemon=True).start()