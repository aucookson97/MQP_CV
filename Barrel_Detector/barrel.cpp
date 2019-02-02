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

    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    pipeline p;

    pipeline_profile profile = p.start(cfg);



    rs2::frameset frames;
    while (true) {
	    if (pipe.poll_for_frames(&frames)) {
	    	rs2::frame color_frame = frames.first(RS2_STREAM_DEPTH);
	    	Mat color_image (Size(640, 480), CV_16U, (void*)color_frame.get_data(), Mat::AUTO_STEP);
	    	imshow("Color Image", color_image);
	    	waitKey(1);
	    }
	}

    return 0;
}

//g++ -std=c++11 barrel.cpp -l realsense2 -l opencv_core -l opencv_highgui -o barrel && ./barrel

