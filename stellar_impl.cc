#include "stellar_impl.h"

StellarErrors StellarImpl::Initialize(const StellarParams &stellar_params)
{
	//create camera device
	deptrum_device.CreateDevice();

	//get camera params
	cv::Mat rgb_camera_matrix, rgb_distortion_coeffs, ir_camera_matrix, ir_distortion_coeffs;
	cv::Mat rotate_matrix, translate_matrix;
	deptrum_device.GetDeviceParams(ir_camera_matrix,
		                           ir_distortion_coeffs,
		                           rgb_camera_matrix,
		                           rgb_distortion_coeffs,
		                           rotate_matrix,
		                           translate_matrix);
	//allocate camera_params pyramid memory
	const int pyramid_levels=stellar_params.pyramid_levels;
	depth_camera_params_pyramid.camera_params_pyramid.resize(pyramid_levels);
	//resize camera params
	float *distortion_params = (float *)rgb_distortion_coeffs.data;
	const int distortion_params_count = 5;
	for (int level=0;level<pyramid_levels;++level)
	{
		memcpy(depth_camera_params_pyramid.camera_params_pyramid[level].distortion_coeffs, 
			   distortion_params, 
			   sizeof(float)*distortion_params_count);
		const float scale_inv = 1.0f/std::pow(2,level);
		depth_camera_params_pyramid.camera_params_pyramid[level].image_height = stellar_params.image_height*scale_inv;
		depth_camera_params_pyramid.camera_params_pyramid[level].image_width = stellar_params.image_width*scale_inv;
		depth_camera_params_pyramid.camera_params_pyramid[level].focal_x = rgb_camera_matrix.at<float>(0, 0)*scale_inv;
		depth_camera_params_pyramid.camera_params_pyramid[level].focal_y = rgb_camera_matrix.at<float>(1, 1)*scale_inv;
		depth_camera_params_pyramid.camera_params_pyramid[level].c_x = rgb_camera_matrix.at<float>(0, 2)*scale_inv;
		depth_camera_params_pyramid.camera_params_pyramid[level].c_y = rgb_camera_matrix.at<float>(1, 2)*scale_inv;
	}
	//allocate gpu data



	return StellarErrors::OK;
}

StellarErrors StellarImpl::StartDevice()
{
	return StellarErrors::OK;
}

StellarErrors StellarImpl::GetFrameData(uint16_t * output_depth_data, uint8_t *output_rgb_data)
{
	return StellarErrors::OK;
}

StellarErrors StellarImpl::DestoryDevice()
{
	return StellarErrors::OK;
}

StellarErrors StellarImpl::StellarFusion()
{
	return StellarErrors::OK;
}

