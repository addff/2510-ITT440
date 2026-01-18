# 🎮 How to Control Your ITT440 Network Programming System

## 📋 Table of Contents
1. [Starting the System](#starting-the-system)
2. [Accessing the Dashboard](#accessing-the-dashboard)
3. [Understanding the Dashboard](#understanding-the-dashboard)
4. [Control Buttons Explained](#control-buttons-explained)
5. [How to Control Each User](#how-to-control-each-user)
6. [Testing the Controls](#testing-the-controls)
7. [Troubleshooting](#troubleshooting)

---

## 🚀 Starting the System

### Step 1: Open PowerShell in Project Directory
```powershell
cd D:\Xampp\htdocs\Docker
```

### Step 2: Start All Containers
```powershell
# Start all services
docker-compose --profile all up -d
```

**What this does:**
- `-d` = detached mode (runs in background)
- `--profile all` = starts all 5 users (Afif, Syahmi, Irfan, Hairiel, Faiz)

### Step 3: Wait for Services to Start (20-30 seconds)
Check status:
```powershell
docker-compose ps
```

You should see 13 containers running:
- ✅ mysql_database
- ✅ python_server1, python_server2, python_server3
- ✅ c_server1, c_server2
- ✅ python_client1, python_client2, python_client3
- ✅ c_client1, c_client2
- ✅ web_dashboard
- ✅ phpmyadmin

---

## 🌐 Accessing the Dashboard

### Open Your Web Browser

**Main Dashboard:**
```
http://localhost:8080
```

**PhpMyAdmin (Database):**
```
http://localhost:8081
Username: dbuser
Password: dbpassword
```

---

## 📊 Understanding the Dashboard

When you open http://localhost:8080, you'll see:

### Top Section: Statistics Cards
- **Total Points** - Sum of all users' points
- **Average Points** - Average across all users
- **Highest Points** - Maximum points any user has
- **Lowest Points** - Minimum points any user has

### Middle Section: User Table
This is where the **CONTROL BUTTONS** are located!

| # | User Name | Points | Last Update | Server | Language | Status | Controls |
|---|-----------|--------|-------------|--------|----------|--------|----------|
| 1 | Afif | 120 | 2026-01-12... | server1:5001 | Python | 🟢 Active | **[⏸️] [🔄]** |
| 2 | Syahmi | 80 | 2026-01-12... | server2:5002 | Python | 🟢 Active | **[⏸️] [🔄]** |
| 3 | Irfan | 90 | 2026-01-12... | server3:5003 | Python | 🟢 Active | **[⏸️] [🔄]** |
| 4 | Hairiel | 60 | 2026-01-12... | server_c1:6001 | C | 🟢 Active | **[⏸️] [🔄]** |
| 5 | Faiz | 70 | 2026-01-12... | server_c2:6002 | C | 🟢 Active | **[⏸️] [🔄]** |

### Bottom Section: Charts
- **Line Chart** - Shows point growth over time
- **Doughnut Chart** - Shows point distribution

---

## 🎛️ Control Buttons Explained

### Two Buttons Per User:

#### 1️⃣ Pause/Resume Button: **⏸️**
**Location:** Yellow button in Controls column

**What it does:**
- **First click** = Pauses point updates for that user
- **Second click** = Resumes point updates

**When paused:**
- Status badge changes: 🟢 Active → ⏸️ Paused
- Points stop increasing every 30 seconds
- Other users continue normally

**Example:**
```
Click ⏸️ on Afif's row
→ Afif's status: ⏸️ Paused
→ Afif's points: FROZEN at current value
→ Other users: Still gaining +10 every 30 seconds
```

#### 2️⃣ Reset Button: **🔄**
**Location:** Red button in Controls column

**What it does:**
- Resets user's points to **0** in the database
- Shows confirmation dialog before resetting
- User continues gaining points after reset

**Example:**
```
Click 🔄 on Syahmi's row
→ Confirmation: "Are you sure you want to reset points for Syahmi to 0?"
→ Click OK
→ Syahmi's points: 80 → 0
→ Points resume: 0 → 10 → 20 → 30...
```

---

## 🕹️ How to Control Each User

### Scenario 1: Pause One User to Show Point Differences

**Goal:** Show that Afif gains points while others stay frozen

**Steps:**
1. Open dashboard: http://localhost:8080
2. Note current points (e.g., All at 50 points)
3. Click **⏸️** button for Syahmi, Irfan, Hairiel, Faiz
4. Leave Afif **Active** (🟢)
5. Wait 30 seconds
6. Observe:
   - Afif: 50 → 60 → 70 → 80 (increasing)
   - Others: 50 (frozen)
7. Click **⏸️** again on others to resume

**Result:** Clear demonstration of which server is active!

### Scenario 2: Reset All Users for Clean Demo

**Goal:** Start everyone from zero points

**Steps:**
1. Click **🔄** button for each user
2. Confirm each reset dialog
3. All users now at 0 points
4. Watch them grow together: 0 → 10 → 20 → 30...

**Use case:** Perfect for starting a fresh presentation!

### Scenario 3: Create Staggered Point Differences

**Goal:** Make users have different point levels

**Steps:**
1. Reset all users (all at 0)
2. Resume only Afif, wait 2 minutes (Afif: 40 points)
3. Pause Afif, resume Syahmi, wait 1 minute (Syahmi: 20 points)
4. Pause Syahmi, resume Irfan, wait 30 seconds (Irfan: 10 points)
5. Resume all users
6. Result:
   - Afif: 40 → 50 → 60 → 70
   - Syahmi: 20 → 30 → 40 → 50
   - Irfan: 10 → 20 → 30 → 40
   - Hairiel: 0 → 10 → 20 → 30
   - Faiz: 0 → 10 → 20 → 30

**Use case:** Demonstrate that servers update at different times!

### Scenario 4: Compare Python vs C Servers

**Goal:** Show Python servers separate from C servers

**Steps:**
1. Pause all C servers (Hairiel, Faiz)
2. Let Python servers run (Afif, Syahmi, Irfan)
3. After 1 minute, pause Python, resume C
4. Observe different point levels
5. Resume all

**Use case:** Demonstrate multi-language implementation!

---

## 🧪 Testing the Controls

### Test 1: Verify Pause Works
```powershell
# Check server logs to confirm pause
docker-compose logs server1 --tail 5
```

Expected output when paused:
```
[2026-01-12 08:35:23] Updates paused for Afif
[2026-01-12 08:35:53] Updates paused for Afif
```

### Test 2: Verify Reset Works
```powershell
# Check database after reset
docker exec mysql_database mysql -udbuser -pdbpassword network_project \
  -e "SELECT user, points FROM user_tracking WHERE user='Afif';"
```

Expected output after reset:
```
+------+--------+
| user | points |
+------+--------+
| Afif |      0 |
+------+--------+
```

### Test 3: Test Control API Directly
```powershell
# Toggle pause for Afif
Invoke-WebRequest -Uri "http://localhost:8080/api/users/Afif/toggle" -Method POST

# Check status
Invoke-RestMethod -Uri "http://localhost:8080/api/users/Afif/status"

# Reset points
Invoke-WebRequest -Uri "http://localhost:8080/api/users/Afif/reset" -Method POST
```

---

## 🔧 Troubleshooting

### Problem 1: Control Buttons Not Appearing

**Symptoms:**
- Dashboard shows user table
- No ⏸️ or 🔄 buttons in Controls column

**Solution:**
```powershell
# Restart web dashboard container
docker-compose restart web_dashboard

# Wait 10 seconds, then refresh browser
# Press Ctrl+F5 (hard refresh) to clear cache
```

**Check browser console:**
- Press F12
- Go to Console tab
- Look for JavaScript errors

### Problem 2: Buttons Don't Work When Clicked

**Symptoms:**
- Buttons appear but clicking does nothing
- No notification appears

**Solution:**
```powershell
# Check if control servers are running
docker-compose logs server1 | grep "Control"
```

Expected output:
```
Control server started on port 6001
```

If not appearing:
```powershell
# Rebuild and restart
docker-compose build server1 server2 server3 server_c1 server_c2
docker-compose restart server1 server2 server3 server_c1 server_c2
```

### Problem 3: Status Shows "Unknown"

**Symptoms:**
- Status column shows blank or "Unknown"
- Buttons appear but status doesn't update

**Solution:**

1. Check control port connectivity:
```powershell
# Test Python server control
curl http://localhost:6001/status

# Test C server control
curl http://localhost:7001/status
```

2. If no response, check server logs:
```powershell
docker-compose logs server1 --tail 20
```

3. Restart affected server:
```powershell
docker-compose restart server1
```

### Problem 4: Dashboard Shows Old Data

**Symptoms:**
- Points don't update
- Status doesn't change after clicking buttons

**Solution:**
```powershell
# Hard refresh browser
# Press Ctrl+F5 or Ctrl+Shift+R

# Clear browser cache
# Chrome: Ctrl+Shift+Delete → Clear browsing data
```

### Problem 5: Container Not Running

**Symptoms:**
- Error message when clicking controls
- Some users don't appear

**Solution:**
```powershell
# Check which containers are running
docker-compose ps

# Restart specific container
docker-compose restart server1

# Or restart all
docker-compose restart
```

---

## 📝 Command Cheatsheet

### Starting/Stopping

```powershell
# Start all services
docker-compose --profile all up -d

# Start only specific users
docker-compose --profile afif --profile syahmi up -d

# Stop all services
docker-compose down

# Stop but keep data
docker-compose stop

# Restart all
docker-compose restart

# Restart specific service
docker-compose restart server1
```

### Monitoring

```powershell
# View all container status
docker-compose ps

# View logs (all services)
docker-compose logs -f

# View logs (specific service)
docker-compose logs server1 --tail 50

# View real-time logs
docker-compose logs -f server1

# Check database
docker exec mysql_database mysql -udbuser -pdbpassword network_project \
  -e "SELECT * FROM user_tracking;"
```

### Control via Command Line

```powershell
# Pause user (via API)
Invoke-WebRequest -Uri "http://localhost:8080/api/users/Afif/toggle" -Method POST

# Reset user (via API)
Invoke-WebRequest -Uri "http://localhost:8080/api/users/Afif/reset" -Method POST

# Check status (via API)
Invoke-RestMethod -Uri "http://localhost:8080/api/users/Afif/status"

# Direct control server (Python)
curl -X POST http://localhost:6001/toggle

# Direct control server (C)
curl -X POST http://localhost:7001/toggle
```

---

## 🎓 For Your Presentation

### Recommended Demo Flow:

1. **Start Fresh**
   - Reset all users to 0
   - Show everyone starting equally

2. **Demonstrate Pause Control**
   - Pause 3 users
   - Let 2 users run
   - Show point differences

3. **Show Language Diversity**
   - Pause Python servers
   - Resume C servers
   - Explain multi-language implementation

4. **Database Verification**
   - Open PhpMyAdmin (http://localhost:8081)
   - Show user_tracking table
   - Demonstrate real-time updates

5. **Architecture Explanation**
   - Show Docker containers (docker-compose ps)
   - Explain client-server communication
   - Demonstrate socket programming

6. **Reset for Q&A**
   - Reset all users
   - Let audience ask questions
   - Test controls live

---

## 🔗 Important URLs

- **Main Dashboard:** http://localhost:8080
- **PhpMyAdmin:** http://localhost:8081
- **API Documentation:** See README.md

## 📞 Quick Reference

**Pause/Resume:** Yellow button (⏸️) in Controls column  
**Reset Points:** Red button (🔄) in Controls column  
**Active Status:** 🟢 Active (points updating)  
**Paused Status:** ⏸️ Paused (points frozen)  
**Update Frequency:** Every 30 seconds  
**Dashboard Refresh:** Every 5 seconds

---

**🎉 You're Ready to Control Your System!**

Just open http://localhost:8080 and start clicking the control buttons in the table!
