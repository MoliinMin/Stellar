#include "point_cloud_generator.h"

__global__ void GpuComputeVertexMap(PtrStep<float3>output_vertex_map,
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

__global__ void GpuComputeNormalMap(PtrStep<float3> output_normal_map, const PtrStepSz<float3> input_vertex_map)
{
	const int x = blockIdx.x*blockDim.x + threadIdx.x;
	const int y = blockIdx.y*blockDim.y + threadIdx.y;

	if (x < 1 || x >= input_vertex_map.cols - 1 || y < 1 || y >= input_vertex_map.rows)
		return;

	float3 left_vertex = input_vertex_map.ptr(y)[x - 1];
	float3 right_vertex = input_vertex_map.ptr(y)[x + 1];
	float3 upper_vertex = input_vertex_map.ptr(y - 1)[x];
	float3 below_vertex = input_vertex_map.ptr(y + 1)[x];

	float3 normal;

	if (left_vertex.z == 0 || right_vertex.z == 0 || upper_vertex.z == 0 || below_vertex.z == 0)
	{
		normal = make_float3(0, 0, 0);
	}
	else
	{
		float3 hor = make_float3(left_vertex.x - right_vertex.x,
			left_vertex.y - right_vertex.y,
			left_vertex.z - right_vertex.z);
		float3 ver = make_float3(upper_vertex.x - below_vertex.x,
			upper_vertex.y - below_vertex.y,
			upper_vertex.z - below_vertex.z);

		Cross(hor, ver, normal);
		normalize(normal);
		if (normal.z > 0)
			normal = make_float3(-normal.x, normal.y, -normal.z);
	}
	output_normal_map.ptr(y)[x] = normal;
}

__device__ void Cross(const float3  target_vector, const float3 source_vector, float3 &output_cross_vector)
{

	float x = target_vector.y*source_vector.z - target_vector.z*source_vector.y;
	float y = -target_vector.x*source_vector.z + target_vector.z*source_vector.x;
	float z = target_vector.x*source_vector.y - target_vector.y*source_vector.x;
	output_cross_vector = make_float3(x, y, z);
}

__device__ void normalize(float3 &input_vector)
{

	float length=sqrt(input_vector.x*input_vector.x+ input_vector.y*input_vector.y+ input_vector.z*input_vector.z);
	float x = input_vector.x / length;
	float y = input_vector.y / length;
	float z = input_vector.z / length;
	input_vector = make_float3(x, y, z);
}

void ComputeVertexMap(GpuMat &output_vertex_map, const GpuMat &input_depth_map, const float data_cutoff, const CameraParams &camera_params)
{
	int cols = input_depth_map.cols;
	int rows = input_depth_map.rows;

	dim3 threads(32, 32);
	dim3 blocks((cols + threads.x - 1) / threads.x, (rows + threads.y - 1) / threads.y);

	GpuComputeVertexMap << <blocks, threads >> > (output_vertex_map, input_depth_map, data_cutoff, camera_params);
	cudaThreadSynchronize();
}


void ComputeNormalMap(GpuMat &output_normal_map, const GpuMat &input_vertex_map)
{
	int cols = input_vertex_map.cols;
	int rows = input_vertex_map.rows;

	dim3 threads(32, 32);
	dim3 blocks((cols + threads.x - 1) / threads.x, (rows + threads.y - 1) / threads.y);

	GpuComputeNormalMap<<<blocks,threads>>>(output_normal_map, input_vertex_map);
	cudaThreadSynchronize(); 
}