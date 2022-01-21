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
};
 
struct PointXyz
{
	float x;
	float y;
	float z;
};

#endif
