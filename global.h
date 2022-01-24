#ifndef GLOBAL_H
#define GLOBAL_H
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
	std::vector<GpuMat> depth_pyramid;                               // ԭʼ���ͼ�Ľ�����
	std::vector<GpuMat> smooth_depth_pyramid;                        // �˲�������ͼ������
	std::vector<GpuMat> color_pyramid;                               // ��ɫͼ��Ľ�����
	std::vector<GpuMat> vertex_pyramid;                              // 3D�������
	std::vector<GpuMat> normal_pyramid;                              // ������������
public:
	FrameData()=default;
	~FrameData() = default;
	FrameData &operator=(FrameData&&frame_data)noexcept
	{
		depth_pyramid = std::move(frame_data.depth_pyramid);

	 
	}


};






#endif