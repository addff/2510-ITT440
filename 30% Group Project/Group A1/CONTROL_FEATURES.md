# 🎮 Real-Time Dashboard Control Features

## Overview
This document describes the real-time pause/resume and reset controls added to the ITT440 Network Programming Dashboard.

## Features Implemented

### 1. **Pause/Resume Control** ⏸️▶️
- Control user point updates without stopping containers
- Each server runs an HTTP control server on port `SERVER_PORT + 1000`
- Toggle button in dashboard for instant control
- Visual status indicator (🟢 Active / ⏸️ Paused)

### 2. **Reset Points** 🔄
- Reset any user's points to zero with confirmation dialog
- Direct database update
- Instant UI refresh after reset

### 3. **Visual Feedback** 📊
- Status badges show active/paused state
- Toast notifications for all actions
- Real-time status updates every 5 seconds

## Architecture

### Control Port Mapping
| User    | Server Port | Control Port | Container     | Language |
|---------|-------------|--------------|---------------|----------|
| Afif    | 5001        | 6001         | server1       | Python   |
| Syahmi  | 5002        | 6002         | server2       | Python   |
| Irfan   | 5003        | 6003         | server3       | Python   |
| Hairiel | 6001        | 7001         | server_c1     | C        |
| Faiz    | 6002        | 7002         | server_c2     | C        |

### API Endpoints

#### Toggle User Updates
```http
POST /api/users/<username>/toggle
```
**Response:**
```json
{
  "success": true,
  "username": "Afif",
  "status": "paused"
}
```

#### Get User Status
```http
GET /api/users/<username>/status
```
**Response:**
```json
{
  "success": true,
  "username": "Afif",
  "status": "active"
}
```

#### Reset User Points
```http
POST /api/users/<username>/reset
```
**Response:**
```json
{
  "success": true,
  "username": "Afif",
  "message": "Points reset to 0"
}
```

## Server Implementation

### Python Servers (server1.py, server2.py, server3.py)
```python
# Global pause flag
update_paused = False

# Control server on port SERVER_PORT + 1000
class ControlHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        global update_paused
        if self.path == '/toggle':
            update_paused = not update_paused
            # Return status
        elif self.path == '/status':
            # Return current status

# Update thread checks flag
if not update_paused:
    # Update database
```

### C Servers (server1.c, server2.c)
```c
// Global pause flag
int update_paused = 0;

// Control server thread on port SERVER_PORT + 1000
void* control_server(void *arg) {
    // Listen for HTTP POST requests
    // Handle /toggle and /status endpoints
}

// Update thread checks flag
if (!update_paused) {
    // Update database
}
```

## Dashboard Controls

### Toggle Button
- Click to pause/resume user updates
- Icon changes based on state
- Status badge updates immediately

### Reset Button
- Click to reset points to 0
- Confirmation dialog prevents accidents
- Data refreshes automatically

### Status Indicators
- 🟢 **Active**: User points updating every 30 seconds
- ⏸️ **Paused**: User points frozen, no updates

## Usage Examples

### 1. Pause a User for Demonstration
1. Open dashboard: http://localhost:8080
2. Find user row (e.g., Afif)
3. Click ⏸️ button in Controls column
4. Status changes to "⏸️ Paused"
5. Points stop increasing

### 2. Resume Updates
1. Click same button again
2. Status changes to "🟢 Active"
3. Points resume increasing

### 3. Reset Points
1. Click 🔄 button
2. Confirm in dialog
3. Points reset to 0
4. Updates continue normally

### 4. Compare User Progress
1. Pause all users: Click ⏸️ for each user
2. Resume selected users: Click ▶️ for chosen users
3. Observe point differences in real-time

## Testing Control Features

### Test Pause/Resume
```bash
# Start all services
docker-compose --profile all up --build

# Open dashboard
http://localhost:8080

# Test pause via API
curl -X POST http://localhost:8080/api/users/Afif/toggle

# Check status
curl http://localhost:8080/api/users/Afif/status
```

### Test Reset
```bash
# Reset user points via API
curl -X POST http://localhost:8080/api/users/Afif/reset

# Verify in database
docker exec -it database mysql -udbuser -pdbpassword network_project \
  -e "SELECT * FROM user_tracking WHERE user='Afif';"
```

### Test Control Server Directly
```bash
# Python server control (port 6001-6003)
curl -X POST http://localhost:6001/toggle

# C server control (port 7001-7002)
curl -X POST http://localhost:7001/toggle
```

## Technical Details

### Why Control Ports?
- Main ports (5001-6002) handle client TCP connections
- Control ports (6001-7002) handle HTTP control requests
- Separation prevents interference with socket protocol

### Thread Safety
- Python: `global update_paused` flag with GIL protection
- C: `volatile int update_paused` atomic flag

### Error Handling
- API returns proper HTTP status codes (200, 404, 500)
- Dashboard shows error notifications
- Servers continue running on control failures

## Benefits

1. **No Container Restarts**: Pause/resume without stopping services
2. **Live Demonstrations**: Show point differences clearly
3. **Easy Testing**: Reset points instantly for repeated tests
4. **User-Friendly**: Visual controls in web interface
5. **Real-Time Feedback**: Instant status updates and notifications

## Troubleshooting

### Toggle Not Working
1. Check server logs: `docker-compose logs server1`
2. Verify control server started: Should see "Control server started on port 6001"
3. Test control endpoint directly: `curl -X POST http://localhost:6001/toggle`

### Status Not Updating
1. Check dashboard JavaScript console for errors
2. Verify API endpoint: `curl http://localhost:8080/api/users/Afif/status`
3. Ensure requests library installed in WebApp: `pip install requests`

### Reset Not Working
1. Check database connection in Flask logs
2. Verify user exists: `docker exec database mysql -udbuser -pdbpassword network_project -e "SELECT * FROM user_tracking;"`
3. Check API response: `curl -X POST http://localhost:8080/api/users/Afif/reset`

## Future Enhancements

Potential improvements:
- [ ] Bulk pause/resume all users
- [ ] Schedule auto-pause/resume (time-based)
- [ ] Point increase rate control (adjust +10 value)
- [ ] History log of control actions
- [ ] Export points data to CSV

## Conclusion

The control features provide powerful demonstration capabilities while maintaining system stability. Users can pause, resume, and reset points through an intuitive web interface without any Docker commands or container management.

Perfect for:
- **Presentations**: Show point differences clearly
- **Testing**: Reset and retry scenarios
- **Learning**: Understand update behavior
- **Debugging**: Isolate individual server issues

---

**Author**: ITT440 Team (Afif, Syahmi, Irfan, Hairiel, Faiz)  
**Date**: 2024  
**Course**: ITT440 Network Programming
