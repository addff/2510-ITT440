# Comprehensive Web Application Performance Testing & Analysis

<br>

**NAME:** AMIRUL HUSAINI BIN ABDUL MANAF

**STUDENT ID:** 2025137953

**CLASS:** CDCS2554C

**TITLE:**  LOAD TESTING USING LOCUST TO WEBSITE HTTPS://DUMMYJSON.COM

<br>

## **INTRODUCTION TO WEB APPLICATION PERFORMANCE TESTING & ANALYSIS**
<p align="justify">
Web application performance testing is a type of non-functional testing that evaluates the behavior, stability, speed, and scalability of a web application under various workloads and conditions. It aims to identify performance bottlenecks and ensure the application can handle expected user loads while providing a positive user experience.</p>
<br>

## 💡 Testing Environment & Objective

### Testing Environment
<img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/990ecd3c-f8ea-47ac-95c1-ee5b653ceaf6" />

This experiment was performed in a Linux environment, specifically Kali Linux, which provides a stable and secure platform for running performance testing tools such as Locust.

### Objective
The main goal of this testing is to assess the performance and stability of the DummyJSON web API under concurrent user load using Locust load testing tool.

<br>

## 🧰 Tool Selection : LOCUST

<img width="500" height="188" alt="image" src="https://github.com/user-attachments/assets/02b93a21-34ec-4e25-b89e-3d1b4e581633" />  

<p align="justify">
Locust is an open-source, Python-based load testing tool designed for performance testing of web applications and APIs. It allows users to define the behavior of virtual users using standard Python code, offering flexibility and extensibility compared to tools relying on graphical user interfaces or domain-specific languages.</p>
<br>

## 🔑 Main Features of LOCUST

- A user-friendly web-based UI.
- Python-based scripting -> Using standard Python code, offering high flexibility and customizability for simulating complex user behaviors,
- Real-time monitoring -> provides an intuitive, web-based user interface for real-time monitoring of test progress, displaying key metrics such as response times, error rates, and throughput.
<br>

### Installation Guide For Linux:

   - **First, update system package:** 
     ```bash
     sudo apt update && sudo apt upgrade -y
     ```
   - **Install python and pip:**  
     ```bash
     sudo apt install python3 python3-pip -y
     ```
   - **Install locust using pip:**  
     ```bash
     pip install locust
     ```
   - **Verify instalation:**  
     ```bash
     locust --version
     ```
<br>     

## 🚀 Test Environment Setup and Methodology.

After finish the installation, open the Locust web interface using the command

  ```bash
  locust -f yourscript.py -H https://dummyjson.com
  ```

<img width="696" height="164" alt="image" src="https://github.com/user-attachments/assets/7f40ca6f-2e52-412d-89ac-8d9cd30e463d" />  

<br>

<br>Then, the open the web interface at the given port number (eg. http://localhost:8089)

<br>

<img width="691" height="411" alt="image" src="https://github.com/user-attachments/assets/df28a326-a546-4cff-86eb-d87f92a54695" />


Here, we can input these information:
- number of users
- ramp up (users started per second)
- host (target)
- run time
  
Then, click the START button and wait for the test to finish.
<br>

## 📊 Raw Data Presentation

<img width="800" height="300" alt="image" src="https://github.com/user-attachments/assets/796a81b2-ed2a-4868-a964-0736791a0023" />

<p align="justify"> Figure 1: Locust web interface displaying test execution and live statistics for 50 users. </p>
<br> <br>

<img width="800" height="300" alt="image" src="https://github.com/user-attachments/assets/6c3066ca-39cd-43dc-80e9-e55f345c6384" />

<p align="justify"> Figure 2: Locust web interface displaying test execution and live statistics for 5 users. </p>
<br> 

## 📈 Comparison Test (5 vs 50 Users)

To observe scalability, two tests were conducted. One with 5 concurrent users (light load) and another with 50 users (mid-heavy load).

| Users      | Avg Time (ms)  | 95% Time (ms)  | Requests/s  | Failures  |
|------------|----------------|----------------|-------------|-----------|
| 5 Users    | 576            | 820            | 574         | 0         |
| 50 Users   | 244            | 840            | 6601        | 0         |

<p align="justify">
When the user count increased from 5 to 50, the average response time changed from  576 ms to 260 ms, while the 95th percentile response time reached 840 ms. This shows that as concurrent user load increases, the API experiences higher latency but remains stable without any failures.
</p>
<br>

## 📝 Interpretation of Results and Identified Bottlenecks

<img width="700" height="500" alt="image" src="https://github.com/user-attachments/assets/1e57b317-6aa0-4595-a8c1-026807ae3091" />  

<p align="justify"> The DummyJSON API demonstrated stable and consistent performance under a 5-minute simulated load in Locust. All endpoints responded successfully without any failure or timeout. Although average response times were within acceptable limits, certain endpoints like `/products/[id]` showed higher response times at the upper percentiles, suggesting potential areas for backend optimization. </p>
<br>

### ⚠️ Identified Bottlenecks

| No. | Bottleneck                        | Description                                                                 | Possible Cause                                 | Recommendation                                                      |
|:---:|:----------------------------------|:----------------------------------------------------------------------------|:-----------------------------------------------|:-------------------------------------------------------------------|
| 1   | High latency on `/products/[id]`  | Endpoint avg = **548.89 ms**, 95th = **1600 ms** — much higher than others | Dynamic data retrieval or slow DB queries      | Implement caching (e.g., Redis) and add DB indexing                |
| 2   | Response time variability         | Aggregated avg = **244.18 ms**, 95th = **1900 ms** — large tail latency     | Backend processing spikes or uneven load       | Profile backend, optimize heavy queries, consider request queueing |
| 3   | Increasing latency with users     | Latency rose during peak **RPS ≈ 23.2**                                     | Limited server resources or sync/blocking I/O  | Scale resources, use async handlers, or add load balancing        |

<br>

## 📖 Recommendations For Improvement 
<p align="justify"> Although the DummyJSON API performed well under moderate load, the following improvements can further enhance scalability and performance if this were a production-level system: </p>

- Implement caching for frequently accessed endpoints.

- Optimize database queries using proper indexing.

- Introduce asynchronous request handling for better concurrency.

- Perform stress testing with higher user counts (100+ users).
<br> 

## 🔖 Conclusion

<p align="justify"> To sum up, load testing with Locust provided helpful data on the behavior of API performance under concurrent user loads.  The experiment assisted in finding possible areas for optimization and demonstrated how system responsiveness changes with increasing traffic.  Overall, it was an interesting and educational exercise that improved my knowledge of system scalability and performance analysis. </p>
<br>

## Demonstration Video

<p>Below is the link for the demonstration video for the load testing<p> 
[https://www.youtube.com/watch?v=ky-4WzHMrb0&t=30s]

## <br>📚 References

- https://locust.io/
- https://www.geeksforgeeks.org/python/load-testing-using-locust/
- https://dummyjson.com/

  
