<div align="center">
<h1 style="font-size:40px; font-weight:bold;">🧬 WEB PERFORMANCE TESTING 🧬</h1>
</div>

**Name:** Anis Nursabrina Lokman  
**Student ID:** 2025900087  
**Group:** 4C
**Course Code:** ITT440 - Network Programming  
**Tool Used:** Apache JMeter  
**Testing Type:** Stress Testing  
**Target Website:** Moodle (Online Learning Management System)
 


## 😵‍💫 What is Stress Testing?
Stress test is the process of gradually increasing user load beyond expected limits to evaluate how a system performs under peak or excessive pressure. It helps identify the maximum capacity the application can handle before performance degrades or failures occur.

## 🧰 Objective
The objective of this stress test is to evaluate the performance, stability, and breaking point of the Moodle website when subjected to a heavy number of concurrent users.  
This test aims to identify bottlenecks, response delays, and potential resource exhaustion when the server is under maximum stress.


## ⚙️ Test Configuration And Methadology
<p align="center">
  <img src="./about.png" width="600">
</p>

<div align="center">

| **Configuration** | **Description** |
|--------------------|-----------------|
| **Tool** | Apache JMeter 5.6.3 |
| **Target** | Moodle |
| **Number of Threads (Users)** | 300 for each page |
| **Ramp-up Period** | 30 seconds |
| **Loop Count** | 1 |
| **Sampler Type** | HTTP Requests (Main page, Login page, Service page) |
| **Listeners Used** | Graph Results, Summary Report, Response Time Graph |

</div>


---

## 🧩 Test Plan Setup
The test plan in JMeter consisted of:
- A **Thread Group** configured with 300 users, simulating high-traffic access to the Moodle website.  
- **Three HTTP Samplers** to simulate requests:
  1. Main Page (`https://moodle.com/`)
  2. Login Page (`https://moodle.com/login/`)
  3. Service Page (`https://moodle.com/services/`)
- Several **Listeners** were added to collect and visualize the test data, including:
  - Summary Report
  - Graph Results
  - Response Time Graph

---

## ✍🏿 Sample Output Data

### 🖼️ Summary Report Output
![Summary Report](./Summaryreport.png)

> The summary report lists the average, min, max response times, number of samples, and throughput values.  
> The service page displayed the highest latency and reduced throughput under high user load.

---

### 📈 Graph Results Viewer
![Graph Results](./graph1.png)

> The Graph Results window demonstrates consistent trends with rising latency for the service page, confirming performance degradation under stress

---

### ⏱️ Response Time Graph
![Response Time Graph](./graph.png)

> The graph shows response times for each request during the 30-second stress test.  
> The main page (black line) response time showing moderate stability.
> The login page (red line) response time suggests good performance, efficient and lightweight.


---

## 📝 Results Summary
| Page | Minimum Response Time | Maximum Response Time | Observation |
|------|-----------------------|---------------------|--------------|
| **Main Page** | ~900 ms | ~1400 ms | Stable performance |
| **Login Page** | ~800 ms | ~900 ms | Consistent and efficient |
| **Service Page** | ~4200 ms | ~5900 ms | Increased response time – potential bottleneck |

---

## 🧠 Interpretation from summary report output
| Metric | Observation |
|--------------|----------------|
| Bottleneck | Service page is the slowest-performing page under load (Avg 5276 ms, Max 6683 ms) |
| Best Performance | Login page are the fast and consistent even during stress (Avg 818 ms) |
| System Stability | 0% error rate the server handled all request succesfully |
| Throughput Trend | Stable overall handling 13.5 request/sec (total) |
| Performance Issuse | High variation on Service Page |

---

## 💡 Recommendations for improvement
The Moodle website can better handle higher loads with reduced response time by improving caching, optimizing the database, and upgrading hardware resource. These will optimise the prevention of bottlenecks and ensurea consistent user experience even heavy traffic periods.  

---


## 🧠 **Conclusion**

Overall, the results highlight that **Moodle can handle moderate loads effectively**, but **performance degradation occurs** when the number of concurrent users increases sharply.  
Optimization efforts should focus on **server tuning, caching, and database efficiency** to enhance scalability and reduce latency during peak usage.

 **In conclusion**, the test successfully identified performance limits, bottlenecks, and improvement areas for Moodle, making it a useful reference for future optimization and capacity planning.

---

## 👩‍💻 Demonstration Video
https://youtu.be/Ba0_LifqMcQ?si=MthQu-5M4zZnw0OU



