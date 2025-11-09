# Web Application Soak Testing with Vegeta 🔥  
![image placeholder]

---

## 📋 Assignment Details  
**Course**: ITT440  
**Name**: Muhammad Zul Aiman Bin Mohd Adnan  
**Matrix Number**: 2024783699  
**YouTube Video**: [Click Here!](#)

---

## 📱 Introduction  
This project demonstrates a 30-second soak test on **JokeAPI** using the **Vegeta load testing tool**. Soak testing helps identify performance degradation, memory leaks, and stability issues under sustained load over an extended period.

---

## ⚙️ Test Environment & Methodology  

### 🔧 Test Setup  
- **Tool**: Vegeta v12.12.0  
- **Rate**: 50 requests/sec  
- **Test Duration**: 30 seconds  
- **Test Type**: Soak Test (Reliability Test)  
- **Target Website**: [JokeAPI](https://v2.jokeapi.dev/joke/Any)  
- **Total Requests**: 1500  

### 📊 Metrics Tracked  
- Requests  
- Latencies  
- Success rate  
- Status Code  
- Error Set  

---

## ⏱ Test Execution  

### 🧪 Vegeta Command  
```bash
vegeta attack -targets=targets.txt -rate=50 -duration=30s > results.bin
vegeta report < results.bin
vegeta report -type=json < results.bin > jokeapi_metrics.json
vegeta report -type=plot < results.bin





✅ Conclusion
This soak test successfully validated JokeAPI’s ability to maintain stability and performance under sustained load, providing high confidence for production integration and user-facing applications.
