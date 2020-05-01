//
// Implement the required functions here.
//
#include "yours.hpp"
#include "given.hpp"

using namespace cv;

void yours::binarizeImage(const cv::Mat& src, cv::Mat& dst, int thresh) {

    // TODO: convert image to gray scale
    // https://docs.opencv.org/4.2.0/d8/d01/group__imgproc__color__conversions.html#ga397ae87e1288a81d2363b61574eb8cab
	cvtColor(src, dst, COLOR_BGRA2GRAY);

    // TODO: Binarize image
    // https://docs.opencv.org/4.2.0/d7/d1b/group__imgproc__misc.html#gae8a4a146d1ca78c626a53577199e9c57
	cv::Mat tempDst = dst.clone(); // deep copy to temporary variable
	threshold(tempDst, dst, thresh, 255, THRESH_BINARY);

}


// TODO: Implement processImage
// use smoothImage from given.hpp
//   (tests only work if you don't change the default value for size)
cv::Mat yours::processImage(const cv::Mat& src) {
	cv::Mat dst, finaDst;
	given::smoothImage(src, dst);
	yours::binarizeImage(dst, finaDst);

	return finaDst;
}

