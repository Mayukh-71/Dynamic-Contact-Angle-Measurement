#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "contour.h"
#include "angle.h"
#include "draw.h"
#include "video.h"
#include "config.h"
using namespace cv;
using namespace std;
int main()
{
    // ==========================================
    // OPEN VIDEO
    // ==========================================
    VideoCapture cap("Input/"+filename+".avi");
    // USE YOUR ACTUAL VALUES
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
    // READ FIRST FRAME
    // ==========================================
    Mat firstFrame;
    if(!cap.read(firstFrame))
    {
        cout << "Cannot read first frame" << endl;
        return -1;
    }
    int width = firstFrame.cols;
    int height = firstFrame.rows;
    // ==========================================
    // CREATE VIDEO WRITER
    // ==========================================
    VideoWriter writer = createVideoWriter(("Output/"+filename+".mp4"),fps,width,height);
    if(!writer.isOpened())
    {
        cout << "Video writer failed" << endl;
        return -1;
    }
    // ==========================================
    // RESET VIDEO
    // ==========================================
    cap.set
    (
        CAP_PROP_POS_FRAMES,
        0
    );
    // ==========================================
    // FRAME LOOP
    // ==========================================
    Mat frame;
    int frameNumber = 0;
    while(cap.read(frame))
    {
        double time = frameNumber/fps;
        vector<Point>droplet = getDropletContour(frame,baseP1,baseP2);
        // ======================================
        // NO CONTACT
        // ======================================
        if(droplet.empty())
        {
            Mat annotated =
            drawAnnotatedFrame
            (
                frame,
                {},
                Point(),
                Point(),
                Point(),
                Vec4f(),
                Vec4f(),
                baseP1,
                baseP2,
                NAN,
                NAN,
                NAN,
                time,
                false
            );
            writer.write(annotated);
            frameNumber++;
            continue;
        }
        // ======================================
        // APEX
        // ======================================
        Point apex = findApex(droplet);
        // ======================================
        // CONTACT POINTS
        // ======================================
        Point leftPoint = findLeftContactPoint(droplet,apex,baseP1,baseP2);
        Point rightPoint = findRightContactPoint(droplet,apex,baseP1,baseP2);
        // ======================================
        // CONTACT FAILURE
        // ======================================
        if(leftPoint.x == -1||rightPoint.x == -1)
        {
            Mat annotated =
            drawAnnotatedFrame
            (
                frame,
                droplet,
                apex,
                Point(),
                Point(),
                Vec4f(),
                Vec4f(),
                baseP1,
                baseP2,
                NAN,
                NAN,
                NAN,
                time,
                false
            );
            writer.write(annotated);
            frameNumber++;
            continue;
        }
        // ======================================
        // TANGENTS
        // ======================================
        Vec4f leftTangent = getLeftTangent(droplet,leftPoint);
        Vec4f rightTangent = getRightTangent(droplet,rightPoint);
        // ======================================
        // BASELINE VECTOR
        // ======================================
        Vec4f baseline(baseP1.x,baseP1.y,baseP2.x,baseP2.y);
        // ======================================
        // ANGLES
        // ======================================
        double leftAngle = calculateLeftContactAngle(leftTangent,leftPoint,rightPoint);
        double rightAngle = calculateRightContactAngle(rightTangent,leftPoint,rightPoint);
        double averageAngle =(leftAngle + rightAngle)/2.0;
        // ======================================
        // ANNOTATED FRAME
        // ======================================
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
            time,
            true
        );
        writer.write(annotated);
        frameNumber++;
        if(frameNumber % 100 == 0)
            cout << "Processed " << frameNumber << " frames" << endl;
    }
    // ==========================================
    // CLEANUP
    // ==========================================
    writer.release();
    cap.release();
    cout << "Saved " + filename + ".mp4" << endl;
    cout << "Processed " << frameNumber << " frames" << endl;
    return 0;
}