#ifndef TYPES_H
#define TYPES_H
struct Measurement
{
    // Time from beginning of video
    double time;
    // Contact angles
    double leftAngle;
    double rightAngle;
    double averageAngle;
    // Contact status
    bool hasContact;
};
#endif