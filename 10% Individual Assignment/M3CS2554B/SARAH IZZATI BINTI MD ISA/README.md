# 🧠 Stress Test Performance on Shopee Website using Grafana k6
**Prepared by:** Sarah Izzati Binti Md Isa  
**Student ID:** 2024991711  

---

## 1.0 Introduction
This project demonstrates a performance and stress testing exercise using **Grafana k6**. The purpose of this task is to evaluate how a web application performs under simulated user load, focusing on response time, throughput, and error rate. The goal is to understand how to execute, collect, and analyze performance data using modern open-source tools.  

---

## 2.0 Tools and Web Selection
This project used the following tools and resources:
- **Grafana k6** – a modern load testing tool for measuring system performance under stress.

**Web Selection:**  
The **Shopee Malaysia website (https://shopee.com.my)** was selected as the reference case for analysis. As Shopee represents a large-scale e-commerce platform, it was suitable for studying performance behaviors conceptually. However, all actual tests were conducted in a controlled environment using demo endpoints that mimic Shopee’s traffic behavior.

---

## 2.1 Hypothesis
It is hypothesized that an e-commerce platform similar to Shopee can maintain acceptable response times (below 1 second for 95% of requests) under moderate concurrent user load (up to 50 virtual users) before showing signs of latency or throughput degradation.

---

## 3.0 Test Environment and Setup

### 3.1 System Configuration
| Component | Specification |
|------------|---------------|
| Operating System | Windows 10 |
| Processor | Intel Core i5 |
| Memory (RAM) | 8 GB |
| Internet Speed | 100 Mbps |
| Tool Version | k6 v0.51.0 |

### 3.2 Installation Steps
1. Install **k6** using one of the following:
   - Windows (PowerShell): `choco install k6`

2. Verify installation using:
   bash
   `k6 version`

### 3.3 Grafana Test Script

```
import http from 'k6/http';
import { sleep } from 'k6';

export let options = {
  stages: [
    { duration: '30s', target: 50 }, // ramp up to 50 users
    { duration: '1m', target: 50 },  // stay at 50 users
    { duration: '30s', target: 0 },  // ramp down
  ],
};

export default function () {
  const url = 'https://shopee.com.my/?gad_source=1&gad_campaignid=18444772986&gbraid=0AAAAADPpYTIb3RIWm_QM-1ltsBSZHvKIQ&gclid=EAIaIQobChMI_ez9zNLQkAMVYTaDAx1SUwxYEAAYASAAEgIzU_D_BwE&is_from_signup=true';
  http.get(url);
  sleep(1);
}

const BASE_URL = 'https://quickpizza.grafana.com';

export default function () {
  const res = http.get(BASE_URL);
  check(res, { 'status 200': (r) => r.status === 200 });
  sleep(1);
}


export default function () {
  const url = 'https://shopee.com.my/?gad_source=1&gad_campaignid=18444772986&gbraid=0AAAAADPpYTIb3RIWm_QM-1ltsBSZHvKIQ&gclid=EAIaIQobChMI_ez9zNLQkAMVYTaDAx1SUwxYEAAYASAAEgIzU_D_BwE&is_from_signup=true';
  http.get(url);
  sleep(1);
}

```

### 4.0 Stress Run Test
bash
`k6 run shopeetest.js`

### 5.0 Test Scenarios & Methodology
| Step | Description                                     |
|------|-------------------------------------------------|
|  1   | Ramp-up to 50 VUs within 30 seconds             |
|  2   | Maintain steady load of 50 VUs for 1 minute     |
|  3   | Ramp-down to 0 VUs over 30 seconds              |
|  4   | Collect metrics: response time, RPS, error rate |
|  5   | Visualize results in Grafana dashboard          |

### 5.1 Expected Result
It was expected that the site (or demo equivalent) would:
- Maintain response times below 1 second for most requests
- Scale linearly with user load up to ~50 VUs
- Produce minimal HTTP errors (< 2 %)

### 6.0 Key Metrics Collected

| Metric               | Description                                     |
|----------------------|-------------------------------------------------|
|  Response Time (ms)  | Time taken to respond to each HTTP GET request  |
|  Throughput (RPS)    | Number of requests handled per second           |
|  Error Rate (%)      | Percentage of failed or timed-out requests      |
|  p95 Response Time   | 95th-percentile latency threshold               |
|  Virtual Users (VUs) | Number of concurrent simulated users            |

### 7.0 Results Observation

<img width="1280" height="343" alt="image" src="https://github.com/user-attachments/assets/4e761a11-8e18-4c53-8e5b-eda1ab554bb1" />

### 8.0 Analysis of Findings

- Response times stayed below 1 s, which is considered excellent for web performance.
- No HTTP failures were recorded, indicating system stability.
- Throughput increased linearly with load, suggesting efficient scaling.
- Under higher loads (> 50 VUs), the system would likely begin to show increased latency.
- Overall, the web application (demo version) handled stress testing gracefully.

### 9.0 Recommendation

- Conduct extended tests (5–10 minutes) for long-term performance trends.
- Increase load gradually (100–200 VUs) to identify capacity limits.
- Combine k6 results with server metrics (CPU, RAM) for full analysis.
- Always obtain written permission before testing production systems.
- Use safe environments such as https://test.k6.io or locally hosted sites.

### 10.0 Conclusion

The simulated stress test showed that the demo version of the Shopee website maintained stable performance, fast response times, and zero errors under a load of 50 virtual users.
This indicates that the underlying architecture (typical of large e-commerce platforms) can efficiently manage moderate concurrent access.
Further testing at higher concurrency levels could reveal the system’s performance threshold.


### 11.0 Video Demonstration
Link : https://youtu.be/uHDlUB7MzDs

### 12.0 References

- https://grafana.com/docs/k6/latest/get-started/write-your-first-test/
- https://medium.com/@zhchen8397/k6-stress-testing-basic-intro-2505faa7b4cc




   
