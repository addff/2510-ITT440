# NAME : MUHAMMAD DANISH AFIQ BIN SOFIAN
# ID   : 2024257838
# GROUP: M3CS2554A

---

# 🧩 Web Application (Performance Test) Using Google Lighthouse

---

## 🏷️ Title & Introduction

### **Title:**  
**Web Application Overall Performance Testing of Epic Games Store**

### **Introduction:**  
Web application performance testing is the process of testing the behavior of a web application under all sorts of conditions, focusing on speed, responsiveness, and overall user experience. The tests are meant to ensure that the web app can load quickly, work efficiently, and maintain consistency across all devices, browsers, and network conditions.

The main tool for performing tests on the web app's performance will be Google Lighthouse in this assessment. Lighthouse automatically audits web pages, allowing you to get measurable scores in categories including Performance, Accessibility, Best Practices, and SEO. Results will let developers understand how their web application currently performs and give them recommendations on what to implement to speed things up.

---

## 🛠️ Tools Selection
Tool selected for this project is Google Lighthouse. It is a built-in app testing tools which can be use on many browser which in this project is Google Chrome. Google lighthouse is a performance auditing tool that checks how well a web app performs for one use, in a one browser session that is on one device.

---

## 🎯 Target Website
The targeted website to perform performance testing for this project is Epic Games Store which is a website for gamers to look and buy for games. This website is chosen because there are many statements from gamers said that Epic Games software and website performs badly. Furthermore, this project could prove are the statements from the gamers are true.

---

## Objectives
This project aims to :
- Assess the overall performance of the web application using measurable metrics such as loading speed, interactivity, and visual stability.
- Identify performance bottlenecks that affect the website’s speed and responsiveness, including large files, unused scripts, or render-blocking resources.
- Evaluate key performance indicators (KPIs) such as First Contentful Paint (FCP), Largest Contentful Paint (LCP), and Total Blocking Time (TBT) to understand the user experience quality.
- Analyze the website’s compliance with web best practices, accessibility standards, and search engine optimization (SEO) guidelines.
- Provide recommendations to improve the website’s performance, aiming to enhance user satisfaction and optimize resource loading.

---

## 🖥️ Setup
| **Category**         | **Details**                                                            |
| -------------------- | ---------------------------------------------------------------------- |
| **Device Type**      | Desktop                                                                |
| **Operating System** | Windows 11 (64-bit)                                                    |
| **Processor (CPU)**  | Intel Core i5 13-gen                                            |
| **Memory (RAM)**     | 12 GB                                                                   |
| **Browser**          | Google Chrome                                    |
| **Testing Tool**     | Google Lighthouse (via Chrome DevTools)                                |
| **Connection Type**  | Simulated 4G network (default Lighthouse throttling)                   |
| **Test Mode**        | Desktop mode                                                           |
| **Target Website**   | [https://store.epicgames.com/en-US](https://store.epicgames.com/en-US) |

---

## 📊 Test Result
Lighthouse Results Summary
| **Category**   | **Score (0–100)** |
| -------------- | ----------------- |
| Performance    | 34                |
| Accessibility  | 95                |
| Best Practices | 74                |
| SEO            | 100               |
<img width="1916" height="968" alt="image" src="https://github.com/user-attachments/assets/28f80d6c-17b6-46b0-806e-0ecfcedfb36b" />


---

## 🔍 Results Analysis

Based on the Lighthouse audit, the Epic Games Store achieved the following scores:

| Category | Score |
|-----------|--------|
| Performance | 34 |
| Accessibility | 95 |
| Best Practices | 74 |
| SEO | 100 |

<img width="1915" height="972" alt="image" src="https://github.com/user-attachments/assets/5763c646-f906-4517-abaa-f3478ecc7c98" />
<img width="1918" height="968" alt="image" src="https://github.com/user-attachments/assets/8ca411f2-ca62-406d-ae83-bdddcc1b0a1a" />

The **Performance** score of 34 indicates that the website loads slowly and contains several optimization issues. Lighthouse identified the following bottlenecks:

- **Large JavaScript bundles** increasing page load time.
- **Render-blocking resources** delaying first contentful paint.
- **High image size** without efficient compression.
- **Third-party scripts** (such as trackers or ads) affecting load speed.
- **Long Total Blocking Time (TBT)** due to complex client-side scripts.

<img width="693" height="523" alt="image" src="https://github.com/user-attachments/assets/a994fbd8-1779-45b5-82ad-7c88e5937529" />
<img width="687" height="378" alt="image" src="https://github.com/user-attachments/assets/71b4fbe3-40af-4b0f-8ac5-df0dfa5b3063" />
<img width="692" height="467" alt="image" src="https://github.com/user-attachments/assets/c2b9dd08-8ba0-42a4-8f32-29f862868169" />


In contrast, the website performed very well in:
- **Accessibility (95)** – good color contrast, proper ARIA labels, and structured HTML.
- **Best Practices (74)** – secure HTTPS usage, no vulnerable libraries.
- **SEO (100)** – strong metadata and mobile-friendly design.

---

## 💡 Findings and Discussion

The results show that while the Epic Games Store website is well-optimized for SEO and accessibility, it struggles with performance efficiency. 
A performance score of 34 suggests that users on slower networks or older devices may experience delays in loading the home page.

Lighthouse traces reveal that most delays occur during the *rendering phase*, largely due to heavy scripts and large image files.
Improving these bottlenecks can significantly enhance user satisfaction and retention.

---

## 🛠️ Recommendations for Improvement

To improve the overall performance score, the following steps are recommended:

1. **Optimize Images** – Compress images using modern formats like WebP.
2. **Minify and Bundle JavaScript/CSS** – Reduce file size and load time.
3. **Implement Lazy Loading** – Load images and videos only when visible on screen.
4. **Reduce Third-Party Scripts** – Remove unused analytics or ad scripts.
5. **Use a Content Delivery Network (CDN)** – Deliver static resources faster.
6. **Cache Static Assets** – Enable browser caching to improve repeat visits.
7. **Monitor Core Web Vitals** – Improve LCP (Largest Contentful Paint) and TBT (Total Blocking Time).

---

## 🏁 Conclusion

The Lighthouse performance test provided valuable insights into the loading efficiency and optimization level of the Epic Games Store website. 
Although the site demonstrates excellent accessibility, SEO, and best practice compliance, its performance can still be improved through image optimization, script management, and caching strategies.

Overall, this assessment demonstrates how web performance testing using Google Lighthouse helps developers identify bottlenecks and plan effective optimization strategies for better user experience.

---

## 📚 References

- Google Lighthouse Documentation: https://developer.chrome.com/docs/lighthouse
- Web.dev Performance Metrics: https://web.dev/performance-scoring/
- Epic Games Store: https://store.epicgames.com/en-US


