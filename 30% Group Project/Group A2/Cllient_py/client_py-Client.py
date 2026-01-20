import os, socket, time

HOST = os.getenv("CLIENT_HOST", "server_py")
PORT = int(os.getenv("CLIENT_PORT", "5002"))
INTERVAL = int(os.getenv("CLIENT_INTERVAL", "10"))

while True:
    try:
        with socket.socket() as s:
            s.connect((HOST, PORT))
            s.sendall(b"GET\n")
            data = s.recv(1024)
            print(f"[PY CLIENT] {data.decode().strip()}", flush=True)
    except Exception as e:
        print("[PY CLIENT] error:", e, flush=True)
    time.sleep(INTERVAL)
