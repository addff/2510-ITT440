# Spike Testing on Open Library website using Apache JMeter

### Name : Juratu binti Abdullah 
### Matric Number : 2023268582 
### Group Class : M3CS2554C 

### Spike Testing Explanation
Spike Testing is a type of performance testing that evaluates a system's behavior when it experiences sudden, extreme increases in load. Unlike gradual load testing, spike testing simulates abrupt traffic surges to determine:
- Whether the system can handle sudden spikes without crashing.
- How response time and error rates change under peak load.
- How quickly the system recovers after the spike.

### 📌 Objective
The objective of this project is to perform a **Spike Test** on the web application [OpenLibrary.org](https://openlibrary.org) using **Apache JMeter**. The test aims to evaluate how the system responds to a sudden surge in user load and whether it can maintain stable performance under extreme conditions.

### ⚙️ Tool Selection: Apache JMeter
![Apache Jmeter logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRfptUW92QFvFjgtP3p9AtGEIX6bsuSL7-YgA&s)

Apache JMeter was selected because it is a **widely used open-source performance testing tool** that supports various protocols such as HTTP, HTTPS, and WebSocket.

**Reasons for choosing JMeter:**
- Easy to configure and execute tests for web applications.
- Provides detailed reports and visual graphs for performance metrics.
- Supports simulation of multiple concurrent users to create realistic load spikes.
- Free and open-source, making it accessible for academic testing.

### Target Web Application: openlibrary.org
![Openlibrary.org website logo](https://blog.openlibrary.org/files/2023/04/cropped-cropped-openlibrary-header.png)
![openlibrary.org website main page](https://upload.wikimedia.org/wikipedia/commons/5/51/OpenLibrarypage.jpg)

[OpenLibrary.org](https://openlibrary.org) is a public, non-commercial website that allows users to access and borrow digital books. It provides an API and a simple web interface suitable for HTTP performance testing.

**Hypothesis:**  
> The openlibrary.org website will remain stable under a sudden spike of 100 virtual users within a short time frame, with minimal errors and acceptable response time.

### 🧩 Test Environment Setup

**Tool:** Apache JMeter 5.6.3  
**Test Type:** Spike Test

**System Used:**
- CPU: Intel Core i5
- RAM: 8 GB
- OS: Windows 11
- Internet: 100 Mbps stable connection

**Test Plan Configuration:**

| Component | Configuration |
|------------|---------------|
| Thread Group | 100 users |
| Ramp-Up Period | 5 seconds |
| Loop Count | 1 |
| Target URL | https://openlibrary.org |
| HTTP Request | GET request to homepage |
| Listeners | Summary Report, View Result Tree, View Results in Table |

### Test Execution Steps

| Step | Description |
|------|--------------|
| 1 | Launch Apache JMeter and create a new test plan. |
| 2 | Add a **Thread Group** and configure 100 users with a 5-second ramp-up period. |
| 3 | Add **HTTP Request Sampler** targeting `https://openlibrary.org`. |
| 4 | Add **Listeners** (Summary Report, View Result Tree, View Results in Table) to capture performance metrics. |
| 5 | Save and execute the test plan. |
| 6 | Observe response times, throughput, and error rates during the spike. |
| 7 | Export reports and analyze the results. |


### Test Results & Analysis

### Result Graph, Tbale and Charts 

![Summary report screenshot](https://github.com/user-attachments/assets/d48aeb03-9529-425f-9f82-f0275d84ba21)
- Result from 'Sumarry Report' 

![Screenshot_20251109-211745_Video Player](https://github.com/user-attachments/assets/fbf8350a-dcae-47b8-a194-de2b4a19563f)
- Result from 'View Result Tree'

![Screenshot_20251109-211718_Video Player](https://github.com/user-attachments/assets/3e5fa43b-201b-4f3e-aa8d-e2d53daa8836)
- Result from 'View Result in Table' 




After executing the spike test, the following key metrics were observed:

| Metric | Observation |
|---------|-------------|
| Total Samples | 100 |
| Average Response Time | ~40 seconds |
| Minimum Response Time | 1.4 seconds |
| Maximum Response Time | ~86 seconds |
| Error Rate | 0% |
| Throughput | ~1.1 requests/sec |
| Success Rate | 100% |
| Warnings | 2 minor warnings in log (no errors) |

**Analysis:**
- All requests were successful with response code 200, indicating no failures during the spike test.
- The average load time was about 1.4 seconds for individual requests, but overall response times varied as more users accessed the website simultaneously.
- The spike test caused temporary delays for some requests (up to 86 seconds), but the system handled the surge without crashing.
- Minor warnings were recorded in JMeter logs but did not impact the success of the test.
- Throughput of 1.1 requests/sec shows the server managed the load steadily.

### Interpretation of Results
The **spike test** confirms that openlibrary.org can handle sudden surges of 100 concurrent users. Temporary increases in response time are expected under peak load, but overall, the system remained stable and resilient.

### Recommendations
To improve performance under spikes:
1. Implement **load balancing** to distribute traffic evenly.
2. Use **caching mechanisms (CDN)** to reduce server load.
3. Monitor **server memory and CPU usage** during peak periods.
4. Introduce **autoscaling** on cloud infrastructure to dynamically handle spikes.

### Conclusion
The spike testing using Apache JMeter demonstrated that **openlibrary.org** is robust and scalable under sudden user surges. Despite temporary delays in response times, all requests were successfully processed with minimal issues.

### 🎥 Video Demonstration
A step-by-step execution and explanation of the JMeter test plan have been recorded and uploaded to YouTube:  
Click here :  [Spike Testing Demo Video](https://youtu.be/Ka2cLhAaQrU?feature=shared) *


