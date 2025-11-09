### NAME: AHMAD FARIS BIN FAZURI
### STUDENT ID: 2025301475  
### CLASS: M3CS2554C 
### SUBJECT: ITT440

---
### 💻Web Application Performance Testing💻

TITLE: WEBSITE PERFORMANCE TESTING USING SIEGE

### 🧰Tool Selection: Siege

🌐What is Siege tools  

Siege is an open-source tool used for website benchmarking and performance testing. It can simulate multiple users accessing one or more URLs at the same time to measure how well a web server responds under load.

Siege provides useful statistics such as total requests, data transferred, response time, transaction rate, concurrency and success status. It supports both HTTP/1.0 and HTTP/1.1, GET and POST methods, cookies, logging and basic authentication.

Users can easily configure tests using command-line options, such as defining how many virtual users will be simulated and for how long. This makes Siege a practical tool for stress testing and evaluating web server performance.

---

### 🎯TEST ENVIRONMENT SETUP AND METHODOLOGY

TESTED ENVIRONMENT 

💾Ubuntu OS  

Ubuntu is an open-source Linux distribution widely used for general computing. Although it is not specifically designed for cybersecurity, Ubuntu supports a wide range of software tools, making it suitable for various tasks, including website performance testing using the “siege” tool.

🛠GUIDE:

1. Update the Ubuntu system with the appropriate command.
2. Install the siege tool using the package manager.
3. Run the performance test by specifying:

* -t1M to run the test for 1 minute
* -c5 to simulate 5 concurrent users

* The target website URL to be tested.
---

🔍TESTED APPLICATION  

[https://tutorialspoint.com/]

Tutorialspoint.com is a lightweight public educational site that mainly serves static pages. While it lacks dynamic or API-driven content, its consistent responses make it suitable for stressing basic HTTP delivery. Its simple structure allows controlled high-load requests to observe performance degradation, availability drops and response slowdowns under stress.

 ***🔑​Key features included***

* Tests behavior under extreme load
* Finds breaking points and failure limits
* Shows response during resource exhaustion
* Measures recovery after overload
* Detects major performance bottlenecks
* Observes how the system degrades

---

### 🔧Testing Infrastructure Setup  

Test results may differ based on hardware and network conditions. Systems with faster CPUs, more RAM or better storage usually handle requests faster. Likewise, internet speed and stability affect response time and reliability. Users with slower networks may see higher delays or errors, so results can vary between environments.

### ⚙️Test Configuration 

Stress test 

* Objective: Identify the point at which the website’s performance begins to degrade by gradually increasing the number of virtual users beyond normal operating levels.
* Test Duration: 30 seconds
* Concurrent Users: 10, 50 and 100 user
* User Behavior: insert command in Ubuntu terminal "siege -c -10 -t 30s https://tutorialspoint.com/"
(note: the current user value and time can be vary depends of the terminal host)

---
### 🗂TEST RESULTS
* 10 users test
  
  <img width="839" height="496" alt="image_2025-11-10_00-07-14" src="https://github.com/user-attachments/assets/07a746d0-13fa-4cd8-a58f-493ac6017e2a" />

* 50 users test
  
  <img width="958" height="495" alt="image_2025-11-10_00-07-29" src="https://github.com/user-attachments/assets/c6e88643-68ee-4d46-9122-9ffcb86b632b" />


* 100 users test
  
  <img width="985" height="498" alt="image_2025-11-10_00-07-45" src="https://github.com/user-attachments/assets/ae3d34d2-21a9-42ac-b8b9-8bb34f7971eb" />


  
### 📊RAW DATA PRESENTATION

<img width="858" height="597" alt="image_2025-11-10_00-07-59" src="https://github.com/user-attachments/assets/0eed4b0b-c664-4890-9b9a-e53342a12dac" />

  
Figure 1: Transaction Time Comparison  

* X-axis: Concurrent users (10, 50, 100)
* Y-axis: Average transaction time in seconds

<img width="1004" height="732" alt="image_2025-11-10_00-08-51" src="https://github.com/user-attachments/assets/c5c1a830-f630-4be6-ac68-738a24fc5629" />

 
Figure 2: Data transfered overviewed


* X-axis: Concurrent users (10, 50, 100)
* Y-axis: Data transfered in MB

<img width="1070" height="721" alt="image_2025-11-10_00-09-05" src="https://github.com/user-attachments/assets/6cca14b2-deca-4dce-8d3f-8ac485e3bacb" />


Figure 3: Transaction Results Under Stress

* X-axis: Concurrent users (10, 50, 100)
* Y-axis: Number of transactions
* Green bars: Successful transactions
* Red bars: Failed transactions (none in the tests)

---

### 🧩 Result Interpretation

Statistic table of 3 tests executed

| Metric                  | 10 Users        | 50 Users        | 100 Users       | Interpretation                                                                                              |
| ----------------------- | --------------- | --------------- | --------------- | ----------------------------------------------------------------------------------------------------------- |
| Transactions        | ~750            | ~1,400          | ~1,250          | Number of successful requests handled — grows up to 50 users, then slightly drops at 100 due to saturation. |
| Elapsed Time        | ~30s            | ~30s            | ~30s            | All tests ran for about the same duration — ensures fair comparison.                                        |
| Data Transferred    | 27.07 MB        | 58.62 MB        | 55.81 MB        | Increases with load, then dips slightly — throughput limit reached.                                         |
| Response Time       | 0.36 s          | 0.89 s          | 2.38 s          | Average response time grows sharply — latency increases with more users.                                    |
| Transaction Rate    | 25.07 trans/sec | 46.75 trans/sec | 41.78 trans/sec | Throughput peaks around 50 users, then declines.                                                            |
| Throughput (MB/sec) | 0.90 MB/s       | 1.95 MB/s       | 1.86 MB/s       | Bandwidth usage scales well up to 50 users.                                                                 |
| Concurrency         | 9.90            | 49.75           | 99.74           | Matches intended load — test setup consistent.                                                              |
| Availability        | 100%            | 100%            | 100%            | No failed transactions — excellent reliability.                                                             |

---
 

### ✅ Bottlenecks Identified

Server Processing Capacity – CPU usage increases under higher load, slowing request handling.

Memory (RAM) Limitations – Insufficient memory can cause delays or minor failures as concurrency rises.

Database Access / Content Retrieval – Slower queries or high DB load can delay responses.

Network Latency – Traffic congestion or limited bandwidth can slow client-server communication.

---

### 💡 Recommendations

* Check disk and memory usage: Use df -h for disk, free -m for memory
* Network speed test: Use `iperf3`between two machines to see if network bandwidth limits performance.
* Task manager: Check running processes at task manager that make your OS heavier and closed unused task or running activity.
* Upgrade an upgradable hardware at your devices such as hard disk for bigger addational storage and RAM for doing many task simultaneously at the same time
---

### 🧾 Conclusion

The Stress Test indicates that the target website handles normal traffic efficiently, but as the load increases, response times start to slow and occasional errors occur. This supports the hypothesis that the website’s performance declines under heavy demand. While it remains adequate for standard browsing and informational purposes, additional optimization is necessary to maintain reliability in high-traffic scenarios.
