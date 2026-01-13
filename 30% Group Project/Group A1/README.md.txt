# Docker Socket-Based Client–Server System
#Source Code
# 🚀 ITT440 Network Programming Project
## Docker-Based Distributed Client-Server System with Real-Time Web Dashboard

## 📖 About

This project is a comprehensive demonstration of **distributed systems**, **socket programming**, and **containerization** developed for the ITT440 Network Programming course. It showcases a multi-container architecture where Python and C socket servers communicate with clients through a MySQL database, all orchestrated with Docker Compose and monitored through a real-time Flask web dashboard.

### 🎯 Project Objectives
- Implement client-server architecture using TCP socket programming
- Demonstrate Docker container networking and orchestration
- Integrate multiple programming languages (Python & C)
- Create real-time data visualization and monitoring
- Show database integration in distributed systems

---

## ✨ Features

### 🖥️ **Multi-Language Socket Servers**
- **3 Python Servers** managing individual users (Afif, Syahmi, Irfan)
- **2 C Servers** managing individual users (Hairiel, Faiz)
- TCP socket communication on ports 5001-5003 (Python) and 6001-6002 (C)
- Auto-update database every 30 seconds with incremental points

### 📱 **Socket Clients**
- **5 Dedicated Clients** (3 Python + 2 C)
- Request user data every 10 seconds
- Auto-reconnect on connection failure
- Real-time response display

### 🌐 **Web Dashboard**
- **Real-time monitoring** with auto-refresh (5s intervals)
- **Interactive charts** (Line chart for growth, Doughnut chart for distribution)
- **Statistics cards** (Total, Average, Max, Min points)
- **Server status indicators**
- **Professional Bootstrap UI** with animations
- **Responsive design** for all devices

### 🗄️ **Database Management**
- MySQL 8.0 with persistent storage
- phpMyAdmin web interface on port 8081
- Centralized user tracking table
- Automatic timestamp updates

### 🎮 **User Control System**
- **Docker Compose Profiles** for selective container startup
- Run individual users, groups, or all at once
- Perfect for demonstrations and testing

### 🔌 **REST API**
- `/api/users` - Get all users data
- `/api/users/{username}` - Get specific user
- `/api/servers` - Get server information
- `/api/stats` - Get system statistics

---

## 🛠️ Technologies

### **Backend**
- Python 3.9 (Socket Programming, Flask API)
- C (Socket Programming with POSIX)
- MySQL 8.0 (Database)
- mysql-connector-python (Python DB Driver)

### **Frontend**
- HTML5, CSS3, JavaScript
- Bootstrap 5.3 (UI Framework)
- Chart.js 4.4 (Data Visualization)
- AJAX (Real-time updates)

### **DevOps**
- Docker 20+ (Containerization)
- Docker Compose 3.8 (Orchestration)
- Docker Networks (Container communication)

### **Tools**
- phpMyAdmin (Database Management)
- Git (Version Control)

---

## 🏗️ Architecture

```
┌────────────────────────────────────────────────────────────────────────┐
│                       DOCKER NETWORK (project_network)                 │
│                                                                          │
│  ┌──────────────┐         ┌──────────────┐         ┌──────────────┐   │
│  │   Browser    │────────>│ Web Dashboard│────────>│   MySQL DB   │   │
│  │ localhost:   │         │  Flask API   │         │ user_tracking│   │
│  │   8080       │         │  Port 8080   │         │   5 users    │   │
│  └──────────────┘         └──────────────┘         └──────┬───────┘   │
│                                                             │           │
│  ┌──────────────┐         ┌──────────────┐                │           │
│  │  phpMyAdmin  │────────>│              │<───────────────┘           │
│  │ localhost:   │         │              │                             │
│  │   8081       │         │              │                             │
│  └──────────────┘         │              │                             │
│                           │              │                             │
│  PYTHON SERVERS (3)       │   Database   │     C SERVERS (2)          │
│  ┌──────────────┐        │              │     ┌──────────────┐       │
│  │ server1:5001 │────────┤              │─────│server_c1:6001│       │
│  │   (Afif)     │        │              │     │  (Hairiel)   │       │
│  └──────────────┘        │              │     └──────────────┘       │
│         ▲                │              │            ▲                │
│         │                │              │            │                │
│  ┌──────────────┐        │              │     ┌──────────────┐       │
│  │ server2:5002 │────────┤              │─────│server_c2:6002│       │
│  │  (Syahmi)    │        │              │     │   (Faiz)     │       │
│  └──────────────┘        │              │     └──────────────┘       │
│         ▲                │              │            ▲                │
│         │                └──────────────┘            │                │
│  ┌──────────────┐                                   │                │
│  │ server3:5003 │                                   │                │
│  │  (Irfan)     │                                   │                │
│  └──────────────┘                                   │                │
│         ▲                                           │                │
│         │                                           │                │
│  PYTHON CLIENTS (3)                    C CLIENTS (2)                 │
│  client1  client2  client3            client_c1  client_c2           │
│                                                                        │
└────────────────────────────────────────────────────────────────────────┘
```

### **Communication Flow**
1. **Servers** connect to MySQL database
2. **Background threads** update user points every 30 seconds
3. **Clients** send TCP requests to servers every 10 seconds
4. **Servers** query database and respond to clients
5. **Web Dashboard** fetches data via REST API every 5 seconds
6. **Users** monitor real-time updates through browser

---

## 📁 Project Structure

```
Docker/
├── 📄 docker-compose.yml           # Container orchestration
├── 📄 README.md                    # Project documentation
├── 📄 USER_CONTROL.md              # User control guide
│
├── 📂 Database/
│   └── init.sql                    # Database schema & initial data
│
├── 📂 Server_Py/                   # Python Servers
│   ├── Dockerfile
│   ├── requirements.txt
│   ├── server1.py                  # Manages Afif
│   ├── server2.py                  # Manages Syahmi
│   └── server3.py                  # Manages Irfan
│
├── 📂 Server_C/                    # C Servers
│   ├── Dockerfile
│   ├── server1.c                   # Manages Hairiel
│   └── server2.c                   # Manages Faiz
│
├── 📂 Client_Py/                   # Python Clients
│   ├── Dockerfile
│   ├── requirements.txt
│   ├── client1.py                  # Connects to server1
│   ├── client2.py                  # Connects to server2
│   └── client3.py                  # Connects to server3
│
├── 📂 Client_C/                    # C Clients
│   ├── Dockerfile
│   ├── client1.c                   # Connects to server_c1
│   └── client2.c                   # Connects to server_c2
│
└── 📂 WebApp/                      # Flask Dashboard & API
    ├── Dockerfile
    ├── requirements.txt
    ├── app.py                      # Flask application
    ├── templates/
    │   └── dashboard.html          # Dashboard UI
    └── static/
        ├── css/
        │   └── style.css
        └── js/
            └── dashboard.js        # Real-time updates
```

---

## 📦 Prerequisites

- **Docker Desktop** (20.10 or higher)
- **Docker Compose** (3.8 or higher)
- **Git** (for cloning)
- **Web Browser** (Chrome, Firefox, Edge)

---

## 📥 Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/itt440-network-programming.git

# Navigate to project directory
cd itt440-network-programming

# Verify Docker is running
docker --version
docker-compose --version
```

---

## 🚀 Quick Start

### **Option 1: Run Everything**

```bash
# Start all containers (5 servers + 5 clients + database + dashboard)
docker-compose --profile all up --build
```

### **Option 2: Run Specific Users**

```bash
# Run only Afif and Syahmi
docker-compose --profile afif --profile syahmi up --build
```

### **Access Interfaces**

Once running, open your browser:

- **🌐 Web Dashboard:** http://localhost:8080
- **🗄️ phpMyAdmin:** http://localhost:8081
  - Username: `dbuser`
  - Password: `dbpassword`

---

## 📚 Usage

### **Basic Commands**

```bash
# Start all containers
docker-compose --profile all up --build

# Start in detached mode (background)
docker-compose --profile all up -d

# Stop all containers
docker-compose down

# Stop and remove all data (fresh start)
docker-compose down -v

# View logs (all containers)
docker-compose logs -f

# View logs (specific container)
docker-compose logs -f server1
docker-compose logs -f web_dashboard

# Check running containers
docker-compose ps

# Restart specific service
docker-compose restart server1
```

### **Database Access**

```bash
# Access MySQL CLI
docker exec -it mysql_database mysql -u dbuser -pdbpassword network_project

# Quick query
docker exec -it mysql_database mysql -u dbuser -pdbpassword -e "SELECT * FROM network_project.user_tracking ORDER BY points DESC;"

# Export database
docker exec mysql_database mysqldump -u dbuser -pdbpassword network_project > backup.sql
```

---

## 🎮 User Control

Control which users run to demonstrate different scenarios:

### **Run Individual Users**

```bash
# Start only Afif
docker-compose --profile afif up -d

# Start only Python users
docker-compose --profile python up -d

# Start only C users  
docker-compose --profile c up -d
```

### **Sequential Start (Show Points Difference)**

```bash
# Terminal 1: Start Afif first
docker-compose --profile afif up -d

# Wait 1-2 minutes (Afif accumulates 20-40 points)

# Terminal 2: Add Syahmi
docker-compose --profile syahmi up -d

# Result: Afif has more points than Syahmi!
```

For detailed control options, see [USER_CONTROL.md](USER_CONTROL.md)

---

## 🔌 REST API

### **Endpoints**

#### Get All Users
```http
GET http://localhost:8080/api/users
```

**Response:**
```json
{
  "success": true,
  "data": [
    {
      "user": "Afif",
      "points": 120,
      "datetime_stamp": "2026-01-12 14:30:00"
    },
    ...
  ],
  "timestamp": "2026-01-12 14:30:05"
}
```

#### Get Specific User
```http
GET http://localhost:8080/api/users/Afif
```

#### Get Server Information
```http
GET http://localhost:8080/api/servers
```

#### Get Statistics
```http
GET http://localhost:8080/api/stats
```

**Response:**
```json
{
  "success": true,
  "data": {
    "total_points": 450,
    "avg_points": 90.0,
    "max_points": 120,
    "min_points": 70
  }
}
```

---

## 📊 Monitoring

### **Web Dashboard Features**

- **User Table**: Real-time display of all 5 users with points and timestamps
- **Statistics Cards**: Total, Average, Max, Min points
- **Line Chart**: Points growth over time (last 20 updates)
- **Doughnut Chart**: Points distribution across users
- **Server Info**: Status and configuration of all servers
- **Auto-refresh**: Updates every 5 seconds automatically

### **Log Monitoring**

```bash
# All containers
docker-compose logs -f

# Specific patterns
docker-compose logs -f | grep "Updated"
docker-compose logs -f | grep "Points"
```

---

## 🐛 Troubleshooting

### **Port Already in Use**

```bash
# Check what's using the port
netstat -ano | findstr :8080

# Kill the process (Windows)
taskkill /PID <PID_NUMBER> /F

# Kill the process (Linux/Mac)
kill -9 <PID_NUMBER>
```

### **Database Connection Error**

```bash
# Check database health
docker-compose ps

# Restart database
docker-compose restart database

# View database logs
docker-compose logs database
```

### **Container Won't Start**

```bash
# Clean everything
docker-compose down -v
docker system prune -f

# Rebuild from scratch
docker-compose --profile all up --build
```

### **YAML Syntax Error**

```bash
# Validate docker-compose.yml
docker-compose config
```
