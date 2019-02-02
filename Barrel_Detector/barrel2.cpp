#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//namedWindow("Depth Image", 0);
	namedWindow("Color Image", 0);

    rs2::pipeline pipe;
    rs2::config cfg;

    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    pipe.start(cfg);

    rs2::frameset frames;
    while (true) {
	    if (pipe.poll_for_frames(&frames)) {
	    	rs2::frame color_frame = frames.first(RS2_STREAM_COLOR);
	    	Mat color_image (Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);
	    	imshow("Color Image", color_image);
	    	waitKey(1);
	    }
	}

    return 0;
}

//g++ -std=c++11 barrel.cpp -l realsense2 -l opencv_core -l opencv_highgui -o barrel && ./barrel

