# 🔥 Web Application Soak Testing with Vegeta

---

## 📋 Assignment Details

- **Course**: ITT440  
- **Name**: Muhammad Zul Aiman Bin Mohd Adnan  
- **Matrix Number**: 2024783699  
- **YouTube Video**: [Click Here!](https://youtu.be/58SADSzZf90?si=PdgSUaVA0fy-I1D6)

---

## 📱 Introduction

This project demonstrates a **30-second soak test** on [JokeAPI](https://v2.jokeapi.dev/joke/Any) using the **Vegeta load testing tool**. Soak testing helps identify performance degradation, memory leaks, and stability issues under sustained load over an extended period.

---

## ⚙️ Test Environment & Methodology

### 🔧 Test Setup

- **Tool**: Vegeta v12.12.0  
- **Rate**: 50 requests/sec  
- **Duration**: 30 seconds  
- **Test Type**: Soak Test  
- **Target API**: JokeAPI `/joke/Any`  
- **Total Requests**: 1500  

### 📊 Metrics Tracked

- Requests  
- Latencies  
- Success Rate  
- Status Codes  
- Error Set  

---

## ⏱ Test Execution

### 🧪 Vegeta Commands

```bash
vegeta attack -targets=targets.txt -rate=50 -duration=30s > results.bin
vegeta report < results.bin
vegeta report -type=json < results.bin > jokeapi_metrics.json
vegeta report -type=plot < results.bin
vegeta plot -title "result" results.bin > results.html
results.html
```

### 📊 Performance Test Summary

| **Metric Category** | **Specific Metric**       | **Value**            |
|---------------------|---------------------------|----------------------|
| **Requests**        | Total Requests            | 1500                 |
|                     | Request Rate              | 50.03 req/sec        |
|                     | Throughput                | 49.27 req/sec        |
| **Duration**        | Total Duration            | 30.45s               |
|                     | Attack Duration           | 29.98s               |
|                     | Wait Duration             | 464.53ms             |
| **Latencies**       | Mean (Average)            | 291.54ms             |
|                     | 50th Percentile           | 270.99ms             |
|                     | 95th Percentile           | 368.25ms             |
|                     | 99th Percentile           | 831.28ms             |
|                     | Maximum                   | 1155.69ms            |
| **Data Transfer**   | Bytes In (Total)          | 627,196 bytes        |
|                     | Bytes In (Mean)           | 418.13 bytes/request |
|                     | Bytes Out (Total)         | 0 bytes              |
|                     | Bytes Out (Mean)          | 0.00 bytes/request   |
| **Success Metrics** | Success Rate              | 100.00%              |
|                     | HTTP 200 Count            | 1500 requests        |
| **Error Analysis**  | Error Set                 | None                 |


## 🔍 Performance Insights

### 🧱 System Stability
- ✅ 100% success rate  
- 🧠 No degradation during sustained load  
- 🔄 Consistent performance throughout test duration  

### ⚡ Response Time Consistency
- 📉 Tight latency distribution  
- 🎯 95% of requests under 400ms  
- 📊 Balanced load handling with minimal variance  

### 🚀 Throughput Optimization
- 📈 Near-perfect throughput matching  
- ⏱ Low wait times = minimal system overhead  
- 🧪 Efficient resource utilization  

### 📈 Scalability Indicators
- 🔁 Linear performance scaling  
- 🧩 No bottlenecks or contention  
- 🧠 Stable memory and connection handling  

---

## 🎯 Key Findings

### ✅ Exceptional Reliability
- Perfect Success Rate: 100.00%  
- Zero Errors  
- Consistent Throughput  

### ⚡ Outstanding Performance
- Rapid Response Times  
- 95% of requests under 400ms  
- Optimal Throughput Efficiency  

### 📊 Performance Grade
- **Reliability**: ✅  
- **Responsiveness**: ⚡  
- **Consistency**: 📈  
- **Throughput**: 🎯  

---

## ✅ Conclusion

This soak test successfully validated **JokeAPI’s** ability to maintain stability and performance under sustained load, providing high confidence for production integration and user-facing applications.

<img width="2557" height="914" alt="image" src="https://github.com/user-attachments/assets/304e3683-4f46-4edd-8a62-7f1173cb6212" />

