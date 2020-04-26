#include <iostream>
#include <vector>

#include "given.hpp"
#include "yours.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

// TODO(student):
// Loads a test image and saves and shows the results of image processing
// Read the docs for OpenCV!
// https://docs.opencv.org/4.2.0/
int main(int argc, char** argv) {

    // TODO: declare some matrices for the images
    // https://docs.opencv.org/4.2.0/d3/d63/classcv_1_1Mat.html
	Mat inputImage(Size(320,240),CV_8UC3);

    // TODO: load image
    // https://docs.opencv.org/4.2.0/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56
    std::string fname = "./data/test.jpg";
    std::string image_path = samples::findFile(fname);
    inputImage = imread(image_path, IMREAD_COLOR);

    // check if image is loaded successfully
    if (!inputImage.data){
      std::cerr << "ERROR: Cannot read file " << fname << std::endl;
      exit(-1);
    }

    // TODO: show input image
    // https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga453d42fe4cb60e5723281a89973ee563
    imshow("Display Input Image", inputImage);
    int k = waitKey(0); // Wait for a keystroke in the window

    // TODO: call the function that handles the actual image processing
    // It's the function in yours.cpp called processImage


    // TODO: save result
    // https://docs.opencv.org/master/d4/da8/group__imgcodecs.html#gabbc7ef1aa2edfaa87772f1202d67e0ce


    // TODO: show result and wait for key
    // https://docs.opencv.org/master/d7/dfc/group__highgui.html#ga5628525ad33f52eab17feebcfba38bd7

}
