#include "draw.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include <iomanip>
using namespace cv;
using namespace std;
Mat drawAnnotatedFrame
(
    const Mat& frame,
    const vector<Point>& droplet,
    const Point& apex,
    const Point& leftPoint,
    const Point& rightPoint,
    const Vec4f& leftTangent,
    const Vec4f& rightTangent,
    const Point& baseP1,
    const Point& baseP2,
    double leftAngle,
    double rightAngle,
    double averageAngle,
    double time,
    bool hasContact
)
{
    Mat output = frame.clone();
    // =====================================================
    // DRAW CONTOUR
    // =====================================================
    if(!droplet.empty())
    {
        drawContours
        (
            output,
            vector<vector<Point>>{droplet},
            -1,
            Scalar(0,255,0),
            2
        );
    }
    // =====================================================
    // BASELINE
    // =====================================================
    line
    (
        output,
        baseP1,
        baseP2,
        Scalar(255,0,0),
        2
    );
    // =====================================================
    // CONTACT VISUALIZATION
    // =====================================================
    if(hasContact)
    {
        // Apex
        circle
        (
            output,
            apex,
            6,
            Scalar(255,255,0),
            -1
        );
        // Contact points
        circle
        (
            output,
            leftPoint,
            7,
            Scalar(0,255,255),
            -1
        );
        circle
        (
            output,
            rightPoint,
            7,
            Scalar(0,255,255),
            -1
        );
        // Left tangent
        Point leftStart
        (
            leftPoint.x - (int)(100 * leftTangent[0]),
            leftPoint.y - (int)(100 * leftTangent[1])
        );
        Point leftEnd
        (
            leftPoint.x + (int)(100 * leftTangent[0]),
            leftPoint.y + (int)(100 * leftTangent[1])
        );
        line
        (
            output,
            leftStart,
            leftEnd,
            Scalar(0,0,255),
            3
        );
        // Right tangent
        Point rightStart
        (
            rightPoint.x - (int)(100 * rightTangent[0]),
            rightPoint.y - (int)(100 * rightTangent[1])
        );
        Point rightEnd
        (
            rightPoint.x + (int)(100 * rightTangent[0]),
            rightPoint.y + (int)(100 * rightTangent[1])
        );
        line
        (
            output,
            rightStart,
            rightEnd,
            Scalar(0,0,255),
            3
        );
    }
    // =====================================================
    // INFORMATION PANEL (TOP LEFT)
    // =====================================================
    rectangle
    (
        output,
        Point(10,10),
        Point(250,110),
        Scalar(0,0,0),
        FILLED
    );
    rectangle
    (
        output,
        Point(10,10),
        Point(250,110),
        Scalar(255,255,255),
        1
    );
    // =====================================================
    // TEXT FORMATTING
    // =====================================================
    stringstream ssLeft;
    stringstream ssRight;
    stringstream ssAvg;
    stringstream ssTime;
    ssLeft << fixed << setprecision(1) << leftAngle;
    ssRight << fixed << setprecision(1) << rightAngle;
    ssAvg << fixed << setprecision(1) << averageAngle;
    ssTime << fixed << setprecision(2) << time;
    // =====================================================
    // CONTACT CASE
    // =====================================================
    if(hasContact)
    {
        putText
        (
            output,
            "Left Angle",
            Point(20,30),
            FONT_HERSHEY_SIMPLEX,
            0.5,
            Scalar(0,0,255),
            1,
            LINE_AA
        );
        putText
        (
            output,
            "= " + ssLeft.str() + " deg",
            Point(120,30),
            FONT_HERSHEY_SIMPLEX,
            0.5,
            Scalar(255,255,255),
            1,
            LINE_AA
        );
        putText
        (
            output,
            "Right Angle",
            Point(20,55),
            FONT_HERSHEY_SIMPLEX,
            0.5,
            Scalar(0,0,255),
            1,
            LINE_AA
        );
        putText
        (
            output,
            "= " + ssRight.str() + " deg",
            Point(120,55),
            FONT_HERSHEY_SIMPLEX,
            0.5,
            Scalar(255,255,255),
            1,
            LINE_AA
        );
        putText
        (
            output,
            "Average",
            Point(20,80),
            FONT_HERSHEY_SIMPLEX,
            0.5,
            Scalar(0,255,255),
            1,
            LINE_AA
        );
        putText
        (
            output,
            "= " + ssAvg.str() + " deg",
            Point(120,80),
            FONT_HERSHEY_SIMPLEX,
            0.5,
            Scalar(255,255,255),
            1,
            LINE_AA
        );
    }
    else
    {
        putText
        (
            output,
            "NO CONTACT",
            Point(20,55),
            FONT_HERSHEY_SIMPLEX,
            0.5,
            Scalar(0,0,255),
            1,
            LINE_AA
        );
    }
    // =====================================================
    // SEPARATOR
    // =====================================================
    line
    (
        output,
        Point(15,90),
        Point(245,90),
        Scalar(255,255,255),
        1
    );
    // =====================================================
    // TIME
    // =====================================================
    putText
    (
        output,
        "Time = " + ssTime.str() + " s",
        Point(20,105),
        FONT_HERSHEY_SIMPLEX,
        0.5,
        Scalar(255,255,255),
        1,
        LINE_AA
    );
    // =====================================================
    // LEGEND BOX (TOP RIGHT)
    // =====================================================
    int legendWidth  = 200;
    int legendHeight = 110;
    int legendX = output.cols - legendWidth - 10;
    int legendY = 10;
    rectangle
    (
        output,
        Point(legendX, legendY),
        Point(legendX + legendWidth,legendY + legendHeight),
        Scalar(0,0,0),
        FILLED
    );
    rectangle
    (
        output,
        Point(legendX, legendY),
        Point(legendX + legendWidth,legendY + legendHeight),
        Scalar(255,255,255),
        1
    );
    // Contour
    line
    (
        output,
        Point(legendX+15, legendY+20),
        Point(legendX+55, legendY+20),
        Scalar(0,255,0),
        2
    );
    putText
    (
        output,
        "Contour",
        Point(legendX+70, legendY+25),
        FONT_HERSHEY_SIMPLEX,
        0.5,
        Scalar(255,255,255),
        1,
        LINE_AA
    );
    // Baseline
    line
    (
        output,
        Point(legendX+15, legendY+40),
        Point(legendX+55, legendY+40),
        Scalar(255,0,0),
        2
    );
    putText
    (
        output,
        "Baseline",
        Point(legendX+70, legendY+45),
        FONT_HERSHEY_SIMPLEX,
        0.5,
        Scalar(255,255,255),
        1,
        LINE_AA
    );
    // Contact Point
    circle
    (
        output,
        Point(legendX+35, legendY+60),
        4,
        Scalar(0,255,255),
        -1
    );
    putText
    (
        output,
        "Contact",
        Point(legendX+70, legendY+65),
        FONT_HERSHEY_SIMPLEX,
        0.5,
        Scalar(255,255,255),
        1,
        LINE_AA
    );
    // Apex
    circle
    (
        output,
        Point(legendX+35, legendY+80),
        4,
        Scalar(255,255,0),
        -1
    );
    putText
    (
        output,
        "Apex",
        Point(legendX+70, legendY+85),
        FONT_HERSHEY_SIMPLEX,
        0.5,
        Scalar(255,255,255),
        1,
        LINE_AA
    );
    // Tangent
    line
    (
        output,
        Point(legendX+15, legendY+100),
        Point(legendX+55, legendY+100),
        Scalar(0,0,255),
        2
    );
    putText
    (
        output,
        "Tangent",
        Point(legendX+70, legendY+105),
        FONT_HERSHEY_SIMPLEX,
        0.5,
        Scalar(255,255,255),
        1,
        LINE_AA
    );
    return output;
}