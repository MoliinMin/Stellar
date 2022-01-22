#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include "cuda_runtime.h"

#include <opencv2/core/cuda.hpp>
#include <opencv2/core/cuda_types.hpp>

 

using cv::cuda::GpuMat;



struct CameraParams
{
	int image_width;
	int image_height;
	float focal_x, focal_y;
	float c_x, c_y;

	float distortion_coeffs[5] = {0};
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

struct FrameData
{
	std::vector<GpuMat> depth_pyramid;                               // 原始深度图的金字塔
	std::vector<GpuMat> smooth_depth_pyramid;                        // 滤波后的深度图金字塔
	std::vector<GpuMat> color_pyramid;                               // 彩色图像的金字塔
	std::vector<GpuMat> vertex_pyramid;                              // 3D点金字塔
	std::vector<GpuMat> normal_pyramid;                              // 法向量金字塔
};




struct StellarParams
{
	int pyramid_levels;


};
#endif
