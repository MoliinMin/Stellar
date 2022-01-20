#include "point_cloud_generator.h"

__global__ void ComputeVertexMap(PtrStep<float3>output_vertex_map,
	                              const PtrStepSz<float> input_depth_map, 
	                              const float data_cutoff, 
	                              const CameraParams &camera_params)
{
	const int x = blockIdx.x*blockDim.x + threadIdx.x;
	const int y = blockIdx.x*blockDim.y + threadIdx.y;

	if (x >= camera_params.image_width || y >= camera_params.image_height)
		return;

	float depth_value = input_depth_map.ptr(y)[x];
	if (depth_value > data_cutoff) depth_value = 0;

	float point_x = (x - camera_params.c_x)*depth_value / camera_params.focal_x;
	float point_y = (y - camera_params.c_y)*depth_value / camera_params.focal_y;

	output_vertex_map.ptr(y)[x] = make_float3(point_x, point_y, depth_value);

}