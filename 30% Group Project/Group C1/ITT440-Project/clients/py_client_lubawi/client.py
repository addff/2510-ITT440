import socket
import time
import sys
import os
from datetime import datetime, timedelta

SERVER_NAME = "py_server_lubawi"
SERVER_PORT = 5004

# Global variables
last_known_points = 0
connection_status = "Disconnected"
last_update_time = datetime.now()
update_counter = 0
log_entries = []
max_log_entries = 10
TABLE_WIDTH = 70

def wait_for_server():
    """Wait for server to be ready"""
    max_retries = 30
    for i in range(max_retries):
        try:
            print(f"Waiting for server... ({i+1}/{max_retries})")
            test_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            test_socket.settimeout(2)
            test_socket.connect((SERVER_NAME, SERVER_PORT))
            test_socket.close()
            print("Server is ready!")
            return True
        except:
            time.sleep(2)
    return False

def add_log_entry(message):
    """Add a log entry with timestamp"""
    global log_entries
    timestamp = datetime.now().strftime("%H:%M:%S")
    log_entry = f"[{timestamp}] {message}"
    log_entries.append(log_entry)
    
    if len(log_entries) > max_log_entries:
        log_entries = log_entries[-max_log_entries:]

def center_text(text, width):
    """Center text within given width"""
    if len(text) >= width:
        return text[:width]
    padding = (width - len(text)) // 2
    return " " * padding + text + " " * (width - len(text) - padding)

def display_table():
    """Display a clean status table with perfect alignment"""
    global last_known_points, connection_status, last_update_time, update_counter, log_entries
    
    # Increment update counter and update time
    update_counter += 1
    last_update_time = datetime.now()
    
    # Print empty line before new table for spacing
    print("\n")
    
    # Top border
    print("╔" + "═" * (TABLE_WIDTH - 2) + "╗")
    
    # Title - centered
    title = "LUBAWI POINTS MONITOR"
    print("║" + center_text(title, TABLE_WIDTH - 2) + "║")
    
    # Separator
    print("╠" + "═" * (TABLE_WIDTH - 2) + "╣")
    
    # Update info line
    update_text = f"Update #{update_counter} | {last_update_time.strftime('%Y-%m-%d %H:%M:%S')}"
    print(f"║ {update_text:<{TABLE_WIDTH-3}}║")
    
    # Status line
    status_text = f"Status: {connection_status}"
    print(f"║ {status_text:<{TABLE_WIDTH-3}}║")
    
    # Server line
    server_text = f"Server: {SERVER_NAME}:{SERVER_PORT}"
    print(f"║ {server_text:<{TABLE_WIDTH-3}}║")
    
    # Separator
    print("╠" + "═" * (TABLE_WIDTH - 2) + "╣")
    
    # Points line - centered value
    points_text = f"Current Points: {last_known_points}"
    points_display = f"║ {points_text:^{TABLE_WIDTH-3}}║"
    print(points_display)
    
    # Separator
    print("╠" + "═" * (TABLE_WIDTH - 2) + "╣")
    
    # Recent Activity header
    print(f"║ Recent Activity:{' ' * (TABLE_WIDTH - 19)}║")
    
    # Display recent log entries
    if log_entries:
        for entry in log_entries[-5:]:
            # Truncate if too long
            if len(entry) > TABLE_WIDTH - 7:
                entry = entry[:TABLE_WIDTH - 10] + "..."
            print(f"║   • {entry:<{TABLE_WIDTH-7}}║")
    else:
        print(f"║   • No recent activity{' ' * (TABLE_WIDTH - 25)}║")
    
    # Bottom border
    print("╚" + "═" * (TABLE_WIDTH - 2) + "╝")
    
    # Show timing info below table
    next_table_time = last_update_time + timedelta(seconds=30)
    print(f"⏰ Next update at: {next_table_time.strftime('%H:%M:%S')}")

def parse_points(response):
    """Parse points from server response"""
    global last_known_points
    
    if "Lubawi Points:" in response or "Points:" in response:
        try:
            # Try different formats
            if "Lubawi Points:" in response:
                parts = response.split("Lubawi Points:")
            else:
                parts = response.split("Points:")
            
            if len(parts) >= 2:
                points_str = parts[1].strip()
                # Extract only numbers
                points_str = ''.join(filter(str.isdigit, points_str))
                if points_str:
                    points = int(points_str)
                    last_known_points = points
                    add_log_entry(f"Updated points to: {points}")
                    return points
        except ValueError:
            add_log_entry(f"Failed to parse points from: {response}")
            pass
    return last_known_points

def get_initial_points():
    """Connect to server once to get initial points before starting regular updates"""
    global last_known_points, connection_status
    
    try:
        print("Getting initial points from server...")
        temp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        temp_socket.settimeout(5)
        temp_socket.connect((SERVER_NAME, SERVER_PORT))
        
        # Request points
        temp_socket.send("GET_POINTS".encode())
        response = temp_socket.recv(1024).decode()
        
        # Parse points from response
        points_parsed = parse_points(response)
        if points_parsed != 0:
            connection_status = "Connected (Initial)"
            print(f"✓ Initial points received: {points_parsed}")
        else:
            print(f"⚠️ Could not parse initial points from: {response}")
        
        temp_socket.close()
        return True
    except Exception as e:
        print(f"⚠️ Could not get initial points: {e}")
        add_log_entry(f"Could not get initial points: {str(e)[:30]}")
        connection_status = "Disconnected"
        return False

def safe_send_receive(client_socket, request):
    """Safely send and receive data with proper error handling"""
    try:
        # Send request
        client_socket.send(request.encode())
        add_log_entry(f"Sent: {request}")
        
        # Receive response with timeout
        client_socket.settimeout(10)
        response = client_socket.recv(1024).decode()
        
        if response:
            add_log_entry(f"Received: {response[:50]}..." if len(response) > 50 else f"Received: {response}")
            return response
        else:
            add_log_entry("Received empty response (connection closed by server)")
            return None
            
    except socket.timeout:
        add_log_entry("Request timeout (no response from server)")
        return None
    except socket.error as e:
        if e.errno == 32:  # Broken pipe
            add_log_entry("Broken pipe - Server closed connection")
        elif e.errno == 104:  # Connection reset by peer
            add_log_entry("Connection reset by server")
        else:
            add_log_entry(f"Socket error: {str(e)[:30]}")
        return None
    except Exception as e:
        add_log_entry(f"Unexpected error: {str(e)[:30]}")
        return None

def start_client():
    global last_known_points, connection_status, update_counter
    
    # Clear screen at the very beginning only
    os.system('cls' if os.name == 'nt' else 'clear')
    
    # Initial header with perfect alignment
    print("╔" + "═" * (TABLE_WIDTH - 2) + "╗")
    title = "LUBAWI POINTS MONITOR - STARTING"
    print("║" + center_text(title, TABLE_WIDTH - 2) + "║")
    print("╠" + "═" * (TABLE_WIDTH - 2) + "╣")
    
    started_text = f"Started: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}"
    print(f"║ {started_text:<{TABLE_WIDTH-3}}║")
    
    server_text = f"Server: {SERVER_NAME}:{SERVER_PORT}"
    print(f"║ {server_text:<{TABLE_WIDTH-3}}║")
    print("╚" + "═" * (TABLE_WIDTH - 2) + "╝\n")
    
    print(f"Python Client (Lubawi) starting...")
    print(f"Will connect to: {SERVER_NAME}:{SERVER_PORT}")
    add_log_entry("Client starting...")
    
    # Wait for server to be ready
    if not wait_for_server():
        add_log_entry("Server not available after 30 attempts")
        print("\n" + "!" * TABLE_WIDTH)
        print("Server unavailable. Continuing in offline mode.")
        print("!" * TABLE_WIDTH + "\n")
        time.sleep(2)
        connection_status = "Offline - Server Unavailable"
        display_table()
    else:
        # Try to get initial points from server
        if not get_initial_points():
            print("Starting with default points: 0")
    
    retry_count = 0
    max_retries = 3
    
    # Initialize last table update time
    last_table_update = time.time()
    
    # Calculate time to first table
    current_seconds = datetime.now().second
    seconds_to_next_interval = 30 - (current_seconds % 30)
    if seconds_to_next_interval == 30:
        seconds_to_next_interval = 0
    
    if seconds_to_next_interval > 0:
        print(f"\nFirst table in {seconds_to_next_interval} seconds...")
        
        # Simple countdown
        for i in range(seconds_to_next_interval, 0, -1):
            if i <= 3 or i % 5 == 0:
                sys.stdout.write(f"\r⏳ {i}...")
                sys.stdout.flush()
            time.sleep(1)
        print("\n")
    
    # Display first table
    display_table()
    last_table_update = time.time()
    
    while True:
        # Check if 30 seconds have passed for new table
        current_time = time.time()
        time_since_last_update = current_time - last_table_update
        
        if time_since_last_update >= 30:
            display_table()
            last_table_update = current_time
        
        retry_count += 1
        
        if retry_count > max_retries:
            retry_count = 0
            add_log_entry("Max retries reached, waiting 30 seconds")
            print(f"\n⚠️ Max retries reached. Waiting 30 seconds...")
            
            # Wait 30 seconds but still show tables every 30 seconds
            wait_start = time.time()
            while time.time() - wait_start < 30:
                current_time = time.time()
                if current_time - last_table_update >= 30:
                    display_table()
                    last_table_update = current_time
                time.sleep(1)
            
            continue
        
        add_log_entry(f"Connection attempt {retry_count}/{max_retries}")
        print(f"\n[Connecting...] (Try {retry_count}/{max_retries})")
        
        try:
            # Create new socket for connection
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client_socket.settimeout(10)
            
            # Connect to server
            client_socket.connect((SERVER_NAME, SERVER_PORT))
            connection_status = "Connected"
            add_log_entry("Connected to server")
            
            # Show table if it's time
            current_time = time.time()
            if current_time - last_table_update >= 30:
                display_table()
                last_table_update = current_time
            else:
                print(f"✓ Connected!")
            
            retry_count = 0  # Reset retry count
            
            # Create a new connection for EACH request
            while True:
                # Check if 30 seconds have passed for new table
                current_time = time.time()
                if current_time - last_table_update >= 30:
                    display_table()
                    last_table_update = current_time
                
                try:
                    # Create a fresh socket for each request
                    request_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    request_socket.settimeout(10)
                    request_socket.connect((SERVER_NAME, SERVER_PORT))
                    
                    # Send request and get response
                    response = safe_send_receive(request_socket, "GET_POINTS")
                    
                    # Close the request socket immediately
                    request_socket.close()
                    
                    if response:
                        # Parse and update points
                        parse_points(response)
                    
                    # Show table if it's time
                    current_time = time.time()
                    if current_time - last_table_update >= 30:
                        display_table()
                        last_table_update = current_time
                    
                    # Wait 10 seconds before next request
                    wait_start = time.time()
                    while time.time() - wait_start < 10:
                        current_time = time.time()
                        if current_time - last_table_update >= 30:
                            display_table()
                            last_table_update = current_time
                        time.sleep(0.5)
                    
                except socket.timeout:
                    add_log_entry("Connection timeout for request")
                    print("Connection timeout. Reconnecting...")
                    break
                except ConnectionRefusedError:
                    add_log_entry("Connection refused for request")
                    connection_status = "Connection Refused"
                    break
                except socket.gaierror:
                    add_log_entry("DNS error for request")
                    connection_status = "DNS Error"
                    break
                except Exception as e:
                    add_log_entry(f"Request error: {str(e)[:30]}")
                    print(f"Request error: {e}")
                    break
            
            # Close main socket
            client_socket.close()
            add_log_entry("Main connection closed")
            
        except socket.timeout:
            connection_status = "Timeout - Retrying"
            add_log_entry("Connection timeout")
            # Show table if it's time
            current_time = time.time()
            if current_time - last_table_update >= 30:
                display_table()
                last_table_update = current_time
        except ConnectionRefusedError:
            connection_status = "Connection Refused"
            add_log_entry("Connection refused")
            # Show table if it's time
            current_time = time.time()
            if current_time - last_table_update >= 30:
                display_table()
                last_table_update = current_time
        except socket.gaierror:
            connection_status = "DNS Error - Offline"
            add_log_entry("DNS resolution failed")
            # Show table if it's time
            current_time = time.time()
            if current_time - last_table_update >= 30:
                display_table()
                last_table_update = current_time
        except Exception as e:
            error_msg = str(e)[:30] + "..." if len(str(e)) > 30 else str(e)
            connection_status = f"Error: {error_msg}"
            add_log_entry(f"Connection error: {error_msg}")
            # Show table if it's time
            current_time = time.time()
            if current_time - last_table_update >= 30:
                display_table()
                last_table_update = current_time
        
        # Show offline status
        if connection_status != "Connected":
            # Show table if it's time
            current_time = time.time()
            if current_time - last_table_update >= 30:
                display_table()
                last_table_update = current_time
            
            print(f"Using last known points: {last_known_points}")
            print(f"Reconnecting in 5 seconds...")
        
        # Wait 5 seconds
        wait_start = time.time()
        while time.time() - wait_start < 5:
            current_time = time.time()
            if current_time - last_table_update >= 30:
                display_table()
                last_table_update = current_time
            time.sleep(0.5)

if __name__ == "__main__":
    try:
        start_client()
    except KeyboardInterrupt:
        print("\n\n" + "=" * TABLE_WIDTH)
        print(f"Client stopped at {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"Final Lubawi Points: {last_known_points}")
        print(f"Total tables shown: {update_counter}")
        print("=" * TABLE_WIDTH)
        sys.exit(0)