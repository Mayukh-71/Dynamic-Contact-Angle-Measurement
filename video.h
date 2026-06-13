#ifndef VIDEO_H
#define VIDEO_H
#include <opencv2/opencv.hpp>
#include <string>
cv::VideoWriter createVideoWriter(const std::string& filename,double fps,int width,int height);
#endif