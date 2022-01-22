#include "stellar_impl.h"

StellarErrors StellarImpl::Initialize(const StellarParams &stellar_params)
{
	deptrum_device.CreateDevice();


	cv::Mat depth_camera_matrix;

	const int pyramid_levels=stellar_params.pyramid_levels;
	depth_camera_params_pyramid.camera_params_pyramid.resize(pyramid_levels);




}

StellarErrors StellarImpl::StartDevice()
{

}

StellarErrors StellarImpl::GetFrameData(uint16_t * output_depth_data, uint8_t *output_rgb_data)
{

}

StellarErrors StellarImpl::DestoryDevice()
{

}

StellarErrors StellarImpl::StellarFusion()
{

}

