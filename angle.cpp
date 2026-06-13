#include "angle.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
using namespace cv;
using namespace std;
// =====================================================
// ANGLE BETWEEN TANGENT AND BASELINE
// =====================================================
double angleBetweenLines(Vec4f line1,Vec4f line2)
{
    double vx1 = line1[0];
    double vy1 = line1[1];
    double vx2 = line2[2] - line2[0];
    double vy2 = line2[3] - line2[1];
    double dot = vx1*vx2 + vy1*vy2;
    double mag1 = sqrt(vx1*vx1 + vy1*vy1);
    double mag2 = sqrt(vx2*vx2 + vy2*vy2);
    if(mag1 == 0 || mag2 == 0)
        return 0;
    double cosTheta = dot / (mag1*mag2);
    double angle = acos(cosTheta)*180.0/CV_PI;
    return angle;
}
// =====================================================
// FIND INDEX OF POINT IN CONTOUR
// =====================================================
int findContourIndex(const vector<Point>& contour,const Point& target)
{
    for(int i=0;i<(int)contour.size();i++)
    {
        if(contour[i] == target)
            return i;
    }
    return -1;
}
// =====================================================
// LEFT TANGENT
// =====================================================
Vec4f getLeftTangent(const vector<Point>& droplet,const Point& leftPoint,double radius)
{
    int idx = findContourIndex(droplet,leftPoint);
    if(idx == -1)
        return Vec4f(0,0,leftPoint.x,leftPoint.y);
    vector<Point>localPoints;
    int window = 8;
    int start = max(0,idx-window);
    int end = min((int)droplet.size()-1,idx+window);
    for(int i=start;i<=end;i++)
        localPoints.push_back(droplet[i]);
    Vec4f line;
    fitLine
    (
        localPoints,
        line,
        DIST_L2,
        0,
        0.01,
        0.01
    );
    return line;
}
// =====================================================
// RIGHT TANGENT
// =====================================================
Vec4f getRightTangent(const vector<Point>& droplet,const Point& rightPoint,double radius)
{
    int idx = findContourIndex(droplet,rightPoint);
    if(idx == -1)
        return Vec4f(0,0,rightPoint.x,rightPoint.y);
    vector<Point>localPoints;
    int window = 8;
    int start = max(0,idx-window);
    int end = min((int)droplet.size()-1,idx+window);
    for(int i=start;i<=end;i++)
        localPoints.push_back(droplet[i]);
    Vec4f line;
    fitLine
    (
        localPoints,
        line,
        DIST_L2,
        0,
        0.01,
        0.01
    );
    return line;
}
// =====================================================
// CONTACT ANGLE
// =====================================================
double calculateLeftContactAngle(Vec4f tangent,const Point& leftPoint,const Point& rightPoint)
{
    // Tangent direction
    double vx = tangent[0];
    double vy = tangent[1];
    // Force tangent upward
    // (image coordinates: upward => vy < 0)
    if(vy > 0)
    {
        vx =- vx;
        vy =- vy;
    }
    // Baseline:
    // left contact -> right contact
    double bx = rightPoint.x - leftPoint.x;
    double by = rightPoint.y - leftPoint.y;
    double dot = vx*bx + vy*by;
    double magT = sqrt(vx*vx + vy*vy);
    double magB = sqrt(bx*bx + by*by);
    if(magT == 0 || magB == 0)
        return 0;
    double cosTheta = dot/(magT*magB);
    double angle = acos(cosTheta)*180.0/CV_PI;
    return angle;
}
// =====================================================
// RIGHT CONTACT ANGLE
// =====================================================
double calculateRightContactAngle(Vec4f tangent,const Point& leftPoint,const Point& rightPoint)
{
    // Tangent direction
    double vx = tangent[0];
    double vy = tangent[1];
    // Force tangent upward
    if(vy > 0)
    {
        vx = -vx;
        vy = -vy;
    }
    // Baseline:
    // right contact -> left contact
    double bx = leftPoint.x - rightPoint.x;
    double by = leftPoint.y - rightPoint.y;
    double dot = vx*bx + vy*by;
    double magT = sqrt(vx*vx + vy*vy);
    double magB = sqrt(bx*bx + by*by);
    if(magT == 0 || magB == 0)
        return 0;
    double cosTheta = dot/(magT*magB);
    double angle = acos(cosTheta)*180.0/CV_PI;
    return angle;
}