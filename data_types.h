#include "cuda_runtime.h"

#include <opencv2/core/cuda.hpp>
#include <opencv2/core/cuda_types.hpp>
// #include "eigen3/Eigen/Core"
// #include "eigen3/Eigen/Eigen"

using cv::cuda::GpuMat;

struct CameraParams
{
	int image_width;
	int image_height;
	float focal_x, focal_y;
	float c_x, c_y;
};
 
