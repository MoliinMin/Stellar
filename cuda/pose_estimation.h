#ifndef POSE_EXTIMATION_H
#define POSE_EXTIMATION_H
#include "../data_types.h"
#include "../global.h"
#include <opencv2/core/cuda_types.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/opencv.hpp>
#include <cuda.h>
#include "utils.h"

__global__ void PoseEstimate(const PtrStep<float> current_rotate_matrix,
	                         const PtrStep<float> current_translate_matrix,
	                         const PtrStep<float3> current_vertex_map,
	                         const PtrStep<float3> current_normal_map,
	                         const PtrStep<float> previous_rotate_matrix_inv,
	                         const PtrStep<float> previous_translate_matrix,
	                         const CameraParams camera_params,
	                         const PtrStep<float3> previous_vertex_map,
	                         const PtrStep<float3> previous_normal_map,
	                         const float distance_threshold,
	                         const float angle_threshold);







#endif
