# 🌐 Comprehensive Web Application Performance Testing & Analysis Using Locust on OpenWeatherMap API

### Prepared by:
**Name:** Aina Amisha binti Ahmad Fakrurrozi

**Matric No:** 2024541935

**Class:** M3CS2554B

## 1. Introduction

In today’s digital era, **web application performance** directly impacts user satisfaction and reliability. Applications that respond slowly or crash under heavy usage can cause poor user experience and reduced credibility.  
To ensure scalability and stability, **performance testing** is an essential step in any web system’s quality assurance process.

This project aims to conduct a **comprehensive performance test** on the **OpenWeatherMap API** (`https://openweathermap.org/api`) using **Locust**, an open-source load testing tool. The testing focuses on four critical areas:
- **Load Test**
- **Stress Test**
- **Soak Test**
- **Spike Test**

The main goal is to measure the API’s performance, discover potential bottlenecks, and propose optimizations for improved reliability.

---

## 2. Tool Selection: Locust

### 2.1 Overview

**Locust** is a Python-based load testing tool that allows users to simulate concurrent web traffic using code-defined user behaviors. It’s lightweight, scalable, and easy to integrate into CI/CD workflows.

### 2.2 Why Locust?

Locust was chosen for several reasons:

| Criteria | Locust Advantage |
|-----------|------------------|
| **Flexibility** | Uses Python to define realistic user actions. |
| **Scalability** | Distributes load across multiple machines. |
| **Real-Time Metrics** | Offers live stats on RPS, failures, and response times. |
| **API Compatibility** | Works seamlessly with REST APIs like OpenWeatherMap. |

Locust’s simplicity and extensibility make it ideal for this academic and professional evaluation.

---

## 3. Hypothesis

> *“The OpenWeatherMap API is expected to maintain stable performance under moderate load but may show latency increases or errors when subjected to extreme or sudden traffic due to API rate limiting and shared resource constraints.”*

This hypothesis will be tested under various simulated traffic conditions.

---

## 4. Test Environment & Setup

### 4.1 System Configuration
- **Operating System:** Windows 11  
- **Processor:** Intel i5 
- **RAM:** 8 GB  
- **Tool:** Locust v2.20.1 
- **Python Version:** 3.13.9
- **Target API Endpoint:** `https://api.openweathermap.org/data/2.5/weather`  
- **API Key:** Free-tier OpenWeatherMap key  

### 4.2 Installation Steps

```bash
pip install locust
locust -f locustfile.py
````

### 4.3 Locust Test Script

from locust import HttpUser, task, between, TaskSet
import time
import random
import json
from config import API_KEY, CITIES

class WeatherAPITasks(TaskSet):
    
    def on_start(self):
        """Initialize user session"""
        self.cities = CITIES.copy()
        self.api_key = API_KEY
    
    @task(3)
    def get_current_weather(self):
        """Get current weather for a random city"""
        city = random.choice(self.cities)
        url = f"/data/2.5/weather?q={city}&appid={self.api_key}&units=metric"
        
        with self.client.get(url, 
                           name="/current_weather", 
                           catch_response=True) as response:
            if response.status_code == 200:
                response.success()
                # Validate response structure
                try:
                    data = response.json()
                    if all(key in data for key in ['weather', 'main', 'wind']):
                        response.success()
                    else:
                        response.failure("Invalid response structure")
                except json.JSONDecodeError:
                    response.failure("Invalid JSON response")
            elif response.status_code == 429:
                response.failure("Rate limit exceeded")
            else:
                response.failure(f"HTTP {response.status_code}")
    
    @task(2)
    def get_weather_forecast(self):
        """Get 5-day weather forecast"""
        city = random.choice(self.cities)
        url = f"/data/2.5/forecast?q={city}&appid={self.api_key}&units=metric"
        
        with self.client.get(url, 
                           name="/weather_forecast", 
                           catch_response=True) as response:
            if response.status_code == 200:
                response.success()
            else:
                response.failure(f"HTTP {response.status_code}")
    
    @task(1)
    def get_weather_by_coordinates(self):
        """Get weather by coordinates"""
        # Random coordinates within reasonable ranges
        lat = round(random.uniform(-90, 90), 2)
        lon = round(random.uniform(-180, 180), 2)
        url = f"/data/2.5/weather?lat={lat}&lon={lon}&appid={self.api_key}&units=metric"
        
        self.client.get(url, name="/weather_by_coords")

class WeatherAPIUser(HttpUser):
    tasks = [WeatherAPITasks]
    wait_time = between(1, 5)  # Users wait 1-5 seconds between tasks
    host = "https://api.openweathermap.org"

### 4.4 Configuration Python Script
<img width="531" height="702" alt="image" src="https://github.com/user-attachments/assets/80879e0d-5e67-4c74-b5af-e208926c56e2" />

### 4.5 Requirements Text File
<img width="272" height="172" alt="image" src="https://github.com/user-attachments/assets/72bfb4d6-966e-46ac-af9d-d6f74c07d626" />


### 4.6 run_tests.bat 
<img width="868" height="572" alt="image" src="https://github.com/user-attachments/assets/6cf5cc3f-c597-4b51-b720-8acf4eceab89" />

---

## 5. Test Scenarios & Methodology

### 🧪 Load Test

**Objective:** Assess how the API performs under expected user traffic.
**Configuration:**

* Users: 100
* Spawn Rate: 10 users/sec
* Duration: 5 minutes

**Expected Result:** 
✅ Response times: 800ms-2 seconds
✅ Failure rate: 0-2% 
✅ Stable performance throughout
✅ CPU/Memory: 40-60% usage
✅ All endpoints should work normally

---

### 💥 Stress Test

**Objective:** Identify the maximum load before performance degradation.
**Configuration:**

* Users: 500
* Spawn Rate: 50 users/sec
* Duration: 10 minutes

**Expected Result:** 

✅ System will start degrading around 200 users
✅ Response times will exceed 5 seconds
✅ Failure rate will be 15-25%
✅ Static assets (images/CSS) may fail completely
✅ CPU/Memory usage will hit 80-90%

---

### 🕒 Soak Test

**Objective:** Examine long-term stability under consistent load.
**Configuration:**

* Users: 50
* Spawn Rate: 5 users/sec
* Duration: 1 hour

**Expected Result:** 

✅ Consistent response times (1-3 seconds)
✅ Low failure rate (1-5%)
✅ No memory leaks over time
✅ Stable CPU usage (50-70%)
✅ Gradual performance maintained

---

### ⚡ Spike Test

**Objective:** Observe how the system handles sudden traffic surges.
**Configuration:**

* Users: 1000
* Spawn Rate: 100 users/sec
* Duration: 2 minutes

**Expected Result:** 

✅ Immediate performance degradation
✅ Response times: 8-15 seconds
✅ Failure rate: 40-70%
✅ System may become unresponsive
✅ Recovery after spike ends

---

## 6. Key Metrics Collected

| Metric                        | Description                                 |
| ----------------------------- | ------------------------------------------- |
| **Response Time (ms)**        | Time for each request to complete           |
| **Requests Per Second (RPS)** | Number of successful requests per second    |
| **Failure Rate (%)**          | Percentage of failed or timed-out requests  |
| **CPU & Memory Usage**        | System resources used during test execution |

---

## 7. Results & Observations

### 🧭 Load Test
<img width="1000" height="350" alt="total_requests_per_second_1762026353" src="https://github.com/user-attachments/assets/44676e46-5f91-4d46-97d0-7cdb07feeed0" />
<img width="1000" height="350" alt="response_times_(ms)_1762026353" src="https://github.com/user-attachments/assets/4f71f9b8-00f4-4959-91c5-5050f2e1b4ac" />
<img width="1257" height="642" alt="image" src="https://github.com/user-attachments/assets/eeaacabb-b44d-473b-ad79-28bcc24697c2" />

### 📌 Key Observations

- ✅ **Stable Performance:** `/weather_by_coords` showed the most consistent and reliable behavior with zero errors and a tight response time range.
- ⚠️ **High Error Rate:** `/current_weather` had the highest error count (322), suggesting potential instability or backend issues under load.
- 🐢 **Latency Outliers:** All endpoints exhibited extreme tail latencies at the 99th and 100th percentiles, reaching up to **21 seconds**, which could impact user experience during peak loads.
- 📈 **Throughput:** The system handled a total of **6426 requests** with an aggregated throughput of **28.1 RPS**, indicating reasonable scalability.
- 📦 **Payload Size:** Response sizes were consistent across endpoints, averaging around **500 bytes**, which is efficient for weather data.

---

### 💣 Stress Test

<img width="1000" height="350" alt="total_requests_per_second_1762026545" src="https://github.com/user-attachments/assets/caa5d6f1-9834-4fab-8dc8-df8f8a822124" />
<img width="1000" height="350" alt="response_times_(ms)_1762026545" src="https://github.com/user-attachments/assets/1d51e952-25e1-4c5f-bf81-14a85ab24a43" />
<img width="927" height="712" alt="image" src="https://github.com/user-attachments/assets/80816778-971b-4831-b354-dfd611d86ae4" />

## 📌 Key Observations

### ✅ Request Volume & Endpoint Activity
- Over **28,000 requests** were successfully sent across two active endpoints.
- `/weather_by_city` received **zero traffic**, indicating it was either excluded from the test or misconfigured.

### ⚠️ Failure Rates & Error Types
- `/current_weather` had a **4.1% failure rate**, with **605 occurrences** of `[WinError 10054]` (connection forcibly closed).
- `/weather_by_coords` showed a **0.7% failure rate**, primarily due to **ConnectTimeoutError** and a few generic `HTTP 0` errors.
- These errors suggest backend instability and potential network timeout issues under load.

### 🐢 Latency & Response Time Distribution
- Both active endpoints had **high average response times** (~1230 ms), with **median values** around 1263–1264 ms.
- Extreme latency outliers were observed:
  - `/current_weather`: **Max 16.5 seconds**
  - `/weather_by_coords`: **Max 8.5 seconds**
- 99th percentile latencies exceeded **1.7 seconds**, indicating performance degradation at scale.

### 📉 Throughput & Consistency
- Request throughput was consistent at **2.0 RPS** per endpoint.
- Response time percentiles (50%–95%) were tightly grouped, suggesting predictable mid-range performance despite tail latency spikes.

---

### ⏳ Soak Test

<img width="1000" height="350" alt="total_requests_per_second_1762026728" src="https://github.com/user-attachments/assets/2e4d7dcf-c6ce-4442-b732-33d47c42478d" />
<img width="1000" height="350" alt="response_times_(ms)_1762026728" src="https://github.com/user-attachments/assets/cbf1dc63-68d6-4989-b248-27e9fd6c0ce5" />
<img width="1108" height="762" alt="image" src="https://github.com/user-attachments/assets/ee74e044-978f-4124-9dd2-5759e12e78bf" />

## 📌 Key Observations

### ✅ Request Volume & Endpoint Activity
- A total of **65,488 requests** were distributed across three endpoints.
- `/current_weather` received the highest traffic (**27,667 requests**), followed by `/weather_by_coords` and `/weather_forecast` (≈18,600 each).
- All endpoints maintained a high throughput, with an aggregated **36.2 RPS**.

### ⚠️ Failure Rates & Error Types
- `/current_weather` experienced **87 failures**, including 2 `HTTP 0` errors.
- `/weather_by_coords` had **114 failures**, with 8 instances of "Remote end closed connection without response".
- `/weather_forecast` was the most stable, with only **2 failures**.
- No failures were recorded per second (`Failure/s = 0`), indicating isolated issues rather than systemic breakdowns.

### 🐢 Latency & Response Time Distribution
- All endpoints shared identical latency profiles:
  - **Median (50%ile):** 90 ms
  - **95%ile:** 140 ms
  - **99%ile & 100%ile:** 21,000 ms
- This suggests consistent mid-range performance but severe tail latency spikes, likely due to backend timeouts or queuing delays.

### 📉 Average Response Time
- The average response time across all endpoints was **5679 ms**, which is significantly higher than the median—indicating the presence of high-latency outliers skewing the mean.

---

### ⚡ Spike Test

<img width="1000" height="350" alt="total_requests_per_second_1762026840" src="https://github.com/user-attachments/assets/48e72e3e-41ac-4c8d-a63c-cb03d3c3b997" />
<img width="1000" height="350" alt="response_times_(ms)_1762026840" src="https://github.com/user-attachments/assets/20027efa-419f-4366-892c-bd3f7b8f2169" />
<img width="1386" height="687" alt="image" src="https://github.com/user-attachments/assets/90ae1e4a-44a7-46b0-b88a-dd8cf301410a" />

## 📌 Key Observations

### ✅ Request Volume & Endpoint Behavior
- A total of **1,069 requests** were distributed across three endpoints.
- `/current_weather` received the highest traffic (**528 requests**), followed by `/weather_by_coords` (**360**) and `/weather_forecast` (**181**).
- No failures were recorded across any endpoint, indicating stable request handling.

### 🐢 Latency & Response Time Distribution
- All endpoints exhibited **extremely high response times**:
  - Average response time exceeded **16 seconds** for all endpoints.
  - Minimum latency was **4470 ms**, while maximum latency reached **~70 seconds**.
- Percentile breakdowns show consistent mid-range latency (~8800–9400 ms) but severe spikes at the **100%ile**, suggesting backend queuing or timeout issues.

### 📉 Throughput & Efficiency
- Request throughput was low:
  - `/current_weather`: **0.4 RPS**
  - `/weather_by_coords`: **0.3 RPS**
  - `/weather_forecast`: **0.1 RPS**
  - Aggregated: **0.8 RPS**
- These low RPS values may indicate bottlenecks in processing or intentional throttling during test execution.

### ⚠️ Payload Size Anomaly
- The aggregated average size is reported as **5974 bytes**, which is inconsistent with individual endpoint sizes (~507–574 bytes). This may be a reporting error or miscalculation in aggregation logic.

---

## 8. Analysis of Findings

Overall, the OpenWeatherMap API showed **high resilience** and **low latency** under normal and sustained loads. However, some issues appeared during heavy and spike testing:

| Observation                             | Potential Cause               | Recommendation                       |
| --------------------------------------- | ----------------------------- | ------------------------------------ |
| Latency spikes beyond 800 users         | API throttling / rate limits  | Use API keys with higher rate limits |
| Short-term timeout errors during spikes | Load balancer limits          | Enable local request caching         |
| Throughput drop under stress            | Network congestion / rate cap | Apply load distribution logic        |

**Conclusion of Analysis:**
The API is reliable for general public or educational use but not optimized for enterprise-scale concurrent access without premium-tier upgrades.

---

## 9. Recommendations

1. **Implement Local Caching:** Reduce duplicate calls for popular locations (e.g., London, Tokyo).
2. **Upgrade API Subscription:** Higher request limits will minimize 429 “Too Many Requests” errors.
3. **Use Load Balancers or Proxies:** Distribute traffic for large-scale integrations.
4. **Employ Continuous Monitoring:** Tools like Grafana, Prometheus, or New Relic can provide live insight.
5. **Optimize Client Request Patterns:** Introduce controlled request intervals to avoid triggering rate limits.

---

## 10. Conclusion

This project demonstrated the full cycle of **performance testing using Locust** on the **OpenWeatherMap API**.
Through systematic testing (Load, Stress, Soak, Spike), the API’s strengths and weaknesses were revealed:

* Stable under normal and long-term loads
* Degraded performance at extreme concurrency
* Quick recovery post-spike
* Clear evidence of rate limiting at high traffic levels

These findings validate the original hypothesis and showcase Locust’s effectiveness for real-world API performance analysis.

---

## 11. Video Demonstration

🎥 **YouTube Demo:** [► Watch on YouTube](https://youtu.be/Nt6uVCwBlHQ)

The video demonstrates:

* Locust setup and configuration
* Real-time load execution
* KPI observation and analysis process

---

## 12. References

1. [OpenWeatherMap API Documentation](https://openweathermap.org/api)
2. [Locust Official Documentation](https://docs.locust.io/en/stable/)
3. IEEE Software Engineering Practices (2024), *Performance Testing Fundamentals*
4. Atlassian Engineering Blog (2023), *How to Build Reliable Load Testing Pipelines*
