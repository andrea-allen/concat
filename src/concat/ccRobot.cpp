#include "ccRobot.h"

void ccRobot::setup(const vector<vector<float>>& _targetAngles) {
    targetAngles = _targetAngles;
    currentPositionIndex = 0;
	numAngles = 6;

	setupCurrentAngles();
	setupSegments();
    ofEnableDepthTest();
}

void ccRobot::update() {
	if (ofGetFrameNum() % 60 == 0) {
		incrementTargetPosition();
		animateToNewPosition();
	}

	for (int i = 0; i < currentAngles.size(); i++) {
		currentAngles.at(i).update(ofGetLastFrameTime());
	}
}

void ccRobot::draw() {
    ofBackground(ofColor::black);
    ofPushMatrix();
    setCoordinateSystem();
    baseSegment.draw();

    ofRotateYDeg(currentAngles.at(0).getCurrentValue());
    ofRotateZDeg(currentAngles.at(1).getCurrentValue());
    lowerSegment.draw();

    upperSegment.translateToRotationCenter();
    ofRotateZDeg(currentAngles.at(2).getCurrentValue());
    ofRotateYDeg(currentAngles.at(3).getCurrentValue());
    upperSegment.draw();

    headSegment.translateToRotationCenter();
    ofRotateZDeg(currentAngles.at(4).getCurrentValue());
    ofRotateYDeg(currentAngles.at(5).getCurrentValue());
    headSegment.draw();

    ofPopMatrix();
}

void ccRobot::resetAnimation() {
    currentPositionIndex = 0;
}

void ccRobot::toggleWireframes() {
    baseSegment.toggleWireframes();
    lowerSegment.toggleWireframes();
    upperSegment.toggleWireframes();
    headSegment.toggleWireframes();
}

void ccRobot::setupCurrentAngles() {
    ofxAnimatableFloat angle;
    for (int i = 0; i < numAngles; i++) {
        currentAngles.push_back(angle);
        currentAngles.back().setup();
        currentAngles.back().setDuration(1);
        currentAngles.back().setCurve(LINEAR);
        currentAngles.back().reset(targetAngles.at(0).at(i));
    }
}

void ccRobot::setupSegments() {
    material.setShininess(120);
    material.setSpecularColor(ofColor(255, 255, 255, 255));

    baseSegment.setup(material);
    baseSegment.setJointRadius(0);
    baseSegment.setBoxSize(500, 100, 500);

    lowerSegment.setup(material);
    lowerSegment.setJointRadius(100);
    lowerSegment.setBoxSize(90, 360, 90);

    upperSegment.setup(material);
    upperSegment.setJointRadius(50);
    upperSegment.setBoxSize(70, 240, 70);

    headSegment.setup(material);
    headSegment.setJointRadius(35);
    headSegment.setBoxSize(30, 100, 30);
}

void ccRobot::incrementTargetPosition() {
	currentPositionIndex++;
	if (currentPositionIndex >= targetAngles.size()) {
		currentPositionIndex = 0;
	}
}

void ccRobot::animateToNewPosition() {
	for (int i = 0; i < currentAngles.size(); i++) {
		float targetAngle = targetAngles.at(currentPositionIndex).at(i);
		currentAngles.at(i).animateTo(targetAngle);
	}
}

void ccRobot::setCoordinateSystem() {
	ofTranslate(ofGetWidth() * 0.75, ofGetHeight());
	ofRotateZDeg(180);
	ofRotateYDeg(180);
}