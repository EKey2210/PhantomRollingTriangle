#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
//    ofEnableDepthTest();
//    ofEnableSmoothing();
    
    for(int i = 0; i < this->shapeNum; i++){
        this->positions[i] = vec2(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
        this->colors[i] = vec3(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0));
        this->velocityX[i] = ofRandom(2,10);
        this->radius[i] = ofRandom(0.005,0.01);
    }
    this->current.allocate(ofGetWidth(),ofGetHeight());
    this->shader.load("Vertex.vert","Fragment.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < this->shapeNum; i++){
        this->positions[i].x -= this->velocityX[i];
        if(this->positions[i].x < -50.0){
            this->positions[i].x = ofGetWidth()+50.0;
            this->positions[i].y = ofRandom(ofGetHeight());
            this->velocityX[i] = ofRandom(2,10);
            this->radius[i] = ofRandom(0.005,0.01);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(255);
//    for(int i = 0; i < this->shapeNum; i++){
//        ofDrawEllipse(this->positions[i], 20, 20);
//    }
    
    this->current.begin();
    
    this->shader.begin();
    this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    this->shader.setUniform1f("time",ofGetElapsedTimef());
    this->shader.setUniform2fv("positions", &this->positions[0].x,this->shapeNum);
    this->shader.setUniform3fv("colors", &this->colors[0].x,this->shapeNum);
    this->shader.setUniform1fv("velocity", &this->velocityX[0],this->shapeNum);
    this->shader.setUniform1fv("radius", &this->radius[0],this->shapeNum);
    this->shader.setUniformTexture("fbo", this->current.getTexture(), 1);
    
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    this->shader.end();
    this->current.end();
    
    this->current.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
