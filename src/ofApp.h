#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include <string>

using namespace ofxCv;
using namespace cv;

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        void buttonBoxClicked();
        void buttonGaussianClicked();
        void buttonMedianClicked();
        void gaussianClicked();
        void saltPepperClicked();
        void einsteinClicked();
        void updateImage();
    
        ofImage im;
        ofxPanel gui;
        ofxPanel guiPhoto;
        ofxIntSlider brushSize;
        ofxButton saltPepper;
        ofxButton einstein;
        ofxButton gaussian;
        ofxButton buttonBox;
        ofxButton buttonGaussian;
        ofxButton buttonMedian;
        Mat mat;
        int mode;
        string photo;
};
