#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "contour.h"
#include "angle.h"
#include "draw.h"
#include "config.h"
using namespace cv;
using namespace std;
int main()
{
    // ==========================================
    // OPEN VIDEO
    // ==========================================
    VideoCapture cap("Input/"+filename+".avi");
    // USE YOUR ACTUAL BASELINE
    if(!cap.isOpened())
    {
        cout << "Cannot open video" << endl;
        return -1;
    }
    // ==========================================
    // FPS
    // ==========================================
    double fps = cap.get(CAP_PROP_FPS);
    cout<<"FPS = "<< fps << endl;
    // ==========================================
    // JUMP TO TEST FRAME
    // ==========================================
    cap.set
    (
        CAP_PROP_POS_FRAMES,
        testFrame
    );
    Mat frame;
    if(!cap.read(frame))
    {
        cout << "Cannot read frame" << endl;
        return -1;
    }
    // ==========================================
    // CONTOUR
    // ==========================================
    vector<Point>droplet = getDropletContour(frame,baseP1,baseP2);
    if(droplet.empty())
    {
        cout << "No droplet found" << endl;
        return -1;
    }
    // ==========================================
    // APEX
    // ==========================================
    Point apex = findApex(droplet);
    // ==========================================
    // CONTACT POINTS
    // ==========================================
    Point leftPoint = findLeftContactPoint(droplet,apex,baseP1,baseP2);
    Point rightPoint = findRightContactPoint(droplet,apex,baseP1,baseP2);
    if(leftPoint.x == -1||rightPoint.x == -1)
    {
        cout << "No contact points found" << endl;
        return -1;
    }
    // ==========================================
    // TANGENTS
    // ==========================================
    Vec4f leftTangent = getLeftTangent(droplet,leftPoint);
    Vec4f rightTangent = getRightTangent(droplet,rightPoint);
    // ==========================================
    // BASELINE VECTOR
    // ==========================================
    Vec4f baseline(baseP1.x,baseP1.y,baseP2.x,baseP2.y);
    // ==========================================
    // ANGLES
    // ==========================================
    double leftAngle = calculateLeftContactAngle(leftTangent,leftPoint,rightPoint);
    double rightAngle = calculateRightContactAngle(rightTangent,leftPoint,rightPoint);
    double averageAngle = (leftAngle + rightAngle)/2.0;
    cout << "Left Angle = " << leftAngle << endl;
    cout << "Right Angle = " << rightAngle << endl;
    cout << "Average Angle = " << averageAngle << endl;
    // ==========================================
    // ANNOTATED FRAME
    // ==========================================
    Mat annotated = 
    drawAnnotatedFrame
    (
        frame,
        droplet,
        apex,
        leftPoint,
        rightPoint,
        leftTangent,
        rightTangent,
        baseP1,
        baseP2,
        leftAngle,
        rightAngle,
        averageAngle,
        testFrame/fps,
        true
    );
    // ==========================================
    // SAVE
    // ==========================================
    imwrite
    (
        ("Output/"+outputname+".png"),
        annotated
    );
    cout << "Saved "+ outputname + ".png" << endl;
    return 0;
}