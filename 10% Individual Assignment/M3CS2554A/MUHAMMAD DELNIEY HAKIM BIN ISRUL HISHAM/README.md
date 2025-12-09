# Comprehensive Web Application Performance Testing & Analysis
**Student Name:** [MUHAMMAD DELNIEY HAKIM BIN ISRUL HISHAM]  
**Course Code:** ITT440  
**Group:** M3CS2554A
**Tool Used:** Apache JMeter 5.6.3  
**Target Web Application:** https://httpbin.org  

---

## 1. Introduction
This project demonstrates how to perform web application performance testing using Apache JMeter.  
The goal is to measure system behavior and response time under different user loads — Load Test, Stress Test, and Soak Test.  
Performance testing ensures that a website can handle multiple users efficiently and identify bottlenecks before deployment.

---

## 2. Tool Selection
Apache JMeter was chosen because it is a free, open-source, and powerful tool for load testing web applications.  
It supports multiple protocols such as HTTP, HTTPS, FTP, and REST APIs, and provides clear graphical reports.  
JMeter can also run in both GUI and command-line (Non-GUI) mode, which makes it suitable for automated testing.

---

## 3. Test Environment
| Component | Description |
|------------|--------------|
| **Tool Used** | Apache JMeter |
| **Operating System** | Windows 10 64-bit |
| **Processor** |  AMD Ryzen 5 |
| **RAM** | 8 GB |
| **Network** | Stable Internet Connection |
| **Recording Tool** | OBS Studio |
| **Tool Version** | Apache JMeter 5.6.3 |
| **Target Website** | https://httpbin.org |

---

## 4. Test Plan and Configuration

### Load Test
| Parameter | Value |
|------------|--------|
| Threads (Users) | 10 |
| Ramp-Up Period | 10 seconds |
| Loop Count | 1 |
| Duration | N/A |

### Stress Test
| Parameter | Value |
|------------|--------|
| Threads (Users) | 10000 |
| Ramp-Up Period | 100 seconds |
| Loop Count | 2 |

### Soak Test
| Parameter | Value |
|------------|--------|
| Threads (Users) | 50 |
| Ramp-Up Period | 10 seconds |
| Duration | 900 seconds (15 minutes) |

---

## 5. Results

### Load Test

![Load Test Graph Summary Report]<img width="1540" height="702" alt="Summary_Report" src="https://github.com/user-attachments/assets/eb5a395b-ff07-4db8-a546-1cca8e7dbf4d" />

- **Average Response Time:** 7.06s  
- **Throughput:** 0.51 requests/sec  
- **Error Rate:** 0%
- **Network(Received):** 0.24 KB/sec 
- **Network(Send):** 0.06 KB/sec

### Stress Test

![Stress Test Graph Summary Report]<img width="1607" height="785" alt="Summary_Report" src="https://github.com/user-attachments/assets/d8badf33-66a6-45c1-91c4-a8ef9df928e4" />

- **Average Response Time:** 5.91s  
- **Throughput:** 72.33 requests/sec  
- **Error Rate:** 47.22%
- **Network(Received):** 111.96 KB/sec 
- **Network(Send):** 4.21 KB/sec

### Soak Test

![Soak Test Graph Summary Report]<img width="1577" height="742" alt="Summary_Report" src="https://github.com/user-attachments/assets/74e3759e-f571-4fc3-99f4-74aaed19f743" />

- **Average Response Time:** 3.8s  
- **Throughput:** 16.03 requests/sec 
- **Error Rate:** 0.42%  
- **Network(Received):** 7.61 KB/sec 
- **Network(Send):** 1.75 KB/sec
---

## 6. Analysis and interpretation
### Load Test
- Average response time between 100–300 ms. Maximum response time was slightly higher due to network. Minimum response time below 100 ms indicates a responsive server.
- 0% error rate during the test. No connection failures or errors were detected. The server operated stably under light load.
- Throughput remained stable around 80–100 req/sec. No signs of resource exhaustion (CPU/RAM). Tests showed consistent performance.
### Stress Test
- Error Rate (47%) – Indicates that the server is starting to fail to provide stable responses when user pressure is too high. Error code 503 (Service Temporarily Unavailable) indicates server overload.
- High Response Time (Average > 43s) – This indicates that requests are taking too long to process, indicating a possible bottleneck in the connection or server capacity.
- Latency & Connect Time – A high connect time (41s) means that the time to open a connection to the server increases dramatically, indicating network congestion or a limit on simultaneous connections.
- Throughput (72 req/sec) – Although it seems high, this number is actually low for 10,000 users because the majority of requests fail.
### Soak Test
- The average response time was 3.08 seconds, showing consistent and stable performance throughout the test period. There was no significant increase in response time even though the test was run for 15 minutes (900 seconds). Showing that the server is able to maintain response speed over the long term.
- The error rate is less than 1%, indicating excellent server stability. A few HTTP 502 (Bad Gateway) errors were detected, indicating minor connection disruptions during light loads. There are no signs of critical issues; the server remains responsive and functioning normally.
- The throughput value was recorded at 16.03 requests per second, showing a smooth and efficient processing rate. Performance remained stable with 50 concurrent users and a 10 second ramp-up. There was no significant drop in throughput, indicating that the server was able to maintain a continuous workload without any problems.

---

## 7. Recommendations
1. Implement caching for frequently accessed data.  
2. Optimize database queries.  
3. Introduce load balancing for traffic distribution.  
4. Use CDN for static resources.  
5. Monitor performance regularly.

---

## 8. Conclusion
Apache JMeter successfully helped measure performance under various load conditions.  
The target website showed stable performance under normal and long-duration tests, but experienced slowdowns under stress.  
By applying optimization strategies, scalability and responsiveness can be improved.

---

## 9. Video Demonstration
🎥 [Watch My Demo on YouTube](https://youtu.be/C4iCHKYThDU)
