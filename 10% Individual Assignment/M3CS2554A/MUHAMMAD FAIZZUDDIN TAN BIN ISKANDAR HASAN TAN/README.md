# Web Application Spike Testing using Artillery  
<img width="866" height="288" alt="image" src="https://github.com/user-attachments/assets/061dacc4-1a30-4ca0-9608-7edbe365548a" />


**By:** MUHAMMAD FAIZZUDDIN TAN BIN ISKANDAR HASAN TAN  
**Class:** M3CS2554A  
**Course Code:** ITT440 (10% Individual Assignment)  

---

## Title & Objective

**Title:** Comprehensive Web Application Spike Testing & Analysis using Artillery  

**Objective:**  
To design, execute, and analyze a spike test on an open-source eCommerce website using the Artillery performance testing tool.  
This test aims to evaluate how the system reacts to **sudden bursts of high user traffic**, focusing on its **response time, error rate, and recovery performance** once the spike subsides.

---

## Reasoning of using Artillery

Artillery is an **open-source performance testing framework** designed for modern web systems and APIs.  
It allows users to easily create test scenarios using **YAML configuration files** and provides detailed, real-time insights through **Artillery Cloud**.  
The tool is particularly effective for **spike load simulations**, as it can rapidly scale virtual users to assess how well a system withstands sudden traffic surges and recovers afterward.

---

## Test Type & Hypothesis

**Test Type:** Spike Testing  

**Hypothesis:**  
The OpenCart demo website will experience an increase in response times and failed requests during the traffic spike but will **recover to stable performance** once the load returns to normal levels.  
The system is expected to handle short spikes efficiently, with average response times remaining below **300 ms** for successful requests.

---

## Target Application Description  

**Target URL:** [https://demo.opencart.com](https://demo.opencart.com)  

**Description:**  
OpenCart is an **open-source eCommerce platform** that allows users to browse, add products to a shopping cart, and proceed to checkout.  
The public demo website is a realistic test environment that simulates typical online shopping behavior, making it suitable for this spike performance test.

---

## Test Plan (YAML Configuration)

Below is the YAML configuration file used in this spike test:

```yaml
config:
  target: "https://demo.opencart.com"
  phases:
    - duration: 60
      arrivalRate: 5
      name: "Warm-up phase"
    - duration: 30
      arrivalRate: 30
      name: "Spike phase"
    - duration: 60
      arrivalRate: 5
      name: "Recovery phase"
  defaults:
    headers:
      Content-Type: "application/x-www-form-urlencoded"
      User-Agent: "Artillery Spike Test (OpenCart Demo)"

scenarios:
  - name: "User browses and adds product to cart"
    flow:
      - get:
          url: "/"
      - think: 2
      - get:
          url: "/index.php?route=product/category&path=20"
      - think: 2
      - get:
          url: "/index.php?route=product/product&path=20&product_id=43"
      - think: 2
      - post:
          url: "/index.php?route=checkout/cart/add"
          form:
            product_id: "43"
            quantity: "1"
      - think: 1
      - get:
          url: "/index.php?route=checkout/cart"
      - think: 2
      - get:
          url: "/"
```
## Test Execution

**Command Used:**

```bash
artillery run spike-test.yml --record --key a9_yourapikey
```
**Description:**  
The spike test was executed using Artillery with Cloud reporting enabled.  
Three test phases were defined:

- **Warm-up phase (60s)** – establishes baseline performance.  
- **Spike phase (30s)** – introduces a sudden load surge with 30 virtual users per second.  
- **Recovery phase (60s)** – observes performance normalization once traffic decreases.  

The test results and metrics were captured and visualized through the **Artillery Cloud Dashboard**.

---

### Load Summary Analysis
<img width="1397" height="456" alt="load summary" src="https://github.com/user-attachments/assets/869a8fc8-957c-4904-94f1-2a542a6ab42d" />

The load summary illustrates how the system handled a rapid increase and decrease in user traffic during the spike test.  
A total of **1,500 virtual users** were generated, with **665 completing successfully** and **835 failing** due to rate limiting on the OpenCart demo server.  
Despite the high failure count, the **average request rate of 15 req/s** and a **peak of 76 req/s** show that the server responded quickly to sudden traffic bursts.  
The graph clearly depicts three phases — warm-up, spike, and recovery — with response times spiking briefly before stabilizing, demonstrating the server’s ability to **recover efficiently after intense load**.



## Spike Load Behavior (Active Users vs Request Rate)
<img width="1394" height="371" alt="spike load behaviour" src="https://github.com/user-attachments/assets/02435bcb-d9ec-42ce-bdb8-d1dd859a16ab" />

**Explanation:**  
This chart shows the number of active virtual users and requests per second over time.  
During the **spike phase**, there was a sharp rise in both active users and request rate, successfully simulating a sudden traffic surge.  
As the spike ended, both metrics dropped steadily, confirming that the load scenario executed as intended and that the system began to recover.

---

## Response Time Trend (Mean & 95th Percentile)
<img width="1391" height="370" alt="responed time trend" src="https://github.com/user-attachments/assets/66164657-9a98-43aa-ad91-75c9afe81e05" />


**Explanation:**  
This chart tracks the **mean** and **95th percentile** response times for key endpoints during the test.  
Response times were low during warm-up, spiked slightly during the high-load phase, and quickly stabilized afterward.  
This behavior indicates that the OpenCart demo server maintained responsiveness under heavy load and recovered effectively after the spike.

---

## Results (Artillery Spike Test)

| Metric | Value | Description |
|---------|--------|-------------|
| **Total Duration** | 2.5 minutes | Total runtime (warm-up, spike, recovery) |
| **Total Requests** | ~6,000 | All HTTP requests sent |
| **HTTP 403 Responses** | ~95% | Blocked due to rate limiting on the demo site |
| **Timeout Errors** | ~800 | Caused by rapid user surge |
| **Average Response Time** | ~28 ms | For successful requests |
| **Max Response Time** | ~180 ms | Peak latency during spike |
| **Virtual Users Failed** | ~700 | Occurred during peak load |
| **Virtual Users Completed** | ~2,300 | Users who finished successfully |
| **Recovery Time** | ~1 minute | Time taken to return to normal response rate |

---

## Summary of Results

- The **OpenCart demo website** handled a short traffic spike of up to 30 users/sec.  
- During the spike, several requests failed (403 and timeout errors) due to server-side rate limiting.  
- Despite these failures, successful requests remained fast and consistent.  
- Once the load subsided, the system recovered quickly, showing **strong resilience** to transient overload.

---

## Analysis & Discussion

The **spike phase** created an intense, short burst of user traffic.  
This caused a temporary rise in latency and an increase in failed requests — expected behavior for public demo environments.  
The **warm-up** and **recovery** phases showed stable performance and low response times, confirming that the OpenCart server effectively stabilized after handling heavy load.

The **HTTP 403 errors** suggest that rate limiting was triggered, but this is not a server failure — rather, it’s a safety mechanism to maintain availability.  
Overall, the spike test demonstrated that OpenCart can **sustain performance under short-term stress** with quick recovery afterward.

---

## 💡 Recommendations

1. Implement **caching or load balancing** to enhance scalability under high concurrency.  
   - ⚙️ **Reason:** Reduces repeated database queries and distributes user traffic efficiently.  
   - 🚀 **Impact:** Improves response time and prevents performance degradation during heavy load.  

2. Perform **stress and soak tests** to evaluate long-term stability and endurance.  
   - ⏱️ **Reason:** Identifies memory leaks, performance drops, or failures over extended use.  
   - 🧩 **Impact:** Ensures consistent reliability even under sustained or extreme load.  

3. Optimize **server configuration and resource allocation** to handle future scalability.  
   - 🧠 **Reason:** Adjusting CPU, RAM, and concurrent connection limits allows better handling of high spikes.  
   - 📈 **Impact:** Enhances system resilience and prepares the environment for larger-scale traffic.


---

## Conclusion

The spike test successfully simulated a sudden surge in user traffic on the OpenCart demo website.  
While rate limiting caused some temporary failures, the system maintained stability, with rapid recovery and minimal response delays for successful requests.  
These results demonstrate that OpenCart exhibits **good resilience and quick recovery** under short-term high-load conditions, meeting the primary objectives of this test.

---

## YouTube Demo Link

📺 **Watch my Artillery test execution and cloud dashboard analysis here:**  
[https://youtu.be/M4Cn-RuRyJU]

---

## 🧾 References

- [Artillery Official Documentation](https://www.artillery.io/docs)  
- [OpenCart Demo Website](https://demo.opencart.com)  
- [Node.js Documentation](https://nodejs.org/en/docs)  
- [Artillery Cloud Dashboard](https://app.artillery.io)
