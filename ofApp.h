#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxPlotter.h"
#include "ofxParticleSystem.h"




class ofApp : public ofBaseApp {
	
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void loadQuestions();
	void falseBeat();
	void realBeat();
	void realVisualisation();
	void falseVisualisation();
	void finishUp();
	int deltaTime;
	int recordTime;
	string msg;
	string msg1;
	ofTrueTypeFont font;
	ofSerial serial;
	ofTrueTypeFont	verdana14;
	ofTrueTypeFont verdana25;
	ofSoundPlayer   music;
	ofxXmlSettings record;
	unsigned long last;
	int counter;
	ofColor col;
	ofxPlotter plotter, plotter2;
	ofPath Rectangle;
	ofxParticleSystem particleSystem, particleSystem1;

};
