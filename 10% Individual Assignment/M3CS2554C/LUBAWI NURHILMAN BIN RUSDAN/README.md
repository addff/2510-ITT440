# Web Performance Spike Testing using Vegeta
<img width="600" height="852" alt="image" src="https://github.com/user-attachments/assets/43bb5240-24ac-42bc-a45e-278bfe7cb3ed" />

## 📝 Tester Details

* **Name** : LUBAWI NURHILMAN BIN RUSDAN
* **Student ID** : 2025159367
* **Course** : ITT 440

## **Introduction**
Vegeta is an open source, HTTP load testing tool built in GO programming language. It is primarily designed to high throughput, robust tool used for load testing APIs and web service. Its name is is a reference to a well known series known as Dragon Ball Z character, who is one of the most iconic character in the series.

## 🛠️ Tool Selection Justification

This article uses **Vegeta** due to its lightweight nature and simplicity, making it ideal for fast, high-concurrency testing of web services and APIs. This is perfect for isolating performance bottlenecks in the stateless API.

## **Testing Machine**
  - OS : Windows 11
  - CPU : Ryzen 7 5800H
  - RAM : 16 GB

## **Test Setup**
  - Tool Version : 12.13.0
  - Test Request : 100 Per seconds
  - Duration : 15 seconds
  - Test Type : Spike Test


## 🎯 **Target Application, Hypothesis**
The target for this performance analysis is the **randomuser.me API**. The randomuser.me API is hypothesized to get high latency spikes as **high latency (90th percentile above 500ms)** and a measurable increase when subjected to a sudden **Spike Test** of 100 requests per second for a duration of 15 seconds. 

<img width="1558" height="500" alt="vegeta-plot (1)" src="https://github.com/user-attachments/assets/49aad5fb-b11c-4da6-8f4f-27c3a230d508" />

Fetch URL of target
```
GET https://randomuser.me/api/
```

**Vegeta Testing Command** 
```
vegeta attack -targets="targets.txt" -rate=100/s -duration=15s -output="spike_test_results.bin"
```

**Vegeta Testing Result**
```
vegeta report < spike_test_results.bin
vegeta plot -title="Spike Test Report" < spike_test_results.bin > spike_test_report.html
```
## 🔥**Performance Test Result** 
### Performance Test Summary

| Metric Category | Specific Metric | Value |
| :--- | :--- | :--- |
| **Requests** | Total Requests | 1500 |
| | Request Rate | 100.04 req/sec |
| **Throughput** | Throughput | 93.29 req/sec |
| **Duration** | Attack Duration | 14.994s |
| | Total Duration | 16.057s |
| **Latencies** | Minimum | 3.857ms |
| | Mean (Average) | 436.229ms |
| | 50th Percentile | 355.889ms |
| | **90th Percentile (P90)** | **743.217ms** |
| | 99th Percentile (P99) | 1.386s |
| | Maximum | 2.218s |
| **Success/Errors** | Success Ratio | 99.87% |
| | Status Codes | 200:1498, 0:2 |

## **✅Recommendations for Improvements** 
Based on the evidence of latency spikes, a recommendation suggested by proffessionals used to enhance the API is :
- Implement Aggresive Caching :  Since the used API generates random but non-sensitive data, by implementing aggresive caching layer could help to offload more requests during the spike, and reducing the load on the system.
- Tune Server Connection Protocol : Current setup successfully manage to avoid failures but it can optimized more. Tuning could help to process the burst faster before it become more severe.

## **Conclusion** 
The performance analysis of Vegeta shows that randomuser.me API is stable enough to avoid any critical failure under a 100 requests per second. The high latency shows a significant failure to meet performance standards during high load. Future efforts to be considered should be prioritizing caching and throttling to ensure better qualify of service for all user.  

## **Video Demonstration**
The detailed video demonstration is in the link given : 
https://youtu.be/baGPjIKtZNU
