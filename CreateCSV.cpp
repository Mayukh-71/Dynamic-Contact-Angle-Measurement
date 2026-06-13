#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "contour.h"
#include "angle.h"
#include "types.h"
#include "csv.h"
#include "config.h"
using namespace cv;
using namespace std;
int main()
{
    // ==========================================
    // OPEN VIDEO
    // ==========================================
    VideoCapture cap("Input/" + filename + ".avi");
    // CHANGE THESE TO YOUR
    // EXPERIMENTAL VALUES
    if(!cap.isOpened())
    {
        cout << "Cannot open video" << endl;
        return -1;
    }
    // ==========================================
    // FPS
    // ==========================================
    double fps = cap.get(CAP_PROP_FPS);
    cout << "FPS = " << fps << endl;
    // ==========================================
    // STORAGE
    // ==========================================
    vector<Measurement>results;
    // ==========================================
    // FRAME LOOP
    // ==========================================
    Mat frame;
    int frameNumber = 0;
    while(cap.read(frame))
    {
        double time = frameNumber/fps;
        Measurement m;
        m.time = time;
        // ==========================
        // DROPLET CONTOUR
        // ==========================
        vector<Point>droplet = getDropletContour(frame,baseP1,baseP2);
        // ==========================
        // NO CONTACT
        // ==========================
        if(droplet.empty())
        {
            m.leftAngle = NAN;
            m.rightAngle = NAN;
            m.averageAngle = NAN;
            m.hasContact = false;
            results.push_back(m);
            frameNumber++;
            continue;
        }
        // ==========================
        // APEX
        // ==========================
        Point apex = findApex(droplet);
        // ==========================
        // CONTACT POINTS
        // ==========================
        Point leftPoint = findLeftContactPoint(droplet,apex,baseP1,baseP2);
        Point rightPoint = findRightContactPoint(droplet,apex,baseP1,baseP2);
        // ==========================
        // NO CONTACT POINTS
        // ==========================
        if(leftPoint.x == -1||rightPoint.x == -1)
        {
            m.leftAngle = NAN;
            m.rightAngle = NAN;
            m.averageAngle = NAN;
            m.hasContact = false;
            results.push_back(m);
            frameNumber++;
            continue;
        }
        // ==========================
        // TANGENTS
        // ==========================
        Vec4f leftTangent = getLeftTangent(droplet,leftPoint);
        Vec4f rightTangent = getRightTangent(droplet,rightPoint);
        // ==========================
        // BASELINE VECTOR
        // ==========================
        Vec4f baseline
        (
            baseP1.x,
            baseP1.y,
            baseP2.x,
            baseP2.y
        );
        // ==========================
        // ANGLES
        // ==========================
        double leftAngle = calculateLeftContactAngle(leftTangent,leftPoint,rightPoint);
        double rightAngle = calculateRightContactAngle(rightTangent,leftPoint,rightPoint);
        double averageAngle = (leftAngle + rightAngle)/2.0;
        m.leftAngle = leftAngle;
        m.rightAngle = rightAngle;
        m.averageAngle = averageAngle;
        m.hasContact = true;
        results.push_back(m);
        frameNumber++;
    }
    // ==========================================
    // SAVE CSV
    // ==========================================
    saveCSV(("Output/" + filename + ".csv"),results);
    cout << "Processed " << frameNumber << " frames" << endl;
    cout << "Saved "+ filename + ".csv" << endl;
    return 0;
}