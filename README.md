# interactive-brush-based-image-filtering
1. Implement the interactive brush-based image filtering.<br />
To implement brush using openCV, I used mousePressed and mouseDragged functions to manipulate with cursor location and cv::Rect to create brush (matrix) around the cursor of size of the brush set by slider. The brush size minimum value is 1 and highest 20 but since kernel size supposed to be odd number and at least 3x3, if the slider is less than 3 it is equal actually equal to 3 and if it is even number it will round up to odd number. Initially, Box filtering is applied but by clicking buttons the filtering mode can be changed to Gaussian or Median filters. To implement filtering of kernel (brush matrix), boxFilter, sepFilter2D with getGaussianKernel and medianBlur functions were used. The brush (region of interest) is updated once mouse is clicked or dragged according to chosen filter mode.<br />
    //matrix around cursor with diameter of brush size<br />
    int min_x = std::max(0, x - kernel/2);<br />
    int min_y = std::max(0, y - kernel/2);<br />
    int max_x = std::min(mat.cols, x + kernel/2);<br />
    int max_y = std::min(mat.rows, y + kernel/2);<br />
    cv::Rect region(min_x, min_y, max_x - min_x, max_y - min_y);<br />
    Mat matRegion = mat(region);<br />
    
    //apply one of the filters<br />
    if (mode == 1){<br />
        boxFilter(matRegion, matRegion, -1, cv::Size(kernel, kernel));<br />
    }<br />
    else if (mode == 2) {<br />
        Mat gaussianKernel = getGaussianKernel(kernel, 1);<br />
        sepFilter2D(matRegion, matRegion, -, gaussianKernel, gaussianKernel);<br />
    }<br />
    else if (mode == 3){<br />
        medianBlur(matRegion, matRegion, kernel);<br />
    }<br />
    
2. Implement the graphical user interfaces allowing the user to select three different image filters: Box, Gaussian, and Media
Different filter modes were implemented by using ofxPanel and ofxButton. Each button on click initiate custom functions to change variable “mode” to corresponding filter mode. From above code it might be found that mode 1 corresponds to Box Filter, mode 2 to Gaussian Filter and mode 3 to Median Filter. <br />
    gui.setup("Filter:");<br />
    gui.add(brushSize.setup("Brush size", 10, 1, 20));<br />
    gui.add(buttonBox.setup("Box Filter"));<br />
    gui.add(buttonGaussian.setup("Gaussian Filter"));<br />
    gui.add(buttonMedian.setup("Median Filter"));<br />
    buttonBox.addListener(this, &ofApp::buttonBoxClicked);<br />
    buttonGaussian.addListener(this, &ofApp::buttonGaussianClicked);<br />
    buttonMedian.addListener(this, &ofApp::buttonMedianClicked);<br /><br />
//example of one of the functions initiated on click<br />
void ofApp::buttonMedianClicked() {<br />
    mode = 3;<br />
}<br />

3. Implement the graphical user interfaces allowing the user to adjust the brush size
The brush size is controlled by ofxIntSlider in range of 1 to 20. The default size is set to be 10.
    gui.add(brushSize.setup("Brush size", 10, 1, 20));
4. Try your program in three images: gaussian.jpg, saltpepper.png, and eistein.jpg.
I added new ofxPanel and three more buttons to let user choose image. <br />
    guiPhoto.setup("Photo:");<br />
    guiPhoto.add(gaussian.setup("Gaussian Noise"));<br />
    guiPhoto.add(saltPepper.setup("Salt and Pepper Noise"));<br />
    guiPhoto.add(einstein.setup("Einstein"));<br />
    gaussian.addListener(this, &ofApp::gaussianClicked);<br />
    saltPepper.addListener(this, &ofApp::saltPepperClicked);<br />
    einstein.addListener(this, &ofApp::einsteinClicked);
<br /><img width="318" alt="image" src="https://github.com/Drace2108/interactive-brush-based-image-filtering/assets/70643580/fdbc0098-831f-4e1a-9eb7-56c71d1adc6d"><br />
Figure 1: Image with Gaussian noise
 <br /><img width="319" alt="image" src="https://github.com/Drace2108/interactive-brush-based-image-filtering/assets/70643580/21f273f4-1b25-46b1-8b0c-d82cd51b22e2"><br />
Figure 2: Image with Salt and Pepper noise
 <br /><img width="311" alt="image" src="https://github.com/Drace2108/interactive-brush-based-image-filtering/assets/70643580/376c6f01-e20d-4440-9fee-3e5f1f83b88c"><br />
Figure 3: Photography of Albert Einstein<br /><br />
5. Discuss the effects of the filters on different images.<br />
<img width="187" alt="image" src="https://github.com/Drace2108/interactive-brush-based-image-filtering/assets/70643580/d3277c71-bade-444c-a3ad-1474ece068fd"><br />
The Gaussian filter is widely utilized to reduce Gaussian noise, which appears as random variations in brightness and color intensity. By convolving the image with a Gaussian kernel, the filter blurs the image while preserving important details. The amount of blurring can be adjusted by modifying the standard deviation of the Gaussian kernel. This filter is particularly effective in scenarios where the noise follows a Gaussian distribution. When applied to images with Gaussian noise, the Gaussian filter yields a smoother appearance and effectively reduces the noise, resulting in enhanced image quality.<br />
<br /><img width="207" alt="image" src="https://github.com/Drace2108/interactive-brush-based-image-filtering/assets/70643580/fac02c69-fd41-46e0-88ba-03075109afca"><br />
Another type of noiseis salt and pepper noise, which manifests as randomly scattered black and white pixels throughout the image. The Median filter is often employed to mitigate this type of noise. By replacing each pixel with the median value within its local neighborhood, the Median filter effectively removes outliers such as salt and pepper noise while preserving image details. When applied to images with salt and pepper noise, the Median filter significantly reduces the noise, resulting in a clearer and more visually pleasing image.
<br /><img width="170" alt="image" src="https://github.com/Drace2108/interactive-brush-based-image-filtering/assets/70643580/689c2001-1cca-4af0-8713-8d0b2eb094c9"><br />
The Box filter works by averaging the pixel values within a defined neighborhood. By adjusting the size of the neighborhood, the intensity of the smoothing effect can be controlled. In this case, the Box filter can be applied to remove wrinkles and create smoother skin texture of Einstein’s portrait. The larger the neighborhood, the more pronounced the blurring effect, effectively reducing the visibility of wrinkles and resulting in smoother skin. By employing the Box filter in this context, the photo of Albert Einstein can be enhanced, drawing attention to his intellectual brilliance rather than the physical signs of aging.
