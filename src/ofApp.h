#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    public:
    void setup();
    void update();
    void draw();
    void drawLine();
    void setCoordinateSystem();

    int armSegmentLength, halfArmSegmentLength;
    int rotationHandleLength;
};
