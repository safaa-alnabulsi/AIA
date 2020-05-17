//
// Implement the required functions here.
//
#include "yours.hpp"
#include "given.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

void yours::preprocessImage(cv::Mat& src, cv::Mat& dst, int bin_thresh, int n_erosions) {
    cv::Mat tmp = src;
    if(src.channels() > 1)
        cv::cvtColor(src, tmp, cv::COLOR_BGR2GRAY);

   // get binary image (white foreground, black background)
	cv::Mat temp_dst = dst.clone(); // deep copy to temporary variable
	threshold(tmp, temp_dst, bin_thresh, 255, THRESH_BINARY_INV);

    // use erosion to get rid of small objects and break connections between leafs
    // use a 3x3 structuring element (cv::Mat::ones(3, 3, CV_8UC1))
	cv::Mat element = cv::Mat::ones(3, 3, CV_8UC1);
    cv::erode(temp_dst, dst, element, Point(-1,-1), n_erosions);

}
// https://docs.opencv.org/2.4/doc/tutorials/core/discrete_fourier_transform/discrete_fourier_transform.html
cv::Mat yours::getFourierDescriptor(const cv::Mat& contour) {
    // convert the countour in a adequate format and make the discrete fourier transform
    // use OpenCVs implementation of the DFT
    cv::Mat contourF;
    contour.convertTo(contourF, CV_32F);

	Mat planes[] = {Mat::zeros(contourF.size(), CV_32F), Mat::zeros(contourF.size(), CV_32F)};
	cv::Mat complexContour;
	cv::merge(planes, 2, complexContour);

	dft(contourF, complexContour);

	return complexContour;
}


cv::Mat yours::normalizeFourierDescriptor(const cv::Mat& fd, int n) {

    // translation invariance F(0) = 0
	// Removing a row from https://gist.github.com/enpe/369a7a17fd9b3856b544#file-main-cpp-L33
	// CV_32FC2 from http://ninghang.blogspot.com/2012/11/list-of-mat-type-in-opencv.html
	cv::Size size = fd.size();
	cv::Mat matOut = Mat::zeros(size.height - 1, size.width, CV_32FC2);
//    cv::Rect rect( 0, 0, size.width, 1 );
//    fd(rect).copyTo(matOut(rect));

    matOut = fd.rowRange(1, fd.rows);

    // rotation invariance F = |F|
    // There are some useful OpenCV functions such as cartToPolar
	cv::Mat magnitude, angle, channels[2];
    split(matOut, channels);
	cartToPolar(channels[0], channels[1], magnitude, angle);

    // scale invariance F(i) = F(i)/|F(1)|
    // What if |F(1)| = 0?

    cv::Mat scaledInv;
    float first_elem = magnitude.at<float>(0, 0);

	if (first_elem != 0) {
	   scaledInv = magnitude/abs(first_elem);
	} else {
	    float start_elem = magnitude.at<float>(n-1, 0);
		scaledInv = magnitude/abs(start_elem);
	}

    // smaller sensitivity for details
    // This one is a bit tricky. How does your descriptor look like?
    // Where are the high frequencies and where are the negative indices?
	// Removing a row from https://gist.github.com/enpe/369a7a17fd9b3856b544#file-main-cpp-L39

	cv::Size sizeScaledInv = scaledInv.size();
	if (sizeScaledInv.height < n ){
		return scaledInv;
	}
	else{
//		cv::Mat scaledMatOut = Mat::zeros(n, size.width, CV_32F);
//        cv::Rect rect1( 0, 0, size.width, 0 );
//        scaledInv(rect1).copyTo(scaledMatOut(rect1));
//		return scaledMatOut;
        return scaledInv.rowRange(0,n);
	}
}


int yours::classifyFourierDescriptor(const cv::Mat& fd, const std::vector<cv::Mat>& class_templates, float thresh) {
    // loop over templates and find closest, return index
    // use cv::norm as a disctance metric
	int index = 0;
	int minIndex = -1;
	float minDist = 100000000;
    for (auto const& tmp : class_templates){
//        std::cout << fd.size();
	    float dist = cv::norm(fd, tmp.rowRange(0, fd.rows));
	    if (dist < minDist && dist <= thresh){
	        minDist = dist;
	        minIndex = index;
	    }
	    index++;
    }

	return minIndex;
}
