#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
    dataParser.setup();
    robot.setup(dataParser.getTargetAngles());
    lighting.setup();

	smallFont.loadFont("selena.otf", 16);
	largeFont.loadFont("selena.otf", 48);
	kinect.setup(12345, smallFont);
	skeletons = kinect.getSkeletons();
	renderer.setup(skeletons, largeFont);
}

void ofApp::update(){
	kinect.update();
    robot.update();
    lighting.update();
}

void ofApp::draw(){
    ofBackground(ofColor::black);
    robot.draw();
    lighting.draw();

	//kinect.drawDebug();
	renderer.draw();
}

void ofApp::keyPressed(int key){
    if (key == 'r') {
        robot.resetAnimation();
    } else if (key == 'w') {
        robot.toggleWireframes();
        lighting.toggleLighting();
    } else if (key == 'l') {
        lighting.toggleLightPositions();
    }
}
