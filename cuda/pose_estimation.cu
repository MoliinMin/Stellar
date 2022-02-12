#include "pose_estimation.h"

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
	                         const float angle_threshold)
{

	const int x = blockIdx.x*blockDim.x + threadIdx.x;
	const int y = blockIdx.y*blockDim.y + threadIdx.y;

	































}
