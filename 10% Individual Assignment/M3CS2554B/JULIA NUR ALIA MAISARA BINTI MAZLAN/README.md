# JULIA NUR ALIA MAISARA BINTI MAZLAN
# 🧩 Web Application Load Testing using Locust

### **Tool:** Locust (Python-based Load Testing Framework)  
### **Target Site:** [BooksToScrape](https://books.toscrape.com)  

---

## 🏷️ Title & Introduction

### **Title:**  
**Web Application Load Performance Testing of BooksToScrape Using Locust**

### **Introduction:**  
Performance testing plays an essential role in determining how well a web application responds under concurrent user activity. This project applies **Locust**, an open-source Python-based tool, to simulate multiple users accessing the **BooksToScrape** website simultaneously.  

By observing how the site reacts to controlled network traffic, this project explores core networking programming concepts such as request handling, latency, and throughput. The activity is designed for **ITT440 (Networking Programming)** to develop skills in analyzing how web applications perform under varying load conditions.

---

## 🎯 Objective

1. To configure and execute a load test using Locust.  
2. To simulate multiple user connections to the BooksToScrape web application.  
3. To monitor response times, request rates, and overall performance stability.  
4. To relate load testing outcomes to networking programming concepts such as latency, concurrency, and data throughput.

---

## ⚙️ Tool & Target Site Selection

### **Tool: Locust**  
Locust is a **Python-based, open-source load testing tool** that allows testers to simulate user traffic and measure system performance under different network loads. It provides a web-based interface for configuring, executing, and monitoring real-time results.

Key features include:
- Written in Python with simple user behavior scripting.  
- Real-time results with response time and throughput metrics.  
- Scalable testing for small or large user simulations.  

### **Target Website: BooksToScrape**  
[BooksToScrape](https://books.toscrape.com) is a public demo e-commerce site used for automation and testing purposes. It is a safe and legal platform for practicing web performance testing as it mimics a real-world online bookstore with multiple categories and pages.

---

## 🧠 Test Plan & Configuration

**Test Environment:**
- **Operating System:** Windows 10  
- **Python Version:** 3.13  
- **Locust Version:** 2.42.0  
- **Network Connection:** Stable Wi-Fi
  

**Test Script File:** `bookstore_performance_test.py`

```python
# Bookstore Load Performance Testing Script

from locust import HttpUser, task, between

class BookStoreClient(HttpUser):
    wait_time = between(2, 5)

    @task(4)
    def open_homepage(self):
        self.client.get("/")

    @task(2)
    def explore_category(self):
        self.client.get("/catalogue/category/books/travel_2/index.html")

    @task(2)
    def open_book_info(self):
        self.client.get("/catalogue/a-light-in-the-attic_1000/index.html")

    @task(1)
    def navigate_next_page(self):
        self.client.get("/catalogue/page-2.html")

    @task(1)
    def quick_search(self):
        self.client.get("/catalogue/category/books_1/index.html")

```
---
## 📊 Results

During the load test, 60 concurrent virtual users were simulated accessing the **BooksToScrape** website over approximately six minutes. The system maintained a stable throughput throughout the test with no recorded failures.

### **Key Observations:**
| Metric | Observation |
|---------|--------------|
| **Number of Concurrent Users** | 60 |
| **Spawn Rate** | 5 users/second |
| **Average Requests per Second (RPS)** | 15–17 |
| **Average Response Time** | 500–800 ms after ramp-up |
| **Peak Response Time** | ≈ 2500 ms (during ramp-up) |
| **Failure Rate** | 0 % |
| **Test Duration** | 6 minutes |

**Graph Summary:**  
<img width="1791" height="863" alt="Screenshot 2025-10-31 131728" src="https://github.com/user-attachments/assets/46ce7171-ae8d-4a60-bec5-e54a8a39a1d2" />
<img width="1752" height="479" alt="image" src="https://github.com/user-attachments/assets/dbd7384a-86a4-4987-92d6-722d4d993edc" />


- The *“Number of Users”* chart shows a smooth increase from 0 to 60 users, maintaining a consistent level thereafter.  
- The *“Requests per Second (RPS)”* curve peaked around 17 RPS and remained steady, indicating stable throughput.  
- The *“Response Time (ms)”* graph displayed an initial spike (≈ 2.5 seconds) during the warm-up period, followed by stabilization below 800 ms for the remainder of the test.  
- The *Failure/s* line remained at zero, showing that all simulated requests completed successfully.

---

## 📈 Analysis & Discussion

The **BooksToScrape** website demonstrated stable and efficient performance under a moderate load of 60 concurrent users.  
The short initial spike in response time likely occurred while the server adjusted to the increasing number of incoming requests; once equilibrium was reached, latency decreased and stabilized.

The average **response time under 1 second** and consistent **throughput of 15–17 RPS** indicate that the web application can handle typical user traffic without degradation.  
The **0 % failure rate** suggests that both the server and network connection were reliable during the test window.

From a networking-programming perspective, the results highlight:
- **Concurrency management** – the server successfully handled multiple simultaneous TCP connections.  
- **Latency adaptation** – response times improved as request queues were optimized.  
- **Bandwidth efficiency** – throughput remained constant, implying no bandwidth bottlenecks.  

Overall, the system performed within acceptable web-performance thresholds, confirming that the target site is well-optimized for moderate concurrent access.

---

## 💡 Recommendations

Based on the observed performance metrics from the load test, the following recommendations are proposed:

1. **Enable caching** for frequently accessed resources such as book thumbnails and category pages to reduce response time during peak traffic.  
2. **Compress static content** (e.g., images, CSS, and JavaScript files) to minimize data transfer size and improve page load speed.  
3. **Implement content delivery networks (CDNs)** to distribute resources geographically and decrease latency for users in different regions.  
4. **Perform regular load and stress testing** to detect potential slowdowns and maintain optimal performance as the website evolves.   

---

## 🧾 Conclusion

The load testing experiment on the **BooksToScrape** web application using **Locust** successfully demonstrated how web systems behave under moderate concurrent user activity.  
With 60 users simulated over six minutes, the website maintained stable throughput and low latency without failures, indicating reliable server performance and efficient network management.

This practical exercise supports key concepts from **ITT440 – Networking Programming**, emphasizing the importance of performance measurement, concurrency handling, and resource optimization in web-based environments.  
The insights gained show that even simple web servers can perform well when network parameters are properly managed and requests are efficiently distributed.

---

## 📚 References

1. Locust Documentation – [https://docs.locust.io](https://docs.locust.io)  
2. BooksToScrape Demo Website – [https://books.toscrape.com](https://books.toscrape.com)  
3. Python Official Documentation – [https://www.python.org/doc/](https://www.python.org/doc/)  
4. Microsoft. (2024). *Network Performance and Optimization in Web Applications*.  

---


## 🎬 **Watch Project Demonstration:**  


https://www.youtube.com/watch?v=70FAa0lcPw4
---



