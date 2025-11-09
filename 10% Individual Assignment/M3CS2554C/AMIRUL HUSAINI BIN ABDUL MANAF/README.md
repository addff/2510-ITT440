# Comprehensive Web Application Performance Testing & Analysis

**NAME:** AMIRUL HUSAINI BIN ABDUL MANAF

**STUDENT ID:** 2025137953

**CLASS:** CDCS2554C

**TITLE:**  LOAD TESTING USING LOCUST TO WEBSITE HTTPS://DUMMYJSON.COM  


## **INTRODUCTION TO WEB APPLICATION PERFORMANCE TESTING & ANALYSIS**
<p align="justify">
Web application performance testing is a type of non-functional testing that evaluates the behavior, stability, speed, and scalability of a web application under various workloads and conditions. It aims to identify performance bottlenecks and ensure the application can handle expected user loads while providing a positive user experience. </p>

## 💡 Testing Environment & Objective

### Testing Environment
<img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/990ecd3c-f8ea-47ac-95c1-ee5b653ceaf6" />

This experiment was performed in a Linux environment, specifically Kali Linux, which provides a stable and secure platform for running performance testing tools such as Locust.

### Objective
The main goal of this testing is to assess the performance and stability of the DummyJSON web API under concurrent user load using Locust load testing tool.  

## 🧰 Tool Selection : LOCUST

<img width="500" height="188" alt="image" src="https://github.com/user-attachments/assets/02b93a21-34ec-4e25-b89e-3d1b4e581633" />  

<p align="justify">
Locust is an open-source, Python-based load testing tool designed for performance testing of web applications and APIs. It allows users to define the behavior of virtual users using standard Python code, offering flexibility and extensibility compared to tools relying on graphical user interfaces or domain-specific languages. </p>

It can be install in python whether in Windows or Linux operating system.
- For Windows: can install at the website https://locust.io/
  
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
     

## 🔑 Main Features of LOCUST

- A user-friendly web-based UI.
- Python-based scripting -> Using standard Python code, offering high flexibility and customizability for simulating complex user behaviors,
- Real-time monitoring -> provides an intuitive, web-based user interface for real-time monitoring of test progress, displaying key metrics such as response times, error rates, and throughput.

## 🚀 Test Environment Setup and Methodology.
<img width="602" height="317" alt="image" src="https://github.com/user-attachments/assets/e38af6f9-c438-4aea-9e9e-7af2bae86841" />

Here, we can input these information:
- number of users
- ramp up (users started per second)
- host
- run time

## 📊 Raw Data Presentation
<img width="602" height="179" alt="image" src="https://github.com/user-attachments/assets/1ca721cb-b481-486f-9f35-132db27810bb" />  

### Result Summary Table
| Endpoint        | Avg Time (ms) | 95% Time (ms) | Requests/s | Failures |
|-----------------|---------------|---------------|-------------|-----------|
| /products       |        93.68       |        570       |       4.1      |     0     |
| /products/[id]  |        88.78       |        480       |       11.4     |     0     |
| /posts          |        548.89      |        1600      |       7.7      |     0     |  


<img width="630" height="164" alt="image" src="https://github.com/user-attachments/assets/8eba9e8a-824a-489c-8574-7145b32eee79" />  


This is the web interface of the LOCUST that is easier to run and monitor. 


## 📝 Interpretation of Results and Identified Bottlenecks

<img width="700" height="500" alt="image" src="https://github.com/user-attachments/assets/1e57b317-6aa0-4595-a8c1-026807ae3091" />  

<p align="justify"> The DummyJSON API demonstrated stable and consistent performance under a 5-minute simulated load in Locust. All endpoints responded successfully without any failure or timeout. Although average response times were within acceptable limits, certain endpoints like `/products/[id]` showed higher response times at the upper percentiles, suggesting potential areas for backend optimization. </p>

### ⚠️ Identified Bottlenecks

| No. | Bottleneck                        | Description                                                                 | Possible Cause                                 | Recommendation                                                      |
|:---:|:----------------------------------|:----------------------------------------------------------------------------|:-----------------------------------------------|:-------------------------------------------------------------------|
| 1   | High latency on `/products/[id]`  | Endpoint avg = **548.89 ms**, 95th = **1600 ms** — much higher than others | Dynamic data retrieval or slow DB queries      | Implement caching (e.g., Redis) and add DB indexing                |
| 2   | Response time variability         | Aggregated avg = **244.18 ms**, 95th = **1900 ms** — large tail latency     | Backend processing spikes or uneven load       | Profile backend, optimize heavy queries, consider request queueing |
| 3   | Increasing latency with users     | Latency rose during peak **RPS ≈ 23.2**                                     | Limited server resources or sync/blocking I/O  | Scale resources, use async handlers, or add load balancing        |



## 📖 Recommendations For Improvement 
<p align="justify"> Although the DummyJSON API demonstrated stable behavior under moderate load, the following recommendations can help enhance performance and scalability if this were a production API: </p>

- Conduct stress testing with higher user counts for scalability assessment.
- Use caching for frequently accessed resources
- Optimize database queries using indexing

## Conclusion

In a nutshell, conducting load testing using Locust provided valuable insights into API performance behavior under concurrent user load. The experiment was both educational and enjoyable, as it deepened my understanding of performance analysis and server optimization.

## Demonstration Video
Below is the link for the demonstration video for the load testing 
https://www.youtube.com/watch?v=ky-4WzHMrb0&t=30s


