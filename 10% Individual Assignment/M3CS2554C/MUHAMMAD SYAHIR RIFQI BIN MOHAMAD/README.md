# Web Application Load Analysis on Vercel Infrastructure Using Apache JMeter

**Author:** Muhammad Syahir Rifqi bin Mohamad Nizam

**Class:** M3CS2554C

**Student ID Number:** 2025395389 

## Introduction

In modern web development, ensuring that an application performs reliably under sustained traffic is critical—especially for production environments hosted on cloud platforms like Vercel. This is where **SOAK testing** becomes an essential part of the performance validation toolkit.

### What is a SOAK Test?

A **SOAK test** is a type of performance test that evaluates how a system behaves under a steady load over an extended period of time. Unlike stress or spike tests that focus on peak limits, SOAK tests aim to uncover:

- **Memory leaks**
- **Resource exhaustion**
- **Latency creep**
- **Backend degradation**
- **Cold start behavior**

By simulating real-world usage patterns over hours, SOAK tests help ensure that applications remain stable, responsive, and error-free during prolonged activity.

### Why SOAK Testing Matters

SOAK testing is especially important for:

- **Cloud-hosted apps** with dynamic scaling and edge deployments  
- **Serverless architectures** prone to cold starts and timeout thresholds  
- **User-facing platforms** where performance degradation impacts UX and retention  
- **CI/CD pipelines** that require pre-deployment validation under realistic conditions  

It provides empirical evidence of long-term reliability, helping developers and DevOps teams make informed decisions about scaling, caching, and infrastructure tuning.

### Why Apache JMeter?

**Apache JMeter** is a widely adopted open-source tool for load and performance testing. Its relevance in SOAK testing stems from:

- **High concurrency simulation** using thread groups and ramp-up strategies  
- **Detailed metrics output** including response time percentiles, throughput, and error rates  
- **Support for HTTP/HTTPS protocols**, ideal for testing REST APIs and web apps  
- **Flexible test logic** with samplers, assertions, and listeners for granular control  
- **CLI mode compatibility**, enabling integration into automated pipelines and headless environments  

JMeter’s extensibility and reliability make it a go-to choice for performance engineers and QA teams across industries.

---

## Test Environment Setup & Methodology

**VIDEO DEMO HERE!:**  
*https://youtu.be/OgiiO7Och_I*

- **Target App:** Vercel-hosted boilerplate web application (Next.js default)  
- **Deployment:** Public URL via Vercel global CDN  
- **Client:** JMeter running on local machine (LAN)  
- **Monitoring Tools:** Apache JMeter  

### Test Scenarios

Two test durations were executed against the same Vercel-hosted app:

| Test Duration | Concurrent Users | Total Requests |
|---------------|------------------|----------------|
| 1 hour        | 50 users         | 1,073,633      |
| 2 hours       | 100 users        | 1,034,051      |

---

## Raw Data Comparison

| Metric                  | Experiment 1 | Experiment 2 |
|-------------------------|--------------|--------------|
| Duration                | 1 hour       | 2 hours      |
| Users                   | 50           | 100          |
| Total Requests          | 1,073,633    | 1,034,051    |
| Failed Requests (%)     | 11.12%       | 11.29%       |
| Avg Response Time (ms)  | 132.14       | 127.03       |
| Max Response Time (ms)  | 704.21       | 678.29       |
| APDEX Score             | 0.888        | 0.886        |
| Throughput (req/sec)    | ~298.23      | ~143.06      |

---

## Endpoint-Level APDEX

| Endpoint               | Exp. 1 APDEX | Exp. 2 APDEX |
|------------------------|--------------|--------------|
| Home Page              | 0.998        | 0.993        |
| HTTP Request           | 0.998        | 0.993        |
| Page Returning 404     | 0.998        | 0.992        |
| Page Returning 404-1   | 0.000        | 0.000        |
| Home Page-1 / Req-1    | 1.000        | 1.000        |

---

## Stability & Performance

- Both tests showed **consistent response times** and **high APDEX scores** across functional endpoints.  
- **No server-side 5xx errors** were observed, indicating backend resilience.

---

## Bottlenecks Identified

### 404-1 Endpoint Failures

- 100% failure rate in both tests  
- Skewed overall failure rate and APDEX  
- Likely due to misconfigured or deprecated routes

### DNS Resolution Errors (Exp. 2)

- 1.25% of total requests failed due to `UnknownHostException`  
- Indicates potential DNS throttling or cold start latency under higher concurrency

### Connection Timeouts

- Present in both tests, slightly reduced in Exp. 2  
- May stem from Vercel cold starts or network congestion

---

## Recommendations

### Fixes

- Remove or repair `Page Returning 404-1` to prevent skewed metrics  
- Enable DNS caching in JMeter and consider using a CDN (e.g., Cloudflare) for DNS failover  
- Implement retry logic for transient errors like timeouts and DNS failures

### Proposed Next Steps

Run a third SOAK test with:

- **Duration:** 3 hours  
- **Users:** 150–200  
- **Cleaned test plan:** exclude 404-1  
- **DNS warm-up strategy**  
- **Real-time monitoring via Vercel Analytics**

---

## Final Conclusion

Both experiments demonstrate that the Next.js app on Vercel handles sustained traffic well, with minimal latency degradation and strong endpoint reliability. However, DNS resolution and misconfigured routes remain key areas for improvement. With targeted optimizations, the app is well-positioned for production-scale traffic.

---
