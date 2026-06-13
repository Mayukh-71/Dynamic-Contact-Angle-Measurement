# Dynamic Contact Angle Measurement using Computer Vision

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![OpenCV](https://img.shields.io/badge/OpenCV-4.x-green)
![Platform](https://img.shields.io/badge/Platform-Windows%207%20-lightgrey)

A computer vision based system for **automatic dynamic contact angle measurement** from droplet videos using custom BaseLine.

The software processes experimental droplet videos, extracts the droplet contour, detects contact points with BaseLine and Contour, fits local tangents, calculates left and right contact angles, generates annotated videos, and exports time-resolved contact angle data for scientific analysis.

---

## Project Overview

Contact angle is one of the most important parameters used to characterize:

- Surface wettability
- Hydrophilicity and hydrophobicity
- Droplet spreading
- Surface energy
- Coating performance
- Microfluidic systems
- Heat transfer applications

Traditionally, contact angle measurements are performed manually, which is time-consuming and prone to human error.

This project automates the entire workflow using OpenCV and C++.

---

## Features

✔ Automatic droplet contour extraction

✔ Contact point detection

✔ Local tangent fitting using OpenCV `fitLine()`

✔ Dynamic contact angle measurement

✔ Left and right angle computation

✔ Average contact angle calculation

✔ Time-resolved analysis

✔ CSV data export

✔ Annotated image generation

✔ Annotated video generation

✔ Modular architecture

---

## Processing Pipeline

```text
Input Video
      │
      ▼
Frame Extraction
      │
      ▼
Contour Detection
      │
      ▼
Contact Point Detection
      │
      ▼
Local Tangent Estimation
      │
      ▼
Contact Angle Calculation
      │
      ▼
CSV Export
      │
      ▼
Annotated Video Generation
```

---

## Example Output

### Original Frame

```text
Droplet resting on substrate
```

### Processed Frame

![Result](Output/Height%20close%20to%20the%20surface(Image%201).png)

Features displayed:

- Droplet contour
- Baseline
- Contact points
- Apex
- Tangents
- Left contact angle
- Right contact angle
- Average contact angle
- Time stamp

---

## Repository Structure

```text
DynamicContactAngleMeasurement/

│
├── Input/
│   └── droplet.avi
│
├── Output/
│   ├── droplet.png
│   ├── results.csv
│   ├── annotated_video.mp4
│   └── average_angle_vs_time.png
│
├── config.h
├── config.cpp
│
├── contour.h
├── contour.cpp
│
├── angle.h
├── angle.cpp
│
├── draw.h
├── draw.cpp
│
├── csv.h
├── csv.cpp
│
├── video.h
├── video.cpp
│
├── CheckDroplet.cpp
├── CreateVideo.cpp
├── CreateCSV.cpp
├── PlotGraph.py
│
└── README.md
```

---

# Module Description

---

## config.h / config.cpp

Stores experiment-specific configuration.

### Parameters

- Input video filename
- Baseline coordinates
- Test frame number
- Future experiment settings

Example:

```cpp
CONFIG.filename
CONFIG.baseP1
CONFIG.baseP2
CONFIG.testFrame
```

This allows all programs to use a common configuration file.

---

## contour.h / contour.cpp

Responsible for droplet extraction.

### Functions

- Binary image generation
- Contour detection
- Largest contour selection
- Droplet contour extraction
- Apex detection
- Contact point detection

Output:

```text
Droplet contour
Apex point
Left contact point
Right contact point
```

---

## angle.h / angle.cpp

Responsible for geometric analysis.

### Functions

#### Tangent Estimation

Uses OpenCV:

```cpp
fitLine()
```

to estimate local tangents around contact points.

#### Contact Angle Calculation

Computes:

- Left contact angle
- Right contact angle
- Average contact angle

using baseline and tangent vectors.

Output:

```text
Left Angle
Right Angle
Average Angle
```

---

## draw.h / draw.cpp

Creates professional visualizations.

### Features

Draws:

- Contour
- Baseline
- Contact points
- Apex
- Tangent lines
- Angle information box
- Legend box
- Time stamp

Output:

```text
Annotated Frame
```

---

## csv.h / csv.cpp

Stores measurement results.

Exports:

```csv
Time,LeftAngle,RightAngle,AverageAngle
```

for every frame.

Output:

```text
results.csv
```

---

## video.h / video.cpp

Handles video generation.

Creates:

```text
annotated_video.mp4
```

from processed frames.

Uses:

```cpp
cv::VideoWriter
```

for encoding and exporting videos.

---

# Main Programs

---


## CheckDroplet.cpp

Single-frame debugging and validation.

Functions:

- Jump to selected frame
- Verify contour detection
- Verify tangent fitting
- Verify contact angles

Output:

```text
annotated_test.png
```

Useful for debugging and parameter tuning.

---

## CreateVideo.cpp

Video generation pipeline.

Functions:

- Read video
- Generate annotations
- Create output video

Output:

```text
annotated_video.mp4
```

---
## CreateCSV.cpp

Primary processing pipeline.

Functions:

- Read video
- Process all frames
- Compute contact angles
- Save CSV

Output:

```text
results.csv
```

---


# Python Utilities

---

## PlotGraph.py

Creates scientific plots directly from exported CSV files.

Generates:

```text
Average Contact Angle vs Time
```

and can be extended for:

- Left angle vs time
- Right angle vs time
- Comparative plots
- Statistical analysis

Output:

```text
average_angle_vs_time.png
```

---

# Installation

## Dependencies

### OpenCV

Install OpenCV 4.x

### Compiler

- GCC
- MinGW
- MSYS2

C++17 or later is required.

---

# Build

```bash
g++ CheckDroplet.cpp contour.cpp angle.cpp draw.cpp config.cpp \-std=c++17 -o contact_angle.exe $(pkg-config --cflags --libs opencv4)
g++ CreateVideo.cpp contour.cpp angle.cpp draw.cpp video.cpp config.cpp \-std=c++17 -o contact_angle.exe $(pkg-config --cflags --libs opencv4)
g++ CreateCSV.cpp contour.cpp angle.cpp csv.cpp config.cpp \-std=c++17 -o contact_angle.exe $(pkg-config --cflags --libs opencv4)
```

---

# Usage

Place the video inside:

```text
Input/
```

Configure:

```cpp
CONFIG.filename /(The name of the input video)
CONFIG.outputname /(The name of the CheckDroplet output image)
CONFIG.baseP1 /(The initial point of BaseLine)
CONFIG.baseP2 /(The final point of Baseline)
CONFIG.testFrame /(The frame of the input video at which the CheckDroplet image is generated)
PlotGraph.filename /(The name of the input video)
PlotGraph.start_row /(The starting point of graph)
PlotGraph.end_row /(The end point of graph)
```

Run:

```bash
./contact_angle.exe
```

Generated outputs:

```text
Output/
├── "outputname".png /(CheckDroplet.cpp)
├── "filename".mp4 /(CreateVideo.cpp)
├── "filename".csv /(CreateCSV.cpp)
└── "filename".png /(PlotGraph.py)
```

---

# Applications

- Wettability analysis
- Surface engineering
- Heat transfer research
- Coating characterization
- Energy systems
- Droplet dynamics
- Microfluidics
- Materials science

---

# Future Improvements

- Automatic baseline detection
- Dynamic graph overlay in video
- GUI application
- Batch video processing
- Machine learning assisted contour detection
- Real-time camera support
- Multi-droplet tracking

---

# Author

Mayukh Paul  
Indian Institute of Technology Kharagpur

Project developed for automated dynamic contact angle analysis using OpenCV and C++.
