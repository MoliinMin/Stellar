
#include "surface_measurement.h"

void SurfaceMeasurement::Init(std::shared_ptr<StellarParams> stellar_params_,
	                          std::shared_ptr<CameraParamsPyramid> camera_params_pyramid_)
{
	camera_params_pyramid = camera_params_pyramid_;
	stellar_params = stellar_params_;
}

void SurfaceMeasurement::Run(FrameData &output_frame_data, cv::Mat &input_depth_map, const cv::Mat &input_rgb_map)
{
	const int pyramid_levels = stellar_params->pyramid_levels;
	//获得第一层，该图像与原始图像大小相同
	output_frame_data.depth_pyramid[0].upload(input_depth_map);
	output_frame_data.color_pyramid[0].upload(input_rgb_map);
	//build pyramids and filter bilaterally on gpu 
	cv::cuda::Stream stream;
	for (size_t level=1;level<pyramid_levels;++level)
	{
		cv::cuda::pyrDown(output_frame_data.depth_pyramid[level-1],output_frame_data.depth_pyramid[level], stream);
	}
	for (size_t level=0;level<pyramid_levels;++level)
	{
		cv::cuda::bilateralFilter(output_frame_data.depth_pyramid[level],  
			                      output_frame_data.smooth_depth_pyramid[level],
			                      stellar_params->kernel_size,
			                      stellar_params->sigma,
			                      stellar_params->spatial_sigma,
			                      cv::BORDER_DEFAULT,
			                      stream);
	}
	stream.waitForCompletion();
	cv::cuda::GpuMat device_vertex_map(stellar_params->image_height,stellar_params->image_width,CV_32FC3);
	for (size_t level=0;level<pyramid_levels;++level)                                              
	{
		ComputeVertexMap(output_frame_data.vertex_pyramid[level], 
			             output_frame_data.smooth_depth_pyramid[level],
			             stellar_params->data_cutoff,
			             camera_params_pyramid->camera_params_pyramid[level]);

		ComputeNormalMap(output_frame_data.normal_pyramid[level],output_frame_data.vertex_pyramid[level]);
	}

}

