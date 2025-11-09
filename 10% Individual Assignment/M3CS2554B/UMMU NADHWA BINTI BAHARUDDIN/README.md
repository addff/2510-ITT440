
<p align="center">
  <img src="https://openweathermap.org/themes/openweathermap/assets/img/logo_white_cropped.png" alt="OpenWeatherMap Logo" width="200"/>
</p>

<h1 align="center">🌤️ API Testing with Postman & OpenWeatherMap</h1>

## 📘 INTRODUCTION
Postman is used in this project to test the OpenWeatherMap API's performance and functionality.  Three levels of load testing (Light, Medium, and Stress) are included to verify the stability of the API under simulated traffic.  Validating response codes, calculating average response times, and making sure the API can manage repeated requests without experiencing performance problems are the objectives.  These tests aid in evaluating dependability and scalability for practical use cases.

## 🎯 OBJECTIVE
- To perform automated API testing using Postman.
- To evaluate the reliability and response time of the OpenWeatherMap API.
- To ensure the returned data (status code 200 and response body) is accurate and consistent.
- To try with different API Key, different places and different purpose of load test (Medium, Stress and Light).

## 🛠️ TOOL & TARGET SITE SOLUTION
**Tool:** Postman  
**Target Site:** [OpenWeatherMap API](https://openweathermap.org/api)  

## 📋 TEST SCENARIOS
- Send GET request with valid latitude and longitude.
- Check if response status is 200.
- Measure average response time.
- Repeat test for multiple iterations to check consistency.
- Use different API key.<br>

   <img width="587" height="231" alt="image" src="https://github.com/user-attachments/assets/f5310651-c76e-4e4e-8077-12291f0a0640" /><br>


## 🧪 TEST PLAN & CONFIGURATION (Medium Load Test)
- **Request Method:** GET  
- **Endpoint:** `https://api.openweathermap.org/data/2.5/weather`  
- **Parameters:** (Depends on place that we want to test. Make sure we knows the longitude and latitude)<br>
  For examples: Melaka
  - `lat = 2.1896`  
  - `lon = 102.2501`  
  - `appid = 5ca69bc7f64a124d9c9180f120a23a01` - you need to get your own API key 
- **Iterations:** 50
- **Delay:** 1000 ms
- **Assertions:** Verify `Status Code = 200`

## 📊 RESULTS (with charts)
| Iteration | Status | Response Time (ms) | Response Size (B) |
|-----------|--------|--------------------|--------------------|
| 1         | ✅ PASS | 41                | 807                |
| 2         | ✅ PASS | 40                | 807                |
| 3         | ✅ PASS | 34                | 807                |
| 4         | ✅ PASS | 257               | 807                |
| 5 - 50    | ✅ PASS | ~87 avg           | 807                |

  **- Average Response Time:** 87 ms  
  **- Total Iterations:** 50  
  **- Duration:** 1m 54s  
  **- All Tests Passed (100%)**  

  <img width="925" height="230" alt="image" src="https://github.com/user-attachments/assets/844b9261-51f9-4aa7-91b4-a36f1173d779" />

## 📈 THROUGHPUT
Throughput helps measure how many requests the API can handle per second during a load test. It's a key performance metric in API testing.

**Example:**
- Total Requests: 50
- Total Duration: 114 seconds


```
Throughput = 10 / 114 ≈ 0.44 requests/sec
```

This means the API handled approximately **0.44 requests per second** during the test. Higher throughput indicates better performance and scalability.


## 🧪 ANOTHER TEST & CONFIGURATION (Light Load Test)
- **Parameters:**<br>
  For examples: Kuala Lumpur
  - `lat = 3.1390`  
  - `lon = 101.6869`  
  - `appid = 617863b3b7a29220c7ecc9dee6700327`
- **Iterations:** 20
- **Delay:** 2000 ms
- **Assertions:** Verify `Status Code = 200`

## 📊 RESULTS (with charts)
| Iteration | Status | Response Time (ms) | Response Size (B) |
|-----------|--------|--------------------|--------------------|
| 1         | ✅ PASS | 41                | 807                |
| 2         | ✅ PASS | 40                | 807                |
| 3         | ✅ PASS | 34                | 807                |
| 4         | ✅ PASS | 257               | 807                |
| 5 - 20    | ✅ PASS | ~102 avg          | 807                |

  **- Average Response Time:** 102 ms  
  **- Total Iterations:** 20  
  **- Duration:** 1m 26s  
  **- All Tests Passed (100%)**  
  

<img width="1106" height="222" alt="image" src="https://github.com/user-attachments/assets/6daa6028-53c6-482c-ba43-9a33502d9f54" />


## 📈 THROUGHPUT
**Result:**
- Total Requests: 20 requests
- Total Duration: 86 seconds


```
Throughput = 20 / 86 ≈ 0.23 requests/sec
```

This means the API handled approximately **0.23 requests per second** during the test.  

## 🧪 ANOTHER TEST & CONFIGURATION (Stress Load Test)
- **Parameters:**<br>
  For examples: Kota Kinabalu, Sabah
  - `lat = 5.9804`  
  - `lon = 116.0735`  
  - `appid = 089f622f3995e2d71cf9b84a5989a1b8`
- **Iterations:** 100
- **Delay:** 0 ms
- **Assertions:** Verify `Status Code = 200`

## 📊 RESULTS (with charts)
| Iteration | Status | Response Time (ms) | Response Size (B) |
|-----------|--------|--------------------|--------------------|
| 1         | ✅ PASS | 41                | 807                |
| 2         | ✅ PASS | 40                | 807                |
| 3         | ✅ PASS | 34                | 807                |
| 4         | ✅ PASS | 257               | 807                |
| 5 - 100   | ✅ PASS | ~82 avg           | 807                |

  **- Average Response Time:** 82 ms  
  **- Total Iterations:** 100  
  **- Duration:** 23s 779ms  
  **- All Tests Passed (100%)**  


  <img width="1229" height="223" alt="image" src="https://github.com/user-attachments/assets/6174ccfd-1f36-450c-83c4-d27ff8227b33" />


## 📈 THROUGHPUT
**Result:**
- Total Requests: 100
- Total Duration: 23s 779ms


```
Throughput = 100 / 23.779 ≈ 4.2 requests/sec
```

This means the API handled approximately **4.2 requests per second** during the test.  


## 🚀 LOAD TEST SUMMARY

| Test Type      | Iterations | Delay   | Duration    | Avg Response Time | Throughput (req/sec) |
|---------------|------------|---------|-------------|--------------------|----------------------|
| 🟢 Light       | 20         | 2000ms  | 1m 26s      | 102 ms            | 0.23                |
| 🟡 Medium      | 50         | 1000ms  | 1m 54s      | 87 ms             | 0.44                |
| 🔴 Stress      | 100        | 0ms     | 23.8s       | 82 ms             | 4.2                 |


### 📈 Insights
All tests passed successfully with 100% success rate. Response times remained under 120 ms across all load levels, demonstrating strong API stability. Throughput increased significantly under stress conditions, indicating good scalability and performance.  

## 📌 ANALYSIS & DISCUSSION
✅ All requests returned a 200 OK status, confirming successful communication with the API.  
⏱️ Response times were stable across Light, Medium, and Stress tests, with averages of 102 ms, 87 ms, and 82 ms respectively.  
📦 The consistent response size (807 B) indicates structured and reliable JSON output.  
⚡ Throughput increased significantly under stress conditions (4.2 req/sec), showing good scalability.  
 
## 💡 RECOMMENDATIONS
- Implement Postman monitors for real-time API uptime tracking.
- Expand testing with invalid parameters (negative test cases).
- Automate collection runs via CI/CD for continuous testing.

## ✅ CONCLUSION
The OpenWeatherMap API demonstrated strong reliability and stability throughout all test iterations. Each request returned a successful `200 OK` status, confirming that the endpoint is functioning as intended. Response times were consistently within acceptable limits, with only minor fluctuations attributed to network latency. The uniform response size and structured JSON output further validate the integrity and predictability of the data provided by the API.

Overall, these results indicate that the OpenWeatherMap API is well-suited for real-time weather data retrieval in production environments. Its performance under repeated requests suggests that it can handle moderate traffic without degradation in speed or accuracy. For future improvements, integrating automated monitoring and expanding negative test cases will enhance robustness and ensure continued reliability under diverse conditions.

## 🔗 REFERENCES
- [OpenWeatherMap API Documentation](https://openweathermap.org/api)
- [Postman Learning Center](https://learning.postman.com/)

## ▶️ EMBEDEED YOUTUBE VIDEO LINK
[Click here to watch the demo](https://youtu.be/A9ePeeLQO5I?si=Fsy3LHZpUunBpAOW)
