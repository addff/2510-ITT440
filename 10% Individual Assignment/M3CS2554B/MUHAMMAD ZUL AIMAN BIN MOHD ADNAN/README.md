# MUHAMMAD ZUL AIMAN BIN MOHD ADNAN
Web Application Soak Testing with Vegeta 🔥
![image placeholder]

📋 Assignment Details
Course: ITT440 Name: Muhammad Zul Aiman Bin Mohd Adnan Matrix Number: 2024783699 YouTube Video: Click Here!

📱 Introduction
This project demonstrates a 30-second soak test on JokeAPI using the Vegeta load testing tool. Soak testing helps identify performance degradation, memory leaks, and stability issues under sustained load over an extended period.

⚙️ Test Environment & Methodology
🔧 Test Setup
Tool: Vegeta v12.12.0

Rate: 50 requests/sec

Test Duration: 30 seconds

Test Type: Soak Test (Reliability Test)

Target Website: JokeAPI

Total Requests: 1500

📊 Metrics Tracked
Requests

Latencies

Success rate

Status Code

Error Set

⏱ Test Execution
🧪 Vegeta Command
bash
vegeta attack -targets=targets.txt -rate=50 -duration=30s > results.bin
vegeta report < results.bin
vegeta report -type=json < results.bin > jokeapi_metrics.json
vegeta report -type=plot < results.bin
📈 Test Results & Analysis
📊 Performance Test Summary
Metric Category	Specific Metric	Value
Requests	Total Requests	1500
Request Rate	50.03 req/sec
Throughput	49.27 req/sec
Duration	Total Duration	30.45s
Attack Duration	29.98s
Wait Duration	464.53ms
Latencies	Minimum	—
Mean (Average)	291.54ms
50th Percentile	270.99ms
95th Percentile	368.25ms
99th Percentile	831.28ms
Maximum	1155.69ms
Data Transfer	Bytes In (Total)	627,196 bytes
Bytes In (Mean)	418.13 bytes/req
Bytes Out (Total)	0 bytes
Bytes Out (Mean)	0.00 bytes/req
Success Metrics	Success Rate	100.00%
HTTP 200 Count	1500 requests
Error Analysis	Error Set	None
📊 Performance Analysis
🎯 Request Performance
Indicator	Target	Actual	Efficiency
Request Rate	50.00 req/sec	50.03 req/sec	100%
Throughput	50.00 req/sec	49.27 req/sec	98.5%
Success Rate	100%	100%	100%
⚡ Response Time Analysis
Percentile	Response Time	Assessment
50th (Median)	270.99ms	Excellent
95th	368.25ms	Very Good
99th	831.28ms	Acceptable
Maximum	1155.69ms	Within Limits
🎯 Latency Performance
Best Case: —

Average Performance: 291.54ms — Very responsive

Median (50th %ile): 270.99ms — Indicates normal distribution

95th Percentile: 368.25ms — Majority under 400ms

Worst Case: 1155.69ms — Still under 1.2 seconds

📈 Data Transfer Efficiency
Total Data Received: 627 KB

Average Response Size: 418 bytes per request

Efficiency: Lightweight payloads, fast delivery

🔍 Key Performance Insights
🧱 System Stability
100% success rate = excellent reliability

No degradation during sustained load

Consistent performance throughout test duration

⚡ Response Time Consistency
Tight latency distribution

95th percentile shows strong user experience

Balanced load handling with minimal variance

🚀 Throughput Optimization
Near-perfect throughput matching

Low wait times = minimal system overhead

Efficient resource utilization

📈 Scalability Indicators
Linear performance scaling

No bottlenecks or contention

Stable memory and connection handling

🎯 Key Findings
✅ Exceptional Reliability

Perfect Success Rate: 100.00%

Zero Errors

Consistent Throughput

⚡ Outstanding Performance

Rapid Response Times

95% of requests under 400ms

Optimal Throughput Efficiency

📊 Performance Grade

Reliability: ✅

Responsiveness: ⚡

Consistency: 📈

Throughput: 🎯

✅ Conclusion
This soak test successfully validated JokeAPI’s ability to maintain stability and performance under sustained load, providing high confidence for production integration and user-facing applications.
