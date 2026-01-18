from flask import Flask, render_template, jsonify, request
import mysql.connector
import os
from datetime import datetime
import requests

app = Flask(__name__)

# Database configuration
DB_CONFIG = {
    'host': os.getenv('DB_HOST', 'database'),
    'user': os.getenv('DB_USER', 'dbuser'),
    'password': os.getenv('DB_PASSWORD', 'dbpassword'),
    'database': os.getenv('DB_NAME', 'network_project')
}

def get_db_connection():
    """Get database connection"""
    try:
        conn = mysql.connector.connect(**DB_CONFIG)
        return conn
    except mysql.connector.Error as err:
        print(f"Database connection error: {err}")
        return None

@app.route('/')
def dashboard():
    """Main dashboard page"""
    return render_template('dashboard.html')

@app.route('/api/users')
def get_all_users():
    """API endpoint to get all users data"""
    conn = get_db_connection()
    if not conn:
        return jsonify({'error': 'Database connection failed'}), 500
    
    try:
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT user, points, datetime_stamp FROM user_tracking ORDER BY user")
        users = cursor.fetchall()
        
        # Convert datetime to string for JSON serialization
        for user in users:
            if user['datetime_stamp']:
                user['datetime_stamp'] = user['datetime_stamp'].strftime('%Y-%m-%d %H:%M:%S')
        
        cursor.close()
        conn.close()
        
        return jsonify({
            'success': True,
            'data': users,
            'timestamp': datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        })
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@app.route('/api/users/<username>')
def get_user(username):
    """API endpoint to get specific user data"""
    conn = get_db_connection()
    if not conn:
        return jsonify({'error': 'Database connection failed'}), 500
    
    try:
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT user, points, datetime_stamp FROM user_tracking WHERE user = %s", (username,))
        user = cursor.fetchone()
        
        if user:
            if user['datetime_stamp']:
                user['datetime_stamp'] = user['datetime_stamp'].strftime('%Y-%m-%d %H:%M:%S')
            
            cursor.close()
            conn.close()
            return jsonify({
                'success': True,
                'data': user
            })
        else:
            cursor.close()
            conn.close()
            return jsonify({'error': 'User not found'}), 404
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@app.route('/api/servers')
def get_servers():
    """API endpoint to get server status"""
    servers = [
        {'name': 'server1', 'user': 'Afif', 'port': 5001, 'control_port': 6001, 'language': 'Python'},
        {'name': 'server2', 'user': 'Syahmi', 'port': 5002, 'control_port': 6002, 'language': 'Python'},
        {'name': 'server3', 'user': 'Irfan', 'port': 5003, 'control_port': 6003, 'language': 'Python'},
        {'name': 'server_c1', 'user': 'Hairiel', 'port': 6001, 'control_port': 7001, 'language': 'C'},
        {'name': 'server_c2', 'user': 'Faiz', 'port': 6002, 'control_port': 7002, 'language': 'C'},
    ]
    
    return jsonify({
        'success': True,
        'data': servers
    })

@app.route('/api/stats')
def get_stats():
    """API endpoint to get overall statistics"""
    conn = get_db_connection()
    if not conn:
        return jsonify({'error': 'Database connection failed'}), 500
    
    try:
        cursor = conn.cursor(dictionary=True)
        cursor.execute("SELECT SUM(points) as total_points, AVG(points) as avg_points, MAX(points) as max_points, MIN(points) as min_points FROM user_tracking")
        stats = cursor.fetchone()
        
        cursor.close()
        conn.close()
        
        return jsonify({
            'success': True,
            'data': stats
        })
    except Exception as e:
        return jsonify({'error': str(e)}), 500

@app.route('/api/users/<username>/toggle', methods=['POST'])
def toggle_user(username):
    """API endpoint to toggle user updates (pause/resume)"""
    # Map usernames to control ports
    user_control_ports = {
        'Afif': 6001,
        'Syahmi': 6002,
        'Irfan': 6003,
        'Hairiel': 7001,
        'Faiz': 7002
    }
    
    if username not in user_control_ports:
        return jsonify({'error': 'User not found'}), 404
    
    control_port = user_control_ports[username]
    
    # Map usernames to container hostnames
    user_containers = {
        'Afif': 'server1',
        'Syahmi': 'server2',
        'Irfan': 'server3',
        'Hairiel': 'server_c1',
        'Faiz': 'server_c2'
    }
    
    container_name = user_containers[username]
    
    try:
        # Call the server's control endpoint
        response = requests.post(f'http://{container_name}:{control_port}/toggle', timeout=2)
        if response.status_code == 200:
            data = response.json()
            return jsonify({
                'success': True,
                'username': username,
                'status': data.get('status', 'unknown')
            })
        else:
            return jsonify({'error': 'Control request failed'}), 500
    except Exception as e:
        return jsonify({'error': f'Failed to contact server: {str(e)}'}), 500

@app.route('/api/users/<username>/status', methods=['GET'])
def get_user_status(username):
    """API endpoint to get user update status"""
    # Map usernames to control ports
    user_control_ports = {
        'Afif': 6001,
        'Syahmi': 6002,
        'Irfan': 6003,
        'Hairiel': 7001,
        'Faiz': 7002
    }
    
    if username not in user_control_ports:
        return jsonify({'error': 'User not found'}), 404
    
    control_port = user_control_ports[username]
    
    # Map usernames to container hostnames
    user_containers = {
        'Afif': 'server1',
        'Syahmi': 'server2',
        'Irfan': 'server3',
        'Hairiel': 'server_c1',
        'Faiz': 'server_c2'
    }
    
    container_name = user_containers[username]
    
    try:
        # Call the server's status endpoint
        response = requests.post(f'http://{container_name}:{control_port}/status', timeout=2)
        if response.status_code == 200:
            data = response.json()
            return jsonify({
                'success': True,
                'username': username,
                'status': data.get('status', 'unknown')
            })
        else:
            return jsonify({'error': 'Status request failed'}), 500
    except Exception as e:
        return jsonify({'error': f'Failed to contact server: {str(e)}'}), 500

@app.route('/api/users/<username>/reset', methods=['POST'])
def reset_user_points(username):
    """API endpoint to reset user points to zero"""
    conn = get_db_connection()
    if not conn:
        return jsonify({'error': 'Database connection failed'}), 500
    
    try:
        cursor = conn.cursor()
        cursor.execute("UPDATE user_tracking SET points = 0, datetime_stamp = NOW() WHERE user = %s", (username,))
        
        if cursor.rowcount == 0:
            cursor.close()
            conn.close()
            return jsonify({'error': 'User not found'}), 404
        
        conn.commit()
        cursor.close()
        conn.close()
        
        return jsonify({
            'success': True,
            'username': username,
            'message': 'Points reset to 0'
        })
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    # Wait for database to be ready
    import time
    time.sleep(10)
    
    app.run(host='0.0.0.0', port=8080, debug=True)
