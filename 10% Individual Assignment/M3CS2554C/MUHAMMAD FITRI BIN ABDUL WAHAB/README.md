# 🧪  Web Application Performance Testing & Analysis  
## Title: Load Testing of FakeStoreAPI Using Grafana K6  

### 👤 Author  
| **Name:** | MUHAMMAD FITRI BIN ABDUL WAHAB  |  
|-----------|-------------|
| **Student ID:** |2025172963  |
| **Course:** |ITT440 – Network Programming  |
| **Institution:** |UiTM Kampus Jasin |

---

## 📚 Background

This project focuses on evaluating how well a web API performs when accessed by multiple users at the same time.  
The testing tool used is **Grafana K6**, which generates **virtual users (VUs)** that behave like real client traffic.

We performed **two types of Load Tests** to compare performance:
| Test Type | Virtual Users | Purpose |
|----------|--------------|----------|
| **Normal Load Test** | 50 VUs | Simulates average expected usage |
| **Heavy Load Test** | 100 VUs | Maximum cloud capacity & stress comparison |

---

## 🎯  Objective  

The purpose of this project is to perform a **Load Test** on a public web application using **K6**, a modern and developer-friendly load testing tool.  

The objective of this experiment is to evaluate:
- Response time under increasing load
- Throughput and request handling efficiency
- System stability during continuous access
- Performance degradation when stressed

---

## ⚙️  Tool Selection Justification  

### 🔸 Why Grafana K6?  
<img width="200" height="174" alt="k6 logo" src="https://github.com/user-attachments/assets/4695c7f3-f91f-4b71-887c-fabcbfc25044" />

Grafana K6 was selected due to its simplicity, lightweight setup, and developer-friendly scripting language (JavaScript).  
Compared to other tools, K6 offers:
- Easier scripting and execution from the command line  
- Faster performance with minimal resource usage  
- Built-in metrics summary and Grafana integration for visualization  

---

## 🌐  Target Web Application  

**Web Application :** [FakeStoreAPI](https://fakestoreapi.com/)  
**Description:** A free online API for testing and prototyping e-commerce applications.  
**Sample Endpoint Used:**  `https://fakestoreapi.com/products`

---

## 🧰  Test Environment Setup  

| Component | Description |
|----------|-------------|
| **Operating System** | Windows 11 |
| **Load Testing Tool** | Grafana K6 |
| **Result Visualization** | Grafana Cloud Dashboard |
| **Execution Platform** | Windows Command Prompt |
| **Target URL** | `https://fakestoreapi.com/products` |

---

## ⚙️ Test Scipts 
### 1️⃣ Normal Load Test (50 VUs)
`Nloadtest.js`
   ```javascript
    import http from 'k6/http';  
    import { sleep } from 'k6';  
    
    export const options = {  
      vus: 50,         // Number of virtual users  
      duration: '30s', // Test duration  
      };  
    export default function () {  
      // Target: FakeStoreAPI 
      const res = http.get('https://fakestoreapi.com/products');  
      sleep(1); // Simulate user wait time between requests  
      }
   ```
### 2️⃣ Heavy Load Test (100 VUs)
`Hloadtest.js`
   ```javascript
    import http from 'k6/http';
    import { sleep } from 'k6';

    export const options = {
      vus: 100,
      duration: '30s',
    };

    export default function () {
      http.get('https://fakestoreapi.com/products');
      sleep(1);
}

   ```
---

## ▶️ Step-by-Step Instructions to Run the Tests 
Step 1 — Login to Grafana Cloud Using Token  
```bash
k6 cloud login --token <TOKEN>
```  

Step 2 — Run Normal Load Test  
```bash  
k6 run --out cloud Nloadtest.js
```  

Step 3 — Run Heavy Load Test  
```bash  
k6 run --out cloud Hloadtest.js
```

Step 4 — View Results
   1. Open Grafana Cloud Dashboard
   2. Go to k6 Test Runs
   3. Select the run history to view:  
      Requests per Second  
      Response Time (http_req_duration)  
      Failure Rate  
      VU Load Behavior  

--- 

## 📊 Results & Analysis
### 1️⃣ Normal Load Test (50 VUs)  

|  <img width="1435" height="942" alt="image" src="https://github.com/user-attachments/assets/6e09223a-84f1-443a-ab40-bda039c7cb55" />  |
|---|
|  Graph Analysis:  |  
|  <img width="1451" height="598" alt="image" src="https://github.com/user-attachments/assets/8eebc302-a28d-4d0a-8b0d-1cb495cf5cce" />  |


### 2️⃣ Heavy Load Test (100 VUs)  

|  <img width="1357" height="808" alt="hloatest result" src="https://github.com/user-attachments/assets/4eb7aa32-718a-4788-ae8a-d0e010b687e7" />  |
|---|
|  Graph Analysis:  |  
|  <img width="1448" height="597" alt="image" src="https://github.com/user-attachments/assets/990a8d8a-a0c9-4c53-8cb6-e8edc7b8ce2b" />  |

## ⚖️ Performance Comparison (Normal Load vs Heavy Load)  

|  Graph:  |
|---|
|  <img width="1465" height="726" alt="graph compare" src="https://github.com/user-attachments/assets/b580cd35-c241-4e86-8b69-5912fbeb34e1" />  |


| Test Condition | Normal Load Test | Heavy Load Test |
|---|---|---|
| **Virtual Users (VUs)** | **50 VUs** | **100 VUs** |
| **Test Duration** | 30 seconds | 30 seconds |
| **P95 Response Time** | **888 ms** | **42,087 ms (42 seconds)** |
| **Peak Request Rate (RPS)** | 36 req/s | 43 req/s |
| **Total Requests Made** | 1,000 requests | 530 requests |
| **HTTP Failure Rate** | 0 failures | 0 failures |
| **Performance Behavior** | Stable and responsive | Severe slowdown, high latency |
| **Scalability Observation** | System handles moderate traffic well | System struggles with heavy concurrency |

---

## 🔍 Bottlenecks Identified

| Issue | Observation | Impact |
|------|-------------|--------|
| **Response Time Increased** | Response time rose from 888 ms (50 VU) to 10s (100 VU). | Slower user experience under heavier traffic. |
| **Throughput Decreased** | Fewer requests were completed during the heavy test. | System cannot handle many concurrent users efficiently. |
| **Possible Backend Resource Limits** | Server performance drops when load increases. | Indicates CPU / Memory / Database constraints. |
| **No Caching Detected** | Same data fetched repeatedly without caching. | Increases unnecessary server work. |

---  

## 💡 Simple Recommendations for Improvement

| Improvement | Benefit |
|------------|----------|
| **Enable server-side caching** (store product list temporarily in memory) | Reduces repeated database calls and speeds up response time. |
| **Optimize database queries** (indexing / reduce unnecessary joins) | Improves data retrieval efficiency and lowers response latency. |
| **Increase server resources or introduce auto-scaling** | Allows the system to handle more concurrent users without performance drop. |
| **Use CDN caching for static or rarely-changing data** | Delivers content faster to users globally. |
| **Implement load balancing across multiple API servers** | Distributes traffic evenly, improving stability and scalability. |  

---

## 🏁 Conclusion  

Based on the results, the performance threshold of the FakeStoreAPI appears to be around 50 concurrent users. At this level, the system operates efficiently with quick response times and stable throughput. However, when the load increases to 100 concurrent users, the response time deteriorates sharply. This indicates limited scalability and suggests that the system may require optimization or resource scaling to support heavier traffic loads.  

---
## 🎥 Demonstration Video
Below is the link for the demonstration video for the load testing  
https://youtu.be/k5N3uuRyptU?si=Bwy-XnpSgZuY4_R7  

## 📔 References  
Grafana Labs. (n.d.). Grafana k6 | Open source load testing tool. Retrieved November 9, 2025, from https://grafana.com/oss/k6/  
Moradian, M. (2019, June 17). Beginner’s guide to load testing with k6 [Blog post]. Medium. https://medium.com/swlh/beginners-guide-to-load-testing-with-k6-85ec614d2f0d  
Grafana Labs. (2021, August 26). How to do performance testing with k6 [Video]. YouTube. https://youtu.be/ghuo8m7AXEM  


