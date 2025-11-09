<h1 align="center"># WEB PERFORMANCE TESTING</h1>
<img width="1024" height="293" alt="LOAD-TESTING-ON-JSONPLACEHOLD-03-11-2025" src="https://github.com/user-attachments/assets/d112f20d-b2bf-4df2-9774-605e2d33270c" />
<br>

##🧑‍🎓 Student Information 

| Field       | Details             | 
|-------------|---------------------|
| 👤 **NAME**    | MUHAMMAD ZAKWAN 'IRFAN BIN MOHD ZAMRY   | 
| 🆔 **STUDENT ID** | 2025127509    |
| 📘 **TITLE**     | LOAD TESTING ON JSONPLACEHOLDER WEB |

##

# 💡 INTRODUCTION TO WEB PERFORMANCE TESTING

| 🧪 **Load Testing** | 🔗 **Do You Know JSONPlaceholder?** |
|----------------------|--------------------------------------|
| Load testing happens when you simulate many users using your website or app at the same time. It’s like giving your system a workout to see how strong and fast it is under pressure. | JSONPlaceholder is a free online REST API service that provides fake data for testing and prototyping web applications. It's widely used by developers to simulate backend responses without needing a real server perfect for learning, demos, and mockups. |
<br>

**What we want to know from this test ?**  💡
<br>
- We want to know if the system stays fast, stable, and error-free when many users use it at once.
<br>

# 🧰 TOOL SELECTION
- Apache JMeter <br>
<img width="349" height="104" alt="image" src="https://github.com/user-attachments/assets/564c25c4-bad6-4d3f-b6a4-ce40440f31eb" />
 <br>
I'm using this powerful open-source tool to perform load testing by simulating continuous heavy load in user traffic. JMeter helping me observe how the system responds under pressure. <br>
<br>

- UBuntu Linux <br>
<img width="449" height="334" alt="image" src="https://github.com/user-attachments/assets/7e6baef3-52e8-49fb-8331-cc9f0ef4ebe9" />

 <br>
I'm using Ubuntu Linux as the operating system to host and execute my performance tests. Its stability, security, and lightweight footprint make it ideal for server-side testing environments. <br>
<br>

# 💻 TEST ENVIRONMENT SETUP & METHODOLOGY 

**Setup:**
| Component | Description |
|------------|-------------|
| **Platform** | Ubuntu 24.04.2 LTS (Linux-based) |
| **Hardware model** | intel Core i5 |
| **Tool** | JMeter |
| **Target Website** | [JSONPlaceholder](https://jsonplaceholder.typicode.com/) |

**Configuration:**
| Parameter                     | Value                                      |
|------------------------------|--------------------------------------------|
| Number of Users              | 200 Users (normal), 1000 Users (Heavy load)              |
| Loop Count                   | 5 Times (Each user sends 5 requests)     |
| Ramp-Up Period               | 60 Second (All users use the system in one period)       |
 

# 🔐 KEY FEATURES OF JMETER (Related to load testing)

- 🚀 **Custom Thread Groups** (set amount of users)  
  can simulate heavy traffic loads using custom thread groups.

- ⏱️ **Sync Timer** (use ramp-up)  
  allow all virtual users hit the server in period of times — perfect for load testing.


- 📊 **Real-Time Performance Metrics** (results analyzation)  
  have built-in listeners to monitor response time, error rate, and system behavior during the load.

<br>
<br>

# 📂 RAW DATA PRESENTATION
|              Normal load of users                  |          Heavy load of users          |
|--------------------------------|-----------------------------|
|<img width="414" height="254" alt="image" src="https://github.com/user-attachments/assets/0f99e64d-46cb-4961-8ad6-e16831880073" /> | <img width="414" height="254" alt="image" src="https://github.com/user-attachments/assets/04e10d06-5eff-405f-bab3-3c3e3e2f9646" />|

| HTTP request   |  **Constant timer**   |
|-------------------------------|---------------------------------|
| <img width="414" height="254" alt="image" src="https://github.com/user-attachments/assets/fcf22ab5-d921-4a88-88ca-8796ba9174ce" />| <img width="414" height="240" alt="image" src="https://github.com/user-attachments/assets/db24f311-cecd-42f5-b25f-8d45f6787985" />|

| **Aggregate graph** <br> (average response time)   |  Response time graph <br> (response time changes over time)   |
|-------------------------------|---------------------------------|
| Normal: (2,772 Milliseconds)<br> <img width="412" height="239" alt="image" src="https://github.com/user-attachments/assets/fe33ea69-5e09-4ef5-ac70-702dbc06614e" /> <br> Heavy load: (5,138 Milliseconds) <br> <img width="412" height="239" alt="image" src="https://github.com/user-attachments/assets/84c8a01a-7baa-4286-991e-27f807fe927f" />| Normal: (system got faster and more stable over time) <br> <img width="413" height="268" alt="image" src="https://github.com/user-attachments/assets/b60451dd-1d5b-463c-a85a-3ab2efde7e81" /> <br> Heavy load: (System unstable)<br> <img width="413" height="268" alt="image" src="https://github.com/user-attachments/assets/e690a681-c5e9-4760-82fc-b0d52b981cb1" /> |

| Summary report (from JMeter)   |  **Status results in table**   |
|-------------------------------|---------------------------------|
| <img width="412" height="250" alt="image" src="https://github.com/user-attachments/assets/9ca06f9f-48f4-4dde-a782-60fbd7b4e95c" />| <img width="402" height="250" alt="image" src="https://github.com/user-attachments/assets/40a0aa11-6538-406a-9330-b460f3e59890" /> <br>  <br> |
<br>

# 📷 DEMONSTRATION VIDEO 

https://youtu.be/w56v21HV2TE
<BR>
<br>

# 📊INTERPRETATION OF RESULT & IDENTIFIED BOTTLENECKS

**Performance comparison: (Normal vs Heavy load)**
| Metric/<br>Graph type | 🟢 Normal load  | 🔴 Heavy load |
|-------------------------------|---------------------------------|-----------|
| Aggregate<br> response time | 🐇 2,772 ms<br>(fast & efficient) | 🐢5,138 ms<br>(slower)|
| Response<br>time trend | 📉 Steady decrease over time <br>(system stabilized) | 📈 Sharp spike <br>(Unstable) |
| System behavior | 🧊 Cold start,<br> then smooth recovery | 🔥 Overload event,<br> temporary bottleneck |

<img width="430" height="201" alt="image" src="https://github.com/user-attachments/assets/43c9cd5c-e81c-436f-a00f-55377de24fdc" />


**Bottlenecks:**
| Bottlenecks type | Evidence from graph  | Interpretation |
|-------------------------------|---------------------------------|--------------|
|🔺 Cold start | High initial response<br> times that gradually improve | Backend warming up,<br> caching delay |
|🔸 Unexpected bottleneck | Response time suddent increase to<br> 24,000 ms, then fast recover | Temporary overload |
|◾ Average latency | Aggregate graph of response time shows<br> a big different between 2,772 ms<br> for normal load and 5,138 ms for heavy load| Early delays significantly<br> impacted overall performance |

# 🆕RECOMMENDATION FOR IMPROVEMENT
🔧 Server & Backend
- Enable warm-up routines to reduce cold start delays
- Optimize database queries and add indexing for faster data access
- Use caching for frequently accessed data to speed up responses


# 🗒️ CONCLUSION
The [JSONPlaceholder](https://jsonplaceholder.typicode.com/) performs efficiently under normal load but shows signs of latency and instability under heavy load, highlighting the need for backend optimization and better load management.

<h1 align="right">By: Muhammad Zakwan (CDCS2554C)</h1>
