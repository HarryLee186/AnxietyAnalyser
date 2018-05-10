#include "ofApp.h"
int heartRate;
int newRate;
bool recalculating;

//--------------------------------------------------------------
void ofApp::setup() {

	verdana25.load("verdana.ttf", 25, true, true);
	verdana25.setLineHeight(34.0f);
	verdana25.setLetterSpacing(1.035);

	last = ofGetElapsedTimeMillis();
	col.setHsb(25, 25, 25);
	plotter.setWindowSize(600);
	plotter2.setWindowSize(600);
	int deltaTime = 0;
	int recordTime = 0;

	ofSetLogLevel(OF_LOG_VERBOSE);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
	verdana25.setLetterSpacing(1.0);
	

	ofSetColor(255);
	if (!serial.setup("COM3", 115200)) {
		ofLogError() << "could not open serial port - listing serial devices";
		serial.listDevices();

	}
	
	

}

//--------------------------------------------------------------
void ofApp::update() {
	
	plotter[""] << heartRate;
	plotter2[""] << newRate;

	ofBackground(col);
	if (ofGetElapsedTimeMillis() - last > 50)
	{
		col.setHue(heartRate * 2.0);
		col.setBrightness(heartRate * 1.8);
		//counter++;
		last = ofGetElapsedTimeMillis();
	}
	string incoming = "";
	if (serial.available() < 0) {
		msg = "Arduino Error";

	}
	else {

		while (serial.available() > 0 && ofGetElapsedTimef() > 0) {
			heartRate = serial.readByte();
			msg = "Heart Rate: " + ofToString(heartRate);
			msg1 = "Heart Rate: " + ofToString(heartRate - 5);
			
		}
	}
	cout << "received : " << incoming << '\m';


}
//--------------------------------------------------------------

void ofApp::draw() {
	
	if (ofGetElapsedTimef() <= 10) {
		verdana25.drawString("Welcome to Anxiety Analyser.", 0, ofGetHeight() / 2);
		verdana25.drawString("In a moment, you'll see your heartrate represented below,", 0, ofGetHeight() / 1.75);
		verdana25.drawString("as well as to the left of this message.", 0, ofGetHeight() / 1.65);
		verdana25.drawString("The higher your heart rate, the more cluttered the screen will appear.", 60, ofGetHeight() / 1.5);
		deltaTime = ofGetElapsedTimeMillis() - recordTime;
		if (deltaTime > 1000) {
			record.loadFile("restingrecording.xml");
			record.addValue("record:beatsPerMinute", heartRate);
			record.addValue("record:time", ofGetTimestampString());
			record.saveFile("restingrecording.xml");
			recordTime = ofGetElapsedTimeMillis();
		}
	}
	else if (ofGetElapsedTimef() > 10 & ofGetElapsedTimef() <= 70 & !recalculating) {
		
		realBeat();
		
		
	}
	else  if (ofGetElapsedTimef() > 70 & ofGetElapsedTimef() <= 130 & !recalculating) {
		falseBeat();
		
	}
	else if (ofGetElapsedTimef() > 130 & ofGetElapsedTimef() <= 150 & !recalculating) {
		finishUp();
	}
	else if (ofGetElapsedTimef() > 150 & ofGetElapsedTimef() < 160 & !recalculating) {
		verdana25.drawString("The program can now exit.", 50, 150);
	}



}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
void ofApp::finishUp() {
	verdana25.drawString("Thank you for using Anxiety Analyser. Please wait.", 50, 150);
	deltaTime = ofGetElapsedTimeMillis() - recordTime;
	if (deltaTime > 1000) {
		record.loadFile("finishingrecording.xml");
		record.addValue("record:beatsPerMinute", heartRate);
		record.addValue("record:time", ofGetTimestampString());
		record.saveFile("finishingrecording.xml");
		recordTime = ofGetElapsedTimeMillis();
	}
}
void ofApp::loadQuestions() {


	if (ofGetElapsedTimef() < 20) {
		verdana25.drawString("Think about your most challenging assignment you need to hand in....", 50, 150);
		
	}
	else if (ofGetElapsedTimef() > 20 & ofGetElapsedTimef() < 30) {
		verdana25.drawString("Is the due date soon?", 50, 150);
	
	}
	else if (ofGetElapsedTimef() > 30 & ofGetElapsedTimef() < 40) {
		verdana25.drawString("How far behind are you on it?", 50, 150);
		
	}
	else if (ofGetElapsedTimef() > 40 & ofGetElapsedTimef() < 50) {
		verdana25.drawString("Think about how it would feel to only have 1 hour left to complete it.", 10, 150);
	
	}
	else if (ofGetElapsedTimef() > 50 & ofGetElapsedTimef() < 60) {
		verdana25.drawString("Would you be able to?", 50, 150);
		
	}
	else if (ofGetElapsedTimef() > 60 & ofGetElapsedTimef() < 70) {
		verdana25.drawString("How stressed and anxious would you feel whilst trying to complete it?", 50, 150);

	}
	
}
//--------------------------------------------------------------
void ofApp::realVisualisation() {

	if (heartRate <= 51) {
		ofDrawRectangle(0, 0, 0, 0);
	}
	if (heartRate > 51 && heartRate <= 53) {
		ofDrawRectangle(0, 668, 100, 100);
	}
	if (heartRate > 53 && heartRate <= 55) {
		ofDrawRectangle(130, 668, 100, 100);
	}
	if (heartRate > 54 && heartRate <= 56) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
	}
	if (heartRate > 55 && heartRate <= 57) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
	}
	if (heartRate > 56 && heartRate <= 58) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
	}
	if (heartRate > 57 && heartRate <= 59) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
	}
	if (heartRate > 58 && heartRate <= 60) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
	}
	if (heartRate > 59 && heartRate <= 61) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
	}
	if (heartRate > 60 && heartRate <= 62) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
	}
	if (heartRate > 61 && heartRate <= 63) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);

	}
	if (heartRate > 62 && heartRate <= 64) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
	}
	if (heartRate > 63 && heartRate <= 65) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
	}
	if (heartRate > 64 && heartRate <= 66) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
	}
	if (heartRate > 65 && heartRate <= 67) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
	}
	if (heartRate > 66 && heartRate <= 68) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
	}
	if (heartRate > 67 && heartRate <= 69) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
	}
	if (heartRate > 68 && heartRate <= 70) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
	}
	if (heartRate > 69 && heartRate <= 71) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
	}
	if (heartRate > 70 && heartRate <= 72) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
	}
	if (heartRate > 71 && heartRate <= 73) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
	}
	if (heartRate > 72 && heartRate <= 74) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
	}
	if (heartRate > 74 && heartRate <= 76) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
	}
	if (heartRate > 76 && heartRate <= 78) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
	}
	if (heartRate > 78 && heartRate <= 80) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
	}
	if (heartRate > 80 && heartRate <= 82) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
	}
	if (heartRate > 82 && heartRate <= 85) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
	}

	if (heartRate > 85 && heartRate <= 87) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
	}
	if (heartRate > 87 && heartRate <= 90) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
	}
	if (heartRate > 90 && heartRate <= 93) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
	}
	if (heartRate > 93 && heartRate <= 96) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
	}
	if (heartRate > 96 && heartRate <= 99) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
	}
	if (heartRate > 99 && heartRate <= 102) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
		ofDrawRectangle(700, 668, 100, 100);
	}
	if (heartRate > 102 && heartRate <= 105) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
		ofDrawRectangle(700, 668, 100, 100);
		ofDrawRectangle(830, 668, 100, 100);
	}
	if (heartRate > 105 && heartRate <= 108) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
		ofDrawRectangle(700, 668, 100, 100);
		ofDrawRectangle(830, 668, 100, 100);
		ofDrawRectangle(960, 668, 100, 100);
	}

}

void ofApp::realBeat() {
	loadQuestions();
	plotter.draw(300, 250, 700, 300);
	if (heartRate < 1) {
		msg = "Heart Rate: Recalculating...";
	}
	if (heartRate > 115) {
		msg = "Heart Rate: Recalculating...";
	}
	verdana14.drawString(msg, 50, 100);
	deltaTime = ofGetElapsedTimeMillis() - recordTime;
	if (deltaTime > 1000) {
		record.loadFile("stressrecording.xml");
		record.addValue("record:beatsPerMinute", heartRate);
		record.addValue("record:time", ofGetTimestampString());
		record.saveFile("stressrecording.xml");
		recordTime = ofGetElapsedTimeMillis();
	}
	realVisualisation();
	cout << heartRate << endl;
}
void ofApp::falseBeat() {
	if (heartRate <= 1) {
		msg = "Heart Rate: Recalculating...";
	}
	if (heartRate > 115) {
		msg = "Heart Rate: Recalculating...";
	}
	


	plotter.draw(300, 250, 700, 300);

	int newRate = heartRate - 5;
	verdana14.drawString(msg1, 50, 100);
	deltaTime = ofGetElapsedTimeMillis() - recordTime;
	if (deltaTime > 1000) {
		record.loadFile("visualrecording.xml");
		record.addValue("record:beatsPerMinute", heartRate);
		record.addValue("record:time", ofGetTimestampString());
		record.saveFile("visualrecording.xml");
		recordTime = ofGetElapsedTimeMillis();
	}
	falseVisualisation();

	//printing heartRate into console.
	cout << heartRate << endl;
	cout << newRate << endl;

}
void ofApp::falseVisualisation() {
	int newRate = heartRate - 5;
	if (newRate <= 51) {
		ofDrawRectangle(0, 0, 0, 0);
	}
	if (newRate > 51 && newRate <= 53) {
		ofDrawRectangle(0, 668, 100, 100);
	}
	if (newRate > 53 && newRate <= 55) {
		ofDrawRectangle(130, 668, 100, 100);
	}
	if (newRate > 54 && newRate <= 56) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
	}
	if (newRate > 55 && newRate <= 57) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
	}
	if (newRate > 56 && newRate <= 58) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
	}
	if (newRate > 57 && newRate <= 59) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
	}
	if (newRate > 58 && newRate <= 60) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
	}
	if (newRate > 59 && newRate <= 61) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
	}
	if (newRate > 60 && newRate <= 62) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
	}
	if (newRate > 61 && newRate <= 63) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);

	}
	if (newRate > 62 && newRate <= 64) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
	}
	if (newRate > 63 && newRate <= 65) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
	}
	if (newRate > 64 && newRate <= 66) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
	}
	if (newRate > 65 && newRate <= 67) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
	}
	if (newRate > 66 && newRate <= 68) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
	}
	if (newRate > 67 && newRate <= 69) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
	}
	if (newRate > 68 && newRate <= 70) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
	}
	if (newRate > 69 && newRate <= 71) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
	}
	if (newRate > 70 && newRate <= 72) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
	}
	if (newRate > 71 && newRate <= 73) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
	}
	if (newRate > 72 && newRate <= 74) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
	}
	if (newRate > 74 && newRate <= 76) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
	}
	if (newRate > 76 && newRate <= 78) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
	}
	if (newRate > 78 && newRate <= 80) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
	}
	if (newRate > 80 && newRate <= 82) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
	}
	if (newRate > 82 && newRate <= 85) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
	}

	if (newRate > 85 && newRate <= 87) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
	}
	if (newRate > 87 && newRate <= 90) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
	}
	if (newRate > 90 && newRate <= 93) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
	}
	if (newRate > 93 && newRate <= 96) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
	}
	if (newRate > 96 && newRate <= 99) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
	}
	if (newRate > 99 && newRate <= 102) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
		ofDrawRectangle(700, 668, 100, 100);
	}
	if (newRate > 102 && newRate <= 105) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
		ofDrawRectangle(700, 668, 100, 100);
		ofDrawRectangle(830, 668, 100, 100);
	}
	if (newRate > 105 && newRate <= 108) {
		ofDrawRectangle(0, 668, 100, 100);
		ofDrawRectangle(130, 668, 100, 100);
		ofDrawRectangle(260, 668, 100, 100);
		ofDrawRectangle(390, 668, 100, 100);
		ofDrawRectangle(520, 668, 100, 100);
		ofDrawRectangle(650, 668, 100, 100);
		ofDrawRectangle(780, 668, 100, 100);
		ofDrawRectangle(910, 668, 100, 100);
		ofDrawRectangle(65, 568, 100, 100);
		ofDrawRectangle(195, 568, 100, 100);
		ofDrawRectangle(325, 568, 100, 100);
		ofDrawRectangle(455, 568, 100, 100);
		ofDrawRectangle(585, 568, 100, 100);
		ofDrawRectangle(715, 568, 100, 100);
		ofDrawRectangle(845, 568, 100, 100);
		ofDrawRectangle(975, 568, 100, 100);
		ofDrawRectangle(0, 468, 100, 100);
		ofDrawRectangle(130, 468, 100, 100);
		ofDrawRectangle(260, 468, 100, 100);
		ofDrawRectangle(390, 468, 100, 100);
		ofDrawRectangle(520, 468, 100, 100);
		ofDrawRectangle(650, 468, 100, 100);
		ofDrawRectangle(780, 468, 100, 100);
		ofDrawRectangle(910, 468, 100, 100);
		ofDrawRectangle(50, 668, 100, 100);
		ofDrawRectangle(180, 668, 100, 100);
		ofDrawRectangle(310, 668, 100, 100);
		ofDrawRectangle(440, 668, 100, 100);
		ofDrawRectangle(570, 668, 100, 100);
		ofDrawRectangle(700, 668, 100, 100);
		ofDrawRectangle(830, 668, 100, 100);
		ofDrawRectangle(960, 668, 100, 100);
	}

}
