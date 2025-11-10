# 🚀 Performance Load Testing on JSONPlaceholder API Using Artillery


**Name:** Nurul’Izzati binti Mohammad Zaki  
**Student ID:** 2025395205  
**Class:** M3CS2554C

🎥 **Demo Video:** [Watch on YouTube](https://youtu.be/PQ_eV3Rm3fs)

---

## 🧭 Introduction

This project focuses on evaluating the performance and stability of the **JSONPlaceholder API** by running a **load test** using **Artillery**, a popular open-source performance testing tool built for Node.js.  
The aim is to measure the system’s behavior when multiple users access it simultaneously and to determine how well it performs under different traffic conditions.
Performance testing is a key step in ensuring that any web service can scale efficiently without causing downtime or errors. Although JSONPlaceholder is a mock REST API commonly used for testing, it is a great candidate for simulating real-world API behavior under load. This helps us practice analyzing performance metrics such as throughput, latency, response times, and stability.

---

## 🎯 Goal and Hypothesis

The main goal of this test is to analyze how **JSONPlaceholder** handles increasing user load and whether it remains stable under pressure.

**Hypothesis:**  
> The JSONPlaceholder API will maintain good performance under load, with average response times below 500 milliseconds, minimal latency spikes, and no request failures even at peak user load.

This hypothesis assumes that the API backend is optimized enough to handle concurrent requests without noticeable slowdowns or timeouts.

---

## ⚙️ Tool Selection Justification

<p align="center">
  <img src="https://github.com/user-attachments/assets/ebebad24-dbb1-4cf0-9f99-22e37df98677" alt="1_p4IQfjORMIMZtN8SJRjzcA" width="500" height="280">
  <br>
  <em>Figure 1: Artillery Perfomance Testing Tool</em>
</p>



Choosing the right tool is one of the most important steps in performance testing because it determines how accurately the test simulates real-world conditions and how meaningful the data collected will be.

For this project, **Artillery** was selected as the primary load testing tool. Artillery is a **modern, open-source performance testing framework** built for **Node.js**, specifically designed to test APIs, web services, and backend systems under different traffic loads.

---

### 🧩 Why Artillery?

| **Reason** | **Explanation** |
|-------------|-----------------|
| **Ease of Setup** | Artillery uses simple and readable **YAML configuration files**, making it beginner-friendly and easy to modify for various test scenarios. |
| **Realistic User Simulation** | Supports **virtual users (VUs)** that mimic real-world interaction patterns such as sending requests, waiting (think time), and repeating actions. |
| **Detailed Metrics** | Provides comprehensive test data, including response times, throughput, latency percentiles (p50, p95, p99), and error rates. |
| **Scalability** | Can easily scale from small local tests to large distributed tests using **Artillery Cloud**. |
| **Integration Support** | Works well with CI/CD pipelines such as GitHub Actions or Jenkins, allowing automated performance testing during deployment. |
| **Lightweight and Efficient** | Runs smoothly without consuming heavy system resources, unlike tools such as JMeter that require a Java runtime and GUI. |
| **Cloud Visualization** | Built-in integration with **Artillery Cloud** for generating interactive graphs and comparing test runs over time. |
| **Active Community & Open Source** | Actively maintained, with a large community contributing plugins, examples, and updates. |
| **Industry Adoption** | Widely used by developers and QA engineers for REST API load testing in real projects, ensuring credibility and reliability. |

Artillery was ultimately chosen because it is:

- **Easy to configure and understand**
- **Accurate and data-rich in its performance metrics**
- **Lightweight yet powerful**
- **Supported by modern visualization (Artillery Cloud)**
- **Aligned with industry best practices**

This combination makes it an excellent tool for both **academic learning** and **professional testing environments**, ensuring credible, reproducible, and clear results.

---

## 🧩 Test Environment

| Component | Details |
| --- | --- |
| Operating System | Windows 11 |
| Node.js Version | 22.21.0 |
| Artillery Version | 2.0.26 |
| Target URL | https://jsonplaceholder.typicode.com |
| Internet Connection | WiFI Broadband Connection |

- This setup was sufficient for performing load testing locally without the need for a dedicated server or cloud infrastructure.
---
## 🧠 Understanding JSONPlaceholder

JSONPlaceholder is a free REST API used for testing and prototyping. It provides typical endpoints found in real applications, such as `/posts`, `/users`, `/comments`, and more.  
In this test, three main endpoints were selected to represent common API operations:
- `GET /posts/1` — Retrieve a single post
- `GET /users/1` — Retrieve user details
- `POST /posts` — Create a new post (simulated write operation)

By mixing both **read** and **write** requests, the test offers a more realistic simulation of actual user interaction with a web API.

---

## 📋 Test Scenario Configuration

Each **virtual user (VU)** mimics a real user’s actions by making several sequential API calls.  
The configuration file (`jsonplaceholder-load-test.yml`) defines this behavior clearly.

| Step | Action | Endpoint | Method |
| --- | --- | --- | --- |
| 1 | Retrieve a post | `/posts/1` | GET |
| 2 | Retrieve a user | `/users/1` | GET |
| 3 | Create a new post | `/posts` | POST |
| 4 | Wait between requests | — | think(1s) |

This structure ensures each simulated user acts realistically, including short pauses between requests.

---

## 📈 Load Phases

| Phase | Duration | Arrival Rate | Ramp To | Description |
| --- | --- | --- | --- | --- |
| Low | 30s | 2 users/sec | 5 users/sec | Establish baseline load |
| Moderate | 60s | 5 users/sec | 10 users/sec | Typical daily traffic simulation |
| Heavy | 90s | 10 users/sec | 15 users/sec | Peak traffic to test stability |

This gradual increase simulates real-world traffic, helping to identify how performance scales with concurrent users.

---

## 🧰 Test Execution

### 🧪 Step 1: Coding (in VS Code Terminal)
```bash
config:
  target: "https://jsonplaceholder.typicode.com"
  phases:
    - duration: 30
      arrivalRate: 2
      rampTo: 5
      name: "Low load test"
    - duration: 60
      arrivalRate: 5
      rampTo: 10
      name: "Moderate load test"
    - duration: 90
      arrivalRate: 10
      rampTo: 15
      name: "Heavy load test"
  defaults:
    headers:
      Content-Type: "application/json"
  http:
    timeout: 30  # prevents timeouts for slower connections

scenarios:
  - name: "Stable JSONPlaceholder Load Test"
    flow:
      - get:
          url: "/posts/1"
      - get:
          url: "/users/1"
      - post:
          url: "/posts"
          json:
            title: "Artillery JSON Load Test"
            body: "This test checks API stability under increasing load."
            userId: 1
      - think: 1
```

### Step 2: Install Node.js and Artillery 

Open the integrated terminal in **Visual Studio Code** and run these commands step by step.

### 1️⃣ Install Node.js (if not installed)

- After installation, verify using:
```bash
node -v
npm -v
```
### 2️⃣ Install Artillery globally
```bash
npm install -g artillery

```
### 3️⃣ Verify Artillery installation
```bash
artillery --version

```
or
```bash
artillery -v

```

### 🧪 Step 3: Run the Test (Basic)
- Run the load test using configuration file. This will display live results directly in the terminal.

```bash
artillery run jsonplaceholder-load-test.yml

```
### 💾 Step 4: Save Test Results Locally
- To save the test output in JSON format inside a results folder, run:

```bash
npx artillery run --output "results/jsonplaceholder-load-test-report.json" jsonplaceholder-load-test.yml

```
- This will create a file named test_output.json inside the results directory.
This can use this file to generate charts or reports.

### ☁️ Step 5: Upload Results to Artillery Cloud (for Graphs)
- To visualize your results on Artillery Cloud, use this command:

> ⚠️ Important: Replace the API key with your own Artillery Cloud key before running.

```bash
npx artillery run --record --key YOUR_ARTILLERY_CLOUD_KEY --output "results/jsonplaceholder-load-test-report.json" jsonplaceholder-load-test.yml

```

---

## 🧮 Test Summary

| **Metric** | **Result** |
|-------------|------------|
| **Total Duration** | 3 minutes 6 seconds |
| **Total Requests Sent** | 5,040 |
| **Completed Requests** | 5,040 |
| **Failed Requests** | 0 |
| **Average Request Rate** | 44 requests/sec |
| **Average Response Time** | 126.1 ms |
| **95th Percentile** | 320.6 ms |
| **99th Percentile** | 415.8 ms |
| **Error Rate** | 0% |
| **Virtual Users Simulated** | 1,680 |

---

## 📊 Data Analysis

<p align="center">
  <img src="https://github.com/user-attachments/assets/adf1012e-c5d3-4669-bbb6-39fc5f0a6aad" alt="Artillery Response Time Graph" width="750"/><br>
  <em>Figure 2: Artillery Cloud graph showing response time and request rate trends</em>
</p>


### 🔹 Throughput
The request rate increased gradually from about **8–10/sec** requests per second in the low phase to around **44/sec** during the heavy phase.
✅ The API handled the growing traffic without showing timeouts or failed responses.

---

### 🔹 Response Time

| **Metric** | **Value** |
|-------------|-----------|
| **Minimum** | 3 ms |
| **Mean** | 126.1 ms |
| **Median (p50)** | 67.4 ms |
| **95th Percentile** | 320.6 ms |
| **99th Percentile** | 415.8 ms |
| **Maximum** | 1,070 ms |

⚡ Most responses completed in under **0.3 seconds**, which is excellent for a public API.
Even at peak load, the system maintained acceptable latency.

---

### 🔹 HTTP Status Codes

| **Status Code** | **Count** | **Description** |
|------------------|-----------|-----------------|
| **200** | 3,360 | Successful `GET` requests |
| **201** | 1,680 | Successful `POST` requests |
| **Errors** | 0 | No failures recorded |

✅ The high number of `2xx` codes confirms consistent uptime and stability during all test phases.

---

## 📉 Graph Interpretation (Artillery Cloud)
<p align="center">
  <img src="https://github.com/user-attachments/assets/69b9b09c-7817-4fe4-a743-5b3afed799d0" alt="Artillery Cloud Graph" width="750"/><br>
  <em>Figure 3: Artillery Cloud graph showing load test metrics</em>
</p>


| **Metric** | **Interpretation** |
|-------------|--------------------|
| **Request Rate Graph** | Shows consistent increase across phases, confirming stable ramp-up. | 
| **Response Time (p95)** | Slight rise during heavy load, but remains within acceptable range. |
| **Virtual Users Graph** | Demonstrates smooth user scaling and proper concurrency simulation. |

These visualizations confirm that JSONPlaceholder sustains good performance even when faced with growing user demand.

---

## 🧠 Result Interpretation and Discussion

The results show that the **JSONPlaceholder API** handled all phases of the load test efficiently with **no errors or request failures**. Across three minutes of testing, the system maintained stable performance, quick response times, and consistent throughput.

During the **low load phase**, the API responded quickly with an average response time below 100 ms, setting a strong performance baseline.  
As the test moved to the **moderate phase**, the throughput increased steadily to about **20 requests per second**, with no drop in performance.  
In the **heavy load phase**, the rate reached around **44 requests per second**, and response times remained stable, averaging **126 ms** with the **95th percentile at 320 ms**.

The **p95 and p99 values** indicate that most users experienced responses under 0.3 seconds, while only a few requests took longer due to normal network delays.  
Throughout all phases, there were **no failed or timed-out requests**, proving the API’s stability under concurrent usage.

The **HTTP response codes** also confirm consistent reliability, with 3,360 successful `GET` requests (200) and 1,680 successful `POST` requests (201). This shows that both read and write operations were processed correctly without interruption.

From a performance perspective, the **Artillery tool** effectively simulated realistic user behavior and provided detailed metrics such as response time and throughput. The system’s scalability was evident, as performance remained steady even as the number of virtual users increased.

In summary:
- ✅ No request failures or timeouts
- ⚡ Average response time: **126 ms**  
- 📈 Throughput scaled up smoothly to **44 requests/sec**  
- 🧩 Stable performance across all test phases  
- 🟢 Consistent 2xx response codes (100% success rate)

Overall, the **JSONPlaceholder API** proved to be **stable, responsive, and reliable** under varying levels of load, and **Artillery** successfully provided accurate, real-world performance insights.

---

### ⚠️ Identified Bottlenecks

| **Observation** | **Impact** |
|------------------|------------|
| Minor latency spikes during heavy load | Negligible; short-lived and within expected tolerance |
| Lack of backend metrics | Could not monitor CPU/memory since the API is public |
| Network delay variance | Slight changes due to routing and external latency factors |

These issues are expected when testing a third-party API without direct server monitoring.

---

## 🧭 Recommendations and Test Plan Justification

### 💡 Recommendations for Real Scenarios

- Implement **caching** and **Content Delivery Networks (CDNs)** to further reduce response times.  
- Integrate system-level monitoring tools like **Prometheus** and **Grafana** for CPU and memory tracking.  
- Conduct **stress** and **soak tests** in addition to load testing to identify breaking points and long-term performance trends.  
- Test from multiple global regions to evaluate latency differences across geographies.  

---

### 📘 Test Plan and Tool Justification

| **Aspect** | **Justification** |
|-------------|-------------------|
| **Test Design** | Gradual ramp-up mimics real-world behavior, avoiding traffic spikes. |
| **Tool Selection** | Artillery chosen for clarity, YAML-based config, and detailed percentile tracking. |
| **Industry Practice** | Follows ISO/IEC 25010 and ISTQB testing guidelines for performance evaluation. |
| **Evidence Collected** | Data shows stable throughput, consistent latency, and zero error rate. |

The approach aligns with **performance engineering best practices** and shows Artillery’s reliability in producing reproducible results.

---

## 🧾 Justification Based on Industry Standards

The testing plan and conclusions align with **industry best practices** for performance testing:

- Gradual load ramping ensures reliable data without artificial stress spikes.  
- Percentile metrics (**p95**, **p99**) provide realistic latency insights beyond averages.  
- Zero error rate confirms **strong API reliability**.  
- Visualization and documentation meet **DevOps and QA** reporting standards.

These findings demonstrate professional-level application of empirical testing and analysis methods suitable for **production-grade API evaluation**.

---

## 🏁 Conclusion

In conclusion, the **load testing results** show that the **JSONPlaceholder API** is **stable, reliable, and efficient** under different levels of simulated user load.

Across all three test phases, **5,040 requests** were successfully completed with **no failures** and an **average response time of only 126 ms**.

This demonstrates that the API can handle **concurrent users effectively**, maintaining consistent performance even as load increases.  
**Artillery** proved to be a reliable and user-friendly tool for simulating realistic load conditions and capturing detailed performance data.

With a **structured test plan**, **gradual load scaling**, and **proper monitoring**, meaningful insights into API behavior can be achieved which helping developers better understand system performance under pressure.

---




























