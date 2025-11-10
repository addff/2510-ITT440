# 💻 Web Performance Analysis : GitHub Repository Load Speed Using GTmetrix 💻

####  STUDENT NAME : NUR IMAN SHAZREEN BINTI MOHD HAZLEE 
####  ITT440 - INDIVIDUAL ASSIGNMENT 
####  GROUP : M3CS2554C
---
<p align="center">
<img width="252" height="132" alt="image" src="https://github.com/user-attachments/assets/98e81f4f-aa05-4463-a5d0-eb8b50864f49"> 
 </p>

<p align="center">
<img width="250" height="134" alt="image" src="https://github.com/user-attachments/assets/25e76800-9219-4048-b2f0-f66346524470" >
</p>

---
## 🎀 1. Introduction 🎀
This report documents the performance analysis of a publicly hosted GitHub repository page (https://github.com/NurImanShazreen/Individual-Assignment-ITT440.git) using the GTmetrix web performance auditing tool. The primary goal of this analysis is to establish a performance baseline, identify existing inefficiencies, and recommend actionable strategies for optimization. The test was conducted on **October 31 2025**, from the **Seattle, WA, USA** test server location.

---
## 📚 2. Objectives 📚
The core objectives of this performance analysis are:

 1. To evaluate the overall load speed and efficiency of the target GitHub repository page using industry-standard metrics, including Google's Core Web Vitals. 
 2. To establish a quantifiable performance baseline by determining the **Performance Score** and **Structure Score**.
 3. To identify and interpret specific performance indicators such as **LCP, TBT, CLS, and TTI**.
 4. To pinpoint structual and content-related bottlenecks, such as slow asset delivery or inefficient code practices, by analyzing the GTmetrix Structure Audits.
 5. To provide a concise summary of findings and initial recommendations for performance improvement. 

---
### 🏃 3. What is a Load Speed? 🏃
Load speed or web performance is a measure of how quickly a web page's content becomes fully visible and interactive to the user. It encompasses several key phases, starting from the moment a user requests a URL until the page is visually stable and able to respond reliably to user inputs. High load speed translates directly into a better User Experience (UX).

Key metrics, particularly the **Core Web Vitals (LCP, FID/TBT, CLS)**, are used by tools like GTmetrix to measure 3 aspects of UX: loading, interactivity, and visual stability.

---
### 🧰 4. Tool Selection Justification 🧰
|Feature | Description |
|---------|------------|
|**User-centric Metrics** | Clear scoring based on metrics that reflect the actual user experience. |
|**Actionable Diagnostics** | Detailed structure audits, complete with **Impact Levels** (Low, Medium, High) and specific potential savings, allowing for targeted optimization efforts. |
|**Waterfall Chart** | A visual breakdown of every single resource request (CSS, JS, images), crucial for identifying specific slow-loading files. | 

---
### 🚁 5. Test Environment Setup 🚁
|Parameter | Configuration | Justification |
|----------|---------------|---------------|
|**Tested URL** | https://github.com/NurImanShazreen/Individual-Assignment-ITT440.git | The specific target page URL |
|**Test Server Location** | Seattle, WA, USA | Used as the initial baseline test environment. A more representative location is recommended for future tests targeting an Asian audience to account for realistic network latency. |
|**Browser** | Chrome (Version 125.0.0.0) | Standard test browser, reflecting the most common modern user agent. |
|**Connection Speed** | Unthrottled (Simulated) | Measures performance under ideal network conditions to isolate server and code inefficiencies. | 

---
### 📑 6. Methodology 📑
|Step | Description |
|-----|-------------|
|**Baseline test Execution** | The target URL was submitted to GTmetrix with the specified environment settings. |
|**Data Extraction and Categorization** | The resulting report data was systematically extracted and categorized into 3 groups: **Overall Scores, Performance Metrics(Core Web Vitals)** and **Structural Audits**. |
|**Interpretation** | Each metric and audit finding was interpreted against accepted industry thresholds to determine teh grade (**Good, OK, Poor**) and identify the areas requiring the most urgent attention. |

---
### 🌺 7. Performance Data Analysis 🌺
The performance analysis provided the following key results:

<p align="center">
<img width="272" height="77" alt="image" src="https://github.com/user-attachments/assets/9efbad74-ac5b-43c9-a1e7-a54926c308fa">
</p>

 <p align="center">
<img width="299" height="206" alt="image" src="https://github.com/user-attachments/assets/dd630e43-2b5a-469d-8fd5-3416570afed5">
</p>

🎼 **7.1 Overall Scoring** 🎼
|Score/Metric | Value | Interpretation |
|-------------|-------|----------------|
|**Performance Score** | B (86%) | Good performance, but indicates room for optimization to achieve an 'A' grade. |
|**Structure Score** | 92% |Excellent structure and adherence to best practices, suggesting the performance issues are minor and specific. | 
|**Fully Loaded Time** | 2.4s | The total time for the page to completely stop all activity, it is a good overall result. |
|**Total Page Size** | 1.17 MB | A moderate size, dominated by JavaScript (931KB). |
|**Total Page Requests** | 121 | A relatively high number of file requests, which can increase latency overhead. |

<p align="center">
<img width="320" height="81" alt="image" src="https://github.com/user-attachments/assets/e6fc3aac-d537-4393-bb3d-640725c11393">
</p>

🕸️ **7.2 Core Web Vitals (User Experience Metrics)** 🕸️
|Metric | Value | Threshold (GTmetrix Goal) | Status |
|-------|-------|---------------------------|--------|
|**Largest Contenful Paint (LCP)** | 1.1s | &le; 1.2s | Good |
|**Total Blocking Time (TBT)** | 250ms | &le; 150ms | Needs Improvement |
|**Cumulative Layout Shift (CLS)** | 0.01 | &le; 0.1 | Good | 

---
### 🔆 8. Result Interpretation 🔆
Based on the Core Web Vitals, the user experience is generally high, with one major exception:
- **Positive Findings (LCP** and **CLS)** : The **LCP** of 1.1s is within the accepted good range, meaning the main content loads quickly. The **CLS** of 0.01 is nearly perfect, indicating that the page is visually stable with no noticeable layout shifts, which is excellent for usability. 
- **Critical Finding (TBT)** : The **TBT** of 250ms significantly exceeds the 150ms threshold. This indicates that the main thread of the browser is being blocked by excessive or long-running JavaScript execution, making the page unresponsive to user input for a quarter of a second during the critical loading phase. This is the primary issue dragging down the overall Performance Score.

---
<p align="center">
<img width="433" height="163" alt="image" src="https://github.com/user-attachments/assets/2a5392fa-71e7-422d-b5d2-0f48eb5452c3">
</p>

### 🌟 9. Identification of Bottlenecks and Failure Points ⭐
Structural audits highlight the specific causes contributing to the **TBT** issue and other inefficiencies:
|Audit Finding | Impact Level | Failure Detail | Proposed Bottleneck Fix |
|--------------|--------------|----------------|-------------------------|
|Use a Content Delivery Network (CDN) | Med | 106 resources found that could benefit from a CDN. | Implement a robust CDN to serve static assests (CSS, JS, images) closer to users, improving **TTFB** and **FCP**. |
|Avoid an excessive DOM size (TBT) | Med-Low | 1024 elements in the Document Object Model. | Refactor the page structure to reduce unnecessary nesting and overall element count, which reduces the time the browser spends processing the layout. |
|Serve static assests with an efficient cache policy | Med-Low | Potential savings of 1.86KB. | Ensure proper HTTP caching headers (**Cache-Control** and **Expires**) are set for all static resources to allow returning users to load the page faster. |
|Reduce unused CSS (FCP/LCP) | Low | Potential savings of 106KB. | Use tools to identify and remove unused CSS or implement "Critical CSS" to load only the styles necessary for the initial view first. | 
|Remove duplicate modules in JavaScript bundles (TBT) | Low | Potential savings of 102KB. | Investigate the JavaScript bundling process to ensure libraries or modules are not included more than once, directly addressing unnecessary main thread work. |

---
### 🥇 10. Summary 🥇
The GitHub repository page demonstrates an overall **Good(B/86%)** performance, achieving success in loading the main content quickly (LCP: 1.1s) and maintaining visual stability (CLS: 0.01). 

The analysis reveals that the most significant performance degradation stems from **Total Blocking Time (TBT = 250ms)**, driven by excessive JavaScript execution and a high volume of file requests (121). 

Recommended Immediate Action: The most impactful change would be the deployment of a Content Delivery Network (CDN) and optimizing the substantial JavaScript size (931KB) by reducing duplicate modules and ensuring efficient parsing, which will directly reduce the TBT and improve overall responsiveness. 

---
## 🎮 YouTube Demo Link 🎮

https://youtu.be/0NDduWN6uNI?si=gthtvp6aKVEmsTwG
-----
