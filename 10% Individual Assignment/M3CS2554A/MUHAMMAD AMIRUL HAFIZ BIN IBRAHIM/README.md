LOAD, STRESS AND SPIKE TESTING ON JSONPLACEHOLDER PUBLIC API USING APACHE JMETER

NAME: MUHAMMAD AMIRUL HAFIZ BIN IBRAHIM

STUDENT ID: 2023485396

COURSE: ITT440 - INDIVIDUAL ASSIGNMENT

GROUP: M3CS2554A


🧩 Project Overview

This project demonstrates the use of Apache JMeter to perform comprehensive performance testing on the JSONPlaceholder public API. The objective is to evaluate how the API behaves under different traffic conditions specifically Load, Stress, and Spike tests to assess its response time, stability, and error tolerance. Unlike a smoke test which verifies basic functionality, these test types push the system to determine its performance limits, scalability, and resilience when subjected to varying user loads. JSONPlaceholder is a free RESTful API used for prototyping and testing, providing endpoints for typical resources such as posts, comments, and users. By applying JMeter-based testing, we can simulate concurrent virtual users making HTTP requests and analyze the system’s behavior under normal and extreme traffic.


🎯 Objectives

The main objectives of this project are as follows:

1. To evaluate the response time and reliability of the JSONPlaceholder API under increasing virtual user load.

2. To determine the breaking point of the API where response degradation or failures begin to occur.

3. To assess the API’s ability to recover from sudden traffic spikes and maintain acceptable performance levels.

4. To collect key performance metrics such as throughput, error rate, and p95 response time for analysis.

5. To establish baseline data for understanding API scalability and readiness for real-world usage.


⚙️ Tool Justification

Apache JMeter was selected as the testing tool because it provides robust support for both HTTP(S) and API-level performance testing. Its graphical interface simplifies test plan design while allowing precise control over virtual user load, ramp-up timing, and request configurations. Compared to developer-centric tools like Grafana k6, JMeter offers visual monitoring via listeners such as Summary Report, Aggregate Report, and View Results Tree, which are ideal for both academic and enterprise-level analysis. JMeter also generates detailed HTML reports for statistical review.

🧰 Test Environment
Component	Details
Platform	Windows 10
Tool	Apache JMeter v5.6.3
Target API	https://jsonplaceholder.typicode.com

Test Type	Load, Stress, and Spike Tests
Endpoint Tested	/posts
Method	GET
Results Stored	/results/jsonplaceholder_test.jtl


🧪 Test Design
Test Type	Purpose	Users / Duration	Metrics Collected
Load Test	Simulate typical API usage under normal conditions	20 Users / 20s Ramp-up / 3 Loops	Response Time, Throughput, Error %
Stress Test	Identify performance degradation under heavy load	200 Users / 20s Ramp-up / 2 Loops	Failure Rate, Max Latency
Spike Test	Evaluate API stability under sudden traffic surge	100 Users / 2s Ramp-up / 1 Loop	Response Time, Error %, Recovery Time


📊 Results and Analysis

🟢 1. Load Test Results

Virtual Users: 20	(Normal user load)
Average Response Time: 180 ms	(Excellent responsiveness)
p95 Response Time: 240 ms	(Below 800 ms threshold)
Error Rate: 0%	(No failed requests)
Throughput: 50 req/sec	(Stable)
Verdict: Passed	(API performs efficiently under normal load)

🧠 Analysis:
The JSONPlaceholder API handled 20 concurrent users smoothly with no failures and maintained consistent response times. The system is stable under expected user traffic.

<img width="1512" height="276" alt="loadtestinfo" src="https://github.com/user-attachments/assets/98daa11a-7659-4c98-a0d3-22466772a06f" />

<img width="753" height="267" alt="loadperformance" src="https://github.com/user-attachments/assets/e05a18ca-944a-4b2a-b408-b121f4f828a0" />

<img width="755" height="347" alt="requestsummary" src="https://github.com/user-attachments/assets/64873aa9-5b96-40bd-baa5-0456b3d324aa" />

<img width="1548" height="311" alt="statistic" src="https://github.com/user-attachments/assets/f0a9394c-7c14-4fdd-a46e-dc3905537266" />


🔴 2. Stress Test Results

Virtual Users: 200	(Heavy concurrent load)
Average Response Time: 950 ms	(Noticeable increase in latency)
p95 Response Time: 1250 ms	(Exceeded 800 ms threshold)
Error Rate: 0% (No timeouts observed)
Throughput: 60 req/sec	(Slight drop due to congestion)
Verdict: Passed (System approaching performance limit)

🧠 Analysis:
Under heavy traffic, it responses effectively While throughput remained relatively high, the API began to show signs of strain, indicating limited scalability at this level.

<img width="1497" height="247" alt="stresstestinfo" src="https://github.com/user-attachments/assets/f857da42-8d64-4ca9-a88c-ea30138de353" />

<img width="751" height="252" alt="stresstestperformance" src="https://github.com/user-attachments/assets/b6029808-1e1f-4408-994a-c424e28d1662" />

<img width="761" height="360" alt="stressrequest" src="https://github.com/user-attachments/assets/24050571-72d8-4290-8057-b2a58999c5b8" />

<img width="1541" height="306" alt="stressteststatistic" src="https://github.com/user-attachments/assets/f778efec-217f-44dd-955f-afeef17f3fd6" />


⚡ 3. Spike Test Results

Virtual Users: 100	(Sudden surge within 2 seconds)
Average Response Time: 720 ms	(Increased temporarily)
p95 Response Time: 790 ms	(Stayed within 800 ms target)
Error Rate: 0%	(no transient errors)
Throughput: 58 req/sec	(Stable)
Verdict: Passed	(Handled sudden spike effectively)

🧠 Analysis:
The system successfully managed a sharp increase in user load. Despite a temporary latency spike, performance stabilized quickly, showing good recovery behavior.

<img width="1511" height="280" alt="spiketestinfo" src="https://github.com/user-attachments/assets/fa820439-8cda-47d5-9569-4ed4b2ce2ee6" />

<img width="752" height="266" alt="spiketestperformance" src="https://github.com/user-attachments/assets/fb636c08-39fd-4fa5-864b-cdb48fb0c1d8" />

<img width="755" height="347" alt="spiketestrequest" src="https://github.com/user-attachments/assets/61a3b3b6-a1dd-426f-9af6-2407c9e567f0" />

<img width="1542" height="310" alt="spiketeststatistic" src="https://github.com/user-attachments/assets/0948b785-f702-491d-8ab9-0aaf398f17e4" />


💡 Hypothesis

It was hypothesized that:

1. The JSONPlaceholder API would maintain stable responses up to 20 concurrent users (Load Test).

2. Performance would degrade beyond 100 users (Stress Test).

3. The API would recover successfully after a sudden spike (Spike Test).


🔧 Recommendations for Improvement

1. Implement Caching: Introduce response caching for frequently accessed endpoints to reduce processing time.

2. Optimize Network Layer: Use Content Delivery Networks (CDNs) or API Gateways to balance global traffic.

3. Rate Limiting: Enforce rate limits to protect the service under extreme request bursts.

4. Horizontal Scaling: Distribute API requests across multiple instances or containers for high availability.

5. Monitor Over Time: Regularly perform JMeter or k6 tests after updates to maintain stable performance metrics.


🎯 Conclusion

Overall, the API is stable under normal and moderate loads, resilient against traffic spikes, and only begins to degrade under extreme concurrent user conditions. This confirms that JSONPlaceholder can serve as a reliable testing platform and that JMeter effectively simulates real-world traffic conditions for performance benchmarking.

Video Simulation:
https://youtu.be/CXaZtI_fI2g

