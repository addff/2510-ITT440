# STRESS TESTING ON DOCKER USING LOCUST 🦗

PREPARED BY: TENGKU SYAURIN ALESSA BINTI TENGKU SAHHIM AFIFI

STUDENT ID: 2025367681

GROUP: CDCS2554C

PREPARED FOR: SIR SHAHADAN BIN SAAD

- **Tools :** Locust
- **Testing Type :** Stress Testing
- **Target Web Application:** Docker (Nginx) Web Server
    <p align="center">
    <img width="298" height="100" alt="image" src="https://github.com/user-attachments/assets/f39b9542-7f9f-432f-92fd-0b25e7cf79ed" />

    <p align="center">
    <img width="246" height="65" alt="image" src="https://github.com/user-attachments/assets/a283fd9e-4320-438f-b12c-0d5591caadbd" />


---
## Introduction
In modern software development, ensuring that a web application performs reliably under high load conditions is critical. Applications are often deployed on cloud or containerized environments like Docker, where scalability and efficiency are top priorities. However, even a well-built system can fail when subjected to excessive user requests or resource constraints.

This project focuses on conducting stress testing on a Dockerized web application using Locust, an open-source performance testing framework written in Python. Stress testing is a crucial aspect of performance engineering — it helps determine the breaking point of an application by gradually increasing the load beyond normal operating conditions.

The primary goal of this testing is to:

-Evaluate how the Docker-hosted Nginx server behaves under increasing traffic.

-Identify thresholds where latency increases or failures begin to appear.

-Understand resource limitations, such as CPU utilization and memory constraints.

By performing stress testing with Locust, this project provides insights into how scalable a containerized web server can be and where optimizations might be necessary before deployment in production environments.

## Tool Selection Justification
Several performance testing tools exist in the current DevOps ecosystem — including Apache JMeter, K6, Artillery, and LoadRunner. Each offers a different approach to load generation and result reporting.

After a comparative review, Locust was selected as the testing tool for this project due to its flexibility, simplicity, and excellent integration with containerized infrastructures.

| **Feature** | **Description** |
|--------------|-----------------|
| 🐍 **Python-based and highly scriptable** | Locust allows users to define realistic user behaviors using simple Python code, rather than relying on complex XML or GUI-based configurations like JMeter. This makes it ideal for flexible, programmatic test scenarios. |
| 🌐 **Web-based interface for live monitoring** | Locust provides a clean and interactive web dashboard where users can start/stop tests, adjust concurrency, and view performance metrics in real time — making it user friendly. |
| ⚙️ **Lightweight and scalable** | It can simulate thousands of users from a single machine and can also be distributed across multiple systems for large-scale testing. |
| 🔄 **Integration with modern CI/CD pipelines** | Locust integrates easily with Docker, GitHub Actions, and Jenkins, making it suitable for automated testing environments. |
| 🐳 **Ease of use for containerized environments** | Since both the target and testing tool can run as Docker containers, Locust is perfectly aligned with this project’s objective. |

In summary, Locust’s Python foundation, real-time observability, and Docker compatibility make it a powerful and modern choice for conducting stress tests in both academic and professional environments.

## 🔧 Installations

- **Install Docker Desktop**
 📘 [Install Docker Desktop on Windows](https://docs.docker.com/desktop/setup/install/windows-install/)
  <br>Install Docker Desktop on Windows from the official website. After installation, ensure it is running.</br>
  In Powershell or VS Code Terminal, run:
  ```bash
  docker --version
  docker ps
  ```

- **Install Python**
  📘 [Install Python](https://www.python.org/downloads/)
  <br>Download and install the latest version of Python. Verify using:</br>
  ```bash
  python --version
  pip --version
  ```

- **Install Locust**
  Install Locust via pip:
  ```bash
  pip install locust
  ```
  Verify Installation:
  ```bash
  locust --version
  ```
  if failed:
   ```bash
  python -m locust --version
  ```
   
- **Install Visual Studio Code (VS Code)**
  <br>This is for editing the Locust test script and run commands in an integrated terminal.</br>
  📘 [Install Visual Studio Code (VS Code)](https://code.visualstudio.com/)
 <br>VS Code will be used to edit Locust scripts and run commands.
Recommended extensions:
- 🐍 Python
- 🐳 Docker
</br>

## Setup Procedure

**1. Launch Docker container**
<br>Create an Nginx container (as the web application target)</br>
It is up to you to use any name for the Docker container.
  ```bash
  docker run -d -p 8088:80 --name stress-target nginx
  ```

 This command deploys a running Nginx web server accessible via http://localhost:8088.
 <br></br>
 **2. Create Locust test script**
 <br></br>
 This will be the file you run on your terminal or PowerShell, and make sure that this script is in the *locust folder*.
 ```javascript
  from locust import HttpUser, task, between

class StressUser(HttpUser):
    wait_time = between(1, 3)

    @task
    def load_homepage(self):
        self.client.get("/")
  ```
This simple script simulates multiple users sending HTTP GET requests to the homepage endpoint.
 **3. Run Locust**
 ```bash
  locust -f (filename).py --host http://localhost:8088
  ```
Locust will provide a web interface, typically accessible at http://localhost:8089, where you can configure:

Number of total users to simulate

Hatch rate (spawn rate)

Test duration

 ## Methodology

| Component | Specification |
|:----------:|:-------------:|
| Testing Target | Docker 28.5.1 |
| Container Engine | Docker Desktop |
| Target App | Nginx (`latest`) |
| Testing Tool | Locust 2.42 |
| Python | 3.13.9 |

The methodology followed these structured steps:

Environment Setup:
Docker was launched to host the Nginx container as the web target. Locust was installed on the local host to act as the load generator.

Script Creation:
The Locust script defined a single user behavior — continuously sending GET requests to /.

Execution of Tests:
Several test rounds were executed, beginning from small user loads (100–500 users) up to higher levels (4000 users).

Data Collection:
Locust automatically recorded response times, requests per second (RPS), and failure rates. The results were observed through the Locust web UI and confirmed using the VS Code terminal logs.

# Raw Data Presentation

- **500 Users**

<img width="1841" height="1125" alt="number_of_users_1762229559 305" src="https://github.com/user-attachments/assets/3c0d6ef3-b552-468f-9662-ab73e50c25f9" />

The system maintained stability.

All requests were successful.

Average response times were consistent.

- **4000 Users**

<img width="1841" height="1125" alt="total_requests_per_second_1762278295 045" src="https://github.com/user-attachments/assets/a41461ff-a37d-42ac-bf8f-6f2e2e2af5d7" />

<br></br>

<img width="1521" height="126" alt="image" src="https://github.com/user-attachments/assets/ff184131-2ce9-4052-bfde-54302f5641ce" />

Significant increase in response time.

High CPU utilization observed on the Docker host.

Several requests failed due to connection resets (10054, 10053).

## Interpretation on the Results

At 500 concurrent users, the Docker container handled requests efficiently. The Nginx service processed all incoming requests successfully without delay or resource exhaustion. This suggests that both the Docker environment and the Nginx server are well-optimized for moderate traffic.

However, as the user load increased to 4000 concurrent users, the system reached its resource threshold. The container was unable to handle the surge in simultaneous connections, leading to error messages like:

ConnectionResetError(10054) — indicating the server forcibly closed the connection.

ConnectionAbortedError(10053) — showing that the client or host machine aborted the waiting connection due to timeout or overload.

These failures occur because Docker assigns limited CPU and memory resources to each container by default. When the incoming requests exceed the Nginx worker thread capacity, it starts rejecting connections.

CPU and Memory Bottleneck

Performance monitoring showed high CPU usage during the 4000-user test. This behavior reflects how containerized environments respond when computational resources are maxed out — throughput decreases, and latency increases dramatically.

Scalability Limit

The results clearly demonstrate that while a single Docker container is efficient for small to medium workloads, it struggles with thousands of concurrent requests. For large-scale traffic handling, horizontal scaling (running multiple containers behind a load balancer) is recommended.

<img width="1810" height="445" alt="image" src="https://github.com/user-attachments/assets/6a0ce63c-9a32-4b76-883f-904ed5cbd8f8" />

<img width="1629" height="131" alt="image" src="https://github.com/user-attachments/assets/c50dc9b1-cc6d-4b53-980b-1be6a6e75d9f" />


## Hypothesis
From the observations:

Nginx within a single container can handle up to 500–1000 concurrent users reliably.

Beyond that, the performance starts to degrade, with dropped connections and increased latency.

The failure rate increases sharply after CPU saturation, confirming that the system reached its maximum operational threshold.

## Conclusion & Recommendations
This stress testing experiment successfully demonstrated the process of using Locust to evaluate the performance of a Dockerized Nginx web server.

The findings reveal that:

- Docker provides an isolated, reproducible environment for testing and deployment.

- Locust is a highly effective tool for generating controlled load and analyzing real-time performance data.

- Resource constraints in Docker containers directly affect system throughput and response stability.

Recommendations for Improvement:

- Increase Docker Resource Allocation:
Allocate more CPU cores and RAM to Docker Desktop via its settings panel.

- Implement Load Balancing:
Deploy multiple Nginx containers behind a reverse proxy or Kubernetes service to distribute traffic evenly.

- Enable Auto-scaling:
In production environments, configure auto-scaling rules so that more containers spawn automatically when CPU usage exceeds a threshold.

- Use Monitoring Tools:
Integrate Prometheus and Grafana to visualize resource usage and performance over time.

- Future Work:
Extend testing scenarios to include POST requests, user authentication, or database interaction to simulate real-world user activity.


 ## 🎥 Demostration Video
 https://youtu.be/gKn5ygyEpC0 
