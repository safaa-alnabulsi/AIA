//
// Implement the required functions here.
//
#include "yours.hpp"
#include "given.hpp"


void yours::preprocessImage(cv::Mat& src, cv::Mat& dst, int bin_thresh, int n_erosions) {


    cv::Mat tmp = src;
    if(src.channels() > 1)
        cv::cvtColor(src, tmp, cv::COLOR_BGR2GRAY);

   // get binary image (white foreground, black background)

    // use erosion to get rid of small objects and break connections between leafs
    // use a 3x3 structuring element (cv::Mat::ones(3, 3, CV_8UC1))

}

cv::Mat yours::getFourierDescriptor(const cv::Mat& contour) {
    // convert the countour in a adequate format and make the discrete fourier transform
    // use OpenCVs implementation of the DFT
}

cv::Mat yours::normalizeFourierDescriptor(const cv::Mat& fd, int n) {

    // translation invariance F(0) = 0

    // scale invariance F(i) = F(i)/|F(1)|
    // What if |F(1)| = 0?

    // rotation invariance F = |F|
    // There are some useful OpenCV functions such as cartToPolar

    // smaller sensitivity for details
    // This one is a bit tricky. How does your descriptor look like?
    // Where are the high frequencies and where are the negative indices?

}

int yours::classifyFourierDescriptor(const cv::Mat& fd, const std::vector<cv::Mat>& class_templates, float thresh) {
    // loop over templates and find closest, return index
    // use cv::norm as a disctance metric
}
