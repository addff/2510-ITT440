# COMPREHENSIVE WEB APP PERFORMANCE TESTING & ANALYSIS
---

### ITT440: GROUP ASSIGNMENT 
### NAME: MUHAMMAD HANIF IRFAN BIN ZAKUAN 
### CLASS: M3CS2554A
---

# :boom: Stress Testing on Local Flask Web App using Siege
---

## :wave: Introduction
This performance testing was performed using Siege which is an open source regression test and benchmarking utility tool that available in Kali Linux to test high level of concurrent on a local flask web app that is simulation of Liquipedia.net pages. The purpose of this testing is to obsereve system behaviour when many user load access in one time and their performance. The test was conducted three test with different amount of virtual user in 60 seconds which were 10 users,50 users and 100 users. The target data to collect was transactions data, the availabilty, average response time in seconds and failed request.

---
## Objective
-  To measure the average response time and the system's performance under various amount of concurrent user traffic using Siege.
-  To determine the maximum handling capacity of the web server functionality and efficiency
-  To show and ensure how stress can be performed safely and ethically by using a local flask web app instead of real website.

---
## Hypothesis
“If users are active at the same time increase, the average response time and error rate are expected to increase, while the overall throughput will drop.
This hypothesis suggests that the simulated Flask server will show clear signs of performance slowdown under heavy user load that similar to what happens in real-world web systems.”



---


## Tool and Target Justification

## Performance Testing Tool (Siege)

The experiment used Siege because this open-source tool can easily handle hundrend users at once and enable to give details result which can checking up stability of server under high pressure request.

---


![horse](https://github.com/user-attachments/assets/63269208-d581-439c-9e17-35f85d606fbd)

## Target Web Application (Liquipedia - Local Flask App)

The experiment used Liquipedia as reference because Liquipedia is a well-known esports wiki that feels familiar and realistic to use in simulations. It includes pages from many games like Dota 2 and Valorant, making it perfect for testing different parts or routes of a web app. The experiment don’t use the real Liquipedia site to ensure the testing ethical so a local flask app copy is created instead to make sure everything is safe and legal.

---
## Test Environment Setup
| Component | Description |
|---------|-----------|
| Environment | Kali Linux 2024.2 (64 bit) |
| Testing Framework | Siege v4.1.6 |
| Programming Language | Python 3.11.2|
| Target Website | Liquipedia — https://www.liquipedia.net (local flask simulating liquipedia Pages) |
| Test Selection | Stress Test | 
| Test Duration | 60 Seconds per round|
| Configuration File | `app.py` |
| Monitoring Tools | `htop`(CPU & Memory Usage), `matplotlib` (Graph plotting) | 
| Network | Localhost (127.0.0.1) |

---
## Load Pattern Design
| Level | Concurrency | Duration | Expected behavior |
|---------|-----------|---------|-----------|
| Low | 10 users| 6o second  | Stable response, no errors |
| Medium | 50 users| 60 second | Slight increase in latency |
| High | 200 users| 60 second | Noticeable slowdown, possible errors |

---
## Testing Procedure
| Step | Description |
|---------|-----------|
| Step 1: Launch the Flask Server  | Local web application was running using the command python3 app.py. This is the simulated Liquipedia.net server locally on `http://127.0.0.1:5000`|
| Step 2: Verify web routes | Open the browser and visit the following URLs: `http://127.0.0.1:5000/`, `http://127.0.0.1:5000/dota2, `http://127.0.0.1:5000/valorant to verify each page run smoothly before testing|
| Step 3: Prepare URL File | Create a text file named urls.txt containing the list of target URLs for the stress test using three url earlier.|
| Step 4: Run Initial Low-Load Test | Execute siege -c 10 -t 1M http://localhost:5000/ to perform a one-minute test with 10 concurrent users. This provides a testing for normal performance. |
| Step 5: Run Medium-Load Test | Increase the concurrency to 50 users using the command siege -c 50 -t 1M -f url.txt. Observe how the system handles moderate simultaneous requests. |
| Step 6: Run High-Load Test | Perform a high concurrency test by increasing to 100 users using siege -c 100 -t 1M -f url.txt. Monitor CPU, memory, and latency impact using htop during the test. |
| Step 7: Collect and Save Logs| Siege automatically saves results to the log file located in /var/log/siege.log. Copy the data for further analysis and record transaction rate, throughput, and average response time. |
| Step 8: Analyze Test Results | Use Pandas in Python to read and summarize data, then Matplotlib to visualize response time trends against concurrency levels. |
| Step 9: Interpret the Findings | Compare the results from low, medium, and high concurrency tests to determine how server performance changes with increasing user load |
| Step 10: Summarize and Document | Compile all observations, metrics, graphs, and conclusions into the final report or GitHub README for submission and presentation |




---
## Raw Data

<img width="666" height="506" alt="image" src="https://github.com/user-attachments/assets/f4264c4d-3658-4cd8-9348-7c64d1f9b2c5" />

<img width="656" height="453" alt="image" src="https://github.com/user-attachments/assets/5233ab7a-a96f-4746-9dd5-8b7e70213605" />

<img width="700" height="361" alt="image" src="https://github.com/user-attachments/assets/da999181-b9cb-4fce-b6c4-35d540b9988a" />\

<img width="624" height="447" alt="image" src="https://github.com/user-attachments/assets/2c4c2acf-91ee-4048-af53-1ed477f5c36e" />

<img width="624" height="442" alt="image" src="https://github.com/user-attachments/assets/a7417df6-1eca-431a-8a59-e5169489db5c" />

---
## Result and Analysis

| Concurrency | Average Response Time (s) | Transaction Rate(trans/sec) |
|---------|-----------|-----------|
| 10 | 0.27 |  36.71 |
| 50 | 0.31 |  149.78 |
| 100 | 0.32 |  296.15 |


The stress test results show that the local Flask server simulated liquipedia.net handled all requests successfully because all test has 100% success rate across all concurrency levels. Firstly, 10 concurrent users has 
the average response time was 0.27 seconds with a transaction rate of 36.71 transactions per second. This show that the system was stable under light load. Next, concurrency increased to 50 users, the average response 
time slightly to 0.31 seconds and the transaction rate increased to 149.78 trans/sec. So, the server efficiently handled more requests without a significant slowdown. At 100 concurrent users, the average response time 
remained relatively stable at 0.32 seconds with the transaction rate increased further to 296.15 trans/sec. This indicated that the server can handle with higher load and maintained consistent performance. In conclusion, 
the results revealed that as concurrency increases, transaction throughput rises substantially while average response time remains nearly constant, confirming that the Flask server can efficiently handle multiple 
concurrent users in this simulated environment.



---
## Recommendations
- Expand Test Scenarios by adding more tests that cover different parts of the web app by database requests to helps get a clearer picture of how the whole system performs under stress.
- Optimize Application Performance by implementing performance optimization strategies such as  handling requests asynchronously to ensure system responsiveness and scalability efficiently.

---
## Conclusion

The stress testing experiment conducted with Siege clearly showed how server performance varies at different levels of user concurrency. The findings show that the local Flask server handled increasing concurrency more
efficiently . From hypothesis, the average response time remained nearly constant (0.27 s to 0.32 s) even as concurrent users increased from 10 to 100. Similarly, the success rate stayed at 100% so there no requests 
failed under higher load. Moreover, the transaction rate (throughput) increased substantially with higher concurrency which from 36.71 trans/sec at 10 users to 296.15 trans/sec at 100 users. These results indicate that 
the server scales well under load by maintaining both responsiveness and reliability. Therefore, the hypothesis is not accepted by predicted slower responses and reduced throughput but the actual data demonstrates that 
this local Flask setup handles concurrent requests efficiently, achieving higher throughput without significant performance degradation.

---


## Youtube Video Demostration
