#ifndef DRAW_H
#define DRAW_H
#include <opencv2/opencv.hpp>
#include <vector>
cv::Mat drawAnnotatedFrame
(
    const cv::Mat& frame,
    const std::vector<cv::Point>& droplet,
    const cv::Point& apex,
    const cv::Point& leftPoint,
    const cv::Point& rightPoint,
    const cv::Vec4f& leftTangent,
    const cv::Vec4f& rightTangent,
    const cv::Point& baseP1,
    const cv::Point& baseP2,
    double leftAngle,
    double rightAngle,
    double averageAngle,
    double time,
    bool hasContact
);
#endif