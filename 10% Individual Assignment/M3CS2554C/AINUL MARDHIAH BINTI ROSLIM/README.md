# 🔥Can It Handle the Heat? A Load Test Article by Ainul's Network Programming 101 ✨

## 🎯 Executive Summary: Gatling Load Test Baseline

This document summarizes the core purpose, findings, and recommendations from the primary load test documented in the README, conducted as part of Ainul's Network Programming 101.

<p align="center">
  <a href="https://gatling.io/" target="_blank">
    <img src="https://cdn.prod.website-files.com/685a8fe4ddca049f26333871/68b5961b1a99f68c22d5cf56_Open%20graph%20Gatling%20image.svg" alt="Gatling Logo Link" width="300">
  </a>
</p>

## 🛠️ Why Gatling, huh? (Tool selection justification)

I picked Gatling as my load testing tool because its modern design makes the entire performance check-up process—from generating traffic to analyzing results—more efficient and reliable.

Gatling uses a smart, **asynchronous architecture** which means it can handle **huge traffic** and simulate thousands of users using very little computer power. This allows me to run bigger, more realistic tests to find the application's true breaking limits.

The test scenarios are written as clean, **simple, and readable code** (a DSL), making them easy to update when the application changes, which also helps the team collaborate better. 

After every test, Gatling automatically generates **amazing, detailed HTML reports**. These reports give me instant insight into the results with graphs that clearly pinpoint the exact slow spots (bottlenecks) in the application. 

Finally, Gatling **fits right into my automated development process (CI/CD)**, ensuring I catch performance problems early and continuously before it ever become a serious issue.
  
---
## 🖥️ You are now at the test run prep! (Test environment setup)
| Category | Component/Software | Purpose in Environment |
| :--- | :--- | :--- |
| **Target Website** | **AUT Base URL** | `https://the-internet.herokuapp.com` |
| **Runtime Environment** | **Java Runtime Environment** | Executes the simulation written in Java. |
| **Load Testing Tool** | **Gatling Open Source** | Core engine for execution and reporting. |
| **Execution Method** | **Terminal / Command Line** | Used to execute the Gatling script via the provided **`gatling.sh`** or **`gatling.bat`** runner files. |
| **Simulation Script** | **Class Name** | `CleanSimulation.java` |
| **Injection Profile** | **Load Strategy** | `rampUsers(10).during(60)` (Injecting **10 users** over **60 seconds**). |
| **Reporting/Analysis** | **Gatling HTML Reports** | The output format used to view and analyze performance metrics. |

---
## 📜 Next Station, My Testing Handbook! (Methodology)

firstly we will go to **PHASE 1** where I initializing my pre - framework in my computer terminal

1.  **Write Java Code**

The coding below is my java coding that Gatling had used to make a Stimulation Load test at `https://the-internet.herokuapp.com`
```java
package example;

import static io.gatling.javaapi.core.CoreDsl.*;
import static io.gatling.javaapi.http.HttpDsl.*;

import io.gatling.javaapi.core.*;
import io.gatling.javaapi.http.*;

public class CleanSimulation extends Simulation {

  private static final HttpProtocolBuilder httpProtocol = http
      .baseUrl("https://the-internet.herokuapp.com")
      .acceptHeader("text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

  private static final ScenarioBuilder scn = scenario("Heroku App Login Workflow FINAL FIX")
      
      // Step 1: GET the Login Page
      .exec(
          http("T01_GET_Login_Page")
              .get("/login")
              .check(status().is(200))
      )
      .pause(1) 
      
      // Step 2: POST the login form data, which includes the automatic redirect to /secure
      .exec(
          http("T02_POST_Login_and_Access_Secure")
              .post("/authenticate")
              .formParam("username", "tomsmith") 
              .formParam("password", "SuperSecretPassword!")
              
              // Check the final state after the redirect (the secured page)
              .check(status().is(200)) 
              // Verification: Check for a unique element on the secured page
              .check(css("h4").is("Welcome to the Secure Area. When you are done click logout below."))
      )
      
      .pause(2) 
      
      .exec(session -> {
          System.out.println("Login Sequence Complete!");
          return session;
      });


  // 3. Injection Profile: 10 users over 60 seconds
  {
    setUp(
      scn.injectOpen(
        // Inject 10 users gradually over 60 seconds for stable, sustained metrics
        rampUsers(10).during(60) 
      )
    )
    .protocols(httpProtocol)
    // 4. Assertion: Expecting success
    .assertions(
        global().failedRequests().percent().lte(1.0)
    );
  }
}
```
2.  **Launch Gatling**

From my Computer terminal or command prompt, I had navigated to my project root
`cd "C:\Users\Ainul Mardhiah\Gatling Open Source"` 

After that, I had run and execute my specific command, which is `.\mvnw.cmd gatling:test`.

And then at my gatling prompt, I type the number 1 because it's corresponds to `example.CleanSimulation` and press Enter.

secondly, we wiil go and see the official load run test at **PHASE 2**.

3.  **Start The Simulation**

I will run the load test and execute the full **10 users over 60 seconds**

And also, it will based on the virtual scenarios that I created to make it suitable for the load testing which is :-

| Step | Virtual User Action |
| :--- | :--- |
| **I** | The user **access the Login Page** and performs an HTTP **GET** request to the `/login` URL. |
| **II** | The user waits for **1 second**, simulating the time a real person takes to look at the page and prepare to type. |
| **III** | The user will **submit the login form** and performs an HTTP POST request to the `/authenticate` endpoint, sending the hardcoded **username** and **password**. | 
| **IV** | The users will **verify success** and checks that the resulting page contains the certain sentences which is **"Welcome to the Secure Area..."**. |
| **V** | The user waits for **2 seconds**, simulating the time they spend viewing the secured content before doing anything else like logging out. | 
| **VI** | The user will **End the virtual scenarios** by completing their session, and their performance metrices such as response times, errors are recorded. | 

last but not least, at **Phase 3** is where I will be making the verdiction about the results!

4. **Get the finalized result**

The terminal will show the Gatling process and at the end of it will send a `Build Succes` or `Build Failed` depending on the app performance.

In addition, I can get the overall reports documentation to analyse the **Global failed requests percentage**, **Response time 95th percentile (p95)**, **Throughput**, and the app **Bottleneck**.  

---

## 😍 Looking at the beautifully mesmerizing factual charts or graphs  (Raw data presentation)

In Global Gatling Documentation : -

<img width="764" height="275" alt="image" src="https://github.com/user-attachments/assets/4988fb63-17b8-4cf6-892b-9c4ce7a25a9d" />

### Response time distribution
<img width="763" height="280" alt="image" src="https://github.com/user-attachments/assets/b23321ad-00aa-47af-a1ab-e6deac220f29" />

### Response time percentiles
<img width="763" height="282" alt="image" src="https://github.com/user-attachments/assets/e682bbd9-46d3-4d8c-a700-53f351b9dc4f" />

### Requests / sec
<img width="762" height="282" alt="image" src="https://github.com/user-attachments/assets/ed61e7c0-4627-403f-9cfc-8c104f3977fb" />

### Response / sec
<img width="761" height="281" alt="image" src="https://github.com/user-attachments/assets/5b373167-d4ac-4fa6-8fc9-8f86b376c5b1" />


In Details bar graph for : -

### T01_GET_Login_Page
<img width="767" height="298" alt="T01_GET_Login_Page" src="https://github.com/user-attachments/assets/63aa8840-c1a7-475a-9f40-87d7e9efb6ba" />

### T02_POST_Login_And_Access_Secure
<img width="765" height="295" alt="T02_POST_Login_And_Access_Secure" src="https://github.com/user-attachments/assets/0450e2ad-9bf2-42e6-bb25-ee07f868e241" />

### T03_POST_Login_And_Access_Secure Redirect 1
<img width="763" height="290" alt="T03_POST_Login_And_Access_Secure Redirect 1" src="https://github.com/user-attachments/assets/f3c27aa3-82b7-4aa9-b88e-8ef230582974" />

---
## 📊 So, What can I say about the Findings...(Interpretation of results)

### 1.0 Response Time (Latency)

**○ Response Time Ranges :** The majority of request which was *75-80%* fell into the **Green** range by the indicating under 800 ms meanwhile, a smaller significant, portion which was *20-25%* situated into the **Yellow or Orange** range.

**○ In depth - explanation :** The initial GET Login Page request is the slowest, with an average of **1.13 seconds** and a poor maximum time of nearly **5 seconds**. Nevertheless, the subsequent POST requests which was the actual acces or login are very fast, averaging around under **420 ms**.

### 2.0 Throughput & Load Profile 

**○ Number of Users Strated per Second & Concurrent Users :** The test employed an infrequent, **spiky load pattern**. The "Number of users started per second" indicated short burts of users foloowed by periods of zero users starting. The "Number of concurrent users" also confirming that this was a **very light load test**, with a peak of only **3 concurrent users** that I assigned for the simulation.

**○ In depth - explanation :** In my opinion, my improvised system's throuput is kinda moderate or we could said easy to achieve the excellent because it succesfully served every request given the minimal load. The number of concurrent users was low, which is suitable and appropriately for such a simple functional verification load test.

### 3.0 Error Rate

**○ Assertion Rate**
| Metric | Value | Threshold Met | Interpretation |
| :--- | :--- | :--- | :--- |
| **Success Rate (OK %)** | 100% | Yes | All system requests completed without any functional failures. |
| **Failed Rate (KO %)** | 0% | Yes | Zero errors were recorded during the simulation. |
| **Global Failed Items (%)** | ≤ 1.0% | Yes | The overall success criteria for the test were met. |

**○ In depth - explanation :** I kinda think my system is **functionally stable** and quite robust under this light load. There are no indication of application errors, connection failures, or functional issues. 

---
## ⚠️ Can I find the Obstruction ?! (Identified bottlenecks)

**Client-Side Bottleneck (Inference)** 
I have find a slight or maybe the main problems in my simulation for the `https://the-internet.herokuapp.com`. The data **clearly points** to a bottlenck in the `/T01 GET Login Page` transaction. 

| Metric | Observation | Hypothesizing |
| :--- | :--- | :--- |
| **Average Response Time** | **1136 ms** (1.13 seconds) | This is **significantly slower** than subsequent transactions (385 ms and 413 ms), consistently causing the largest delay in the user flow. |
| **Maximum Response Time** | **4890 ms** (4.89 seconds) | A maximum time near **5 seconds** for a simple GET request is a major performance concern and indicates a very poor worst-case user experience.

**○ In depth - surmise :** The first request to load the login page is the **application's slowest transaction** and is acting as a transactional bottleneck for the user flow. Poosible causes include heavy initial server processing, slow database queries for session setup, or large static content loading.

---
## 🚨Now it's time for advocate (Recommendations for improvement) ##

The goal is to bring the average response time for the initial Login Page GET REQUEST **down below 500 ms** to match the performance of subsequent successful transactions. In addition, i think the slow load time could be due to several issues on the server handling this request. So I guess I should start analyzing the **server-side logs** and running a **code profiler** on the execution path for this specific request (`/T01 GET Login Page`). 

**Recommendation on server-side logs** : Aggressively investigate and optimize the `/T01 GET Login Page` request.

○ I should bring the average response time for this request **below 500 ms** too ensure fast,consistent user entry point and also look for code inefficiences, slow database calls such as session setup, configuration loading), or unnecessarily large page assets contributing to the **1136** ms average.

**Recommendation on code profiler** : I think even when it is still functionally stable, my test needs to inforce performance requirements in the future.

○ I would add **Response Time Assertions** to my test script. For instance, add a rule or coding that forces the test to fail if the **90th percentile reponse time** for any core transaction exceeds a specific Service Level Objective like 15 seconds. This ensures future runs won't pass if the performance degrades.

---
## ‼️The Summarization Of My Verdiction (Final conclusions)

I think at the end of this experimental test performance of website application and Analysis, I can assure you that it is **Stable, But Slow to Start**. The system also can also be indicated by the color such as when it is currently **Green** 🟩 for **Functional stability** but **Yellow** 🟨 for Perfformance readines.

The **Positive Outcome** that I could get was the test achieved a *100%* **success rate** with **zero errors** under light load, confirming functional stability.

The **Critical Weakness** is that the `/T01 GET Login Page` transaction is a **transactional bottleneck**, averaging *1.13* **seconds** and peaking near *5* **seconds**. This is I think the single biggest performance risk to the user experimence.

---
## 🎥 Wanna see a video? Link below ! (Video Demonstration)

<a href="https://youtu.be/Zpucm2vnlpQ" target="_blank">Visit the video at my YouTube channel</a>

---
# 🍀That's all for now, Thank You for reading my humble Article 💖

Individual Assignment : Comprehensive Web Application Performance Testing & Analysis

Edited By : Ainul Mardhiah binti Roslim

Matric No : 2024553785

Class Registered : M3CS2554C

Code Subject : ITT440 

Subject Name : Network Programming

Checked By : Sir Shahadan bin Saad

![Untitled video - Made with Clipchamp (2)](https://github.com/user-attachments/assets/9ff6d5f4-f091-470e-8cc1-ae73e6aefb0b)
