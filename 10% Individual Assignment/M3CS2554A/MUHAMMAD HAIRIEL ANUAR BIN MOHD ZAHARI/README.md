# **⚡️Reqres API Load Test using BlazeMeter⚡️**  
<img width="900" height="350" alt="image" src="https://github.com/user-attachments/assets/42213e1a-1233-474d-83c4-4359806fc9dc" />

### Name: MUHAMMAD HAIRIEL ANUAR BIN MOHD ZAHARI
### Course: ITT440 
### Group: M3CS2554A  

---

## **💻Introduction**
The goal of this project is to employ load testing to assess the performance of the public API Reqres.in. Load testing guarantees that a system can manage concurrent requests without degradation and assists in determining how well it operates under particular user loads.

Measuring response time, throughput, and stability when numerous users access the API at once is the aim of this test. BlazeMeter, a cloud-based performance testing application that offers simple configuration, monitoring, and reporting, was used to conduct the test.

---

## **📽️Project Overview**
The target system for this project is **Reqres.in**, a free and publicly available REST API used for testing and prototyping HTTP requests.  

The project aims to:
- Simulate multiple virtual users (VUs) accessing the Reqres API.
- Measure average response time, throughput, and error rate.
- Evaluate the scalability and consistency of the API under continuous load.

**Endpoint tested:**
GET https://reqres.in/api/users?page=2

This endpoint was chosen because it contains actual HTTP request-response cycles and provides a paginated list of user data in JSON format, making it perfect for performance testing. Reqres.in offers a reliable and regulated environment for load testing without impacting any production systems because it is made for safe testing.

**Screenshot of API response:**

<img width="457" height="619" alt="image" src="https://github.com/user-attachments/assets/da7ff3dc-163f-42b7-a51e-3b8e09677f7f" />
<img width="724" height="414" alt="image" src="https://github.com/user-attachments/assets/282cda18-c468-4050-97fb-7310d1a54bbe" />


---

## **🛠️Tool Selection and Justification**
The tool selected for this project is **BlazeMeter**, an online performance testing platform that supports **Apache JMeter** scripts and cloud-based execution.

**Reasons for choosing BlazeMeter:**
1. **Ease of Use:** Offers a user-friendly interface for creating and running tests without the need for local setup.
2. **Scalability:** Allows hundreds of concurrent users to test from the cloud.
3. **Detailed Analytics:** Automatically produces comprehensive reports that include error rates, throughput, and response time percentiles.
4. **Integration Ready:** Suitable for automated testing with CI/CD tools.
5. **Free Tier:** Up to 50 concurrent users are supported under the free plan, which is appropriate given the scope of the project.

BlazeMeter was selected for its simplicity, flexibility, and professional reporting capabilities.

---

## **🧱Test Setup**

| Category | Details |
|-----------|----------|
| **Tool Used** | BlazeMeter (JMeter engine) |
| **Test Type** | Load Test |
| **Target API** | `https://reqres.in/api/users?page=2` |
| **Virtual Users (VUs)** | 50 |
| **Test Duration** | 10 minutes |
| **Ramp-Up Time** | Automatically handled by BlazeMeter |
| **Test Location** | US East (Virginia, Google Cloud) |
| **Request Method** | GET |
| **Expected Response Code** | 200 OK |
| **Success Criteria** | 95% of requests under 500 ms, error rate < 1% |

BlazeMeter continually sent GET queries to the Reqres API endpoint for 10 minutes at a time while simulating 50 concurrent virtual users. BlazeMeter's reporting system automatically captured metrics like response time, throughput, and errors.

---

## **📄Test Result**
**Summary of Results (from BlazeMeter Dashboard):**
<img width="1288" height="105" alt="image" src="https://github.com/user-attachments/assets/5ff95015-d6a5-4561-8374-c8891ceec37a" />


| Metric | Result | Description |
|--------|---------|-------------|
| **Max Virtual Users** | 50 | Total concurrent users simulated |
| **Average Throughput** | 480.27 hits/sec | Average successful requests per second |
| **Average Response Time** | 98.84 ms | Mean response time for all requests |
| **90th Percentile Response Time** | 115 ms | 90% of requests completed within this time |
| **Error Rate** | 0% | All requests succeeded |
| **Average Bandwidth** | 46.39 MiB/s | Average data transfer per second |
| **Test Duration** | 10 minutes | Total execution time |

**Load:** 

<img width="629" height="375" alt="image" src="https://github.com/user-attachments/assets/121bbb22-645c-4c96-9fcc-e86b293f042b" />


**Response Time:**

<img width="619" height="369" alt="image" src="https://github.com/user-attachments/assets/12b5f9c2-c88a-41cc-84fa-4585d514201b" />

**Main Timeline Chart:**

<img width="1920" height="1080" alt="main-timeline-chart-a492942d-2760-420b-ad75-9ad92909b2fc" src="https://github.com/user-attachments/assets/6c87ceb7-931d-4ef8-ae73-3c8b47468bc8" />


---

## **🔬Analysis**

### **Performance**
The Reqres API maintained excellent performance under a steady load of 50 virtual users.  
- The **average response time** of ~99 ms indicates very fast server processing.  
- The **90th percentile** of 115 ms shows that even the slowest requests were well within acceptable performance limits.  
- The **throughput** of 480 hits per second demonstrates high efficiency.  
- The **error rate** of 0% confirms the API handled the load flawlessly.

### **Scalability**
According to the test results, Reqres.in can simply scale to support at least 50 concurrent users without experiencing any performance issues. Higher VUs (e.g., 100–200) in future tests may assist determine the breaking point at which errors or an increase in response time occur.

### **Consistency**
There were no spikes or slowdowns in response times over the course of the 10-minute test.  
All simulated users showed consistent throughput and bandwidth usage, indicating dependable and predictable system performance.

---

## **🧬Raw Data**
| Parameter | Value |
|------------|--------|
| **Total Requests Sent** | ~288,000 (480 req/s × 600 seconds) |
| **Successful Requests (2xx)** | 100% |
| **Failed Requests** | 0 |
| **Minimum Response Time** | ~90 ms |
| **Maximum Response Time** | ~120 ms |
| **Average Response Time** | 98.84 ms |
| **90th Percentile** | 115 ms |
| **Average Bandwidth** | 46.39 MiB/s |

---

## **🔑Performance Results and Analysis**
The collected data shows that the Reqres API is **highly stable and responsive** under continuous load conditions.  

**Key Observations:**
- Response times consistently under 120 ms.
- No requests were unsuccessful.
- The throughput was kept at about 480 requests/second.
- The average bandwidth use is 46 MB/s.

**Interpretation:**
These numbers show how effectively Reqres.in's backend infrastructure manages many GET requests at once.  
All simulated users get consistent performance, which is a clear sign of great backend optimisation and dependable APIs.

---

## **📁Conclusion and Improvement**

### **Conclusion**
The Reqres API's outstanding performance and stability were validated by the BlazeMeter load test. The system maintained an average response time of less than 100 ms with 50 virtual users and no failures. It is demonstrating exceptional reactivity and efficiency.

### **Recommendations for Improvement**
1. **Increase Load Scale:** Perform stress testing with more users to find the performance threshold.  
2. **Multi-Region Testing:** Execute the same test from other geographic regions to observe latency differences.  
3. **Longer Testing Duration:** Run a soak test (1–2 hours) to detect long-term resource issues.  
4. **Integrate Monitoring Tools:** Use APM tools for server resource tracking.  

---

## **📼Video Demonstration**
https://youtu.be/vqqTmLdNRXs?si=Fj3QCHUdwbZvBmz0
