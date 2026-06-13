#ifndef ANGLE_H
#define ANGLE_H
#include <opencv2/opencv.hpp>
#include <vector>
// =====================================================
// ANGLE BETWEEN TWO LINES
// =====================================================
double angleBetweenLines(cv::Vec4f line1,cv::Vec4f line2);
// =====================================================
// LEFT TANGENT USING fitLine()
// =====================================================
cv::Vec4f getLeftTangent(const std::vector<cv::Point>& droplet,const cv::Point& leftPoint,double radius = 25.0);
// =====================================================
// RIGHT TANGENT USING fitLine()
// =====================================================
cv::Vec4f getRightTangent(const std::vector<cv::Point>& droplet,const cv::Point& rightPoint,double radius = 25.0);
// =====================================================
// CONTACT ANGLE
// =====================================================
double calculateLeftContactAngle(cv::Vec4f tangent,const cv::Point& leftPoint,const cv::Point& rightPoint);
double calculateRightContactAngle(cv::Vec4f tangent,const cv::Point& leftPoint,const cv::Point& rightPoint);
#endif