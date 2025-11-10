# 💻 Analyzing Banking Web Application Stability Through Spike Testing  

---

## 👤 Author Information
**Name:** MUHAMMAD WAFIY SUFI BIN KAMARUDDIN  
**Group:** M3CS2554C  

---

## 🧭 Table of Contents
- [🧩 Introduction](#-introduction)
- [🎯 Objective](#-objective)
- [🗺️ Scope](#️-scope)
- [🧰 Tool Used](#-tool-used)
- [🧠 Test Plan](#-test-plan)
- [📊 Test Summary – 200 Users](#-test-summary--200-users)
- [📈 Locust Graph Result (200 Users)](#-locust-graph-result-200-users)
- [📊 Test Summary – 1000 Users](#-test-summary--1000-users)
- [📈 Locust Graph Result (1000 Users)](#-locust-graph-result-1000-users)
- [🧾 Summary](#-summary)

---

## 🧩 Introduction  
This report presents the results of **spike testing** conducted on the **Parabank web application** — a dummy online banking site used for testing purposes.  

💥 The goal is to observe how the system handles sudden increases in user load and how it recovers once the traffic drops.

---

## 🎯 Objective  
- ⚡ To evaluate system performance during sudden user load spikes.  
- 📈 To monitor response time, error rate, and recovery time.  
- 🛡️ To assess the stability and reliability of the Parabank website.

---

## 🗺️ Scope  
The Spike Test focuses on:  
- 🔐 Login page performance  
- 💳 Checkout process under high load  

---

## 🧰 Tool Used  

| 🧪 Tool | 🔍 Purpose |
|-----------|-----------|
| ⚙️ **Locust** | Load and spike testing tool | 
| 🏦 **Parabank** | Dummy banking website for testing |

---

## 🧠 Test Plan  

| 🕓 Phase | ⚙️ Action | ⏱️ Duration | 👥 No. of Users |
|-----------|-----------|-----------|-----------|
| 🟢 **Baseline Test** | Normal Load Testing | 1 Minute | 1 User |
| 🟠 **Spike Test 1** | Sudden Increase | 1 Minute | 200 Users |
| 🔴 **Spike Test 2** | Extreme Load | 2 Minutes | 1000 Users |

---

## 📊 Test Summary – 200 Users  

| 🕒 Time Period  | 👥 Number of Users | ⏱️ Response Time (ms) | 📡 Total Requests Per Second |
|-----------|-----------|-----------|-----------|
| **11:01 PM - 11:10 PM** | Ramps up linearly from 0 to ~200 users. | Both 50th and 95th percentiles rise linearly, showing the system is getting slower under load. | 🟢 RPS: Stable <br> 🔴 Failures/s: Flat at 0 |
| **11:10 PM** | Reaches the maximum load of ~200 users. | Response times (especially 95th percentile) shoot up to over **2,000 ms (2 seconds)**. | 🔴 Failures/s: Spikes sharply from 0 to over 60 failures/second. |
| **11:10:20 PM – 11:11 PM** | Load held steady at ~200 users. | Response times drop suddenly — misleading, as requests are failing instantly. | 🔴 Failures/s: Stays high, showing the system continuously failing under load. |

---

## 📈 Locust Graph Result (200 Users)
<p align="center">
  <img width="700" alt="total_requests_per_second_1761750658 657" src="https://github.com/user-attachments/assets/29d97a47-b335-477f-9168-39afd6069f0c" />
</p>

---

## 📊 Test Summary – 1000 Users  

| 🕒 Time Period  | 👥 Number of Users | ⏱️ Response Time (ms) | 📡 Total Requests Per Second |
|-----------|-----------|-----------|-----------|
| **11:02** | 200 Users | 0 ms | 🟢 50th Percentile: Stable & very low (near 0 ms) <br> 🟣 95th Percentile: Stable & very low (near 0 ms) <br> ✅ RPS: Low and Stable <br> ❌ Failures: 0 |
| **11:19** | 1000 Users | 50th Percentile jumps to ~1,000–2,000 ms (1–2 seconds). | ⚠️ Huge gap shows inconsistent user experience and reduced system stability. |

---

## 📈 Locust Graph Result (1000 Users)
<p align="center">
  <img width="700" alt="total_requests_per_second_1761751165 101" src="https://github.com/user-attachments/assets/d6f172fb-d5d4-4bdf-b5a3-445f85c0e691" />
</p>

---

## 🧾 Summary
🧠 The spike testing results show that **Parabank performs well under low to moderate loads**, but **struggles significantly when the user count spikes to 200 or beyond**.  
⚙️ High response times and rising failure rates indicate potential bottlenecks in the backend or database handling under stress.  

📌 **Recommendation:**  
- Optimize backend load handling.  
- Improve database query efficiency.  
- Implement caching and scalable architecture to enhance resilience during traffic spikes.  

---

<p align="center">
  🚀 *[Video Link : (https://youtu.be/QZkTbFNKAcM) — Banking Web App Stability Analysis by Wafiy Sufi*
</p>
