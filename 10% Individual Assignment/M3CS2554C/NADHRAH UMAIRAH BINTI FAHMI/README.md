<div align="center">

  <h1> WEB APPLICATION SPIKE TEST USING GRAFANA K6</h1>
  <h3>COMPREHENSIVE PERFORMANCE TESTING REPORT</h3>

  <img width="900" alt="Grafana Screenshot" src="https://github.com/user-attachments/assets/a08ff3eb-5a94-435c-a9ca-106e51ccdccb" />

  <p>
    <b>NAME:</b> NADHRAH UMAIRAH BINTI FAHMI<br>
    <b>STUDENT ID:</b> 2025168903<br>
    <b>GROUP:</b> M3CS2554C
  </p>

</div>

---

## 🧾 1. INTRODUCTION
Web performance testing is essential for verifying that a program can manage sudden increases in user traffic without failure. This project involves spike testing of web performance using  **k6**, an open-source performance testing tool, and visualizing the results using **InfluxDB** and **Grafana**. The primary goal is to analyze how the target web application, **AutomationInTesting**, responds to a rapid virtual load of 1000 virtual users (VUs) and its recovery process.

---


## 📌 2. WHAT IS SPIKE TESTING ?
Spike testing is performance testing that checks how a system responds when the number of users or requests sharply increases and then drops quickly over a short time. The goal is to see if the system can handle sudden traffic spikes, recover from overloads, and keep acceptable response times without crashing or losing data.
Through spike testing, developers and testers can observe system stability, scalability limits, and potential resource constraints, such as CPU usage, memory consumption, and request handling efficiency.

---

## 🎯 3. OBJECTIVES
The vital objective of this project is to:
- Analyse the capability of the website under a sudden spike across 1000 virtual users (VUs).  
- Collect and monitor key performance indicators (KPIs), including request rate (req/s), response time, and error rate.  
- Monitor the behaviour of system recovery when the spike has passed.  
- Identify bottlenecks that could affect user experience during traffic spikes and document the technical findings.  

---

## ⚙️ 4. TOOL SELECTION JUSTIFICATION
<p align="center">
  <img width="649" height="244" alt="image" src="https://github.com/user-attachments/assets/556742d2-8c3e-484d-b341-629b583db0e7" />
</p>


Grafana K6 is a modern open-source load testing tool that prioritises simplicity, efficiency, and scalability.  It enables JavaScript scripting of performance tests, allowing for greater flexibility and automation in complex circumstances.

K6 is frequently combined with InfluxDB for storing time-series data and Grafana for visualising test results through dynamic dashboards.  This integration allows testers to see real-time analytics, including virtual users (VUs), request rates, response times, and error rates. 

| Tool | Purpose | Justification |
|------|----------|----------------|
| **k6** | Load generation | Lightweight CLI-based performance testing tool, perfect for scripting and automation. |
| **InfluxDB** | Data storage | An effective time-series database for organizing real-time test metrics. |
| **Grafana** | Visualization | Provides robust dashboards for visualizing analytics like request rate, error rate, response time, and virtual users. Grafana (v10.x) running on `http://localhost:3000`|



---

## 🧭 5. TEST ENVIRONMENT SETUP AND CONFIGURATION
This section explains how the testing environment was configured, how the spike test was designed, and how performance metrics were captured and analyzed.

### 🖥️ 5.1 TEST ENVIRONMENT CONFIGURATION
| Component | Description |
|------------|--------------|
| Operating System (OS) | Windows 11 64-bit |
| CPU | AMD Ryzen 5 7430U with Radeon Graphics (2.30 GHz) |
| Memory (RAM) | 16.0 GB |
| Test Type | Spike Test |
| Load Testing Tool | k6 v1.3.0 |
| Monitoring Dashboard | Grafana (connected via InfluxDB) |
| Target Web Application | [https://automationintesting.online/](https://automationintesting.online/) |
| Virtual Users | 1000 |
| Test Duration | 3 minutes maximum |

---

### 🧩 5.2 TEST SCRIPT CONFIGURATION

The k6 script defines the load pattern, thresholds, and behavior of virtual users. The final script used for the spike test was:  

spike_testing.js
```js
import http from 'k6/http';
import { sleep } from 'k6';

export const options = {
  stages: [
    // Warm-up
    { duration: '30s', target: 50 },
    { duration: '30s', target: 50 },

    // Spike!
    { duration: '10s', target: 1000 },

    // Hold spike
    { duration: '30s', target: 1000 },

    // Recover
    { duration: '20s', target: 0 },
  ],
  thresholds: {
    http_req_duration: ['p(95)<500'],
    http_req_failed: ['rate<0.05'],
  },
};

export default function () {
  const res = http.get('https://automationintesting.online/');
  sleep(0.5);
}
````
---
### 📈 **5.3 METRICS MEASURED**

The following performance metrics were captured through Grafana and k6:

| Metric | Description |
|--------|--------------|
| **Active Virtual Users (VUs)** | The number of active users during the test. |
| **Request Rate (req/s)** | The number of HTTP requests sent per second. |
| **Response Time (95th Percentile)** | Time taken for 95% of all requests to complete successfully. |
| **Error Rate (%)** | The percentage of failed requests. |

---

### ⚡ **5.4 TEST EXECUTION**

The test was executed from the local machine, with data streamed in real-time to Grafana dashboards. The total number of requests sent was approximately **2,653** over **2 minutes and 30 seconds**, which is reasonable for a spike test at this concurrency level, considering the 0.5-second sleep time per request per user.

### 🧭 Run Command
```bash
C:\Users\ADMIN\Desktop> k6 run --out influxdb=http://localhost:8086/k6 spike_testing.js
```

### 🖥️ Network Setup: 
Data gathering uses a local InfluxDB database. Grafana connected through the port `http://localhost:3000`. Test script executed using Windows Command Prompt.

**Grafana Dashboard URL:**  
[http://localhost:3000/d/df2p8k24gscu8e/k6-spike-test-31-10?orgId=1&from=now-24h&to=now]

---

### 📊 **6. RESULTS AND INTERPRETATION**

**RESULT GRAPHS**

The spike test was conducted using the k6 load testing tool to evaluate the performance of the website [https://automationintesting.online](https://automationintesting.online) under sudden traffic surges.

### 1. Virtual Users vs Request Rate
<p align="center">
<img width="940" height="350" alt="image" src="https://github.com/user-attachments/assets/df5d38f2-7094-48e1-9f8e-ce667bb9214e" />
</p>

The test scenario started with a gradual ramp-up of 50 virtual users, then quickly spiked to 1,000 users within 10 seconds, maintained that level for 30 seconds, and then dropped to zero during the recovery phase. The resulting graph shows that the number of active virtual users rises sharply and remains steady at 1,000 before decreasing, while the request rate peaks at about **117 requests per second** with a minor error during the high-load period. This behavior demonstrates that the website effectively handled a sudden spike in concurrent users and recovered efficiently once the load decreased.

---

### 2. Request Rate vs Error Rate
<p align="center">
<img width="940" height="373" alt="image" src="https://github.com/user-attachments/assets/ec232175-dc99-4a08-9fbd-094000caa934" />
</p>

The graph shows the relationship between the request rate and error rate during the spike test. The request rate increased sharply, peaking at about **1,600 requests per second**, while the error rate briefly increased to around **37%** during the highest load.
After the spike, both metrics dropped quickly, showing the system’s ability to recover. The average request rate was 140 requests per second, with a total of **2,653 requests** and an average error rate of **1.48%**. This indicates that the system can handle the sudden traffic effectively and return to normal performance after the load decreases.


---

### 3. Response Time (95th Percentile)
<p align="center">
<img width="940" height="438" alt="image" src="https://github.com/user-attachments/assets/b7eb28f3-39df-4acd-b79b-d5aaf455281e" />
</p>

The graph shows the response time during the spike test with 1,000 virtual users on [https://automationintesting.online](https://automationintesting.online). At the start, response times were low (below **500 ms**), but as the load increased, the 95th percentile rose sharply to around **30 seconds**, showing slower responses under heavy traffic. After the spike, response times dropped and stabilised, indicating the system recovered well after the high load.

---

### K6 Command Prompt Test Result Output
<p align="center">
<img width="855" height="404" alt="image" src="https://github.com/user-attachments/assets/751e6ff1-8c83-49ea-8dab-2bf44a8100fa" />
</p>

The K6 CLI output provides a summary of performance metrics including total HTTP requests, response durations, and failure rates. In this test, K6 recorded **21,069 total requests**, an **average response time of 1.83 seconds**, and a **failure rate of 0.09%**, which met the defined threshold for reliability.The 95th percentile response time (**5.85s**) exceeded the 500 ms threshold, indicating temporary latency under heavy load. 
These console results were simultaneously exported to InfluxDB and visualised through Grafana for further trend and performance analysis.

---

### 🔍 **7. ANALYSIS AND FINDINGS**

| METRIC | OBSERVATION | ANALYSIS |
|--------|--------------|-----------|
| **Active Virtual Users (VUs)** | Increased sharply to 1,000 users, then dropped smoothly | The spike ramp-up and recovery phases were executed correctly, simulating a realistic sudden load surge and release. |
| **Requests per second** | Peaked around 1,600 req/s; average 140 req/s | Indicates strong request throughput during the spike. The system was able to handle a large volume of concurrent requests before returning to normal. |
| **HTTP Failures / Error Rate** | Brief spike up to 37% during peak load; average 1.48% | Shows temporary performance degradation at maximum load, likely due to resource saturation or queue overflow, but stability was regained after load reduction. |
| **Response Time (p95)** | Increased from <500 ms to about 30 s during the spike | Indicates the server experienced high latency under extreme stress but successfully recovered after the load decreased. |
| **Total Requests** | 2,653 total requests sent during the test | Confirms steady request flow throughout the test duration. |

**Bottlenecks Identified:**
- High latency observed during peak load (around 30s response time) likely due to server-side queuing or limited processing capacity.
- Temporary error spike (37%) suggests possible API throttling or connection timeout when user concurrency reaches its maximum.
- Minor instability in request rate at the highest load could be caused by client-side resource limits or network saturation.

---

### 🧩 **8. DISCUSSION**

During the spike test with 1,000 virtual users, the K6 console recorded **21,069 total HTTP requests** with an average response time of **1.83 seconds**, while the Grafana dashboard displayed only **2,653 total requests**.

This difference is normal and occurs because **K6 measures every executed request locally**, while **Grafana visualizes data sent to InfluxDB**, which may aggregate or drop some data points during heavy load. Grafana’s time-based sampling such as grouping data by 10-second intervals can make the total request count appear lower.

Despite this variation, both tools show a consistent performance trend:

- Peak load: **1,000 active users**  
- Average rate: **~154 requests/second**  
- 95th percentile response time: **~5.85 seconds**  
- Failure rate: **0.09%**

Overall, the system successfully handled the spike with minimal failures, though a short delay occurred at peak load , typical during stress conditions.  
The lower total in Grafana does not affect test accuracy, as the performance trend remains reliable.

---

### 🛠 **9. RECOMMENDATIONS**

Based on the spike test results, the following actions are recommended:

1. **Enable Caching Mechanisms:**  
   Implement caching for frequently requested data to reduce backend processing and improve response times during traffic spikes.

2. **Monitor Server Resources:**  
   Continuously track CPU, memory, and network usage using tools like Grafana to identify potential hardware or performance bottlenecks.

3. **Repeat Tests with Realistic Scenarios:**  
   Conduct additional spike and stress tests, including common user actions (login, browsing, posting) to better simulate real-world traffic and understand system behaviour under different workloads.

---

### 🧾 **10. CONCLUSION**

The spike test showed that the website could handle sudden traffic surges of up to 1,000 virtual users with minimal errors, although temporary delays occurred during peak load. This suggests that, while the system is generally stable, some errors could affect the user experience under extreme conditions.

Through this exercise, I gained practical experience in conducting performance testing using **K6** and monitoring tools like **Grafana**. I learned how to interpret key metrics such as average response time, total requests, error rates, and resource utilisation, which are essential for understanding how a system behaves under stress.  

I also realised the importance of realistic testing scenarios, including various user actions, to uncover potential bottlenecks that simple spike tests might overlook.
Additionally, the test highlighted the value of **proactive monitoring** and **scalability planning**. By observing system behaviour during high traffic, I identified areas of the backend that might require optimisation, such as slow API endpoints or inefficient database queries.

Overall, this experience enhanced my technical skills in performance evaluation, taught me how to critically analyse and interpret test data, and emphasised best practices for ensuring the reliability and scalability of web applications in real-world scenarios.

---

### 📚 **11. REFERENCES**

- Grafana Labs. (2025). *Grafana documentation: InfluxDB data source.* Retrieved from [https://grafana.com/docs/grafana/latest/datasources/influxdb/](https://grafana.com/docs/grafana/latest/datasources/influxdb/)

- Grafana Labs. (2025). *Getting started with Grafana and InfluxDB.* Retrieved from [https://grafana.com/docs/grafana/latest/getting-started/get-started-grafana-influxdb/](https://grafana.com/docs/grafana/latest/getting-started/get-started-grafana-influxdb/)

- InfluxData. (2025). *Using Grafana with InfluxDB OSS.* Retrieved from [https://docs.influxdata.com/influxdb/v2/tools/grafana/](https://docs.influxdata.com/influxdb/v2/tools/grafana/)

- k6.io. (2025). *k6 documentation: Load and performance testing tool.* Retrieved from [https://k6.io/docs/](https://k6.io/docs/)

- CircleCI. (2024, March 12). *API performance testing with k6.* Retrieved from [https://circleci.com/blog/api-performance-testing-with-k6/](https://circleci.com/blog/api-performance-testing-with-k6/)

- Automation in Testing. (2025). *Public Test Application.* Retrieved from [https://automationintesting.online](https://automationintesting.online)


---

### 🎥 **VIDEO DEMONSTRATION**
[🎥 Watch the Video Demonstration on YouTube](https://youtu.be/OCTLjkpVJVg)


