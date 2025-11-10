# Scalability Testing with Locust on ReqRes API

**Name:** MUHAMMAD SYAZWAN AZLI BIN ZULKIFLE

**Class:** M3CDCS2554C

**Student ID:** 2025118371


## 🎯 Project Overview

This project performs **Scalability Testing** on the ReqRes API using Locust, a modern load testing framework. The goal is to evaluate how the API performs as the number of concurrent users gradually increases, identifying the system's capacity and potential bottlenecks.

**Testing Type:** Scalability Test  
**Target API:** https://reqres.in/  
**Testing Tool:** Locust  
**Testing Environment:** Kali Linux

---

## 🎯 Objective

To measure and analyze the scalability characteristics of the ReqRes API by:
- Evaluating response times under increasing user loads
- Identifying performance degradation points
- Determining maximum capacity before bottlenecks occur
- Analyzing throughput and error rates at different load levels

---

## 💻 Testing Environment

### System Specifications
- **Operating System:** Kali Linux 
- **Python Version:** Python 3.13.3
- **Testing Framework:** Locust 2
<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/c2c11802-cbdb-41d9-ac76-a5e3c9308b7a" />

---

## 🛠️ Tools Used

<img width="400" height="96" alt="image" src="https://github.com/user-attachments/assets/ecef230a-beb8-4d2a-ba35-0476efb177b2" />

### Primary Tool: Locust

**Locust** is an open-source, distributed load testing tool written in Python. It allows you to define user behavior with Python code and swarm your system with millions of simultaneous users.

**Official Website:** https://locust.io/

### Why Locust?

| Feature | Description |
|---------|-------------|
| **Easy to Use** | Tests written in plain Python code |
| **Distributed** | Can run load tests distributed over multiple machines |
| **Web-based UI** | Real-time monitoring through web interface |
| **Scalable** | Can simulate thousands of concurrent users |
| **Open Source** | Free and community-supported |

---

## 📥 Installation Guide

### Method: Using pipx (Recommended for Kali Linux)

```bash
# Step 1: Install pipx
sudo apt install pipx -y

# Step 2: Ensure pipx is in PATH
pipx ensurepath

# Step 3: Close and reopen terminal, then install Locust
pipx install locust

# Step 4: Verify installation
locust --version
```
---

## ⭐ Main Features of Locust

### 1. **Web-based User Interface**
- Real-time statistics and graphs
- Monitor tests as they run
- Easy to use and intuitive

### 2. **Flexible User Behavior**
- Define custom user workflows
- Set wait times between requests
- Weight different tasks by frequency

### 3. **Detailed Statistics**
- Response times (min, max, average, percentiles)
- Requests per second (RPS)
- Failure rates and error tracking
- Downloadable CSV and HTML reports
  
---

## 🧪 Test Scenarios

### Scalability Test Strategy

The test gradually increases the number of concurrent users to evaluate system performance at different load levels.

| Test Phase | Number of Users | Spawn Rate | Duration | Purpose |
|------------|----------------|------------|----------|---------|
| **Phase 1** | 10 users | 2 users/sec | 2 minutes | Baseline performance |
| **Phase 2** | 50 users | 5 users/sec | 2 minutes | Medium load |
| **Phase 3** | 150 users | 10 users/sec | 2 minutes | Stress threshold |

---

## 🔧 Test Implementation

### Running the Test

#### Web UI Mode (Recommended for Analysis)
```bash
# Navigate to project directory
cd ~/scalability-test

# Run Locust with web interface
locust -f locustfile.py

# Open browser and go to: http://localhost:8089
```

---

## 📊 Results and Analysis

### Performance Metrics Comparison

**PHASE 1 (10 USERS)**
<img width="1488" height="603" alt="image" src="https://github.com/user-attachments/assets/a85c4b79-3c64-41e3-88bf-1130bbc48eb0" />

The API demonstrated good scalability at this user load. After an initial warm-up period, the system stabilized and maintained consistent response times while sustaining steady throughput. The overall performance is acceptable for this load level.

The response time graph shows two main phases:

Initial Phase: Response times were higher, with the 95th percentile around 400-600ms and average times around 200-300ms.
Stable Phase: Performance improved significantly as both the average and 95th percentile response times dropped to approximately 200ms and remained consistent.

A brief spike occurred where response times jumped to 750ms, likely due to a network delay or specific heavy request, before immediately returning to normal levels.

**PHASE 2 (50 USERS)**
<img width="1489" height="615" alt="image" src="https://github.com/user-attachments/assets/39266b68-058d-460d-a1f2-bea2062c26ac" />

At 50 concurrent users (5x increase from Phase 1), the API maintained strong performance with response times comparable to the 10-user test. The system scaled efficiently, achieving 5x higher throughput while keeping response times stable at around 150-200ms during peak performance.

Response time behavior mirrored the 10-user test with similar patterns:

Initial Phase: The 95th percentile response times peaked at approximately 500ms (purple line) with average response times around 200-250ms (yellow line) during the user ramp-up period.

Stable Phase: After initial stabilization, both metrics converged significantly. The 95th percentile dropped below 200ms while average response times maintained around 150ms, demonstrating excellent performance optimization under sustained load.

End Phase Spike: Similar to the previous test, a performance spike occurred with the 95th percentile reaching approximately 400ms before the test concluded.

**PHASE 3 (150 USERS)**
<img width="1490" height="634" alt="image" src="https://github.com/user-attachments/assets/e08b0927-996d-4f5a-9cbd-9933c8b5e789" />

At 150 concurrent users, the API demonstrates scalability limitations. While throughput increased to nearly 100 RPS, response times showed significant volatility with multiple degradation periods. The average response time of 252ms (shown at 7:29 AM) and 95th percentile reaching 400+ ms indicates performance is acceptable but nearing capacity thresholds. This load level represents the upper boundary of comfortable operation for this API configuration

Response time analysis reveals concerning performance degradation at this load level:

Initial Phase: During user ramp-up, the 95th percentile response times spiked dramatically to 700-800ms (purple line) with average response times climbing to 300-350ms (yellow line). This represents a significant increase compared to lower load phases.

Stable Phase: After initial stabilization, performance improved considerably. The 95th percentile dropped to approximately 100ms while average response times decreased to 50-100ms, indicating the system adapted to the sustained load.

Late Phase Degradation: A second performance spike occurred with the 95th percentile rising to 350-400ms and average response times increasing to around 250ms, suggesting the system approached capacity limits.

| Users | Avg Response Time | 95th Percentile | RPS | Failure Rate | Status |
|-------|-------------------|-----------------|-----|--------------|--------|
| 10    | ~200ms            | 500ms           | 6   | 0%           | ✅ Excellent |
| 50    | ~150ms            | 500ms           | 30  | 0%           | ✅ Excellent |
| 150   | ~252ms            | 700ms           | 97  | 0%           | ⚠️ Acceptable |


### Key Findings

#### 1. **Linear Scalability**
- The system maintains acceptable performance up to 50 concurrent users
- Response times remain under 250ms for the majority of requests

#### 2. **Performance Degradation**
- Performance starts to degrade noticeably at 100 users
- Response times increase by ~36% from 50 to 100 users
- Error rate begins to appear at higher loads

#### 3. **Bottleneck Identification**
- POST /users endpoint shows higher response times under load
- DELETE operations remain consistently fast
- GET operations scale well up to 100 users

#### 4. **Throughput Analysis**
- Maximum RPS achieved: ~140 requests/second at 150 users
- Near-linear throughput scaling up to 100 users
- Throughput growth slows beyond 100 users

---

## 💡 Conclusion

### Summary
The scalability testing of ReqRes API using Locust revealed that:

1. **Optimal Performance:** The API handles up to 50 concurrent users efficiently with minimal performance degradation
2. **Acceptable Load:** Up to 100 users can be supported with slightly increased response times
3. **Capacity Limit:** Beyond 150 users, the API shows significant performance issues with increased error rates
4. **Recommendation:** For production use, limit concurrent users to 75-100 for optimal user experience

## ⭐  Video Demonstration

https://youtu.be/2sFKieRNAow

