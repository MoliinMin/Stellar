#include "deptrum_device.h"
#include "opencv2/opencv.hpp"

int main()
{
	DeptrumDevice device;
	device.CreateDevice();
	device.OpenDevice();
	device.CreateStream();
	device.AllocateMemery();
	device.StartCapture();
	const int rgb_width = device.GetRgbFrameWidth();
	const int rgb_height = device.GetRgbFrameHeight();
	const int depth_width = device.GetDepthFrameWidth();
	const int depth_height = device.GetDepthFrameHeight();

	uint8_t* color = new uint8_t[depth_width * depth_height * 3];
	while (1)
	{
		cv::Mat depth_frame, rgb_frame;
		device.GetFrame(depth_frame,rgb_frame);
		
		Visualizer::DrawDepthMapInColorByHist(color,
			                                 (uint16_t*)depth_frame.data,
			                                  depth_frame.rows,
			                                  depth_frame.cols);

		cv::Mat color_depth_image(depth_frame.size(),CV_8UC3, color);
		cv::imshow("rgb_stream",rgb_frame);
		cv::imshow("depth_stream", color_depth_image);
		cv::waitKey(20);
	}
	device.DestoryDevice();

	delete[]color;
	return 0;
}