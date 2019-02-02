#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

Scalar low_threshold = (0, 0, 200); //H, S, V=200
Scalar high_threshold = (179, 50, 255); //H, S=50, V

int main()
{
	// Setup blob detector parameters
	SimpleBlobDetector::Params params;


	params.filterByArea = true;
	params.minArea = 1000;
	params.maxArea = std::numeric_limits<float>::max();
	params.filterByCircularity = false;
	params.filterByConvexity = false;
	params.filterByInertia = false;
	//Ptr<SimpleBlobDetector> detector = 	SimpleBlobDetector::create(params);
	SimpleBlobDetector detector(params);

	namedWindow("Color Image", 0);

    Mat img, gray, hsv, mask, res;

    img = imread("grass_example.png");


    // Remove everything that isn't white
    cvtColor(img, hsv, CV_BGR2HSV);
	inRange(hsv, Scalar(0, 0, 200), Scalar(179, 50, 255), mask);
	bitwise_and(img, img, res, mask=mask);

	// Invert image to detect white blobs
	bitwise_not(res, res); 

	// Detect Blobs
	std::vector<KeyPoint> keypoints;
	detector.detect(res, keypoints);
	
	// Draw Blobs
	Mat img_kp;
	drawKeypoints(res, keypoints, img_kp, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
	cout << "Size: " << keypoints.size();

	for (size_t i = 0; i < keypoints.size(); i++) {
		cout << "\nCenter: " << keypoints[i].pt; 
		cout << "\nSize: " <<  keypoints[i].size;
	}

	imshow("Color Image", img_kp);
	waitKey(0);
	//imshow("Color Image", res);
	//waitKey(0);

	/*    

    cvtColor(res, gray, CV_BGR2GRAY);

    GaussianBlur(gray, gray, Size(5, 5), 2, 2);
    //imshow("mask", mask);


    vector<Vec3f> circles;

    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows/8, 200, 100, 0, 0);

    for (size_t i = 0; i < circles.size(); i++) {
    	cout << circles[i];
    	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    	int radius = cvRound(circles[i][2]);

    	circle(gray, center, 3, Scalar(0, 255, 0), -1, 8, 0);
    	circle(mask, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }

    cout << circles.size();
    

    imshow("Color Image", gray);
    waitKey(0);
    */

    return 0;
}

//g++ -std=c++11 circle_detection.cpp -l opencv_core -l opencv_highgui -l opencv_imgproc -l opencv_features2d -l opencv_objdetect -o circle_detection && ./circle_detection

