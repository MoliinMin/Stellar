#ifndef POINT_CLOUD_GENERATOR_H
#define POINT_CLOUD_GENERATOR_H

#include "../data_types.h"
#include "../global.h"
#include <opencv2/core/cuda_types.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/opencv.hpp>
#include <cuda.h>
#include "utils.h"

using namespace cv::cuda;
using cv::cuda::GpuMat;
__global__ void GpuComputeVertexMap(PtrStep<float3>output_vertex_map,const PtrStepSz<float> input_depth_map,const float data_cutoff,const CameraParams camera_params);

__global__ void GpuComputeNormalMap(PtrStep<float3> output_normal_map,const PtrStepSz<float3> input_vertex_map);

__device__ void Cross(const float3  target_vector, const float3 source_vector, float3 &output_cross_vector);


__device__ void normalize(float3 &input_vector);


void ComputeVertexMap(GpuMat &output_vertex_map, const GpuMat &input_depth_map, const float data_cutoff, const CameraParams camera_params);

void ComputeNormalMap(GpuMat &output_normal_map,const GpuMat &input_vertex_map);




#endif
