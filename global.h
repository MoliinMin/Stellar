#ifndef GLOBAL_H
#define GLOBAL_H
#include "cuda_runtime.h"

#include <opencv2/core/cuda.hpp>
#include <opencv2/core/cuda_types.hpp>
using namespace cv::cuda;
using cv::cuda::GpuMat;

struct CameraParams
{
	int image_width;
	int image_height;
	float focal_x, focal_y;
	float c_x, c_y;
	float distortion_coeffs[5] = { 0 };
};

struct CameraParamsPyramid
{
	std::vector<CameraParams> camera_params_pyramid;
};
struct PointXyz
{
	float x;
	float y;
	float z;
};

class FrameData
{
public:
	std::vector<GpuMat> depth_pyramid;                               // 原始深度图的金字塔
	std::vector<GpuMat> smooth_depth_pyramid;                        // 滤波后的深度图金字塔
	std::vector<GpuMat> color_pyramid;                               // 彩色图像的金字塔
	std::vector<GpuMat> vertex_pyramid;                              // 3D点金字塔
	std::vector<GpuMat> normal_pyramid;                              // 法向量金字塔
public:
	FrameData() = default;
	~FrameData() = default;
	FrameData &operator=(FrameData&&frame_data)noexcept
	{
		depth_pyramid = std::move(frame_data.depth_pyramid);
		smooth_depth_pyramid = std::move(frame_data.smooth_depth_pyramid);
		color_pyramid = std::move(frame_data.color_pyramid);
		vertex_pyramid = std::move(frame_data.vertex_pyramid);
		normal_pyramid = std::move(frame_data.normal_pyramid);
		return *this;
	}
	FrameData(const int levels) :depth_pyramid(levels),
		                         smooth_depth_pyramid(levels),
		                         color_pyramid(levels),
		                         vertex_pyramid(levels),
		                         normal_pyramid(levels)
	{
	}
// 	void Reset()
// 	{
// 		depth_pyramid[0].setTo(0);
// 	
// 	}


};






#endif
