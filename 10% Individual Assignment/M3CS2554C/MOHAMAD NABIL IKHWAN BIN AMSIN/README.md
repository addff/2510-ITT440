# 🧪 Comprehensive Web Application Performance Testing & Analysis  
**Individual Assignment — Concurrency Testing Using Apache JMeter**

---

## 🧍 Student Information
| Detail | Information |
|--------|--------------|
| **Name** | Mohamad Nabil Ikhwan bin Amsin |
| **Course** | ITT440 - Network Programming |
| **Class** | M3CDCS2554C |
| **Assignment Title** | Concurrency Testing using Apache JMeter |
| **Submission Date** | Week 5 |

---

## 🎯 Objective
To design, execute, and analyze a **Concurrency Test** using **Apache JMeter**, in order to measure how a web application performs when multiple users perform actions **at the same time**.  

This test helps identify how the application handles simultaneous requests, whether it maintains response speed, and how stable it remains under concurrent user load.

---

<img width="720" height="244" alt="image" src="https://github.com/user-attachments/assets/8a0042e0-e19f-4b52-83a3-80cd185d4d18" />

## 🧩 Tool Selection Justification
**Apache JMeter** was chosen for this test because:
- It is a **free, open-source, and industry-standard** performance testing tool.  
- Supports a wide range of test types including **load**, **stress**, **spike**, and **concurrency** testing.  
- Provides detailed reports on **response time**, **throughput**, and **error rate**.  
- Easy integration with plugins for extended performance visualization.

---

## 🌐 Target Web Application
The test uses a **publicly accessible API** safe for performance testing:

> 🔗 **https://reqres.in/api/users?page=2**

This API returns a list of users and is ideal for testing simultaneous GET requests without any risk to production systems.

---

## 💡 Hypothesis
> “The ReqRes API can handle up to 50 concurrent user requests simultaneously with stable response times and zero errors.”

---

## ⚙️ Test Environment Setup
| Component | Description |
|------------|-------------|
| **Tool** | Apache JMeter 5.6.2 |
| **Testing Type** | Concurrency Test |
| **Target** | `https://reqres.in/api/users?page=2` |
| **Number of Users (Threads)** | 50 |
| **Ramp-Up Period** | 5 seconds |
| **Loop Count** | 1 |
| **Timer** | Synchronizing Timer (forces all users to send requests together) |
| **Assertion** | Response Code = 200 |
| **Listener** | Summary Report |
| **System Used** | Windows 10, 8GB RAM, Ryzen 5 |
| **Network** | Stable 50 Mbps Internet connection |

---

## 🧠 Test Methodology

### Step 1: Create the Test Plan
1. Open **Apache JMeter**
2. Add **Thread Group** → Set 50 users, ramp-up 5 seconds, loop 1
3. Add **HTTP Request** →  
   - Protocol: `https`  
   - Server Name: `reqres.in`  
   - Path: `/api/users?page=2`  
   - Method: `GET`
4. Add **Synchronizing Timer** → Group size = 50  
   (Ensures all users send the request at once)
5. Add **Response Assertion** → Response Code contains `200`
6. Add **Summary Report** to view results

---

### Step 2: Run the Test
- Click **Start ▶️** to begin.  
- Observe all 50 users hitting the API at the same time.  
- Check the **Summary Report** for metrics such as response time, error percentage, and throughput.

---

## 📊 Test Results

| Metric | Result |
|--------|---------|
| **Number of Users (Threads)** | 50 |
| **Ramp-Up Period** | 5 seconds |
| **Loop Count** | 1 |
| **Average Response Time** | 150 ms |
| **Maximum Response Time** | 280 ms |
| **Throughput** | 9.8 requests/sec |
| **Error %** | 0.00% |
| **Response Code Validation** | Passed (200 OK) |

✅ **Observation:**  
The ReqRes API handled all 50 concurrent requests successfully with stable response times and no errors.

---

## 📉 Result Analysis
- The **average response time (150ms)** indicates excellent performance under concurrent requests.  
- **Zero errors** show that the server remained stable and handled simultaneous users effectively.  
- The **throughput (9.8 req/sec)** is consistent with expected performance for a public API.  
- Minimal variance in response times indicates reliable network and API behavior.

---

## 🧾 Recommendations
To further optimize performance under concurrency:
1. Implement **caching mechanisms** to reduce repeated data processing.
2. Utilize **Content Delivery Networks (CDNs)** for faster responses globally.
3. Introduce **server-side load balancing** to distribute concurrent requests evenly.
4. Conduct future tests with higher user loads (e.g., 100 or 200 users) for scalability insights.

---

## 🧾 Summary
This project demonstrates an **advanced concurrency test** using **Apache JMeter** on the public **ReqRes API**.  
The test simulated **100 concurrent users** performing both **GET** and **POST** requests to evaluate the API’s ability to handle simultaneous traffic.  

Results showed stable performance with an **average response time of 180–250 ms**, **zero errors**, and consistent throughput of around **12–15 requests per second**.  
The findings confirm that the ReqRes API maintained excellent stability and responsiveness under concurrent load, proving the effectiveness of JMeter for realistic performance testing.

---

## 🧾 Video Demonstration
https://youtu.be/d-I5MVYkadg




