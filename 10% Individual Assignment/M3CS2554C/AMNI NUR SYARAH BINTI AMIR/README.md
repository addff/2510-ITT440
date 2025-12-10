# AMNI NUR SYARAH BINTI AMIR
# 2025759181
---
# What is Load Testing?

Load testing is a type of performance testing used to evaluate how a system behaves under a specific amount of user demand. It measures how well a website, application, or server performs when multiple users access it simultaneously.

To conclude, load testing simulates real-world traffic to determine how many users your system can handle before it slows down or fails.

---

## Why Do We Need Load Testing?

Load testing is essential for ensuring the stability and reliability of web applications. Without it, websites may crash or become unresponsive during high-traffic situations.

**Key reasons include:**
- 🧠 **Identify performance limits** — find out the maximum number of users the system can handle.
- ⚙️ **Detect bottlenecks** — locate which part of the system (CPU, memory, or network) causes slow performance.
- 💡 **Improve user experience** — ensure consistent response times even during peak loads.
- 💼 **Ensure readiness for production** — test before deployment to avoid downtime or service interruptions.

---

## What Does Load Testing Measure?

A load test typically measures several key performance indicators (KPIs), including:

- **Response Time** – how long it takes for the server to respond to a request.
- **Throughput** – the number of requests the server can process per second.
- **Success Rate / Status Code** – how many requests are successful versus failed.
- **Error Rate** – the percentage of failed requests during heavy load.
- **Server Resource Usage** – CPU, memory, and network utilization.

---

## ✅ Objective

- Evaluate how the server responds when multiple users access the website simultaneously.
- Measure key performance metrics such as response time, throughput, and error rate.
- Identify potential performance bottlenecks in the system.
- Observe server resource utilization (CPU, memory, and network) during load conditions.

---

## 🛠️ Tools Used

### FreeBSD
FreeBSD is a free and open-source Unix-like operating system used for servers and networking.  
It provides high performance, stability, and security, making it suitable for hosting and testing environments.

### k6
k6 is a modern load testing tool for developers.  
It is used to simulate virtual users and test how web applications and APIs perform under load.  
k6 provides metrics like response time, request rate, and error percentage.

### MobaXterm
MobaXterm is an all-in-one remote computing tool for Windows.  
It allows users to connect to remote servers via SSH and includes a built-in terminal, file manager, and X11 server for GUI applications.

### WordPress
WordPress used to create and manage websites.  
In this project, it acts as the web application being tested under simulated user load to observe the server performance.

### 🧪 Test 1: 10 VUs with 50s Duration

**Command:**
*export const options = {
  vus: 10,
  duration: '30s',
};*

**Result:**  
Successful.

**Output:**  
K6 test completed with 100 iterations, 0 failed requests, and consistent response times. 

*Average response time:* 4.24s  
*Min:* 2.36s | *Max:* 5.45s | *p(90):* 5.04s | *p(95):* 5.25s  
*Data received:* 1.22 MB | *Data sent:* 1.06 kB

System performance monitored using `btop` during execution.  
CPU usage peaked moderately, RAM usage remained stable, and no bottlenecks were observed.

**Image:**
![K6 test output screenshot](https://raw.githubusercontent.com/AI75-25/2510-ITT440/79bf2f34b96e06a4fee6b0852dcc45c78bdba2c1/ss-test1.png)


### 🧪 Test 2: 100 VUs with Staged Duration

**Command:**
*export const options = {
  stages: [
    { duration: '10s', target: 10 },   
    { duration: '20s', target: 50 },   
    { duration: '20s', target: 100 },  
    { duration: '10s', target: 0 },    
  ],
};*

**Result:**  
Partially successful.

**Output:** 
K6 test executed with ramping stages from 10 to 100 virtual users. Total iterations: 196 Checks passed: 82.83% (164 out of 198) Checks failed: 17.17% (34 out of 198) Status 200: 82% success rate

*Average response time:* 19.53s  
*Min:* 12.01s | *Max:* 60.00s | *p(90):* 59.99s | *p(95):* 60.00s  

**Image:**
![K6 test output screenshot](https://raw.githubusercontent.com/AI75-25/2510-ITT440/79bf2f34b96e06a4fee6b0852dcc45c78bdba2c1/Screenshot%202025-11-09%20181734.png)

## 📋 Summary

To summarize, load testing helps determine how a system performs under real-world user demand. It simulates multiple users accessing a website or application at the same time to measure key performance metrics such as response time, throughput, and error rate.

When the number of users increases, the system may begin to slow down, response times become longer, throughput may decrease, and errors can occur if the server reaches its capacity. This behavior helps us to identify the exact point where performance degradation starts.

In this project, tools like FreeBSD, k6, MobaXterm and WordPress were used to create a controlled test environment for observing system behavior under load. The results provide insight into performance bottlenecks, system stability and resource usage efficiency.

To conclude, load testing is an important process to ensure that a web application  
remains stable, responsive and scalable even as user traffic grows.

## 🎥 Video:
(https://youtu.be/imcvgSbj9X0?si=nyoeNcgskXAI3FkC)
*Data received:** 20 MB | *Data sent:* 17 kB

