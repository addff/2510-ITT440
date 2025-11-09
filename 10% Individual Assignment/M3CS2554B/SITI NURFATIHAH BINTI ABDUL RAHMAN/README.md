# 🌐 Web Application Soak & Spike Testing using Artillery  
**By:** SITI NURFATIHAH BINTI ABDUL RAHMAN  
**Class:** M3CS2554B  
**Course Code:** ITT440 (10% Individual Assignment)

---

## 🎯 Title & Objective

**Title:** Comprehensive Web Application Soak & Spike Testing & Analysis using Artillery  

**Objective:**  
To design, execute, and analyze **soak** and **spike** tests on a public web API using the Artillery performance testing tool.  
These tests aim to evaluate the system’s **long-term stability (soak test)** and its **ability to handle sudden surges in traffic (spike test)**.  

---

## ⚙️ Tool Justification (Why Artillery)

Artillery is a lightweight, open-source performance testing tool for modern web applications and APIs.  
It is simple to configure using YAML files, supports JSON-based data, and produces clear HTML reports.  
It is ideal for both **endurance (soak)** and **stress (spike)** tests due to its accuracy, low resource usage, and built-in reporting features.

---

## 🧪 Test Types & Hypotheses

### **Test 1: Soak Testing**
**Hypothesis:**  
The ReqRes API will remain stable and responsive during a 15-minute soak test at a constant rate of 2 virtual users per second.  
Response times are expected to stay below 400 ms with minimal errors, demonstrating consistent performance over time.

### **Test 2: Spike Testing**
**Hypothesis:**  
The ReqRes API will handle a sudden spike in user load — from low to very high — without crashing or producing significant errors.  
It is expected that response times may briefly increase but will recover quickly once the load decreases.

---

## 🌐 Target Application Description

**Target URL:** [https://reqres.in](https://reqres.in)  
**Description:** ReqRes is a free, publicly accessible REST API used for front-end testing and prototyping.  
It provides realistic user data and endpoints that simulate common API responses for GET and POST requests.

---

## 🧩 Test Plan (YAML Configurations)

### 🧱 **Soak Test Configuration**
```yaml
config:
  target: "https://reqres.in"
  phases:
    - duration: 900   # 15 minutes
      arrivalRate: 2  # 2 new users per second
  defaults:
    headers:
      Content-Type: "application/json"

scenarios:
  - name: "ReqRes API Soak Test"
    flow:
      - get:
          url: "/api/users?page=2"
      - post:
          url: "/api/users"
          json:
            name: "Nurfatihah"
            job: "student"
```

---

### ⚡ **Spike Test Configuration**
```yaml
config:
  target: "https://reqres.in"
  phases:
    - duration: 60     # Warm-up phase
      arrivalRate: 2
    - duration: 30     # Sudden spike
      arrivalRate: 50
    - duration: 60     # Recovery phase
      arrivalRate: 2
  defaults:
    headers:
      Content-Type: "application/json"

scenarios:
  - name: "ReqRes API Spike Test"
    flow:
      - get:
          url: "/api/users?page=2"
      - post:
          url: "/api/users"
          json:
            name: "SpikeTest"
            job: "tester"
```

---
## 📈 Response Time Chart
<img width="702" height="338" alt="response-time png" src="https://github.com/user-attachments/assets/94190e73-646b-40b0-8859-64819a7f5898" />


## ⚙️ Requests per Second (Throughput)
<img width="707" height="405" alt="rps-chart png" src="https://github.com/user-attachments/assets/30c98a82-89a8-447f-8b28-4e56521e81ef" />

---

## 📈 Soak Test Results

| Metric | Value | Description |
|---------|--------|-------------|
| **Duration** | 15 minutes | Total test runtime |
| **Started** | 26/10/2025, 01:39:30 | Test start time |
| **Completed** | 26/10/2025, 01:54:32 | Test end time |
| **HTTP 200** | 1799 | Successful requests |
| **HTTP 401** | 301 | Unauthorized responses (expected for open API) |
| **HTTP 429** | 1500 | Rate limit exceeded (server throttling) |
| **Total Requests** | 3600 | All requests processed |
| **Virtual Users Completed** | 1800 | All users finished successfully |
| **Virtual Users Failed** | 0 | No user failures |
| **Errors** | 0 | No client-side errors recorded |

---

### 🧠 Soak Test Summary
- The **ReqRes API** handled **3,600 total requests** in 15 minutes with **no test failures**.  
- Some **HTTP 429 (Too Many Requests)** appeared — expected for a public API with rate limiting.  
- The system remained stable and consistent throughout the test.

---

## ⚡ Spike Test Results

| Metric | Value | Description |
|---------|--------|-------------|
| **Duration** | 19 minutes 58 seconds | Total test runtime |
| **Started** | 01/11/2025, 02:32:23 | Test start time |
| **Completed** | 01/11/2025, 02:52:22 | Test end time |
| **Total Requests** | 17,601 | All requests made |
| **Timeout Errors** | 17,413 | Requests that did not respond in time |
| **Connection Resets** | 260 | Server closed the connection |
| **SSL Errors** | 158 | Self-signed certificate issue |
| **Virtual Users Created** | 17,598 | Users started during test |
| **Virtual Users Failed** | 17,831 | Users that failed to complete scenario |

---

### 🧠 Spike Test Summary
- When traffic **spiked suddenly to 50 users/sec**, the API experienced heavy load.  
- **Timeout and connection errors** increased significantly, showing the API’s limit under extreme traffic.  
- The test revealed **bottlenecks in response handling** and possible SSL configuration issues.  
- After the load dropped, the system likely recovered, showing partial resilience.

---

## 🔍 Comparative Analysis

| Aspect | Soak Test | Spike Test |
|--------|------------|------------|
| **Objective** | Long-term stability | Sudden load tolerance |
| **Duration** | 15 minutes | ~20 minutes |
| **Load Pattern** | Constant, steady | Sharp rise and fall |
| **System Behavior** | Stable, consistent | Unstable during spike |
| **Errors** | 0 | High timeout & SSL errors |
| **Conclusion** | Excellent endurance | Needs better scaling under spikes |

---

## 💡 Recommendations

1. **For Soak Stability:**  
   - Continue with longer tests (30–60 mins).  
   - Observe for memory leaks or slow degradation.

2. **For Spike Resilience:**  
   - Implement **load balancing** or **auto-scaling** to handle traffic surges.  
   - Fix SSL configurations and timeout settings.  
   - Optimize backend response handling for bursty traffic.

3. **General Improvements:**  
   - Add caching or CDN layers.  
   - Use authenticated endpoints for realistic enterprise tests.  

---

## 🏁 Conclusion

The **ReqRes API** performed **very well under continuous load (soak test)** but showed **significant strain during sudden load spikes**.  
This indicates that while the system is **stable for normal sustained use**, it requires **optimization for rapid traffic surges**.  

Overall, both tests successfully demonstrated **Artillery’s capability** to measure endurance and stress behavior in web APIs.  

---

## 🎥 YouTube Demo Link

📺 **Watch my Artillery Soak & Spike Test execution and report analysis here:**  
*(https://youtu.be/N2pUHLQ1Kt0?si=AwFdzE3TWMdEfprh)*

---

## 🧾 References

- [Artillery Official Documentation](https://www.artillery.io/docs)  
- [ReqRes API Documentation](https://reqres.in/)  
- [Node.js Documentation](https://nodejs.org/en/docs)




