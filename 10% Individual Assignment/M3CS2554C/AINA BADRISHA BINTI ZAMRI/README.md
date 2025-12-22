<p align="center">
  <img src="https://raw.githubusercontent.com/aaxxyeon-bit/images/refs/heads/main/banner.png" alt="Banner" width="1000" height="300"/>
</p>


<h1 align="center">💻 Comprehensive Web Application Performance Testing & Analysis using Grafana k6 on BlazeDemo</h1>

<p align="center">
  <strong>AUTHOR :</strong> AINA BADRISHA BINTI ZAMRI <br>
  <strong>STUDENT ID :</strong> 2025197759 <br>
  <strong>GROUP :</strong> M3CS2554C <br>
  <strong>COURSE :</strong> ITT440 – NETWORK PROGRAMMING
</p>

---


## 🧩 1. Introduction


### <ins>Objective</ins>  
The purpose of this project is to **design, execute, and critically analyze a performance test plan** for a real-world web application using **Grafana k6**. The test aims to evaluate the **scalability and stability** of the target web application and identifying potential bottlenecks under varying user loads.<br><br>


### 🌐 <ins>Target Web Application</ins>  
**Target Website:** BlazeDemo [https://blazedemo.com](https://blazedemo.com)  
BlazeDemo is a public simple flight booking demonstration site often used for testing purposes. It simulates typical web functionalities such as form submission, page navigation, and dynamic content rendering. The site is designed for non-destructive testing and educational use, making it an ethical and legal choice for performance evaluation.<br><br>


###  <ins>Hypothesis</ins>  
It is hypothesized that **BlazeDemo** can handle moderate user loads (up to 100 concurrent users) with stable response times. However, beyond this threshold, the application may begin to experience **performance degradation** due to limited server capacity or backend response delays.

--- 

## ⚙️ 2. Tool Selection Justification  

###  <ins>Selected Tool: Grafana k6 CLI</ins>
**k6** is a modern, developer-centric load and performance testing tool built for both local and cloud-based execution. It was chosen for the following reasons:

| No. | 🧩 **Feature** | 💡 **Reason for Selection** |
|:---:|:----------------:|:----------------------------:|
| 1 | Open-source & Developer-friendly | Freely available and highly customizable for performance testing without license cost. |
| 2 | Scriptable in JavaScript | Enables writing realistic user scenarios using a language familiar to most developers. |
| 3 | CLI & Cloud Options | Offers both local command-line and Grafana Cloud execution modes for flexibility. |
| 4 | Grafana Integration | Provides seamless visualization and monitoring of real-time metrics via Grafana dashboards. |
| 5 | Automation & CI/CD Ready | Can be easily integrated into automated pipelines for continuous performance testing. |
| 6 | Lightweight Design | Minimal resource usage, ideal for testing APIs and lightweight web applications. |

<br>

### 🔧 <ins>Supporting Tool: Grafana Cloud Dashboard</ins> 
Grafana Cloud Dashboard is used to visualize the performance testing results from k6.  
Grafana provides clear and interactive visual insights into key metrics such as request duration, virtual user (VU) ramp-up patterns, and pass/fail thresholds.  
This powerful visualization made it easier to observe system behavior, identify performance bottlenecks, and understand trends over time through detailed charts and dashboards.<br><br>

###  <ins>Screenshot: Terminal Running k6 (BlazeDemo Scalability Test)</ins>

<p align="center">
  <a href="https://github.com/aaxxyeon-bit/images/blob/main/k6_terminal_run.png?raw=true" target="_blank">
    <img src="https://github.com/aaxxyeon-bit/images/blob/main/k6_terminal_run.png?raw=true" 
         alt="Terminal running Grafana k6 scalability test for BlazeDemo website" 
         width="800px"/>
  </a>
  <br/>
  <sub>Terminal running <code>k6 run blazedemo_scalability_test.js</code> — click image to view in full size.</sub>
</p>

---

## 🧩 3. Test Type and Justification


### <ins>Selected Test Type: **Scalability Test**</ins>

A scalability test gradually increases user load to identify the point where performance metrics begin to degrade.  
This testing type helps determine the maximum capacity of a system before its performance becomes unacceptable. Scalability 
testing focuses on understanding growth thresholds and how performance changes as users increase progressively.<br><br>

### 🧠 <ins>Justification</ins>

Since BlazeDemo simulates a real-world flight booking website, it’s important to analyze how its performance scales  
with increasing concurrent users. This test helps evaluate how efficiently the backend handles increasing traffic over time  
and whether the system remains stable, responsive, and efficient as user demand grows.

---

## 🧪 4. Test Environment Setup  

| Component | Description |
|------------|-------------|
| **Testing Tool** | Grafana k6 (CLI & Cloud Integration) |
| **IDE** | Visual Studio Code |
| **Execution Mode** | Cloud Execution (`k6 cloud`) |
| **Virtual Users (VUs)** | Maximum 100 (within free-tier limit) |
| **Test Duration** | 18 minutes (ramp-up and ramp-down included) |
| **Metrics Monitored** | Response Time, Throughput, Error Rate, CPU, Memory |

---

## 🧬 5. Test Scenario

The scalability test simulates gradually increasing virtual users (VUs) to evaluate how BlazeDemo handles higher user traffic and maintains performance stability over time.

This test type helps measure how well the system scales, how response time changes as load increases, and at which point performance begins to degrade.



### 🔹 <ins>Test Scenario Overview</ins>

| **Stage** | **Description** | **Purpose / Reason** |
|------------|-----------------|-----------------------|
| **Warm-up** | Starts with a small number of users accessing the website. | Allows caching, server initialization, and resource allocation before the main load begins. |
| **Small Load** | Simulates light, typical usage conditions. | Confirms system responsiveness under expected user traffic. |
| **Medium Load** | Gradually increases user traffic. | Tests how performance scales when more users access the site simultaneously. |
| **High Load** | Pushes the system to upper thresholds (heavy traffic). | Identifies the scalability limit and monitors response time and throughput. |
| **Cool-down** | Gradual reduction of users after the high load phase. | Checks how efficiently the system recovers after intensive usage. |

<br>

### 🧠 <ins>Why Use Multiple Stages?</ins>

- 📈 **Smooth scaling** — prevents overwhelming the system abruptly.  
- 📈 **Identifies early bottlenecks** — shows when performance degradation starts.  
- 📈 **Mimics real-world patterns** — simulates natural traffic growth and decline cycles.  
- 📈 **Improves reliability analysis** — helps observe how the system behaves before, during, and after peak load.

<br>

---

## 💻 6. Scalability Test Scripts

Below are two variations of the same scalability test, adjusted for different testing environments.



### **(A) Local Execution – Up to 500 VUs**

--> This version is executed via the k6 CLI locally.  
--> There is no enforced VU limit, so it can simulate large-scale testing.

```js
import http from 'k6/http';
import { check, sleep, group } from 'k6';
import { Trend } from 'k6/metrics';

// optional custom metric
let pageLoadTrend = new Trend('page_load_time_ms');

export let options = {
  // stages define a ramp-up scalability profile
  stages: [
    { duration: '2m', target: 10 },     // warm-up
    { duration: '3m', target: 100 },     // small load
    { duration: '5m', target: 250 },    // medium load
    { duration: '5m', target: 500 },    // high load (scale up)
    { duration: '3m', target: 0 }       // scale down
  ],
  thresholds: {
    // example pass/fail thresholds you can later adjust
    'http_req_failed': ['rate<0.05'],       // <5% errors
    'http_req_duration': ['p(95)<1500']     // 95% requests < 1500ms
  },
  // other settings
  vus: 1
};

const BASE = 'https://blazedemo.com';

export default function () {
  group('homepage + search', function () {
    let res1 = http.get(BASE + '/');
    pageLoadTrend.add(res1.timings.duration);
    check(res1, {
      'homepage status 200': (r) => r.status === 200,
    });
    sleep(1 + Math.random() * 2);

    // simulate searching flights => open reserve page
    // We use a GET to /reserve.php with query params (this mimics selecting a flight)
    // adjust params if needed after exploring the site manually
    let res2 = http.get(BASE + '/reserve.php?fromPort=Paris&toPort=Buenos%20Aires');
    pageLoadTrend.add(res2.timings.duration);
    check(res2, {
      'reserve page 200': (r) => r.status === 200,
    });
    sleep(Math.random() * 3);
  });
}
```
### **(B) Grafana Cloud Execution – Up to 100 VUs**

--> This version of the scalability test is executed through Grafana Cloud’s k6 platform.  
--> Grafana Cloud’s free tier limits concurrent virtual users (VUs) to 100, so this script is optimized within that constraint.  
--> It streams test metrics directly to the Grafana Cloud dashboard for real-time visualization and analysis.

```js
import http from 'k6/http';
import { check, sleep, group } from 'k6';
import { Trend } from 'k6/metrics';

// optional custom metric
let pageLoadTrend = new Trend('page_load_time_ms');

export let options = {
  // stages define a ramp-up scalability profile
  stages: [
    { duration: '2m', target: 10 },     // warm-up
    { duration: '3m', target: 30 },     // small load
    { duration: '5m', target: 60 },    // medium load
    { duration: '5m', target: 100 },    // high load (scale up)
    { duration: '3m', target: 0 }       // scale down
  ],
  thresholds: {
    // example pass/fail thresholds you can later adjust
    'http_req_failed': ['rate<0.05'],       // <5% errors
    'http_req_duration': ['p(95)<1500']     // 95% requests < 1500ms
  },
  // other settings
  vus: 1
};

const BASE = 'https://blazedemo.com';

export default function () {
  group('homepage + search', function () {
    let res1 = http.get(BASE + '/');
    pageLoadTrend.add(res1.timings.duration);
    check(res1, {
      'homepage status 200': (r) => r.status === 200,
    });
    sleep(1 + Math.random() * 2);

    // simulate searching flights => open reserve page
    // We use a GET to /reserve.php with query params (this mimics selecting a flight)
    // adjust params if needed after exploring the site manually
    let res2 = http.get(BASE + '/reserve.php?fromPort=Paris&toPort=Buenos%20Aires');
    pageLoadTrend.add(res2.timings.duration);
    check(res2, {
      'reserve page 200': (r) => r.status === 200,
    });
    sleep(Math.random() * 3);
  });
}
```
<br>

---
## 🧾 7. Results & Analysis

This section presents and analyzes the outcomes of the scalability test executed in two environments:

1. **Local CLI Execution (Max 500 VUs)**  
2. **Grafana Cloud Execution (Max 100 VUs)**  

Both tests evaluated BlazeDemo’s performance stability as the number of virtual users (VUs) increased gradually.<br><br>


### **7.1 Local CLI Scalability Test (500 VUs)**

--> This test was executed locally using the k6 CLI and allowed a maximum of 500 virtual users.  
--> The goal was to identify the upper scalability limit of the BlazeDemo site without external restrictions.

**📊 Summary of Key Metrics**

| **Metric** | **Result** |
|-------------|------------|
| **95th Percentile Response Time** | 592.7 ms |
| **Average Response Time** | 395.9 ms |
| **Maximum Response Time** | 3.69 s |
| **HTTP Request Failed** | 0.00% |
| **Total Requests Made** | 102,890 |
| **Data Received** | 620 MB |
| **Average Iteration Duration** | 4.3 s |
| **Thresholds** | ✅ `p(95)<1500ms` and `rate<0.05` passed |

<br>

**🧠 Analysis**

- The system successfully handled up to 500 concurrent users without breaching the performance thresholds.  
- Average response time (~396 ms) and p(95) response time (~593 ms) indicate strong backend stability.  
- No request failures were recorded so it's suggesting excellent server reliability under load.  
- The increasing iteration duration (up to 6 s at the 95th percentile) shows that response time gradually grows as VUs ramp up but remains acceptable within limits.  
- This confirms that BlazeDemo scales effectively up to 500 users locally.<br><br>

**📷 CLI Execution Output:**

<p align="center">
  <a href="https://github.com/aaxxyeon-bit/images/blob/main/scalability%20500.png?raw=true" target="_blank">
    <img src="https://github.com/aaxxyeon-bit/images/blob/main/scalability%20500.png?raw=true" 
         alt="Terminal output showing scalability test up to 500 VUs executed locally using k6 CLI" 
         width="800px"/>
  </a>
  <br/>
  <sub>Figure 2: Terminal output showing scalability test up to 500 VUs executed locally using k6 CLI — click image to view in full size.</sub>
</p>

<br><br>

<p align="center">
  <a href="https://github.com/aaxxyeon-bit/images/blob/main/scalability%20500%202.png?raw=true" target="_blank">
    <img src="https://github.com/aaxxyeon-bit/images/blob/main/scalability%20500%202.png?raw=true" 
         alt="Terminal output showing scalability test up to 500 VUs executed locally using k6 CLI" 
         width="800px"/>
  </a>
  <br/>
  <sub>Figure 3: Terminal output showing scalability test up to 500 VUs executed locally using k6 CLI — click image to view in full size.</sub>
</p>

<br><br>
 

### **7.2 Grafana Cloud Scalability Test (100 VUs)**

--> This version was executed using Grafana Cloud’s k6 platform, which has a maximum limit of 100 concurrent VUs.  
--> It visualizes results in real time through Grafana dashboards.

**📊 Summary of Key Metrics**

| **Metric** | **Result** |
|-------------|------------|
| **Requests Made** | 22.6K |
| **HTTP Failures** | 4 |
| **Peak Requests per Second (RPS)** | 52.83 req/s |
| **95th Percentile Response Time** | 2,556 ms |
| **Max VUs** | 100 |

<br>

**🧠 Analysis**

- The performance was stable up to 100 users although p(95) response time (~2.5s) is notably higher than in the local run.  
- The slight increase in response latency may result from network distance, cloud infrastructure overhead or Grafana’s shared environment.  
- Despite 4 HTTP failures, the failure rate remained minimal (≈0.018%) which indicate consistent performance reliability.  
- The Peak RPS (52.83) reflects efficient request throughput even at higher load stages.  
- The visualization clearly shows a correlation between VU ramp-up and request rate, demonstrating the scalability behavior under cloud monitoring.<br><br>

**📷 Grafana Cloud Dashboard Visualization:**

<p align="center">
  <a href="https://github.com/aaxxyeon-bit/images/blob/main/Screenshot%202025-11-03%20005936.png?raw=true" target="_blank">
    <img src="https://github.com/aaxxyeon-bit/images/blob/main/Screenshot%202025-11-03%20005936.png?raw=true" 
         alt="Grafana Cloud visualization of the scalability test (up to 100 VUs)." 
         width="800px"/>
  </a>
  <br/>
  <sub>Figure 4: Grafana Cloud visualization of the scalability test (up to 100 VUs). — click image to view in full size.</sub>
</p>

<br><br>

### **📈 7.3 Comparative Insights**

| **Aspect** | **Local (500 VUs)** | **Grafana Cloud (100 VUs)** |
|-------------|---------------------|------------------------------|
| **Max Concurrent Users** | 500 | 100 |
| **Average Response Time** | 395.9 ms | ~2.5 s |
| **Failures** | 0 | 4 |
| **RPS (Peak)** | ~95 req/s | 52.83 req/s |
| **Environment** | Local machine | Grafana Cloud |
| **Visualization** | CLI metrics | Real-time dashboard |
| **Scalability Observation** | Excellent up to 500 users | Stable under 100 users but higher latency |

<br><br>

### ⚙️ 7.4 Resource Utilization Analysis

- To complement the performance metrics, CPU and memory usage were monitored during executions.  
- The line chart below illustrates the CPU usage trend during the test execution.<br><br>

<p align="center">
  <a href="https://github.com/aaxxyeon-bit/images/blob/main/CPU_CHART.png?raw=true" target="_blank">
    <img src="https://github.com/aaxxyeon-bit/images/blob/main/CPU_CHART.png?raw=true" 
         alt="CPU Chart" 
         width="800px"/>
  </a>
  <br/>
  <sub>Figure 5: Load-Generator CPU & Memory during 100 VUs Scalability Test. — click image to view in full size.</sub>
</p>

<br><br>

During the warm-up phase, CPU usage started around 15%, with memory consumption at approximately 170 MB as the test initialized and virtual users (VUs) began connecting. As the load transitioned into the small and medium load stages, both CPU and memory utilization increased steadily, reaching around 60–65% CPU and 270 MB RAM by the medium phase.

At the high load stage (100 VUs), resource utilization peaked — CPU usage climbed to roughly 80%, while memory consumption reached about 310 MB, correlating directly with the maximum number of active VUs. This behavior demonstrates the expected linear scalability, where system resource consumption increases proportionally with simulated user load.

Finally, during the cool-down stage, as virtual users ramped down, both CPU and memory usage dropped sharply back to baseline levels (≈30% CPU and ≈200 MB RAM), confirming no residual memory leaks or abnormal resource retention after test completion.


<br><br>

### 7.5 Interpretation of Results & Bottlenecks

| **Observation** | **Potential Cause** | **Impact** | **Recommendation** |
|------------------|----------------------|-------------|---------------------|
| Increased response time in Grafana Cloud run (≈2.5 s) | Network latency between Grafana Cloud servers and BlazeDemo | Slight delay under higher concurrency | Deploy closer test regions or edge servers to reduce latency. |
| Minor HTTP request failures | Temporary connection timeouts | Negligible | Implement retry logic in the backend to improve fault tolerance. |
| High CPU utilization spikes under 500 VUs | Peak concurrent user simulation | May affect throughput at higher scales | Optimize server threading and caching mechanisms. |

<br><br>

### 7.6 Recommendations & Optimization Strategies

1. **Server-Side Optimization:**  
   Implement caching for frequently accessed resources (e.g., homepage assets) to reduce repeated request load.

2. **Load Balancing:**  
   Introduce a load balancer or CDN layer to distribute incoming traffic evenly across multiple servers.

3. **Database Connection Pooling:**  
   Ensure efficient connection management to prevent query bottlenecks during high concurrency.

4. **API Response Optimization:**  
   Compress payloads and minimize response size to improve network efficiency.

5. **Infrastructure Scaling:**  
   Use auto-scaling groups to dynamically allocate resources during traffic spikes.

6. **Continuous Monitoring:**  
   Integrate Grafana dashboards into CI/CD pipelines for ongoing performance visibility.


---

## 🧭 8. Recommendations Based on Industry Best Practices

Based on the scalability test outcomes and performance analysis, several optimization recommendations can be made to improve system resilience, scalability, and long-term efficiency.

### ⚙️ <ins>Performance Optimization</ins>
- **Enable caching mechanisms** (e.g., CDN, in-memory caching such as Redis) to reduce repetitive HTTP requests and response latency.  
- **Optimize backend queries** by reducing database round trips and indexing frequently accessed data.  
- **Implement connection pooling** to manage multiple simultaneous database or API requests efficiently.<br> 

### 📈 <ins>Testing & Monitoring Improvements</ins>
- **Integrate continuous performance testing** into CI/CD pipelines using Grafana k6 Cloud for consistent monitoring and early detection of bottlenecks.  
- **Set automated thresholds** (for p95 latency, error rate, throughput) to trigger alerts when performance drifts occur.  
- **Correlate infrastructure metrics** (CPU, memory, and network I/O) with response time to locate root causes faster.<br>

### ☁️ <ins>Scalability & Infrastructure</ins>
- **Adopt horizontal scaling** (e.g., adding more application instances) when load exceeds safe CPU/memory thresholds.  
- **Utilize load balancers** to distribute requests evenly across multiple servers.  
- **Leverage containerization** (e.g., Docker, Kubernetes) for efficient resource allocation and dynamic scaling.<br>  

### 🔒 <ins>Reliability & Security</ins>
- Regularly perform **stress and endurance testing** alongside scalability tests to identify hidden bottlenecks under sustained load.  
- Ensure **secure API configurations** and TLS encryption to maintain integrity during high-traffic conditions.  
- Follow **DevSecOps best practices** by including security validation in every performance testing cycle.<br>

---

## 🏁 9. Conclusion and Reflection

Throughout this project, executing the scalability test for BlazeDemo using Grafana k6 CLI and Grafana Cloud was a very insightful experience for me. It allowed me to understand how scalability testing works in practice. It's not just from a theoretical perspective but by actually observing how the system reacts under different levels of traffic.

When I ran the local 500-VU test, I was surprised to see how well the system handled a large number of virtual users without any request failures. It showed me how performance can remain stable even when the load increases significantly as long as the application and infrastructure are properly optimized.  

Using Grafana Cloud for the 100-VU test was also interesting because I could see the test results live through visual dashboards. The charts helped me understand metrics such as response time, throughput, and resource utilization more clearly. It made me realize how useful visualization tools are for analyzing performance data and identifying patterns that might not be obvious in raw numbers.

From this experience, I learned the importance of proper test planning, interpreting performance metrics correctly, and maintaining consistent monitoring during execution. I also gained confidence in using k6 as a load-testing tool and now have a clearer picture of how scalability testing fits into real-world software performance evaluation.

Overall, this assignment gave me hands-on exposure to real testing practices and helped me appreciate how scalability testing can ensure a system continues to perform reliably as user demand grows.


---

## 🎥 10. Video Demonstration

📽️ *A walkthrough video of the test setup, execution, and Grafana visualization.*

➡️ [Watch the Demonstration Video](https://youtu.be/QF5iE5gthgw)

📽️ *Demonstration of running k6 test from VS Code and visualising results in Grafana Cloud.*

➡️ [Watch the VS Code & Grafana Cloud Demo](https://youtu.be/SECOND_YOUTUBE_LINK)

---

## 📚 11. References

- Grafana Labs. (2024). *k6 Open Source Load Testing Tool.* Retrieved from [https://k6.io](https://k6.io)  
- Grafana Labs Documentation. (2024). *k6 Cloud Insights.* Retrieved from [https://grafana.com/docs/k6/](https://grafana.com/docs/k6/)  
- BlazeDemo. (n.d.). *Sample Web Application for Load Testing.* Retrieved from [https://blazedemo.com](https://blazedemo.com)  
- Microsoft Azure Architecture Center. (2023). *Performance Efficiency Checklist.* Retrieved from [https://learn.microsoft.com/en-us/azure/architecture/framework/scalability](https://learn.microsoft.com/en-us/azure/architecture/framework/scalability)  
- Google Cloud. (2024). *Best Practices for Load Testing Web Applications.* Retrieved from [https://cloud.google.com/architecture](https://cloud.google.com/architecture)  

<p align="center">
  <img src="https://raw.githubusercontent.com/aaxxyeon-bit/images/refs/heads/main/banner.png" alt="Banner" width="1000" height="300"/>
</p>

