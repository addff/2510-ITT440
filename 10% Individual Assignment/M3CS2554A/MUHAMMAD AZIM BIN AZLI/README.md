# Web Application Load Testing with Vegeta 🔥

<img width="600" height="852" alt="image" src="https://github.com/user-attachments/assets/0760177f-6683-4f3f-90e1-6bfb18941c04" />


# 📋 Assignment Details
### - **Course:** ITT440
### - **Name:** MUHAMMAD AZIM BIN AZLI
### - **Matrix Number:** 2024539875
### - **Youtube Video: https://youtu.be/ChZh3fb80Do**


# 📱Introduction
This project demonstrates a **30-second load test and 50 request per second** on BlazeDemo using the **Vegeta load testing tool**.  
Load testing helps evaluate the **server’s performance, reliability, and responsiveness** under simulated user traffic.


# ⚙️ Test Environment & Methodology

## Test Setup
- **Tool:** Vegeta v12.12.0  
- **Rate:** 50 requests per second  
- **Duration:** 30 seconds  
- **Test Type:** Load Test (Performance & Stability)  
- **Target Website:** BlazeDemo  
- **Total Requests:** ~1500  

## Metrics Tracked
- Requests per second  
- Latencies (min, mean, percentiles, max)  
- Throughput rate  
- Success ratio  
- Status code  
- Error set  


# ⏱ Test Execution

## Vegeta Command
```bash
# Open the CMD or windows powerShell as administrator and enter the director of the file location
cd C:\Users\HP\Documents\vegeta_12.12.0_windows_amd64

# Create target file
Set-Content -Encoding Ascii targets.txt "GET https://blazedemo.com/"

# Run Vegeta attack (30 seconds at 50 requests/sec)
& .\vegeta.exe attack -duration 30s -rate 50 -targets targets.txt -output results.bin

# Generate test report
cmd /c ".\vegeta.exe report < results.bin"

# Create HTML plot
cmd /c ".\vegeta.exe plot < results.bin > plot.html"

# Open the HTML visualization
Start-Process plot.html
```


## 📈 Test Results & Analysis

### 📊 Raw Test Result Output
```plaintext
PS C:\Users\HP\Documents\vegeta_12.12.0_windows_amd64> cmd /c ".\vegeta.exe report < results.bin"

Requests      [total, rate, throughput]         1500, 50.04, 49.49
Duration      [total, attack, wait]             30.307s, 29.978s, 329.44ms
Latencies     [min, mean, 50, 90, 95, 99, max]  301.747ms, 360.631ms, 345.07ms, 390.247ms, 441.223ms, 645.301ms, 1.503s
Bytes In      [total, mean]                     6711000, 4474.00
Bytes Out     [total, mean]                     0, 0.00
Success       [ratio]                           100.00%
Status Codes  [code:count]                      200:1500
Error Set:
```

### 📊 Performance Test Summary

| **Metric Category** | **Specific Metric** | **Value** |
|----------------------|---------------------|-----------|
| **Requests** | Total Requests | 1500 |
|  | Request Rate | 50.04 req/sec |
|  | Throughput | 49.49 req/sec |
| **Duration** | Total Duration | 30.307s |
|  | Attack Duration | 29.978s |
|  | Wait Duration | 329.44ms |
| **Latencies** | Minimum | 301.747ms |
|  | Mean (Average) | 360.631ms |
|  | 50th Percentile | 345.07ms |
|  | 90th Percentile | 390.247ms |
|  | 95th Percentile | 441.223ms |
|  | 99th Percentile | 645.301ms |
|  | Maximum | 1.503ms |
| **Data Transfer** | Bytes In (Total) | 6,711,000 bytes |
|  | Bytes In (Mean) | 4,474 bytes/request |
|  | Bytes Out (Total) | 0 bytes |
|  | Bytes Out (Mean) | 0.00 bytes/request |
| **Success Metrics** | Success Rate | 100.00% |
|  | HTTP 200 Count | 1500 requests |
| **Error Analysis** | Error Set | No errors |


# 📊 Performance Analysis

### 🎯 Request Performance

| **Indicator** | **Target** | **Actual** | **Efficiency** |
|----------------|------------|-------------|----------------|
| Request Rate | 50 req/sec | 50.04 req/sec | 100% |
| Throughput | 50 req/sec | 49.49 req/sec | 99% |
| Success Rate | 100% | 100% | 100% |

### ⚡ Response Time Analysis

| **Percentile** | **Response Time** | **Assessment** |
|----------------|-------------------|----------------|
| 50th (Median) | 345.07msms | Excellent |
| 90th | 390.247ms | Very Good |
| 95th | 441.223ms | Good |
| 99th | 645.301ms | Acceptable |
| Maximum | 1.503ms | Within Limits |


## 🎯 Latency Performance
- Best Case: 301ms → Fast and responsive
- Average Case: 360ms → Consistent user experience
- 90th Percentile: <400ms → 90% of users get responses under half a second
- Worst Case: 1.5s → Rare but acceptable under load


## 📈 Data Transfer Efficiency
- Total Data Received: 6.71 MB across all requests
- Average Response Size: 4.47 KB/request
- Throughput Efficiency: 98.9% success under sustained 50 req/sec


## 🔍 Key Performance Insights

1. **System Stability**
   - The 100% success rate confirms BlazeDemo handled all requests without failure.
   - Performance remained consistent throughout the 30-second load test.
   - No degradation, errors, or timeouts were detected — indicating strong reliability.

2. **Response Time Consistency**
   - Latency distribution (301ms to 1.503s) shows predictable response behavior under load.
   - 95th percentile at 441ms ensures smooth experience for most users.
   - Minimal deviation between mean (360ms) and median (345ms) indicates steady server performance.

3. **Throughput Optimization**
   - Near-perfect throughput matching (49.49/50 = 99% efficiency) demonstrates strong load handling.
   - Low wait time (329ms) suggests efficient backend and minimal queuing delay.
   - Server sustained almost full request rate without performance drop.

4. **Scalability Indicators**
   - Linear request handling — performance scales with incoming rate.
   - No signs of server saturation or throttling.
   - Consistent latency and zero errors show readiness for higher load scaling.


# 🎯 Key Findings

### ✅ Exceptional Reliability
- **100% Success Rate:** All requests completed successfully.
- **No Errors:** No timeout or HTTP failure observed.
- **Consistent Performance:** Stable throughput and response times.

### ⚡ Outstanding Performance
- **Average Latency:** 360ms (Excellent).
- **Max Latency:** 1.5s (Within acceptable threshold).
- **High Efficiency:** 49.49/50 req/sec achieved.

### 📊 Performance Grade: **Excellent**
- **Reliability:** 100% ✅
- **Responsiveness:** A ⚡
- **Consistency:** Excellent 📈
- **Throughput:** A+ 🎯

### Performance Metrics
<img width="1910" height="922" alt="vegeta-plot" src="https://github.com/user-attachments/assets/e3d7f5c1-8853-49ec-875c-48e4c2c6537a" />


# ✅ Conclusion
The BlazeDemo website maintained excellent performance and stability under a load of 50 requests per second for 30 seconds.
With a 100% success rate, low latency, and no degradation, BlazeDemo demonstrates robust handling capacity suitable for production-scale environments.


# 📺 References

- Tool: Vegeta Load Testing Tool
- Target Website: https://blazedemo.com/
- Test Environment: Windows PowerShell 
- YouTube Video: https://youtu.be/ChZh3fb80Do


 
