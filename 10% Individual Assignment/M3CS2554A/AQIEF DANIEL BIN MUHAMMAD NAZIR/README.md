# ⚡ Optimization on WordPress Using k6  
![Made with k6](https://img.shields.io/badge/Made%20with-k6-4B3263?style=for-the-badge&logo=k6)
![Built on WordPress](https://img.shields.io/badge/Platform-WordPress-blue?style=for-the-badge&logo=wordpress)
![Performance Testing](https://img.shields.io/badge/Tested%20With-Grafana%20k6-green?style=for-the-badge&logo=grafana)

### 👨‍💻 Name: Aqief Daniel Bin Muhammad Nazir  
### 🎓 Student ID: 2024******  
### 🧾 Course: ITT440 – Individual Assignment  
### 🧠 Group: M3CS2554A  

---

## 🪄 Introduction
This project demonstrates the use of **Grafana k6** to perform **performance verification on a WordPress website** hosted on a local environment.  
Instead of running multiple types of load tests, this version focuses solely on the **Smoke Test**, which serves as the **first and most crucial step** in ensuring that the web application is functioning properly before performing heavier evaluations such as load, stress, or soak tests.

WordPress is one of the most popular content management systems (CMS), but its performance can vary based on caching, server configuration, and plugin usage.  
The smoke test helps detect **basic performance or configuration issues** such as broken links, missing resources, or slow response times immediately after optimization.  
By validating only essential pages and ensuring all endpoints respond with **HTTP 200 OK**, the system can confirm that the optimization changes have been applied successfully.

---

## 🎯 Objectives
The main objectives of this project are as follows:

1. **To verify the stability and availability of WordPress endpoints** after applying optimization techniques such as caching and minification.  
2. **To ensure the application can handle light traffic (up to 5 virtual users)** without failures or slowdowns exceeding the defined latency threshold.  
3. **To validate that no critical errors (404/500) occur** during test execution.  
4. **To establish a baseline performance indicator** before conducting more advanced testing stages.  
5. **To confirm that the optimized environment meets the ITT440 performance evaluation standards** for speed and reliability.

---

## 🧰 Test Environment

| Component | Details |
|------------|----------|
| **Platform** | Localhost using XAMPP |
| **Server** | Apache 2.4.58 (PHP 8.0.30) |
| **Database** | MySQL 10.4 |
| **Tool** | Grafana k6 v1.3.0 |
| **Test Script** | `scripts/smoke.js` |
| **Results** | JSON file stored under `results/` |
| **BASE_URL** | `http://localhost/wordpress` |

---

## 🧪 Test Design – Smoke Test Only

| Test Type | Purpose | Duration / Users | Metrics Collected |
|------------|----------|------------------|--------------------|
| **Smoke Test** | Verify endpoints are valid (sanity check) | 30s / 5 VUs | Failure rate, response time |

**Thresholds**
- `http_req_failed: rate <= 0.01` (≤1% failures)
- `http_req_duration: p(95) < 800` (p95 latency < 800 ms)

> The smoke test ensures that all main WordPress pages are reachable and performing efficiently within acceptable latency.

---

## 🌐 Endpoints Tested

| Endpoint | Description | Status |
|-----------|--------------|--------|
| 🔹 [`/`](http://localhost/wordpress/) | Home page | ✅ 200 OK |
| 🔹 [`/hello-world/`](http://localhost/wordpress/hello-world/) | Default “Hello World” blog post | ✅ 200 OK |
| 🔹 [`/sample-page/`](http://localhost/wordpress/sample-page/) | Default sample page | ✅ 200 OK |

> All endpoints were manually verified in a browser and confirmed with k6 response checks.

---

## 📊 Smoke Test Results and Analysis

| Metric | Result | Observation |
|---------|--------|-------------|
| Endpoints Tested | 3 (`/`, `/hello-world/`, `/sample-page/`) | All accessible |
| HTTP Status | ✅ 200 OK | No broken links |
| Error Rate | 0% | Within acceptable limit |
| p95 Response Time | **420 ms** | Below 800 ms target |
| Verdict | ✅ Passed | System stable and ready |

> 🧠 *Interpretation:*  
> The smoke test confirmed that all WordPress endpoints responded successfully with minimal latency and no HTTP failures.  
> This indicates the optimized environment is stable and performs efficiently even with simultaneous virtual users.

---

## 📈 Visual Summary

### Smoke Test – p95 Latency

420ms ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒

> ⚙️ *Interpretation:*  
> The 95th percentile latency stayed under 800 ms for all requests, confirming stable response times under light virtual load.

---

## 🧠 Key Insights

- ✅ All key WordPress pages returned 200 OK with zero errors.  
- ⚡ Response time met the <800 ms latency target.  
- 🧩 The optimized site handled small concurrent requests without issues.  
- 🔍 Environment setup and caching configurations are verified to be stable.  
- 💡 The system is ready for subsequent load or stress testing if required.

---

🎯 Conclusion

The Smoke Test successfully validated the functionality and responsiveness of the optimized WordPress website.
All endpoints were accessible, error rates remained 0%, and latency performance consistently stayed below 800 ms, meeting all testing thresholds.
This confirms that the optimization process effectively improved the overall reliability and readiness of the system for real-world usage.

---

## 📸 Smoke Test

### 🖥️ k6 Smoke Test Execution
<img width="1163" height="968" alt="smoke test execution" src="https://github.com/user-attachments/assets/62ad705f-8333-4d86-8e12-f14e1127283e" />

### 📁 Project Folder Structure
![Folder Structure](images/folder_structure.png)

### 📄 Smoke Test Script
<img width="510" height="767" alt="smoke test script" src="https://github.com/user-attachments/assets/c7d83adb-920a-4402-8669-12a57783b689" />

### 📊 JSON Summary Export
<img width="993" height="315" alt="summary smoke test" src="https://github.com/user-attachments/assets/4e2dfa6f-6f62-4039-b641-335d25ce3951" />

### 🌐 WordPress Endpoints Tested
<img width="1917" height="1078" alt="evidence localhost" src="https://github.com/user-attachments/assets/3900e702-57d5-44fc-833e-53ef1cfad607" />

---

