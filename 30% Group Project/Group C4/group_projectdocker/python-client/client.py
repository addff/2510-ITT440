import socket

HOST = "python-server"
PORT = 5002

def print_table(username, points, timestamp):
    print("\n+----------------+----------------+-------------------------+")
    print("|     User       |     Points     |      Last Update        |")
    print("+----------------+----------------+-------------------------+")
    print(f"| {username:<14} | {points:<14} | {timestamp:<23} |")
    print("+----------------+----------------+-------------------------+\n")

def fetch_and_display():
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((HOST, PORT))

        response = client_socket.recv(1024).decode().strip()
        client_socket.close()

        parts = response.split()
        username = parts[1]               
        points = parts[3]                
        timestamp = ' '.join(parts[6:])   
        timestamp = timestamp.rstrip(')') 

        print_table(username, points, timestamp)

    except Exception as e:
        print("Connection failed:", e)

def main():
    while True:
        fetch_and_display()
        again = input("Check again? (y/n): ").strip().lower()
        if again != 'y':
            print("Goodbye!")
            break

if __name__ == "__main__":
    main()