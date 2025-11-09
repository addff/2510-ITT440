# 🧪 Website Stress Testing Using Artillery

### NAME: **MUHAMMAD FARIS IMRAN BIN RUSDI**
### STUDENT ID: 2025137413
### CLASS: M3CDCS2554C
### TITLE: STRESS TESTING ON WEBSITE https://pokeapi.co/

---

## 🧩 Introduction

   <img width="1024" height="277" alt="image" src="https://github.com/user-attachments/assets/4d351fb5-5bc2-4d1f-85f7-942a62064738" n/>


This project focuses on **Stress Testing a web API** using **Artillery.io** to analyze its performance, stability, and reliability under extreme load conditions.
The main goal is to identify the **breaking point** of the system , how much traffic it can handle before performance starts to degrade.

Stress testing helps developers and organizations ensure that the system can withstand unexpected spikes in user requests and still maintain acceptable performance levels.

---

## 🧠 Objective

* To determine the **maximum capacity** of the target API.
* To identify **response degradation**, **timeouts**, and **failure rates** under stress.
* To observe how the system behaves beyond its operational limits.
* To document findings using **data, charts, and summaries** for future optimization.

---

🧪 Why Artillery for Stress Testing

Artillery was chosen for stress testing because it is lightweight, flexible, and easy to use. It can simulate realistic user traffic, identify performance bottlenecks, and generate clear reports. Its support for multiple protocols and integration with the Artillery Cloud Dashboard makes it ideal for analyzing system performance efficiently.

--

## 🧰 Tool Selection

| Tool                          | Purpose                                                    |
| ----------------------------- | ---------------------------------------------------------- |
| **Artillery.io**              | Open-source performance testing tool for APIs and web apps |
| **Node.js (NPM)**             | Required to install and run Artillery                      |
| **Linux / Kali VM**           | Testing environment for executing stress tests             |
| **Artillery Cloud Dashboard** | Provides visualization and performance tracking            |

---

## 🖥️ Testing Environment

| Component            | Description                                             |
| -------------------- | ------------------------------------------------------- |
| **Operating System** | Kali Linux (VirtualBox)                                 |
| **Tool**             | Artillery.io                                            |
| **Target**           | Pokémon API endpoint (for functional stress simulation) |
| **Duration**         | 5 minutes and 25 seconds                                |
| **Phases**           | Warm-up → Moderate Load → Stress → Break Point          |

---

## ⚙️ Steps to Run the Project

1. **Install Node.js & Artillery**

   ```bash
   sudo apt update
   sudo apt install nodejs npm -y
   sudo npm install -g artillery
   ```

2. **Create a YAML Test File**
   
    nano name file.yml
     
   ```yaml
   config:
     target: "https://pokeapi.co/api/v2"
     phases:
       - duration: 60
         arrivalRate: 10
         name: "Warm up"
       - duration: 60
         arrivalRate: 30
         name: "Moderate load"
       - duration: 90
         arrivalRate: 50
         name: "Stress test"
       - duration: 60
         arrivalRate: 100
         name: "Break point"
   scenarios:
     - name: "Get Pokemon Info"
       flow:
         - get:
             url: "/pokemon/1"
   ```
    write and save the code 
4. **Run the Test**

   ```bash
   artillery run stress-test.yml --record --key <API KeyS>


   ```

5. **View Results**

   * In the terminal (real-time stats)
   * On [Artillery Cloud Dashboard](https://app.artillery.io/)

---

## 🎯 Target

The API under test was chosen to simulate **a real-world endpoint** — fetching Pokémon data via a GET request.
This allows realistic evaluation of how a public API might respond under sudden bursts of requests.

---

## 📊 Raw Data Highlights

| Metric                             | Result       |
| ---------------------------------- | ------------ |
| **Total Duration**                 | 5 min 25 sec |
| **Requests Sent**                  | 13,800       |
| **Successful Responses (200/404)** | 4,319        |
| **Timeout Errors (ETIMEDOUT)**     | 9,481        |
| **Average Response Time**          | 199.3 ms     |
| **Peak Response Time (Max)**       | 2996 ms      |
| **95th Percentile**                | 1130.2 ms    |
| **99th Percentile**                | 1686.1 ms    |
| **Failed Virtual Users**           | 9,481        |
| **Completed Virtual Users**        | 4,319        |

---

## 📈 Graph Analysis
<img width="940" height="329" alt="image" src="https://github.com/user-attachments/assets/89921ab1-e25e-42ff-9c44-9694ea52b6e4" />

   _Graph of analysis_

<img width="940" height="271" alt="image" src="https://github.com/user-attachments/assets/c96e72f5-5123-4399-9a65-4d0785e2b13a" />

   _Graph of HTTP performance_

Visual representation from the Artillery Cloud Dashboard shows:

* A **steady response time** during warm-up.
* **Gradual performance drop** under moderate load.
* **Significant timeouts** during peak stress and break point phases.
* **Error spikes (ETIMEDOUT)** showing the system’s breaking threshold.


---

## 🧾 Test Report Summary

| Phase         | Duration | Avg Req/sec | Avg Response (ms) | Errors |
| ------------- | -------- | ----------- | ----------------- | ------ |
| Warm-Up       | 60s      | 10          | 59                | 0      |
| Moderate Load | 60s      | 30          | 70                | 1      |
| Stress Test   | 90s      | 50          | 191               | 596    |
| Break Point   | 60s      | 148         | 178               | 9,481  |

<img width="506" height="739" alt="image" src="https://github.com/user-attachments/assets/10bc1b2a-7287-4b6f-bd8e-249a659526e6" />

   _Picture of summary report_

---

## 🧩 Key Findings

* The system remained **stable up to moderate load** (≈30 requests/sec).
* **Performance degradation** started beyond 50 concurrent users.
* The **break point** occurred when reaching ~100 requests/sec.
* A total of **9,481 timeout errors** indicates the server limit was exceeded.

---

## 🧠 Conclusion

This stress testing project successfully demonstrates:

* The **importance of scalability** testing before deployment.
* The **behavior of APIs under extreme traffic conditions**.
* How Artillery provides clear metrics and visual insights into performance.

Improvements could include:

* Implementing **caching** or **load balancing**.
* Optimizing backend queries.
* Deploying **distributed servers** to handle peak traffic efficiently.

---

## Video Demonstration
Here link for video demontration https://youtu.be/FzWspnh26HI
