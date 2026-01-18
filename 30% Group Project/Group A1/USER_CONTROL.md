# 🎮 User Control Guide

## 🚀 Method 1: Docker Compose Profiles (Choose Users at Startup)

### **Run Specific Users Only**

```bash
# Run only Afif (server1 + client1)
docker-compose --profile afif up --build

# Run only Syahmi (server2 + client2)
docker-compose --profile syahmi up --build

# Run only Irfan (server3 + client3)
docker-compose --profile irfan up --build

# Run only Hairiel (server_c1 + client_c1)
docker-compose --profile hairiel up --build

# Run only Faiz (server_c2 + client_c2)
docker-compose --profile faiz up --build
```

### **Run Multiple Specific Users**

```bash
# Run Afif + Syahmi only
docker-compose --profile afif --profile syahmi up --build

# Run Afif + Irfan + Faiz
docker-compose --profile afif --profile irfan --profile faiz up --build

# Run all Python users (Afif, Syahmi, Irfan)
docker-compose --profile python up --build

# Run all C users (Hairiel, Faiz)
docker-compose --profile c up --build
```

### **Run All Users (Default)**

```bash
# Run everything
docker-compose --profile all up --build
```

---

## 📊 **What Gets Started**

| Profile | Servers Started | Clients Started |
|---------|----------------|----------------|
| `afif` | server1 (Python) | client1 |
| `syahmi` | server2 (Python) | client2 |
| `irfan` | server3 (Python) | client3 |
| `hairiel` | server_c1 (C) | client_c1 |
| `faiz` | server_c2 (C) | client_c2 |
| `python` | server1, server2, server3 | client1, client2, client3 |
| `c` | server_c1, server_c2 | client_c1, client_c2 |
| `all` | All 5 servers | All 5 clients |

---

## 🎯 **Use Cases**

### **Show Points Differences**

```bash
# Start Afif first (let him accumulate points)
docker-compose --profile afif up --build

# Wait 1-2 minutes, then in another terminal add Syahmi
docker-compose --profile syahmi up -d

# Now Afif will have more points than Syahmi!
```

### **Compare Python vs C**

```bash
# Run all Python servers
docker-compose --profile python up --build

# In another terminal, check database
docker exec -it mysql_database mysql -u dbuser -pdbpassword -e "SELECT * FROM network_project.user_tracking;"

# Stop and run C servers
docker-compose down
docker-compose --profile c up --build
```

### **Demo Individual Users**

```bash
# Show Hairiel only
docker-compose --profile hairiel up --build

# In presentation, show logs
docker-compose logs -f server_c1 client_c1
```

---

## 🔄 **Dynamic Control (Start/Stop During Runtime)**

### **Start Additional Users Without Stopping Others**

```bash
# Terminal 1: Start Afif
docker-compose --profile afif up --build

# Terminal 2: Add Syahmi (while Afif still running)
docker-compose --profile syahmi up -d

# Terminal 3: Add Irfan
docker-compose --profile irfan up -d
```

### **Stop Specific User**

```bash
# Stop only Afif's server and client
docker-compose stop server1 client1

# Restart them
docker-compose start server1 client1
```

### **Stop All But Keep Database & Dashboard**

```bash
# Stop all servers/clients
docker-compose stop server1 server2 server3 server_c1 server_c2 client1 client2 client3 client_c1 client_c2

# Database and web dashboard still running!
# Access http://localhost:8080 to see frozen points
```

---

## 💡 **Presentation Scenarios**

### **Scenario 1: Show Sequential Growth**

```bash
# Step 1: Start Afif only (0 points)
docker-compose --profile afif up -d

# Step 2: Wait 30 seconds, check dashboard
# Afif: 10 points, others: 0

# Step 3: Start Syahmi
docker-compose --profile syahmi up -d

# Step 4: Wait 30 seconds
# Afif: 20 points, Syahmi: 10 points, others: 0

# Step 5: Start everyone else
docker-compose --profile all up -d
```

### **Scenario 2: Python vs C Comparison**

```bash
# Start Python servers first
docker-compose --profile python up -d

# Let them run for 2 minutes (Python gets 40 points each)

# Then start C servers
docker-compose --profile c up -d

# Python users: 40+ points
# C users: 10 points (just started)
```

### **Scenario 3: Individual Demo**

```bash
# Terminal 1: Show logs
docker-compose --profile afif logs -f

# Terminal 2: Watch database
watch -n 2 'docker exec mysql_database mysql -u dbuser -pdbpassword -e "SELECT * FROM network_project.user_tracking;"'

# Terminal 3: Open dashboard
# http://localhost:8080
```

---

## 📝 **Quick Reference**

```bash
# ONE USER
docker-compose --profile afif up --build

# TWO USERS
docker-compose --profile afif --profile syahmi up --build

# ALL PYTHON
docker-compose --profile python up --build

# ALL C
docker-compose --profile c up --build

# EVERYONE
docker-compose --profile all up --build

# ADD USER DURING RUNTIME
docker-compose --profile <username> up -d

# STOP SPECIFIC USER
docker-compose stop server1 client1

# CHECK RUNNING CONTAINERS
docker-compose ps
```

---

## 🎬 **Best Presentation Flow**

```bash
# 1. Start with empty database
docker-compose down -v
docker-compose up database web_dashboard phpmyadmin -d

# 2. Show dashboard (all users at 0 points)
# http://localhost:8080

# 3. Start Afif only
docker-compose --profile afif up -d

# 4. Show logs and dashboard (Afif updating)
docker-compose logs -f server1

# 5. After 1 minute, start Syahmi
docker-compose --profile syahmi up -d

# 6. Show difference in points
# Afif: 20-30 points
# Syahmi: 10 points

# 7. Gradually add others
docker-compose --profile irfan up -d
docker-compose --profile hairiel up -d
docker-compose --profile faiz up -d

# 8. Final view: all users with different points!
```

**Note:** Database, web_dashboard, and phpmyadmin always run (no profiles) so you can always monitor the system! 🎯
