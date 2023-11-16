#include "ofApp.h"
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("Filter:");
    gui.add(brushSize.setup("Brush size", 10, 1, 20));
    gui.add(buttonBox.setup("Box Filter"));
    gui.add(buttonGaussian.setup("Gaussian Filter"));
    gui.add(buttonMedian.setup("Median Filter"));
    
    guiPhoto.setup("Photo:");
    guiPhoto.add(gaussian.setup("Gaussian Noise"));
    guiPhoto.add(saltPepper.setup("Salt and Pepper Noise"));
    guiPhoto.add(einstein.setup("Einstein"));
    
    gaussian.addListener(this, &ofApp::gaussianClicked);
    saltPepper.addListener(this, &ofApp::saltPepperClicked);
    einstein.addListener(this, &ofApp::einsteinClicked);

    buttonBox.addListener(this, &ofApp::buttonBoxClicked);
    buttonGaussian.addListener(this, &ofApp::buttonGaussianClicked);
    buttonMedian.addListener(this, &ofApp::buttonMedianClicked);
    
    mode = 1;
    photo = "gaussian.jpg";
    
    updateImage();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawMat(mat, 0, 0);
    gui.setPosition(im.getWidth(), 0);
    gui.draw();
    guiPhoto.setPosition(im.getWidth(), gui.getHeight());
    guiPhoto.draw();
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
    mousePressed(x,y,button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(x > im.getWidth() || y > im.getHeight() || x < 0 || y < 0){
        return;
    }
    
    //temporary variable to adjust kernel size to be odd and not less than 3
    int kernel = brushSize;
    if (kernel < 3){
        kernel = 3;
    }
    else if(kernel % 2 == 0){
        kernel += 1;
    }
    
    //matrix around cursor with diameter of brush size
    int min_x = std::max(0, x - kernel/2);
    int min_y = std::max(0, y - kernel/2);
    int max_x = std::min(mat.cols, x + kernel/2);
    int max_y = std::min(mat.rows, y + kernel/2);
    cv::Rect region(min_x, min_y, max_x - min_x, max_y - min_y);
    Mat matRegion = mat(region);
    
    //apply filter mode
    if (mode == 1){
        boxFilter(matRegion, matRegion, -1, cv::Size(kernel, kernel));
    }
    else if (mode == 2) {
        Mat gaussianKernel = getGaussianKernel(kernel, 1);
        sepFilter2D(matRegion, matRegion, -1, gaussianKernel, gaussianKernel);
    }
    else if (mode == 3){
        medianBlur(matRegion, matRegion, kernel);
    }
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

//--------------------------------------------------------------
void ofApp::buttonBoxClicked() {
    mode = 1;
}

//--------------------------------------------------------------
void ofApp::buttonGaussianClicked() {
    mode = 2;
}

//--------------------------------------------------------------
void ofApp::buttonMedianClicked() {
    mode = 3;
}

//--------------------------------------------------------------
void ofApp::gaussianClicked() {
    photo = "gaussian.jpg";
    updateImage();
}

//--------------------------------------------------------------
void ofApp::saltPepperClicked() {
    photo = "saltpepper.png";
    updateImage();
}

//--------------------------------------------------------------
void ofApp::einsteinClicked() {
    photo = "eistein.jpg";
    updateImage();
}

//--------------------------------------------------------------
void ofApp::updateImage(){
    im.load(photo);
    im.setImageType(OF_IMAGE_GRAYSCALE);
    mat = toCv(im);
}
