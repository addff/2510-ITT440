# 🧪 Spike Testing on Open Library Website using Apache JMeter

### Name: Juratu binti Abdullah  
### Matric Number: 2023268582  
### Group Class: M3CS2554C  

---

## Spike Testing Explanation
Spike Testing is a type of performance testing that evaluates a system's behavior under **sudden, extreme increases in load**. Unlike gradual load testing, spike testing simulates abrupt traffic surges to determine:

- Whether the system can handle sudden spikes without crashing.
- How response time and error rates change under peak load.
- How quickly the system recovers after the spike.

---

## 📌 Objective
The objective of this project is to perform a **Spike Test** on the web application [OpenLibrary.org](https://openlibrary.org) using **Apache JMeter**.  

The goal is to evaluate how the system responds to a **sudden surge in user load** and whether it maintains stable performance under extreme conditions.

---

## ⚙️ Tool Selection: Apache JMeter
![Apache JMeter logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRfptUW92QFvFjgtP3p9AtGEIX6bsuSL7-YgA&s)

**Reasons for choosing JMeter:**

- Open-source and widely used for performance testing.
- Supports multiple protocols: HTTP, HTTPS, WebSocket.
- Allows simulation of multiple concurrent users.
- Provides detailed reports and visual graphs.
- Free and accessible for academic projects.

---

## 🌐 Target Web Application: OpenLibrary.org
![OpenLibrary.org logo](https://blog.openlibrary.org/files/2023/04/cropped-cropped-openlibrary-header.png)  
![OpenLibrary.org main page](https://upload.wikimedia.org/wikipedia/commons/5/51/OpenLibrarypage.jpg)

[OpenLibrary.org](https://openlibrary.org) is a **public, non-commercial website** that allows users to access and borrow digital books. It provides an API and a simple web interface suitable for HTTP performance testing.

**Hypothesis:**  
> The OpenLibrary.org website will remain stable under a sudden spike of 100 virtual users, with minimal errors and acceptable response time.

---

## 🧩 Test Environment Setup

**Tool:** Apache JMeter 5.6.3  
**Test Type:** Spike Test  

**System Specifications:**
- CPU: Intel Core i5  
- RAM: 8 GB  
- OS: Windows 11  
- Internet: 100 Mbps stable connection  

**Test Plan Configuration:**

| Component       | Configuration                        |
|-----------------|--------------------------------------|
| Thread Group    | 100 users                             |
| Ramp-Up Period  | 5 seconds                             |
| Loop Count      | 1                                     |
| Target URL      | https://openlibrary.org               |
| HTTP Request    | GET request to homepage               |
| Listeners       | Summary Report, View Result Tree, View Results in Table |

---

## 🚀 Test Execution Steps

| Step | Description |
|------|-------------|
| 1    | Launch Apache JMeter and create a new test plan. |
| 2    | Add a **Thread Group** and configure 100 users with a 5-second ramp-up period. |
| 3    | Add **HTTP Request Sampler** targeting `https://openlibrary.org`. |
| 4    | Add **Listeners** (Summary Report, View Result Tree, View Results in Table). |
| 5    | Save and execute the test plan. |
| 6    | Observe response times, throughput, and error rates during the spike. |
| 7    | Export reports and analyze results. |

---

## 📊 Test Results & Analysis

### Result Graphs, Tables, and Charts
- **Summary Report:**  
![Summary Report](https://github.com/user-attachments/assets/d48aeb03-9529-425f-9f82-f0275d84ba21)

- **View Result Tree:**  
![View Result Tree](https://github.com/user-attachments/assets/fbf8350a-dcae-47b8-a194-de2b4a19563f)

- **View Results in Table:**  
![View Results in Table](https://github.com/user-attachments/assets/3e5fa43b-201b-4f3e-aa8d-e2d53daa8836)

---

### Key Metrics

| Metric                   | Observation |
|---------------------------|------------|
| Total Samples             | 100        |
| Average Response Time     | ~40 seconds|
| Minimum Response Time     | 1.4 seconds|
| Maximum Response Time     | ~86 seconds|
| Error Rate                | 0%         |
| Throughput               | ~1.1 requests/sec |
| Success Rate             | 100%       |
| Warnings                  | 2 minor warnings (no errors) |

**Analysis:**
- All requests were successful with HTTP code 200.  
- Average load time per request: ~1.4 seconds.  
- Temporary delays occurred for some requests (up to 86 seconds) due to simultaneous user access.  
- Minor warnings did not impact the test success.  
- Throughput of 1.1 requests/sec shows the server managed the spike steadily.

---

## 🧠 Interpretation of Results
The **spike test** demonstrates that OpenLibrary.org can handle sudden surges of 100 concurrent users.  
Temporary increases in response time are expected under peak load, but the system remains **stable and resilient**.

---

## 💡 Recommendations
1. Implement **load balancing** to distribute traffic evenly.  
2. Use **caching/CDN** to reduce server load.  
3. Monitor **server memory and CPU usage** during peak periods.  
4. Introduce **autoscaling** to dynamically handle spikes.

---

## 🧾 Conclusion
The spike testing using Apache JMeter demonstrated that **OpenLibrary.org** is **robust and scalable** under sudden traffic surges.  
Temporary response delays were observed but all requests were successfully processed with minimal issues.

---

## 🎥 Video Demonstration
A step-by-step execution and explanation of the JMeter test plan have been recorded and uploaded to YouTube:  

[![Watch the video](https://img.youtube.com/vi/Ka2cLhAaQrU/0.jpg)](https://youtu.be/Ka2cLhAaQrU?feature=shared)  

Click the thumbnail or link above to watch the demonstration.

---
