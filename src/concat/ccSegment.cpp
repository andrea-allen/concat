#include "ccSegment.h"

void ccSegment::setup(ofMaterial& _material) {
    material = _material;
    showWireframes = false;
    setBoxSize(1, 1, 1);
    setJointRadius(1);
}

void ccSegment::translateToRotationCenter() {
    ofTranslate(0, joint.getRadius());
}

void ccSegment::draw() {
    material.begin();
    ofFill();

    ofPushMatrix();
    drawJoint();
    drawBox();
    drawRotationHandle();
    ofPopMatrix();
    ofTranslate(0, segmentHeight);
    material.end();
}

void ccSegment::setBoxSize(float width, float height, float depth) {
    box.set(width, height, depth);
    halfBoxWidth = width * 0.5;
    halfBoxHeight = height * 0.5;
    calculateSegmentHeight();
}

void ccSegment::setJointRadius(float radius) {
    joint.setRadius(radius);
    calculateSegmentHeight();
}

void ccSegment::toggleWireframes() {
    showWireframes = !showWireframes;
}

void ccSegment::calculateSegmentHeight() {
    segmentHeight = box.getHeight() + joint.getRadius();
}

void ccSegment::drawJoint() {
    ofSetLineWidth(1);

    if (showWireframes) {
        ofSetColor(ofColor::white);
        joint.drawWireframe();
    }
    else {
        ofSetColor(ofColor::grey);
        joint.draw();
    }
}

void ccSegment::drawBox() {
    ofTranslate(0, joint.getRadius() + halfBoxHeight);
    ofSetLineWidth(1);

    if (showWireframes) {
        ofSetColor(ofColor::white);
        box.drawWireframe();
    }
    else {
        ofSetColor(ofColor::grey);
        box.draw();
    }
}

void ccSegment::drawRotationHandle() {
    if (showWireframes) {
        ofSetColor(ofColor::green);
        ofSetLineWidth(2);
        ofDrawLine(halfBoxWidth, 0, box.getWidth(), 0);
    }
}