#ifndef DEPTRUM_DEVICE_H
#define DEPTRUM_DEVICE_H
//#include "include/opencv/opencv"
#include "opencv2/opencv.hpp"
#include "deptrum/deptrum.h"


 using namespace deptrum;
 using namespace deptrum::aurora;
#define DEFAULT_DEVICE_INDEX 0

 class DeptrumDevice
 {
 public:
	 DeptrumDevice();
	 ~DeptrumDevice();
	 bool CreateDevice();

	 bool OpenDevice();

	 bool CreateStream();

	 bool AllocateMemery();

	 bool StartCapture();

	 bool GetFrame(cv::Mat &output_depth_frame,cv::Mat &output_rgb_frame);

	 void DestoryDevice();

	 int GetRgbFrameWidth() const
	 {
		 return rgb_frame.cols;
	 }

	 int GetRgbFrameHeight() const
	 {
	 
		 return rgb_frame.rows;
	 }

	 int GetDepthFrameHeight() const
	 {
		 return depth_frame.cols;
	 }
     
	 int GetDepthFrameWidth() const
	 {
		return  depth_frame.rows;
	 }

	 void GetDeviceParams(cv::Mat &output_ir_camera_params,
		                  cv::Mat &output_ir_distortion_params,
		                  cv::Mat &output_rgb_camera_params,
		                  cv::Mat &output_rgb_distortion_params,
		                  cv::Mat &output_rotate_matrix,
		                  cv::Mat &output_translate_matrix);

 private:


 
 private:
	 Device *global_device;
	 Stream * depth_stream;
	 Stream * rgb_stream;
	 deptrum::Frame rgb_frame;
	 deptrum::Frame depth_frame;
 };






#endif
