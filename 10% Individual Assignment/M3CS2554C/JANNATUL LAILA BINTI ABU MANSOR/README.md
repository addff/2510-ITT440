# WEB PERFORMANCE ANALYSIS: JOOMLA DEMO WEBSITE STRESS TEST USING GTMetrix
####  STUDENT NAME : JANNATUL LAILA BINTI ABU MANSOR
####  ITT440 INDIVIDUAL ASSIGNMENT 
####  GROUP : M3CS2554C
 <hr>
<p align="center">
<img width="352" height="232" alt="image" src="https://github.com/user-attachments/assets/98e81f4f-aa05-4463-a5d0-eb8b50864f49" /> </p>

 <p align="center">
<img width="372" height="286" alt="JOOMLA" src="https://github.com/user-attachments/assets/b95c696b-fb75-478f-8f08-60160ea11a6a" /> </p>

 <hr>

## 1.0 INTRODUCTION

<p align="justify"> In the digital world, web application performance plays a crucial role in determining user satisfaction, conversion rates, and overall business success.  User annoyance and abandonment can result from delays of even a few seconds.  Through the use of stress testing, this report provides a thorough performance analysis of the public Joomla demonstration website (https://demo.joomla.org/).  In order to determine a system's breaking point and comprehend performance degradation patterns, stress testing is a non-functional testing method that assesses how a system responds to extreme load, frequently above its typical operating capacity.  This study evaluates the application's responsiveness, stability, and resource management by simulating prolonged high traffic conditions using the GTmetrix performance tool. </p>
 <hr>
 
## 2.0 OBJECTIVES

<p align="justify"> This stress testing assignment's main goals are: 
<ul>
 <li><p align="justify"><strong> To Create and Run a Stress Test: Create and run a systematic stress test strategy against the target Joomla application using the GTmetrix tool. </li>
 <li><p align="justify"><strong> To Create and Test a Hypothesis: Make a claim about the stability of the application under load and support it with empirical evidence. </li>
 <li><p align="justify"><strong> To Find Performance Bottlenecks: Examine important performance indicators to identify problems that are influencing stability, throughput, and response time. </li>
 <li><p align="justify"><strong> To Evaluate Metrics Focused on Users: Measure the real-user experience, assess the Core Web Vitals, Cumulative Layout Shift (CLS), Total Blocking Time (TBT) and Largest Contentful Paint (LCP). </li>
 <li><p align="justify"><strong> To Offer Practical Suggestions: Record results and suggest tangible, research-based fixes to address performance problems that have been identified. </li>
</ul>
</p>
 <hr>

## 3.0 WHAT IS STRESS TESTING
 
<p align="justify"> Stress testing assesses a system's resilience and error-handling skills under exceptionally high loads, frequently more than it is intended to support. Instead of simulating typical user traffic, the main objective is to test the system's limits in order to: 
<ul>
 <li><p align="justify"><strong> Find the application's breaking point. </li>
 <li><p align="justify"><strong> observe how the system gets worse when its capacity is used up. </li>
 <li><p align="justify"><strong> Determine how the system bounces back once the load has stabilised. </li>
 <li><p align="justify"><strong> Find configuration problems, memory leaks, or hidden bugs that only show up in severe circumstances. </li>
</ul>
By simulating the impact of high server-side resource consumption and competition, GTmetrix is used to repeatedly analyse the page under test conditions. This enables us to see how performance metrics remain stable over several test rounds. </p>
 <hr>

## 4.0 TOOL SELECTION JUSTIFICATION

<p align="justify"> The tool selected for this analysis is GTMetrix.</p> 
<ol> 
 <li><p align="justify"><strong><p align="justify"><strong>Accessibility and Usability: GTmetrix is a web-based software as a service platform that doesn't require complicated local setup or installation, so a broad spectrum of users can use it. This guarantees consistent test execution from a controlled location and removes variables associated with test environment setup. </li>
 <li><p align="justify"><strong><p align="justify"><strong>Comprehensive Reporting: Offers waterfall charts, Core Web Vitals, and comprehensive performancExtensive Performance Analysis. GTmetrix combines server-level performance data with real-world browser timings using Google Lighthouse to present a comprehensive picture of performance. Core Web Vitals, which are industry standards for user experience, are among the many metrics it provides. </li>
 <li><p align="justify"><strong><p align="justify"><strong>Professional Reporting: To diagnose the sequence and impact of resource loading, the tool produces comprehensive, visual reports with waterfall charts. Presenting findings to a professional audience requires this. </li>
 <li><p align="justify"><strong><p align="justify"><strong>Stress Testing Capability: GTmetrix enables continuous testing and monitoring over time, despite not being a conventional load runner that virtualises thousands of users. Multiple, consecutive test rounds are used as a stand-in for stress testing in this analysis, exposing trends in degradation and performance consistency. </li>
 <li><p align="justify"><strong> Industry Recognition: GTmetrix is a widely recognized and trusted tool in the web performance community, lending credibility to the analysis and its findings. </li> </p> </ol>
 <hr>

 ## 5.0 TEST ENVIRONMENT SETUP
 
<p align="justify"> The test environment was set up to create a baseline before carefully introducing stressors.
<ol>
    <li><p align="justify"><strong> Testing Tool: GTMetrix </li>
    <li><p align="justify"><strong> Test Server Location: GTmetrix's Vancouver, Canada server. </li>
    <li><p align="justify"><strong> Browser: Google Chrome </li>
    <li><p align="justify"><strong> Connection Speed: Cable (5Mbps down, 1Mbps up). </li>
    <li><p align="justify"><strong> Target Application URL: Public Joomla Demo Site https://launch.joomla.org/ </li>
    <li><p align="justify"><strong> Test Rounds: Three consecutive tests were performed to simulate sustained load and identify trends or degradation, labeled as Round 1, Round 2, and Round 3. </li>
    <li><p align="justify"><strong> Type of Test: Stress testing using performance trend tracking and repeated analysis </li> </ol> </p>
 <hr>
 
## 6.0 METHODOLOGY

<p align="justify">
 <ol>
    <li><p align="justify"><strong> Target Selection: The publicly accessible Joomla Launch site was chosen. </li> <!-- 1 -->
    <li><p align="justify"><strong> Test Execution: <!-- 2 -->
     <ul>
      <li><p align="justify"><strong> Multiple test runs were conducted via GTMetrix. </li>
      <li><p align="justify"><strong> Baseline Establishment: To create a performance baseline for the application, a single initial test (Round 1) was run. </li>
      <li><p align="justify"><strong> Stress Simulation: Two tests (Rounds 2 and 3) were conducted quickly after each other. By repeatedly requesting the page, this methodology creates a stress condition that puts the server under pressure and demonstrates how reliably it can deliver performance. </li> 
      <li><p align="justify"><strong> Performance data was collected including: </li>
       <ul>
         <li><p align="justify"><strong> Redirect Duration </li>
         <li><p align="justify"><strong> Time to First Byte (TTFB) </li>
         <li><p align="justify"><strong> DOM Content Loaded Time </li>
         <li><p align="justify"><strong> Connection Duration </li>
         <li><p align="justify"><strong> First Paint </li>
         <li><p align="justify"><strong> Onload Time </li>
         <li><p align="justify"><strong> Backend Duration </li>
         <li><p align="justify"><strong> DOM Interactive Time </li>
         <li><p align="justify"><strong> Fully Loaded Time </li>
       </ul>
      <li><p align="justify"><strong> The original hypothesis was that, as a feature-rich Content Management System (CMS), the Joomla demo site would perform worse under stress, mainly due to slower Time to Interactive and higher server response times (TTFB) caused by JavaScript. </li> <!-- 3 -->
     </ul>
    </li>
<BR> <p align="center">
<img width="954" height="685" alt="BROWSER TIMING" src="https://github.com/user-attachments/assets/6946ea31-4153-4bb0-beee-28f6d5109818" /> </p>
  
<p align="center">
<img width="954" height="685" alt="PERFORMANCE" src="https://github.com/user-attachments/assets/39af9551-714b-4e48-a2a1-6fc7755aff6b" /> </p>
    <li><p align="justify"><strong> Stress simulation: Despite GTMetrix's inability to support conventional multi-user stress tests, load was simulated through repeated runs and performance analysis under cached and uncached conditions. </li> <!-- 3 -->
   <li><p align="justify"><strong> Data Collection: Metrics were recorded from GTMetrix reports and Lighthouse audits. </li>
 </ol>
</p>
<hr>

## 7.0 PERFORMANCE DATA ANALYSIS

### 7.1 Overall Scoring
<p align="justify"> Throughout the three test rounds, the overall GTmetrix grade fluctuated, suggesting performance instability under low stress:
<ul> 
 <li><p align="justify"><strong> Round 1: B (92%) </li>
 <li><p align="justify"><strong> Round 2: B (94%) </li>
 <li><p align="justify"><strong> Round 3: B (89%) </li>
</ul> 
Following a slight improvement in Round 2, this regression in Round 3 indicates that the application's performance is brittle and susceptible to being adversely affected by repeated loads, even from a single user. </p>

<p align="center">
<img width="954" height="685" alt="GRADE" src="https://github.com/user-attachments/assets/462b02a3-78fc-4f1a-bc58-452e6ac86abd" /> </p>

### 7.2 Core web Vitals (User Experience Metrics)
<p align="justify">
<ul> 
 <li><p align="justify"><strong> In Round 3, the Largest Contentful Paint (LCP) regressed from 1.3s which is good, in Round 1 to 1.6s shows that it needs some improvement. This suggests that when under stress, the main content renders more slowly. </li>
 <li><p align="justify"><strong> Total Blocking Time (TBT): Exhibited notable fluctuations. After improving from 121 ms in Round 1 to 86 ms in Round 2, it deteriorated to 125 ms in Round 3. This indicates main thread blocking and uneven JavaScript execution. </li>
 <li><p align="justify"><strong> Regardless of load conditions, Cumulative Layout Shift (CLS) remained at a perfect 0 throughout all rounds, demonstrating exceptional visual stability. </li>
</ul> 
</p>
<p align="center">
<img width="954" height="685" alt="WEB VITALS" src="https://github.com/user-attachments/assets/a982f35f-9ec2-4579-980b-c41427bd6d2b" /> </p>
<hr>

## 8.0 RESULT INTERPRETATION

<p align="justify"> The findings support the original theory. With a "Fast to Show, Slow to Use" profile, the Joomla demo site clearly shows performance degradation under stress. The page's interactivity (TTI) is subpar and gets worse in the final test, even though it is still visually stable (CLS). The main conclusions are:
<ol>
 <li><p align="justify"><strong> Slow Interactivity: Throughout all tests, the Time to Interactive (TTI) remained extremely high (~4 seconds), and in Round 3, it deteriorated to 4.2 seconds. </li>
 <li><p align="justify"><strong> JavaScript Bottleneck: Client-side script execution is identified as the main bottleneck, and the high and erratic Total Blocking Time (TBT) is the direct cause of the slow TTI. </li>
 <li><p align="justify"><strong> Structural Deficiencies: An excessive amount of HTTP requests (more than 150 per page) is one of the underlying architectural problems that are reflected in the consistently low "Structure" score (averaging 78%). </li>
</ol>
</p>
<hr>

## 9.0 IDENTIFICATION OF BOTTLENECKS AND FAILURE POINTS

<p align="justify"> 
<ol>
 <li><p align="justify"><strong> Primary Bottleneck: Excessive and Blocking JavaScript </li>
 <table>
  <tr>
   <th>EVIDENCE</th>
   <th>IMPACT</th>
  </tr>
  <tr>
   <td>long TTI (~4s) and high TBT (~120ms). Two sizable Google Tag Manager scripts (about 229 KB in total) and several jQuery libraries were regularly displayed in the Waterfall Chart as loading ahead of schedule and preventing the main thread from running.</td>
   <td>fter the page first paints, users are unable to interact with it for more than 4 seconds, which results in a subpar user experience.</td>
  </tr>
 </table>
 <li><p align="justify"><strong> Secondary Bottleneck: High Number of HTTP Requests </li>
 <table>
  <tr>
   <th>EVIDENCE</th>
   <th>IMPACT</th>
  </tr>
  <tr>
   <td>152-155 requests are made for each page load. The Structure score (77–79%) was continuously low.</td>
   <td>The Fully Loaded Time (a fixed 7.9s) rises with each request, adding overhead and needlessly taxing the server and network.</td>
  </tr>
 </table>
 <li><p align="justify"><strong> Potential Failure Point: Server-Side Performance </li>
 <table>
  <tr>
   <th>EVIDENCE</th>
   <th>IMPACT</th>
  </tr>
  <tr>
   <td>The average Time to First Byte (TTFB) was 450 ms, which is slower than optimal. Server-side resource contention is also suggested by the Round 3 regression in LCP and FCP.</td>
   <td>Every subsequent stage of the page loading process is delayed by slower server response times.</td>
  </tr>
 </table>
</ol>
</p>
<p align="center">
<img width="954" height="685" alt="REQUEST" src="https://github.com/user-attachments/assets/e537c371-0aab-468a-912d-7e398bbce802" /> </p>
<hr>

## 10.0 SUMMARY

<p align="justify"> The target Joomla application's serious performance flaws were successfully found by this stress test analysis. Despite having a stable visual design, the website has serious problems with interactivity because of poorly optimised JavaScript and an ineffective page structure with excessive requests. Under the strain of repeated testing, the performance was found to be unstable and regressed. The following top suggestions are put forth to address these problems:
<ul>
 <li><p align="justify"><strong> Defer Non-Critical JavaScript: To avoid main thread blocking, load analytics and third-party scripts asynchronously. </li>
 <li><p align="justify"><strong> Reduce HTTP Requests: To cut down on the overall number of requests, combine CSS/JS files and make use of image sprites. </li>
 <li><p align="justify"><strong> Optimise images by converting big PNG files to more contemporary WebP formats. </li>
 <li><p align="justify"><strong> Improve TTFB and offload the delivery of static assets by implementing caching and a CDN. </li>
</ul>

Even with higher load conditions, the Joomla demo site can provide a faster, more dependable, and consistent user experience by putting these changes into practice. </p>
<hr>

## PRESENTATION LINK

https://youtu.be/DIq83zXCypQ?si=lYWstGQSQYtb2sEm

<!-- [ <p align="justify">  </p> ]paragraph -->
<!-- [ <ul> <li><p align="justify"><strong>  </li>  </ul> ] bullet points --> 
<!-- <ol> <li><p align="justify"><strong>  </li>  </ol> numeric points -->
<!-- [ <hr> section devider ] [ <br> enter ] -->

<!-- 
 Under high-load circumstances, these modifications would improve stability and performance. -->






