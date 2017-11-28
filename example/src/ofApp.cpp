#include "ofApp.h"

/*
 * Settings
 */

/* Audio */
#define OUT_CHANNELS 0
#define IN_CHANNELS 2
#define SAMPLE_RATE ofxVokaturi::SAMPLE_RATE
#define BUFFER_SIZE 256
#define NUM_BUFFERS 4

//--------------------------------------------------------------
void ofApp::setup(){
	soundStream.printDeviceList();
	soundStream.setup(this, OUT_CHANNELS, IN_CHANNELS, SAMPLE_RATE, BUFFER_SIZE, NUM_BUFFERS);

	ofBackground(53, 53, 53);
}

//--------------------------------------------------------------
void ofApp::update(){
	valid = vokaturi.isValid();
	if(valid)
		emotions = vokaturi.getEmotions();
}

//--------------------------------------------------------------

#define DRAW_EMO(__emo, y)						\
	ofDrawBitmapString(#__emo + ofToString(": ")			\
		+ ofToString(emotions.__emo, 4), 4, (1 + y) * 18)

void ofApp::draw(){
	ofDrawBitmapString(ofToString("VOKATURI STATUS: ")
		+ (valid ? "VALID" : "NOT VALID"), 4, 18);
	DRAW_EMO(neutrality, 1);
	DRAW_EMO(happiness, 2);
	DRAW_EMO(sadness, 3);
	DRAW_EMO(anger, 4);
	DRAW_EMO(fear, 5);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input)
{
	vokaturi.record(input.getBuffer());
}
