#ifndef POINT_CLOUD_GENERATOR_H
#define POINT_CLOUD_GENERATOR_H

#include "data_types.h"
#include <opencv2/core/cuda_types.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/opencv.hpp>

using namespace cv::cuda;
using cv::cuda::GpuMat;
__global__ void ComputeVertexMap(PtrStep<float3>output_vertex_map,const PtrStepSz<float> input_depth_map,const float data_cutoff,const CameraParams &camera_params);

#endif
