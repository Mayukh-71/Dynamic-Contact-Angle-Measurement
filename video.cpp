#include "video.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
VideoWriter createVideoWriter(const string& filename,double fps,int width,int height)
{
    VideoWriter writer
    (
        filename,
        VideoWriter::fourcc
        (
            'm',
            'p',
            '4',
            'v'
        ),
        fps,
        Size
        (
            width,
            height
        )
    );
    if(!writer.isOpened())
        cout << "Failed to create video writer" << endl;
    return writer;
}