# FATIN NAZILAH BINTI MOHD NAZLI

# Real-Time Human Pose Estimation Using MediaPipe and OpenCV

## 1. Introduction

Human pose estimation is a computer vision technique that focuses on detecting and tracking key points of the human body, such as the head, arms, and legs, from images or video. These key points, also known as landmarks, can be used to understand human movement and posture.

In recent years, pose estimation has been widely used in various applications including fitness tracking, sports analysis, rehabilitation, animation, and human–computer interaction. With the availability of lightweight frameworks, pose estimation can now be performed in real time using a standard webcam.

This report presents a simple implementation of real-time human pose estimation using **MediaPipe Pose** and **OpenCV** in Python.



## 2. Objectives

The objectives of this project are:

* To capture real-time video using a webcam
* To detect human body landmarks using MediaPipe Pose
* To draw pose landmarks and skeleton connections on video frames
* To display real-time pose estimation results



## 3. Tools and Technologies

The following tools and technologies were used in this project:

### 3.1 Python

Python is used as the main programming language due to its simplicity and strong support for computer vision libraries.

### 3.2 OpenCV

OpenCV is used to:

* Access the webcam
* Process video frames
* Display the output video

### 3.3 MediaPipe Pose

MediaPipe Pose is a machine learning solution developed by Google that provides accurate real-time pose detection with 33 body landmarks.



## 4. System Overview

The system works by capturing video frames from a webcam, processing each frame using the MediaPipe Pose model, and drawing detected body landmarks and connections on the frame. The processed video is then displayed in real time until the user exits the program.



## 5. Methodology

### 5.1 Webcam Initialization

The webcam is initialized using OpenCV to capture live video input.

### 5.2 Frame Processing

Each captured frame is:

* Flipped horizontally for a mirror effect
* Converted from BGR to RGB format for MediaPipe compatibility

### 5.3 Pose Detection

The RGB frame is passed to the MediaPipe Pose model, which detects body landmarks such as shoulders, elbows, hips, knees, and ankles.

### 5.4 Landmark Drawing

If landmarks are detected, they are drawn on the original frame using points and lines to form a pose skeleton.

### 5.5 Display and Termination

The output is displayed in a window and the program terminates when the ESC key is pressed.


## 6. Code Implementation

The pose estimation system is implemented using the following Python code:

```python
import cv2
import mediapipe as mp

mp_pose = mp.solutions.pose
mp_drawing = mp.solutions.drawing_utils
pose = mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5)

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = pose.process(rgb_frame)

    if results.pose_landmarks:
        mp_drawing.draw_landmarks(
            frame,
            results.pose_landmarks,
            mp_pose.POSE_CONNECTIONS,
            mp_drawing.DrawingSpec(color=(0,255,0), thickness=2, circle_radius=3),
            mp_drawing.DrawingSpec(color=(0,0,255), thickness=2)
        )

    cv2.imshow("MediaPipe Pose Estimation", frame)

    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
```


## 7. Results and Discussion

The system successfully detects and tracks human body landmarks in real time using a webcam. The pose skeleton updates smoothly as the user moves, demonstrating effective real-time tracking.

The accuracy of detection is generally high under good lighting conditions. However, rapid movements or partial body visibility may reduce tracking stability.


## 8. Limitations

Some limitations of the system include:

* Reduced accuracy in low-light environments
* Difficulty tracking very fast movements
* Limited performance when the full body is not visible


## 9. Conclusion

In conclusion, this project demonstrates a simple and effective implementation of real-time human pose estimation using MediaPipe and OpenCV. The system is capable of detecting and visualizing human body landmarks using a standard webcam.

This project helps in understanding the fundamentals of pose estimation and computer vision and can be extended for more advanced applications such as exercise repetition counting, posture correction, and motion analysis.

## 10. Video Presentation Link

The video presentation for this project is provided as part of the individual assignment submission. The presentation includes an introduction, code explanation, and live demonstration of the pose estimation system.

Video Presentation Link: https://youtu.be/lHmkIZVWGyM?si=hr5NbM1ri0AMecTd



