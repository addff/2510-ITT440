
# 🧪 Stress Testing Report – Moodle Website



**Name:** Sabrina Lokman  
**Student ID:** 202xxxxxxx  
**Course Code:** ITTxxx – Web Performance Testing  
**Tool Used:** Apache JMeter  
**Testing Type:** Stress Testing  
**Target Website:** Moodle (Demo Site)  
**Date:** November 2025  



## 🧰 1. Objective
The objective of this stress test is to evaluate the performance, stability, and breaking point of the Moodle website when subjected to a heavy number of concurrent users.  
This test aims to identify bottlenecks, response delays, and potential resource exhaustion when the server is under maximum stress.



## ⚙️ 2. Test Configuration
| Configuration | Description |
|----------------|--------------|
| **Tool** | Apache JMeter 5.6.3 |
| **Target** | Moodle Online Learning Management System |
| **Number of Threads (Users)** | 300 concurrent users |
| **Ramp-up Period** | 30 seconds |
| **Loop Count** | 1 |
| **Sampler Type** | HTTP Requests (Main page, Login page, Service page) |
| **Listeners Used** | Graph Results, View Results Tree, Summary Report, Response Time Graph |

---

## 🧩 3. Test Plan Setup
The test plan in JMeter consisted of:
- A **Thread Group** configured with 300 users, simulating high-traffic access to the Moodle website.  
- **Three HTTP Samplers** to simulate requests:
  1. Main Page (`https://moodle.com/`)
  2. Login Page (`https://moodle.com/login/`)
  3. Service Page (`https://moodle.com/services/`)
- Several **Listeners** were added to collect and visualize the test data, including:
  - View Results Tree
  - Summary Report
  - Graph Results
  - Response Time Graph

---

## 📊 4. Results Summary
| Page | Response Time (Start) | Response Time (End) | Observation |
|------|-----------------------|---------------------|--------------|
| **Main Page** | 1400 ms | 1100 ms | Stable performance |
| **Login Page** | 900 ms | 900 ms | Consistent and efficient |
| **Service Page** | 4100 ms | 5000 ms | Increased response time – potential bottleneck |

**Average Throughput:** Stable  
**Error Rate:** None detected  
**Performance Trend:** Gradual degradation under heavy load, especially on service page.

---

## 🧾 5. Sample Output Data

### 🖼️ a. Response Time Graph
![Response Time Graph](images/response_time_graph.png)

> The graph shows response times for each request during the 30-second stress test.  
> The main and login pages maintained stable performance, while the service page showed increasing response time.

---

### 🖼️ b. Summary Report Output
![Summary Report](images/summary_report.png)

> The summary report lists the average, min, max response times, number of samples, and throughput values.  
> The service page displayed the highest latency and reduced throughput under high user load.

---

### 🖼️ c. Graph Results Viewer
![Graph Results](images/graph_results.png)

> The Graph Results window demonstrates consistent trends with rising latency for the service page, confirming performance degradation under stress.

---

## 🔍 6. Analysis
The stress test revealed that the Moodle website could maintain stable performance for basic operations (main and login pages) even under 100 concurrent users.  
However, as load persisted, the service page experienced a noticeable increase in response time from **4.1 seconds to 5.0 seconds**, indicating resource exhaustion or server-side bottlenecks.

This behavior suggests that Moodle’s heavier modules require more server processing power or database optimization.

---

## 🧠 7. Interpretation
| Observation | Interpretation |
|--------------|----------------|
| Stable response for login & main pages | Server handles light operations efficiently |
| Gradual increase in service page response time | Indication of bottleneck and high CPU/DB usage |
| Performance drops after ~80 concurrent users | Server nearing its stress threshold |
| No major request failures | Application remained stable under stress |

---

## 💡 8. Recommendations
1. Optimize backend queries or add caching for the service module.  
2. Increase memory and CPU allocation for the web server.  
3. Implement load balancing for high-traffic environments.  
4. Regularly perform stress and load tests to track performance trends.  

---

## 📈 9. Conclusion
The Moodle demo website performed reliably under moderate load but showed signs of degradation as the number of users increased.  
Response times remained stable for lighter requests but rose significantly for resource-intensive operations, confirming a performance bottleneck under stress conditions.  

The test successfully identified the website’s performance limit and provided insights for future optimization and scaling strategies.

---

## 👩‍💻 10. Version Verification
To confirm JMeter installation and version:

```bash
"C:\Program Files\apache-jmeter-5.6.3\bin\jmeter.bat" --version
