# MUHAMMAD KAMAL BIN OTHMAN
**WEB APPLICATION PERFORMANCE TESTING**

**STUDENT ID: 2025118299**  
**CLASS: M3CS2554C**  
**TITLE: WEBSITE LOAD TESTING USING SIEGE**

---

### **TOOL SELECTION JUSTIFICATION: SIEGE**

Siege was selected as the testing tool for this performance analysis due to several reasons:

**1. Open-Source Tool**  
Siege is an open-source tool, which is completely free to use without any fees. Siege also allows users to modify the code and customize it according to their specific needs. This tool also provide transparency and continuous improvement through contributions from developers around the world.

**2. Support for HTTP and HTTPS Testing**  
Siege is primarily designed for testing HTTP and HTTPS-based web servers, which makes it very suitable for testing the performance of web applications and services. This allows it to simulate multiple users making requests to the web server, which is very suitable for several test like stress test, load test, and spike test.

**3. Lightweight and Efficient**  
Siege is a lightweight tool that does not require significant system resources to operate due to the use of command line (CLI) instead of Graphical User Interface (GUI). It is ideal for quick tests with minimum resource, and it can easily handle scenarios with a high number of concurrent users. Siege offers essential features such as customizable delays between requests to simulate realistic user behavior.

**4. Ease of Use**  
Siege is known for its beginner-friendly concept and ease of use. The command-line interface (CLI) allows users to perform specific tests by providing several basic parameters, such as the number of concurrent users, test duration, and the target URL. Additionally, the tool provides clear output, making it easy to analyze results.

---

### **TEST ENVIRONMENT SETUP AND METHODOLOGY**

#### **TESTED ENVIRONMENT**

<img width="1919" height="990" alt="kali" src="https://github.com/user-attachments/assets/e3c37f2e-ee8a-46bf-b0a1-58ccb010bf18" />
  
Kali Linux is an open-source Linux distribution that is created for cybersecurity purpose. Even though it is closely related with cybersecurity, it is also can be used for other purposes, such as website's performance test in this case using 'siege' tool.

**GUIDE:**  
1. Update the Kali Linux using this command
   
   <img width="274" height="54" alt="image" src="https://github.com/user-attachments/assets/06c9cf33-e4ff-4e88-8c93-173b2c8d6ecf" />

3. Install 'siege' using this command (URL via GitHub)
   
   <img width="440" height="64" alt="image" src="https://github.com/user-attachments/assets/eebf5309-aa5d-4638-8f8f-66abb0a142b0" />

5. Run test using this command:
   
   <img width="393" height="66" alt="image" src="https://github.com/user-attachments/assets/051d09f1-32af-4c7c-a8ad-b350f25b9760" />
  
   - `-c50` represents 50 users  
   - `-t1M` represents 1 minute duration
   - `-d5` represents random delay between 1-5 seconds
   - Specify the target website’s URL / File

---

**TESTED APPLICATION** 

- https://tools-httpstatus.pickup-services.com/
- https://tools-httpstatus.pickup-services.com/200
- https://tools-httpstatus.pickup-services.com/206
- https://tools-httpstatus.pickup-services.com/302
- https://tools-httpstatus.pickup-services.com/404


This website is a public HTTP Status Code testing service that provides various endpoints to simulate server responses. It is primarily designed for testing HTTP client behavior and verifying response codes such as 200 OK, 204 No Content, or 404 Not Found. Due to its lightweight feature, this website is suitable for quick performance and availability testing.

**Key features include:**  
1. Simulation of standard HTTP response codes  
2. Minimal payload responses for fast network benchmarking  
3. Simple API endpoints suitable for automated or manual testing  
4. Public accessibility without permission needed  

---

**TEST INFRASTRUCTURE SETUP**

Testing Tool: Siege 4.1.6  
Operating System: Windows 11  
System Memory: 32 GB RAM  
Processor: AMD Ryzen 5 5600H  
Network Connection: 131 Mbps mobile hotspot (may introduce variable latency)

#### **TEST CONFIGURATION**

**Performance Test Design**

Objective: Evaluate the website’s response consistency and throughput under moderate concurrent user load in 1 minute.  
Concurrent Users: 50 virtual users  
Test Duration: 60 seconds (1 minute)  
User Behavior: Accessed the following URLs:
- https://tools-httpstatus.pickup-services.com/
- https://tools-httpstatus.pickup-services.com/200
- https://tools-httpstatus.pickup-services.com/206
- https://tools-httpstatus.pickup-services.com/302
- https://tools-httpstatus.pickup-services.com/404

**HTTP Request Configuration**  

Protocol: HTTPS  
Server Name: tools-httpstatus.pickup-services.com  
Server URL: https://tools-httpstatus.pickup-services.com/  
HTTP Method: GET  
Port: 443  

---

### **RAW DATA PRESENTATION**

<img width="512" height="325" alt="image" src="https://github.com/user-attachments/assets/69a3d3df-7ca6-46dd-9417-64cda9d8f45f" />

                          Figure 1: Raw Output


<img width="512" height="325" alt="image" src="https://github.com/user-attachments/assets/320ed710-f925-450e-8e3b-1918b6bbbd51" />
  
    Figure 2: Transaction Summary showing successful and failed transactions  


<img width="512" height="325" alt="image" src="https://github.com/user-attachments/assets/83818dda-e01c-489a-a964-617257d408f7" />
  
                Figure 3: Key Performance Metrics Overview  


<img width="512" height="320" alt="image" src="https://github.com/user-attachments/assets/b3d95514-876c-46c0-ba51-fe4dc06d09ea" />
  
                  Figure 4: Transaction Time Comparison  

---

### **INTERPRETATION OF RESULTS**

The performance test on the website https://tools-httpstatus.pickup-services.com/ shows that the site can handle response times well when there is a moderate load. The average response time of 2.69 seconds, as shown in Figure 2, suggests that the server can manage multiple requests within a reasonable timeframe. Although the longest transaction recorded was 19.18 seconds, this is still within an acceptable range for a public service under load, especially with 50 concurrent users accessing the same website simultaneously. This indicates stable system performance for handling multiple user groups.

The website is good at handling data, with a throughput rate of 0.21 MB/sec, as shown in Figure 2. The transaction rate of 64.88 transactions per second shows that the server can manage multiple requests per second without serious problems, maintaining network utilization and server load. The total data transferred during the test was 12.35 MB, which shows that the website efficiently handles resource usage while maintaining stable data transfer capabilities.

The website successfully processed 3909 transactions with a 98.99% availability rate, even though 40 of them failed. This failure rate may be attributed to network timeouts or transient issues like rate limiting, which are common in public testing endpoints. However, the overall result of 3909 successful transactions in just 60 seconds shows that the server can manage massive traffic without serious problems.

---

### **BOTTLENECKS**

The performance test found a number of problems with the system's performance.  
The first bottleneck is the high average response time. Despite the website handling requests consistently, the average response time recorded during the test was 2.69 seconds, which is a little high for users. Even though response times ranged from 0.77 to 19.18 seconds, the average time could cause noticeable delays in page loading, affecting user experience. The high response time could be due to factors such as network latency, server load, or traffic congestion.

The second bottleneck is the unknown system capacity limit. The test simulated 50 concurrent users, and the website handled these requests efficiently, with a success rate of 98.99%. However, since the website performed well under this load, we cannot determine its true capacity. This limitation was due to the test configuration not being aggressive enough to push the system to its limits. To find the breakpoint, higher user loads should be tested in future evaluations.

The final bottleneck is that only a single endpoint was tested. During the test, only `/GET` was used. In real-world scenarios, other endpoints like `/POST`, `/PUT`, and `/DELETE` add backend processing time. Testing only one endpoint with fixed load does not fully evaluate the system. Real scenarios involve varied requests with different complexities that can affect performance differently.

---

### **RECOMMENDATIONS OF IMPROVEMENT**

While the website performed well under moderate load, some areas could be improved to enhance performance, especially for high traffic volumes.

**1. Optimize Response Time**  
The average response time of 2.69 seconds is high and may cause noticeable delays for end-users. The website should implement caching to reduce repeated data processing and use a Content Delivery Network (CDN) to offload traffic and reduce distance between servers and users, speeding up response times.

**2. Increase Test Limits**  
Although the website handled 50 concurrent users well, the test did not reach the system's maximum capacity. Future tests should increase concurrent users to identify the actual performance limit of the server.

**3. Reduce Failure Rate**  
The test resulted in a failure rate of 1.01% (40 failed transactions). Engineers should review error handling to minimize failed requests and ensure rate-limiting does not block valid traffic. Load balancing can also help distribute user traffic and reduce server overload.

---

### **CONCLUSION**

In conclusion, the website https://tools-httpstatus.pickup-services.com/ showed stable performance under moderate load, managing 50 concurrent users with 2.69 seconds average response time. The website’s throughput of 0.21 MB/sec and transaction rate of 64.88 transactions/sec indicate efficient handling of multiple requests simultaneously. However, improvements such as response time optimization and failure reduction are needed. By addressing these, the website can achieve higher availability and provide a better experience during high traffic conditions.

### **VIDEO**

## https://www.youtube.com/watch?v=OszLN6ys1mQ

### **JUSTIFICATION**

I selected Siege over alternatives like Apache JMeter or Grafana K6 because it is beginner-friendly and also provides realistic user simulation with random delays (-d5 parameter), supports concurrent connections (-c50), and generates complete transaction reports. The test plan focused on multiple HTTP status endpoints (200, 206, 302, 404) to simulate real-world user behavior and identify how different server responses impact performance under load. Based on the output we observed, we recommend that this website improve their availability when many users access the website simultaneously. In addition, this approach follows the specific standard recommendation for comprehensive web application performance testing, aligning with industry best practices.

### **REFERENCES**

Fulmer, J. E. (2023). Siege: An HTTP/HTTPS load testing and benchmarking tool (Version 4.0.5) [Computer software]. JoeDog Software. https://github.com/JoeDog/siege

Fulmer, J. E. (2023). Siege user manual and documentation. JoeDog Software. https://www.joedog.org/siege-manual/

Fielding, R., Gettys, J., Mogul, J., Frystyk, H., Masinter, L., Leach, P., & Berners-Lee, T. (1999). *Hypertext Transfer Protocol - HTTP/1.1* (RFC 2616). IETF. https://www.ietf.org/rfc/rfc2616.txt

Fulmer, J. E. (2023). Siege source code repository [Source code]. GitHub. https://github.com/JoeDog/siege

Molenaar, J. (2022). Web performance testing and benchmarking methodologies. In K. Johnson (Ed.), Modern DevOps practices (pp. 145-167). O'Reilly Media.
