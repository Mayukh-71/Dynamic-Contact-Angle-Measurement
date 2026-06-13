# Dynamic Contact Angle Measurement using OpenCV

## Overview

This project automates the measurement of droplet contact angles from video recordings using computer vision techniques implemented in C++ and OpenCV.

The software processes each frame of a droplet video, extracts the droplet contour, identifies the left and right contact points, estimates local tangents at the contact line, and computes the corresponding contact angles. The measured values are exported for further analysis and visualization.

The project was developed to eliminate manual angle measurements and provide a reproducible framework for dynamic wetting studies.

---

## Features

* Automatic droplet contour extraction
* Contact point detection
* Tangent estimation at the contact line
* Left and right contact angle calculation
* Average contact angle computation
* Frame-by-frame video analysis
* CSV export of measurements
* Annotated output video generation
* Debug visualizations for algorithm validation

---

## Methodology

For each video frame:

1. Read and preprocess the image.
2. Extract the droplet contour using OpenCV.
3. Detect the substrate baseline.
4. Identify left and right contact points.
5. Estimate local tangents near each contact point.
6. Compute contact angles relative to the baseline.
7. Save measurements and generate visual outputs.

---

## Repository Structure

```text
.
├── Input/
│   └── Sample input video
│
├── Output/
│   ├── Contact angle data (.csv)
│   ├── Annotated output video
│   └── Result images
│
├── Debugs/
│   ├── Intermediate processing outputs
│   └── Validation visualizations
│
├── CheckDroplet.cpp
├── angle.cpp
├── contour.cpp
├── draw.cpp
├── config.cpp
└── config.h
```

---

## Sample Workflow

Input Video

* Droplet spreading / evaporation video

Processing

* Contour detection
* Contact point localization
* Tangent fitting
* Angle computation

Outputs

* Annotated frames
* Output video
* CSV file containing contact-angle measurements
* Debug visualizations

---

## Sample Results

### Annotated Contact Angle Detection


```markdown
(Output/Height close to the surface.png)
```

### Angle Measurement Data

Example CSV output:

```text
Time,LeftAngle,RightAngle,AverageAngle
0.00,91.4,89.6,90.5
0.04,91.1,89.4,90.2
...
```

### Output Visualization

Place a graph or processed frame here:

```markdown
![Result](Output/Height close to the surface(Image 1).png)
```

---

## Technologies Used

* C++
* OpenCV
* Computational Geometry
* Image Processing
* Video Analysis

---

## Applications

* Surface wettability characterization
* Contact angle measurement
* Droplet dynamics analysis
* Fluid mechanics experiments
* Wetting and spreading studies

---

## Future Improvements

* Automatic baseline detection under varying illumination
* Sub-pixel contact point estimation
* Real-time video processing
* Statistical analysis across multiple experiments
* GUI-based user interface

---

## Author

Mayukh Paul

Indian Institute of Technology Kharagpur

---

## License

This repository is intended for academic, educational, and research purposes.
For reuse or collaboration, please contact the author.
