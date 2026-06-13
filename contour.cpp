#include "contour.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
using namespace cv;
using namespace std;
// =====================================================
// DISTANCE FROM POINT TO LINE
// =====================================================
double pointToLineDistance(Point p,Point a,Point b)
{
    double A = b.y - a.y;
    double B = a.x - b.x;
    double C = b.x*a.y - a.x*b.y;
    return fabs(A*p.x + B*p.y + C)/sqrt(A*A + B*B);
}
// =====================================================
// SELECT DROPLET CONTOUR
// =====================================================
vector<Point>getDropletContour(const Mat& frame,const Point& baseP1,const Point& baseP2)
{
    Mat gray;
    Mat thresh;
    // ==========================================
    // GRAYSCALE
    // ==========================================
    cvtColor
    (
        frame,
        gray,
        COLOR_BGR2GRAY
    );
    // ==========================================
    // THRESHOLD
    // ==========================================
    threshold
    (
        gray,
        thresh,
        80,
        255,
        THRESH_BINARY_INV
    );
    // ==========================================
    // BLUR
    // ==========================================
    GaussianBlur
    (
        thresh,
        thresh,
        Size(5,5),
        0
    );
    // ==========================================
    // MORPHOLOGY
    // ==========================================
    morphologyEx
    (
        thresh,
        thresh,
        MORPH_OPEN,
        getStructuringElement
        (
            MORPH_ELLIPSE,
            Size(3,3)
        )
    );
    // ==========================================
    // DEBUG IMAGE
    // ==========================================
    imwrite
    (
        "threshold_debug.png",
        thresh
    );
    // ==========================================
    // FIND CONTOURS
    // ==========================================
    vector<vector<Point>> contours;
    findContours
    (
        thresh,
        contours,
        RETR_EXTERNAL,
        CHAIN_APPROX_NONE
    );
    // ==========================================
    // SELECT CONTOUR TOUCHING BASELINE
    // ==========================================
    int chosenIndex = -1;
    double tolerance = 8.0;
    for(int i=0;i<(int)contours.size();i++)
    {
        bool touchesBaseline = false;
        for(auto& p : contours[i])
        {
            double dist = pointToLineDistance(p,baseP1,baseP2);
            if(dist < tolerance)
            {
                touchesBaseline = true;
                break;
            }
        }
        if(touchesBaseline)
        {
            chosenIndex = i;
            break;
        }
    }
    // ==========================================
    // NO CONTACT YET
    // ==========================================
    if(chosenIndex == -1)
        return {};
    // ==========================================
    // RETURN CONTOUR
    // ==========================================
    return contours[chosenIndex];
}
// =====================================================
// APEX
// =====================================================
Point findApex(const vector<Point>& droplet)
{
    Point apex = droplet[0];
    for(const auto& p : droplet)
    {
        if(p.y < apex.y)
            apex = p;
    }
    return apex;
}
// =====================================================
// LEFT CONTACT POINT
// =====================================================
Point findLeftContactPoint(const vector<Point>& droplet,const Point& apex,const Point& baseP1,const Point& baseP2,double tolerance)
{
    Point leftPoint(-1,-1);
    for(const auto& p : droplet)
    {
        if(p.x >= apex.x)
            continue;
        double dist = pointToLineDistance(p,baseP1,baseP2);
        if(dist < tolerance)
        {
            if(leftPoint.x == -1||p.x > leftPoint.x)
                leftPoint = p;
        }
    }
    return leftPoint;
}
// =====================================================
// RIGHT CONTACT POINT
// =====================================================
Point findRightContactPoint(const vector<Point>& droplet,const Point& apex,const Point& baseP1,const Point& baseP2,double tolerance)
{
    Point rightPoint(-1,-1);
    for(const auto& p : droplet)
    {
        if(p.x <= apex.x)
            continue;
        double dist = pointToLineDistance(p,baseP1,baseP2);
        if(dist < tolerance)
        {
            if(rightPoint.x == -1||p.x < rightPoint.x)
                rightPoint = p;
        }
    }
    return rightPoint;
}