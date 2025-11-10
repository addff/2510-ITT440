#### STUDENT NAME : MUHAMMAD AMIR SAFWAN BIN SHAZALI
#### STUDENT ID : 2024963165
#### GROUP : M3CS2554B
# 🔍 Spike Testing of JSONPlaceHolder using Grafana k6
###  INTRODUCTION
 <div align="justify"> Performance testing helps determine how a system handles sudden increases in user load. In this project, I conducted a spike test using Grafana k6, a modern open-source load testing tool. The spike test measures how well a system responds to an unexpected surge of traffic in a short period of time. For this test, I used JSONPlaceholder, a free online REST API commonly used for testing and prototyping. It simulates real-world API responses without affecting a live production system. The purpose of this test is to observe how the API behaves when it suddenly receives a large number of requests — checking for slowdowns, failed requests, or performance recovery after the spike ends. </div>

---
### OBJECTIVES
- To simulate a sudden spike in virtual users sending requests to the JSONPlaceholder API using Grafana k6.
- To measure the system’s response time, throughput, and error rate during and after the spike period.
- To observe how quickly the system recovers after the sudden increase in load.
- To analyze the test results and provide recommendations for improving performance and stability.

---
### Tool Used:Grafana K6

<p align="center">
<img width="500" height="243" alt="image" src="https://github.com/user-attachments/assets/5df4a326-0bf7-4b27-8fdc-4072251865ba" />
 
Grafana k6 is a modern open-source load testing tool designed for testing APIs, microservices, and web applications.
Key reasons for choosing k6:
- It supports scripting in JavaScript, which is easy to customize.
- Command-line interface works efficiently in Ubuntu.
- Real-time results and integration with Grafana dashboards.
- Lightweight yet capable of handling thousands of virtual users.

---
### Type of Test: Spike Test

A spike test is a type of performance test where the number of virtual users suddenly increases to a high level and then rapidly drops.
#### Purpose:
To evaluate how the system behaves when subjected to a sharp load increase checking for crashes, slow responses, or recovery delays.

---
### Target Web Application: JSONPlaceholder API

<p align="center">
<img width="500" height="243" alt="image" src="https://github.com/user-attachments/assets/a341382c-47fc-4092-a9d8-a3e14e23c960" />
 
URL: https://jsonplaceholder.typicode.com/posts

This is a public REST API commonly used for testing and prototyping. It safely allows simulated requests without impacting any real systems, making it an ethical and legal target for performance testing.

---
### Test Environment Setup

Operating System: Ubuntu 18.04 LTS

Tool: Grafana k6 (installed via apt)

Target URL: JSONPlaceholder (/posts)


Command Used:

<img width="478" height="300" alt="image" src="https://github.com/user-attachments/assets/48a9e87e-f1d4-4f09-9d67-cf29bac01e08" />

---
### Test Hypothesis

It is expected that JSONPlaceholder, being a mock API service, will handle the spike load efficiently without any failed requests. Response time may slightly increase during the 100-VU spike but should remain stable and below 1 second for most requests.

---
### Test Plan

| **Stage**    | **Duration** | **Target Virtual Users (VUs)** | **Stage Name**        | **Expected Behaviour** |
| ------------ | ------------ | ------------------------------ | --------------------- | -----------
| **Warm-up**  | 30 seconds   | 10 VUs                         | Normal baseline load  | Starts with a small number of users to gradually warm up the system, establish a connection, and record normal response   times before the spike. |
| **Spike**    | 25 seconds   | 100 VUs                        | Sudden load surge     | A rapid increase from 10 to 100 virtual users to simulate a sudden burst of traffic (e.g., flash sale, viral event, or unexpected user influx). Tests how the system reacts to a sudden spike. |
| **Recovery** | 30 seconds   | 10 VUs                         | Load reduction        | Reduces load back to normal levels to observe how quickly and smoothly the system recovers and stabilizes after the high-stress period. |
| **Cooldown** | 20 seconds   | 0 VUs                          | Test completion       | Gradually reduces all users to zero, ending the test while monitoring if performance metrics return to baseline. |

---
### Test Result Summary

| **Category**             | **Metric**                            | **Result**                    | **Interpretation**                                                                     |
| ------------------------ | ------------------------------------- | ----------------------------- | -------------------------------------------------------------------------------------- |
| **HTTP Performance**     | **Total Requests Made**               | **3,193 requests (≈3.2K)**    | Total number of HTTP requests sent during the entire spike test.                       |
|                          | **HTTP Failures**                     | **0 (0%)**                    | No failed or timed-out requests — excellent API stability.                             |
|                          | **Average Response Time**             | **≈ 44.93 ms**                | Fast response across all users, showing strong performance.                            |
|                          | **p95 Response Time**                 | **82 ms**                     | 95% of all requests completed in under 82 ms — very low latency even during peak load. |
| **Execution Metrics**    | **Virtual Users (VUs)**               | **Max: 100, Min: 1**          | Test successfully simulated up to 100 concurrent users during spike.                   |
|                          | **Iterations Completed**              | **3,193**                     | Each iteration represents one completed user action (GET request).                     |
| **Network Usage**        | **Data Received**                     | **≈ 89 MB (841 kB/s)**        | API responses received by k6 during the test.                                          |
|                          | **Data Sent**                         | **≈ 499 kB (4.7 kB/s)**       | Total request payloads sent to the API.                                                |
| **Resource Utilization** | **CPU / Memory (local test machine)** | **≈ 35–40% CPU, ~120 MB RAM** | Low resource usage on Ubuntu client during test generation.                            |

---
### Performance Summary Observation

#### Throughput	
- Measures how many requests the system can handle per second.
- Test achieved ~30 requests per second (RPS) on average and peak 91.67 RPS during the spike.
- This shows the API can handle high traffic smoothly without slowdown

#### Error Rate
- Shows the percentage of failed or timed-out requests.
- Test recorded 0% error rate — no failed requests.
- Indicates excellent stability and reliability under load.

#### Raw Data Presentation
<img width="1426" height="583" alt="image" src="https://github.com/user-attachments/assets/654a6e7a-cf89-4bf3-9ea3-b3eae82524a4" />

The graph shows how the system handled the spike test over time. As the number of virtual users increased, the request rate also rose sharply, reaching its peak during the spike phase. Despite the high load, the response time remained low and stable, and no errors occurred throughout the test. This indicates that the API maintained consistent performance and quickly recovered after the traffic returned to normal.

---
### Interpretation of Results
| **Aspect**        | **Observation / Result**                                | **Interpretation**                                                                            |
| ----------------- | ------------------------------------------------------- | --------------------------------------------------------------------------------------------- |
| **Response Time** | Average 44.93 ms, 95th percentile 81.43 ms              | The API responded quickly and consistently, maintaining low latency even during peak load.    |
| **Throughput**    | Peak 91.67 req/s, average 30.1 req/s                    | The system sustained high request rates efficiently throughout the spike phase.               |
| **Error Rate**    | 0% (no failed requests)                                 | All requests were completed successfully, indicating strong reliability and stability.        |
| **Recovery**      | Response time normalized after the spike load decreased | The system recovered smoothly and returned to its normal performance after traffic reduction. |
| **Network Usage** | 89 MB received, 499 kB sent                             | Network performance was stable and efficient, showing no delay or congestion.                 |

### Identified Bottlenecks
| **Component**                   | **Observation**                    | **Bottleneck Identified** | **Remarks**                                     |
| ------------------------------- | ---------------------------------- | ------------------------- | ----------------------------------------------- |
| **Server/API Performance**      | Stable response time and 0% errors | None detected           | The API efficiently handled all spike traffic.  |
| **Network**                     | No delay or packet loss observed   | None detected           | Network handled load well without slowdowns.    |
| **Load Handling (Concurrency)** | Smooth scaling to 100 VUs          | None detected           | System showed strong scalability and stability. |
| **Client Resource Usage**       | CPU ~35–40%, Memory ~120 MB        | None detected           | Load generator (k6) ran efficiently on Ubuntu.  |

---
### Recommendations

1. **Implement Auto-Scaling:**
   Enable automatic scaling of servers or containers to handle sudden increases in user traffic and maintain stable performance.

2. **Use Load Balancing:**
   Distribute traffic evenly across multiple servers to prevent overload on a single node and ensure better reliability.

3. **Optimize Backend Performance:**
   Improve database queries, enable caching, and streamline backend code to reduce response time under heavy load.

4. **Monitor System Resources:**
   Continuously track CPU, memory, and network usage using Grafana or Prometheus to detect performance issues early.

5. **Conduct Regular Performance Tests:**
   Schedule periodic spike and stress tests to ensure the system remains stable and responsive as user demand grows.

---
### Conclusion

The spike test conducted using Grafana k6 on the JSONPlaceholder API successfully demonstrated the system’s ability to handle sudden increases in user load. Throughout the test, the API maintained fast response times, stable throughput, and recorded a 0% error rate, even when traffic spiked to 100 virtual users.

The results show that the target API is highly responsive and resilient, with no significant performance degradation or failures observed. The system quickly recovered after the spike phase, indicating strong stability and efficient resource utilization.

Overall, the test confirms that the API can manage unexpected surges in traffic while maintaining excellent performance, making it reliable for high-demand or production-like environments.

---
### YouTube Demo:  [Click to Watch Demonstration Video](https://youtu.be/jvD_tTaQw-0)
