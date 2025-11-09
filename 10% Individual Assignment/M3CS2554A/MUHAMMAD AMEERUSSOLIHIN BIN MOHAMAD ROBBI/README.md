# ⚡ Spike Testing On OWASP Using Gatling ⚡

### 📝 *ITT440 - INDIVIDUAL ASSIGNMENT*
#### 🧑‍🎓 NAME : MUHAMMAD AMEERUSSOLIHIN BIN MOHAMAD ROBBI
#### 🎓 STUDENT ID : 2024963323
#### 👥 GROUP : M3CS2554A
---
## 🎯  Project Overview

The goal of this test was to evaluate the application’s stability and responsiveness under a sudden surge in user load, in line with [**OWASP**](https://owasp.org/www-project-juice-shop/) performance testing practices. A spike test simulates abrupt traffic increases to determine whether a system can handle sharp load variations without functional or performance degradation.

## ⚙️ Test Setup

| Parameter | Configuration |
|------------|---------------|
| **💻System Environment** | Windows 11, Java JDK 17, 24 GB RAM |
| **🛠️Tool** |  Gatling 3.10.4 (Highcharts bundle) |
| **📋Language** | Scala simulation (SpikeTest.scala) |
| **📈Type of Test** | Spike Test |
| **🌍Target URL** | (https://owasp.org/www-project-juice-shop/) |
| **🧍Total Virtual Users** | 320 concurrent |
| **⏱Duration** | ~47 seconds |
| **📽️Scenario** | 1️⃣ Open Home Page → 2️⃣ Search Flights |

## 🧾 Script/Command

### Gatling 
```scala
import io.gatling.core.Predef._
import io.gatling.http.Predef._
import scala.concurrent.duration._

class SpikeTest extends Simulation {

  val httpProtocol = http
    .baseUrl("https://owasp.org/www-project-juice-shop/") //Target URL
    .acceptHeader("text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8")
    .userAgentHeader("Gatling Spike Test")

  val scn = scenario("OWASP Spike Test")
    .exec(http("Open Home Page").get("/").check(status.is(200)))
    .pause(1)
    .exec(http("Search Flights")
      .post("/reserve.php")
      .formParam("fromPort", "Boston")
      .formParam("toPort", "London")
      .check(status.is(200))
    )

  setUp(
    scn.inject(
      nothingFor(5.seconds),             // delay starting
      atOnceUsers(10),                   // baseline load
      nothingFor(10.seconds),
      atOnceUsers(300),                  // sudden spike 🚀
      nothingFor(30.seconds),
      atOnceUsers(10)                    // recovery phase
    )
  ).protocols(httpProtocol)
}
```

###  Command Prompt
```bash
// In Command
cd (FileLocation)
gatling.bat
```
---

## 🧠 Hypothesis
The test expected the server should maintain stability and return valid HTTP 200 responses for both endpoints.

## 🔍 Test Summary

| ✅ Test Execution | ❌ Response Outcome |
|------------|---------------|
| Most users will injected and complete their scenarios | All requests to the “Search Flights” endpoint failed, producing HTTP 405 |
| Gatling successfully parsed results and generated the summary report | The server rejected the HTTP method used |
| No test level runtime errors occurred | The endpoint was inaccessible or restricted under high load or security policies |

## 🔬 Quantitative Results

| Metric | Total | OK | KO |
|---------|--------|-------------|----------|
| Total Request | 640 | 320 | 320 |
| Min Response Time (ms) | 61 | 222 | 61 |
| Max Response Time (ms) | 3536 | 3536 | 661 |
| Mean Response Time (ms) | 641 | 1175 | 107 |
| Std. Deviation | 587 | 342 | 51 |
| 50th Percentile | 279 | 1200 | 112 |
| 75th Percentile | 1199 | 1384 | 320 |
| 95th Percentile | 1478 | 1550 | 142 |
| 99th Percentile | 1756 | 2095 | 219 |
| Request/sec | 14.88 | 7.44 | 7.44 |

### Distribution Summary

#### 🟢 6% of requests completed below 800 ms.
#### 🔵 19% between 800–1200 ms.
#### 🔵 25% exceeded 1200 ms.
#### 🔺 50% failed (405 responses).
---
## 📊 Raw Data
<table align="center">
  <tr>
    <th>Chart</th>
    <th>Description</th>
  </tr>
  <tr>
    <td align="center">
      <img width="1200" height="800" alt="response_time_distribution" src="https://github.com/user-attachments/assets/fc59c0af-890d-4910-8c79-fd8bdc16b81c" />
    </td>
    <td>
      <b>Response Time Distribution (ms)</b><br>
      The results show an increasing trend in response time as the percentile rises. This indicates that under sudden load, some requests experienced delays, but the overall response pattern remained predictable and stable.
    </td>
  </tr>
  <tr>
    <td align="center"><img width="1200" height="800" alt="throughput_chart" src="https://github.com/user-attachments/assets/c359aa05-3809-419b-a7e2-cfc5f500bf34" />
" />
    </td>
    <td>
      <b>TThroughput Chart (Requests per Second)</b><br>
      The throughput remained steady around 14.88 requests/second, indicating that the server infrastructure could maintain consistent request handling capacity during the spike.
    </td>
  </tr>
  <tr>
    <td align="center"><img width="1000" height="1000" alt="request_success_rate" src="https://github.com/user-attachments/assets/ee0c85f9-12fc-4d31-90b6-2cefac36ebe6" />
    </td>
    <td>
      <b>Request Success Rate (OK vs KO)</b><br>
      Half of the requests (50%) succeeded, while the other half failed with HTTP 405 (Method Not Allowed) errors.
    </td>
  </tr>
</table>

---

## 🧬 Analysis
### a. Functional Behavior

- The home page requests (Open Home Page) were consistently successful, confirming that:
  
      -The Gatling setup and load injection worked properly.
      -The web server could handle the basic GET request load.

- The Search Flights requests, however, all failed. Since the error was 405, not 500 or 503, this points to a client side or configuration issue rather than outright server overload.

- Possible causes:

      -The Gatling script is using the wrong HTTP method (eg: POST instead of GET).
      -The target API endpoint blocks certain request types or origins.
      -Sudden spike triggered security mechanisms such as rate limiting or WAF rules.

### b. Performance Metrics

- Even though half the requests failed:

      -The system remained responsive (no timeouts or connection errors).
      -Successful requests had an average latency around 1.1 seconds, peaking at 3.5 seconds.
      -These values are within acceptable ranges for short spike testing.
  
> This suggests that the infrastructure could handle load, but application logic or routing caused functional failures.

### c. Stability Observation

The system sustained 320 concurrent users over 47 seconds without any critical crash or service outage.
Therefore, infrastructure stability is acceptable, but functional reliability under sudden load is not yet optimal.

## 💡 Recommendations

- 🟩 Verify HTTP Methods:
  
Confirm the correct HTTP method (GET/POST/PUT) for the Search Flights endpoint and
update the Gatling request definition accordingly.

- 🟩 Validate Endpoints Before Spike Testing:
  
Run a small smoke test (1–5 users) to confirm 200 OK responses before performing high load spikes.

- 🟩 Monitor Server Logs:
  
Check application or API gateway logs for “405” or “Method Not Allowed” entries to identify the rejection cause.

- 🟩 Implement Gradual Ramp Up:
  
Add a short warm up or ramp phase before the spike to mimic more realistic traffic surges and prevent immediate overload.

- 🟩 Check Security Configurations:
  
Firewalls or API gateways may interpret repeated identical requests as suspicious, temporarily relax security settings for controlled performance testing.

## 🧩 Conclusion

The Gatling spike test successfully simulated a sudden increase of 320 users and provided valuable insights.
While the server infrastructure showed resilience and remained responsive, the application layer rejected half of the requests with HTTP 405 errors.
This indicates that under sudden high load, the system fails functionally rather than performance wise — the requests reach the server but are not processed as intended.

## 📹 Video Demostration
- https://youtu.be/MWb81sAqkBM
