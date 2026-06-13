#ifndef CONTOUR_H
#define CONTOUR_H
#include <opencv2/opencv.hpp>
#include <vector>
// =====================================================
// SELECT DROPLET CONTOUR
//
// Returns the contour that touches
// the substrate baseline.
// =====================================================
std::vector<cv::Point>getDropletContour(const cv::Mat& frame,const cv::Point& baseP1,const cv::Point& baseP2);
// =====================================================
// DISTANCE OF POINT FROM BASELINE
// =====================================================
double pointToLineDistance(cv::Point p,cv::Point a,cv::Point b);
// =====================================================
// APEX
//
// Highest point of droplet contour.
// =====================================================
cv::Point findApex(const std::vector<cv::Point>& droplet);
// =====================================================
// LEFT CONTACT POINT
// =====================================================
cv::Point findLeftContactPoint(const std::vector<cv::Point>& droplet,const cv::Point& apex,const cv::Point& baseP1,const cv::Point& baseP2,double tolerance = 5.0);
// =====================================================
// RIGHT CONTACT POINT
// =====================================================
cv::Point findRightContactPoint(const std::vector<cv::Point>& droplet,const cv::Point& apex,const cv::Point& baseP1,const cv::Point& baseP2,double tolerance = 5.0);
#endif