# 🧪 Apache JMeter Load Testing on Laravel 10 Web Application
[**VIDEO LINK**](https://drive.google.com/drive/folders/1S-7GMCLzYHVUQN-1Y1Ny6w-cYDLO6_OT?usp=sharing)

### Prepared for: MR. SHAHADAN BIN SAAD

**Name: MOHAMMED ZUHAYR BIN MOHD ZAKI**  

**Student ID: 2025163001**  

**Group: M3CDCS2554C**  

**Course: ITT440 (Network Programming)**

## 📘 Overview
This project demonstrates a **Load Test** conducted using **Apache JMeter** on a **self-hosted Laravel 10 web application**.  
The objective is to evaluate the application’s performance under expected user traffic which are identifying average response times, throughput, and potential bottlenecks.

## ❔What is load testing?

- Load testing is a type of performance testing
- The testing determines a system's performance according to real life conditions
- It confirms if the present infrastructure is enough to run the application

---  

## ⚙️ Environment Setup

### **System Configuration**
- **Operating System:** Windows 11  
- **Web Framework:** Laravel 10 (PHP 8.2)  
- **Database:** MySQL 8.0  
- **Web Server:** Apache (Localhost running on Laragon)  
- **Testing Tool:** Apache JMeter 5.6.3  

### **Pre-Requisites**
1. Laravel app is running locally (e.g., `http://127.0.0.1:8000`)
2. Apache JMeter is installed → [Download JMeter](https://jmeter.apache.org/download_jmeter.cgi)
3. Java 8 or newer installed and configured in PATH


---

## 🧩 Test Objective

- Measure **response time** and **throughput** under expected user load.
- Identify any **performance degradation** or **error rates** under concurrent traffic.
- Provide actionable insight into Laravel app scalability.

---

## 🌐 Web pages that are tested

**Laravel default page**

<img width="1920" height="1080" alt="Screenshot (58)" src="https://github.com/user-attachments/assets/d454d8fd-6230-4f81-b327-09e776cbe0cf" />

**Home page**

<img width="1920" height="1080" alt="Screenshot (59)" src="https://github.com/user-attachments/assets/164eddd9-82bc-4407-a210-006ec7bed529" />

**Form page**

<img width="1920" height="1080" alt="Screenshot (60)" src="https://github.com/user-attachments/assets/e48e6e47-8132-4bad-a4d6-30670fa06599" />

---

## 🧱 Test Design

### **Scenario**
Users perform a typical workflow:
1. Go to default Laravel homepage  
2. Navigate to homepage  
3. Navigate to form  

### **Endpoints Tested**
| Endpoint | Method | Description |
|-----------|---------|-------------|
| `/` | GET | Default Laravel page |
| `/home` | GET | Homepage |
| `/expenses/create` | GET | Form page |

### **JMeter Components**
- **Thread Group:** 50 Virtual Users
> I limited to 50 users since I tested it on a locally hosted website  
- **Ramp-Up Time:** 30 seconds  
- **Loop Count:** 5 iterations  
- **HTTP Request Sampler:** For each endpoint  
- **Listener:** Summary Report, View Results Tree  
- **HTML Dashboard Report:** For visual analytics  

---

## 🚀 Execution Steps

1. Launch JMeter (GUI mode for setup)
2. Create a new **Test Plan** and add:
   - Thread Group  
   - HTTP Requests for each Laravel route  
   - Listeners for data visualization  
3. Configure Thread Group:
   - Users: `100`
   - Ramp-Up: `60 seconds`
   - Loop Count: `10`
4. Save the .jmx file
5. Run the test in **non-GUI mode** for performance (make sure the directory has been changed in the terminal):
   ```
   jmeter -n -t [jmx file] -l [results file] -e -o report

---

## Results

> The results may vary from testing on actual pre-existing websites since the environment of hosting differs.


### <ins>Throughput</ins> 

### Hits Per Second

<img width="1635" height="520" alt="Hits Per Second" src="https://github.com/user-attachments/assets/488edc39-db5d-42df-a4e8-ec3a860133b5" />

### Codes Per Second

<img width="1635" height="524" alt="Codes Per Second" src="https://github.com/user-attachments/assets/cc376340-ea91-40b9-b15a-77075501cb71" />

### Transactions Per Second

<img width="1634" height="522" alt="Transactions Per Second" src="https://github.com/user-attachments/assets/d9ecd476-c055-480c-a140-4b1455555d1c" />

### Total Transactions Per Second

<img width="1637" height="522" alt="Total Transactions Per Second" src="https://github.com/user-attachments/assets/2f4c8062-1b54-477d-9476-8fe1f6ff9bfc" />


### Response Time vs Request

<img width="1638" height="524" alt="Response Time vs Request" src="https://github.com/user-attachments/assets/e2a17721-383f-46eb-9450-78208bf33bab" />

### Latency vs Request

<img width="1639" height="517" alt="Latency vs Request" src="https://github.com/user-attachments/assets/d6cfd96c-a1ee-4802-94bc-b362018364ff" />


### <ins>Response Times</ins>

### Response Time Percentiles

<img width="1640" height="523" alt="Response Time Percentiles" src="https://github.com/user-attachments/assets/ff33d637-c870-4154-9ba8-af362d5875a2" />


### Response Time Overview

<img width="1640" height="523" alt="Response Time Overview" src="https://github.com/user-attachments/assets/07a07ee1-f441-4ae1-b3ec-9feaa72032f6" />

### Time Vs Threads

<img width="1636" height="525" alt="Time vs Threads" src="https://github.com/user-attachments/assets/da92f9ec-b394-45c1-a14e-579c7ec059f4" />

### Response Time Distribution

<img width="1645" height="530" alt="Response Time Distribution" src="https://github.com/user-attachments/assets/88760593-af6d-45a3-a1c8-c267148e4edf" />

## Future Recommendations

1. The middleware logic in the Laravel can be optimised for efficiency
2. The server needs to have backup in case of downtime
3. Database queries should be optimized for efficiency and security

---
❤️Thank you © MOHAMMED ZUHAYR | 2025163001 | ITT440 | M3CS2554C | 2510

   
