# 🧪 Apache JMeter Load Testing on Laravel 10 Web Application

### Prepared for: MR. SHAHADAN BIN SAAD

**Name: MOHAMMED ZUHAYR BIN MOHD ZAKI**  

**Student ID: 2025163001**  

**Group: M3CDCS2554C**  

**Course: ITT440 - Network Programming**

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
- **Thread Group:** 100 Virtual Users  
- **Ramp-Up Time:** 60 seconds  
- **Loop Count:** 10 iterations  
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
5. Run the test in **non-GUI mode** for performance
