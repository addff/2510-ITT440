# 🔍 Soak Testing of ChatGPT using JMeter
<img width="150" height="174" alt="logo jmeter" src="https://github.com/user-attachments/assets/d7592b5b-5432-40fc-a210-f899c9628e7a" />

#### 🧑‍🎓 STUDENT NAME : NUR EZZATY BINTI HUSIN
#### 📝 ITT440 - INDIVIDUAL ASSIGNMENT
#### 👥 GROUP : M3CS2554A

---
### 🎓 Introduction
Performance testing helps us understand how a website works when many people use it at the same time or for a long period. It checks if the website stays fast, stable, and reliable. For this assignment, I choose ChatGPT as the web application to test. ChatGPT is a popular AI chatbot that lets users talk to it by typing messages. I focused on a type of performance test called a Soak Test. This test checks how well the system performs when it is used continuously for a long time. It helps find problems like slow responses or crashes that might happen after hours of use. To do this test, I used Apache JMeter, a tool commonly used for performance testing. Since we are not allowed to test ChatGPT’s real servers, I created simulated results. These results show what we might expect if we tested a similar system for a long time.

---
### 🧠 Objectives
- To simulate a continuous number of virtual users interacting with the ChatGPT web interface over an extended period.
- To observe the system’s response time, throughput, and error rate.
- To identify potential memory leaks, performance degradation, or slowdowns that may appear after long usage.
- To analyze the results and give recommendations for better performance and stability.

---
### 🧪 Tool Selection
| **Features** |	**Explaination** |
|------------|----------|
| **Free and Open-Source** |	Apache JMeter is free to use and open-source, making it suitable for both academic and professional projects |
| **User-Friendly Interface** |	It allows easy creation of test plans and thread groups without complex setup |
| **Supports Multiple Test Types** |	JMeter can perform load, stress, and soak testing effectively |
| **Detailed Performance Metrics** |	It provides graphs, reports, and logs for detailed performance analysis |
| **Web Application Simulation** |	JMeter can simulate multiple users sending HTTP requests, making it ideal for web-based performance testing |

---
### 🧰 Test Setup and Configuration
| **Component** |	**Description** |
|------------|----------|
| **Tool Used** |	Apache JMeter 5.6 |
| **Operating System** |	Windows 10 |
| **Memory** |	8 GB |
| **Processor**	| Intel Core i5 |
| **Target Application** |	https://chat.openai.com |
| **Test Duration** |	1 hour |
| **Virtual Users** (Threads) |	50 |
| **Ramp-up Period** | 5 minutes |

The test simulates 50 virtual users continuously sending requests to ChatGPT over a period of 1 hour. This setup represents a medium load that stays constant for a long duration to observe if the system can maintain stable performance

---
### 📋 Test Scenario and Procedure

---
### 📈 Simulated Test Results

---
### 🚧 Bottlenecks and Recommendations

---
### ✅ Conclusion

---
### 📚 References

---
### 🎥 YouTube Video Presentation
[]

  
