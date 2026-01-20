import os, socket, threading, time
import mysql.connector

DB_HOST = os.getenv("DB_HOST", "db")
DB_NAME = os.getenv("DB_NAME", "attendance_db")
DB_USER = os.getenv("DB_USER", "root")
DB_PASS = os.getenv("DB_PASS", "root")
USER_NAME = os.getenv("ATT_USER", "student_py")
PORT = int(os.getenv("PORT", "5002"))
UPDATE_INTERVAL = int(os.getenv("UPDATE_INTERVAL", "30"))

def db_connect():
    return mysql.connector.connect(
        host=DB_HOST,
        user=DB_USER,
        password=DB_PASS,
        database=DB_NAME
    )

def get_latest():
    conn = db_connect()
    cur = conn.cursor()
    cur.execute(
        "SELECT points, datetime_stamp FROM attendance WHERE user=%s",
        (USER_NAME,)
    )
    row = cur.fetchone()
    cur.close()
    conn.close()
    return row

def update_points_forever():
    while True:
        try:
            conn = db_connect()
            cur = conn.cursor()
            cur.execute(
                "UPDATE attendance SET points=points+1, datetime_stamp=NOW() WHERE user=%s",
                (USER_NAME,)
            )
            conn.commit()
            cur.close()
            conn.close()
            row = get_latest()
            if row:
                print(f"[PY SERVER] user={USER_NAME} points={row[0]} time={row[1]}", flush=True)
        except Exception as e:
            print("[PY SERVER] error:", e, flush=True)
        time.sleep(UPDATE_INTERVAL)

def handle_client(conn):
    data = conn.recv(1024).decode().strip()
    if data.upper() == "GET":
        row = get_latest()
        if row:
            msg = f"USER={USER_NAME} POINTS={row[0]} TIME={row[1]}\n"
        else:
            msg = "ERROR=NO_RECORD\n"
    else:
        msg = "ERROR=SEND_GET\n"
    conn.sendall(msg.encode())
    conn.close()

def main():
    threading.Thread(target=update_points_forever, daemon=True).start()
    s = socket.socket()
    s.bind(("0.0.0.0", PORT))
    s.listen(10)
    print(f"[PY SERVER] listening on {PORT}", flush=True)
    while True:
        c, _ = s.accept()
        threading.Thread(target=handle_client, args=(c,), daemon=True).start()

if __name__ == "__main__":
    main()
