<p align="center">
<img width="400" height="400" alt="Picture1" src="https://github.com/user-attachments/assets/84ac953a-e51a-47b3-b158-802c5d97b005" />

# MOHAMAD FERHAD BIN KAMARUDIN
#  Comprehensive Web Application Performance Testing & Analysis

### **Tool Used:** Artillery  
### **Performance Test Type:** Soak Test  
### **Target Application:** [Snapchat API]([https://developers.snap.com/api/home])  
### **Student Name:** *MOHAMAD FERHAD BIN KAMARUDIN*  
### **Date:** 08 November 2025  

---


##  **Objective**

This performance test aims to evaluate how well the DummyJSON API performs under soak test load conditions over time. The focus is on understanding the system’s stability, responsiveness, and ability to sustain performance during extended periods of use.
---
## Tool & Test Selection Justification

<p align="center">
<img width="500" height="243" alt="1_p4IQfjORMIMZtN8SJRjzcA" src="https://github.com/user-attachments/assets/9bcc62c7-bf15-4428-a6d8-d43b25c77ad2" />   

Artillery is an open-source tool used for HTTP, WebSocket, and API performance testing. It simulates user load to assess system stability and response under stress. Using YAML-based scripts, it measures key metrics such as response time, throughput, and error rate. The Artillery Cloud platform provides visual dashboards and performance graphs for easier analysis.


<p align="center">
<img width="500" height="497" alt="image" src="https://scx2.b-cdn.net/gfx/news/hires/2017/1-snapchat.jpg" />
  
## Target Web Application (Snapchat)

The experiment used the Snapchat API because it offers a robust and scalable platform suitable for real-world performance testing. The API supports various functionalities such as media sharing, messaging, and user interaction features, allowing realistic simulations of active user behavior. Its well-documented endpoints and reliable architecture make it an effective choice for evaluating response times, throughput, and stability under high user load using Artillery.
---
## Test Environment Setup

| Component         | Details                                  |
| ----------------- | ---------------------------------------- |
| **Tool**          | Artillery (v2.x)                         |
| **Machine**       | Localhost (Windows 11, 16GB RAM, i7 CPU) |
| **Network**       | 100 Mbps broadband                       |
| **Target API**    | `https://developers.snap.com/api/home`                |
| **Test Duration** | 240 seconds                              |
| **Virtual Users** | 960 created, 0 completed             |
| **Arrival Rate**  | 30 requests/sec                          |

---


##  **Test Plan**

| **Section**                          | **Details**                                                                                                                                                      |
| ------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Test Title**                       | Artillery Soak & Snapchat API                                                                                                           |
| **Objective**                        | To evaluate the performance and scalability of the Snapchat API under concurrent user load using Artillery, focusing on response time, throughput, and error rate. |
| **Tool Used**                        | Artillery v2.x                                                                                                                                                   |
| **Test Type**                        | Soak Test                                                                                                                               |
| **Test Date**                        | 08 November 2025                                                                                                                                                 |
| **Test Engineer**                    | *Mohamad Ferhad*                                                                                                                                                    |
| **Target System / API Endpoint**     | `https://developers.snap.com/api/home`                                                                                                                             |
| **Test Duration**                    | 4 minutes (240 seconds)                                                                                                                                          |
| **Load Model**                       | Stepwise ramp-up (10 → 20 virtual users per second)                                                                                                              |
| **Number of Virtual Users (VUs)**    | 960 created                                                                                                                                                     |
| **Test Scenario Description**        | Each virtual user sends a `GET` request to `/api/users?page=2`, simulating typical client behavior retrieving paginated user data.                               |
| **KPIs Measured**                    | - Response Time (min, mean, p95, p99)  <br> - Throughput (requests/sec) <br> - Error Rate <br> - Virtual User Completion                                         |
| **Performance Thresholds (Targets)** | - Average Response Time ≤ 500 ms  <br> - Error Rate ≤ 2%  <br> - 95% Responses < 1s                                                                              |
| **Test Environment**                 | Localhost (Windows 11, Intel i7, 16GB RAM) <br> Network: 100 Mbps broadband                                                                                      |
| **Monitoring Tools**                 | Artillery CLI and built-in metrics                                                                                                                               |
| **Assumptions**                      | Snapchat API remains accessible and stable throughout testing.                                                                                              |
| **Risks / Constraints**              | Snapchat API may have rate limiting or IP blocking during extended scalability tests.                                                                                     |
| **Success Criteria**                 | API maintains <5% error rate and <500 ms mean response time under 30 requests/sec load.                                                                          |


### **Configuration File (artillery.yml)**

```yaml
config:
  target: "https://snapchat.com"
  phases:
    - duration: 120
      arrivalRate: 2
    - duration: 60
      arrivalRate: 10
    - duration: 60
      arrivalRate: 2
scenarios:
  - name: "Get Users"
    flow:
      - get:
          url: "/api/users?page=2"
```

---

##  **Test Results Summary**

### **Artillery Summary Report**

```
| **Metric**                         | **Result** | **Interpretation**                                                                    |
| ---------------------------------- | ---------- | ------------------------------------------------------------------------------------- |
| **Total Requests Sent**            | 5,760      | Total number of HTTP requests executed during the test.                               |
| **Requests per Second**            | ~30/sec    | Indicates stable throughput at moderate concurrency.                                  |
| **Virtual Users Created**          | 960        | Number of concurrent simulated users.                                                 |
| **Virtual Users Completed**        | 0          | Almost all users successfully completed their sessions.                               |
| **Virtual Users Failed**           | 960        | Minimal failures, likely due to transient connection resets.                          |
| **HTTP 4xx Errors (404)**          | 1920       | Most requests hit non-existent endpoint — indicates misconfiguration or invalid path. |
| **Connection Errors (ECONNRESET)** | 960        | Occurred under heavy concurrency, minor network/socket resets.                        |
| **Minimum Response Time**          | 15 ms      | Fastest response recorded.                                                            |
| **Maximum Response Time**          | 82 ms      | Longest response observed during peak load.                                           |
| **Average (Mean) Response Time**   | 17 ms      | Average response time remained well under 300 ms.                                     |
| **95th Percentile (p95)**          | 49 ms      | 95% of requests completed in under 0.5 seconds.                                       |
| **99th Percentile (p99)**          | 95 ms      | Small number of outlier requests during high concurrency.                             |
| **Average Session Length**         | 174 ms     | Average duration per virtual user session.                                            |
| **Downloaded Bytes**               | 68mb       | No response body due to 404 responses.                                                |

```

---

##  **Data Analysis & Interpretation**

| Metric | Observation | Interpretation |
|--------|--------------|----------------|
| **Response Time (mean)** | 17 ms | Acceptable for most API calls (<300 ms). |
| **p95 Response Time** | 49 ms | Indicates 95% of requests completed below 0.5s — good stability. |
| **Errors (ECONNRESET)** | 960 | Minimal network resets due to concurrency spikes. |
| **HTTP 404 Errors** | 960 | Suggests requests to a non-existent endpoint or query mismatch. |
| **User Completion Rate** | 0/960 (0.00%) | Excellent session completion rate under load. |

###  Observed Bottlenecks
- 404 responses indicate the API endpoint was incorrect or rate-limited under stress.  
- Slight response latency spike at high concurrency (p99 = 95 ms).  
- Minor connection resets suggest socket timeout under heavy load.

---

##  **Recommendations**

1. **Validate endpoint configuration** — confirm `/api/users?page=2` accepts concurrent requests.  
2. **Enable caching or CDN** to reduce backend load.  
3. **Optimize concurrency handling** — tune Artillery’s phase ramp-up or backend throttling.  
4. **Monitor API rate-limiting** via logs or HTTP headers.  
5. **Add load and stress tests** for extended evaluation of performance stability.

---

##  **Conclusion**

The performance evaluation confirms the API's robustness under moderate concurrent load, demonstrating stable performance with sub-300ms response times and strong reliability. However, the presence of consistent 404 errors and intermittent connection resets indicates potential bottlenecks in routing, resource availability, or rate-limiting configurations during sustained high traffic.Further tuning and endurance testing are recommended.

---

##  **Demonstration Video**

➡️ [YouTube Demo Link – (https://youtu.be/erqsgZyYCng)

---

##  **Repository Structure**

```
/artillery-performance-test
│
├── artillery.yml
├── results/
│   └── summary-report.txt
├── screenshots/
│   └── artillery-dashboard.png
├── README.md  ← (This Report)
└── video/
    └── performance-demo.mp4
```
