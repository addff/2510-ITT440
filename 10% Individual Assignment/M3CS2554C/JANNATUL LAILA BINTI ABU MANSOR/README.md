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
 <li> To Create and Run a Stress Test: Create and run a systematic stress test strategy against the target Joomla application using the GTmetrix tool. </li>
 <li> To Create and Test a Hypothesis: Make a claim about the stability of the application under load and support it with empirical evidence. </li>
 <li> To Find Performance Bottlenecks: Examine important performance indicators to identify problems that are influencing stability, throughput, and response time. </li>
 <li> To Evaluate Metrics Focused on Users: Measure the real-user experience, assess the Core Web Vitals, Cumulative Layout Shift (CLS), Total Blocking Time (TBT) and Largest Contentful Paint (LCP). </li>
 <li> To Offer Practical Suggestions: Record results and suggest tangible, research-based fixes to address performance problems that have been identified. </li>
</ul>
</p>
 <hr>

## 3.0 WHAT IS STRESS TESTING
 
<p align="justify"> Stress testing assesses a system's resilience and error-handling skills under exceptionally high loads, frequently more than it is intended to support. Instead of simulating typical user traffic, the main objective is to test the system's limits in order to: 
<ul>
 <li> Find the application's breaking point. </li>
 <li> observe how the system gets worse when its capacity is used up. </li>
 <li> Determine how the system bounces back once the load has stabilised. </li>
 <li> Find configuration problems, memory leaks, or hidden bugs that only show up in severe circumstances. </li>
</ul>
By simulating the impact of high server-side resource consumption and competition, GTmetrix is used to repeatedly analyse the page under test conditions. This enables us to see how performance metrics remain stable over several test rounds. </p>
 <hr>

## 4.0 TOOL SELECTION JUSTIFICATION

<p align="justify"> The tool selected for this analysis is GTMetrix. </p> 
<ol> 
 <li> Accessibility and Usability: GTmetrix is a web-based software as a service platform that doesn't require complicated local setup or installation, so a broad spectrum of users can use it. This guarantees consistent test execution from a controlled location and removes variables associated with test environment setup. </li>
 <li> Comprehensive Reporting: Offers waterfall charts, Core Web Vitals, and comprehensive performancExtensive Performance Analysis. GTmetrix combines server-level performance data with real-world browser timings using Google Lighthouse to present a comprehensive picture of performance. Core Web Vitals, which are industry standards for user experience, are among the many metrics it provides. </li>
 <li> Professional Reporting: To diagnose the sequence and impact of resource loading, the tool produces comprehensive, visual reports with waterfall charts. Presenting findings to a professional audience requires this. </li>
 <li> Stress Testing Capability: GTmetrix enables continuous testing and monitoring over time, despite not being a conventional load runner that virtualises thousands of users. Multiple, consecutive test rounds are used as a stand-in for stress testing in this analysis, exposing trends in degradation and performance consistency. </li>
 <li> Industry Recognition: GTmetrix is a widely recognized and trusted tool in the web performance community, lending credibility to the analysis and its findings. </li> </p> </ol>
 <hr>

 ## 5.0 TEST ENVIRONMENT SETUP
 
<p align="justify"> The test environment was set up to create a baseline before carefully introducing stressors.
<ol>
    <li> Testing Tool: GTMetrix </li>
    <li> Test Server Location: GTmetrix's Vancouver, Canada server. </li>
    <li> Browser: Google Chrome </li>
    <li> Connection Speed: Cable (5Mbps down, 1Mbps up). </li>
    <li> Target Application URL: Public Joomla Demo Site https://launch.joomla.org/ </li>
    <li> Test Rounds: Three consecutive tests were performed to simulate sustained load and identify trends or degradation, labeled as Round 1, Round 2, and Round 3. </li>
    <li> Type of Test: Stress testing using performance trend tracking and repeated analysis </li> </ol> </p>
 <hr>
 
## 6.0 METHODOLOGY

<p align="justify">
 <ol>
    <li> Target Selection: The publicly accessible Joomla Launch site was chosen. </li> <!-- 1 -->
    <li> Test Execution: <!-- 2 -->
     <ul>
      <li> Multiple test runs were conducted via GTMetrix. </li>
      <li> Baseline Establishment: To create a performance baseline for the application, a single initial test (Round 1) was run. </li>
      <li> Stress Simulation: Two tests (Rounds 2 and 3) were conducted quickly after each other. By repeatedly requesting the page, this methodology creates a stress condition that puts the server under pressure and demonstrates how reliably it can deliver performance. </li> 
      <li> Performance data was collected including: </li>
       <ul>
         <li> Redirect Duration </li>
         <li> Time to First Byte (TTFB) </li>
         <li> DOM Content Loaded Time </li>
         <li> Connection Duration </li>
         <li> First Paint </li>
         <li> Onload Time </li>
         <li> Backend Duration </li>
         <li> DOM Interactive Time </li>
         <li> Fully Loaded Time </li>
       </ul>
      <li> The original hypothesis was that, as a feature-rich Content Management System (CMS), the Joomla demo site would perform worse under stress, mainly due to slower Time to Interactive and higher server response times (TTFB) caused by JavaScript. </li> <!-- 3 -->
     </ul>
    </li>
<BR> <p align="center">
<img width="954" height="685" alt="BROWSER TIMING" src="https://github.com/user-attachments/assets/6946ea31-4153-4bb0-beee-28f6d5109818" /> </p>
  
<p align="center">
<img width="954" height="685" alt="PERFORMANCE" src="https://github.com/user-attachments/assets/39af9551-714b-4e48-a2a1-6fc7755aff6b" /> </p>
    <li> Stress simulation: Despite GTMetrix's inability to support conventional multi-user stress tests, load was simulated through repeated runs and performance analysis under cached and uncached conditions. </li> <!-- 3 -->
   <li> Data Collection: Metrics were recorded from GTMetrix reports and Lighthouse audits. </li>
 </ol>
</p>
<hr>

## 7.0 PERFORMANCE DATA ANALYSIS

### 7.1 Overall Scoring
<p align="justify">
<ul> 
 <li> Performance Scoring: 67% </li>
 <li> Structure Score: 79% </li>
 <li> Fully Loaded Time: 8.7s </li>
</ul> </p>

<p align="center">
<img width="954" height="685" alt="GRADE" src="https://github.com/user-attachments/assets/462b02a3-78fc-4f1a-bc58-452e6ac86abd" /> </p>

### 7.2 Core web Vitals (User Experience Metrics)
<p align="justify">
<ul> 
 <li> Largest Contentful Paint (LCP): 2.5s </li>
 <li> Total Blocking Time (TBT): 236ms </li>
 <li> Cumulative Layout Shift (CLS): 0 </li>
</ul> 
The page is visually stable (excellent CLS score) and loads its main content acceptably. Interactivity is crucial, though, because the high TBT suggests that the page is unresponsive for an extended period of time after loading.</p>
<p align="center">
<img width="954" height="685" alt="WEB VITALS" src="https://github.com/user-attachments/assets/a982f35f-9ec2-4579-980b-c41427bd6d2b" /> </p>
<hr>

## 8.0 RESULT INTERPRETATION

<p align="justify"> The stress test revealed several performance issues:
<ol>
 <li> Slow LCP: showing that the main content is being rendered slowly. </li>
 <li> High TBT: suggesting that the main thread be blocked by a poorly optimied JavaScript execution </li>
 <li> Long FUlly Loaded Time: 8.7s, this indicate there are elements that use a lot of resources and the slow server response. </li>
</ol>
Under repeated process, the site showed a very much consistent degradation in performance metrics, especially in TBT and LCP which indicates a poor stress tolerance.
</p>
<hr>

## 9.0 IDENTIFICATION OF BOTTLENECKS AND FAILURE POINTS

<p align="justify"> 
<ol>
 <li> Backend Duration: 1.3s, this shows delays in server-side processing. </li>
 <li> Large Image Files: several images over 100KB contribute to slow loading. </li>
 <li> Render-Blocking Resources: CSS and JavaScript files delaying page rendering. </li>
 <li> Third-Party scripts: Google TAg MAnager and reCAPTCHA add a very significant overhead. </li>
</ol>
</p>
<p align="center">
<img width="954" height="685" alt="REQUEST" src="https://github.com/user-attachments/assets/e537c371-0aab-468a-912d-7e398bbce802" /> </p>
<hr>

## 10.0 SUMMARY

<p align="justify"> The GTMetrix stress test of https://launch.joomla.org/ revealed a notable performance snags under load, especially in Largest Contentful Paint (LCP) and Total Blocking Time (TBT). Render-blocking Scripts and resource-heavy content cause the application to perform poorly under stress, resulting in a less than ideal user experince. Overall it is recommended to enhance server response times, postponing non-essential JavaScript and optimizing images. Under high-load circumstances, these modification would improve stability and website smooth opration. </p>


<hr>

<!-- [ <p align="justify">  </p> ]paragraph -->
<!-- [ <ul> <li>  </li>  </ul> ] bullet points --> 
<!-- <ol> <li>  </li>  </ol> numeric points -->
<!-- [ <hr> section devider ] [ <br> enter ] -->

<!-- 
 Under high-load circumstances, these modifications would improve stability and performance. -->






