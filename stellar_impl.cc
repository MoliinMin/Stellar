#include "stellar_impl.h"

Stellar *Stellar::Create()
{
	return new StellarImpl();
}

void Stellar::Destory(Stellar *stellar_object)
{
	delete stellar_object;
}

StellarErrors StellarImpl::Initialize(const StellarParams &stellar_params)
{
	//create camera device
	deptrum_device.CreateDevice();
	deptrum_device.OpenDevice();
	const int pyramid_levels = stellar_params.pyramid_levels;
	global_frame_data = FrameData(pyramid_levels);
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
	//const int pyramid_levels=stellar_params.pyramid_levels;
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
	for (int level=0;level<pyramid_levels;++level)
	{
		std::cout << level << std::endl;
		const int image_width = depth_camera_params_pyramid.camera_params_pyramid[level].image_width;
		const int image_height = depth_camera_params_pyramid.camera_params_pyramid[level].image_height;
		global_frame_data.depth_pyramid[level] = cv::cuda::createContinuous(image_height,image_width,CV_32FC1);
		global_frame_data.smooth_depth_pyramid[level] = cv::cuda::createContinuous(image_height,image_width,CV_32FC1);
		global_frame_data.color_pyramid[level] = cv::cuda::createContinuous(image_height,image_width,CV_8UC3);
		global_frame_data.vertex_pyramid[level] = cv::cuda::createContinuous(image_height,image_width,CV_32FC3);
		global_frame_data.normal_pyramid[level] = cv::cuda::createContinuous(image_height,image_width,CV_32FC3);
	}
	//
	surface_measurement.Init(std::make_shared<StellarParams>(stellar_params),
		                     std::make_shared<CameraParamsPyramid>(depth_camera_params_pyramid));


	return StellarErrors::OK;
}

StellarErrors StellarImpl::StartDevice()
{

	deptrum_device.CreateStream();
	deptrum_device.AllocateMemery();
	deptrum_device.StartCapture();
	return StellarErrors::OK;
}

StellarErrors StellarImpl::GetFrames(cv::Mat &output_depth_frame, cv::Mat &output_rgb_frame)
{
	deptrum_device.GetFrame(output_depth_frame,output_rgb_frame);
	return StellarErrors::OK;
}

StellarErrors StellarImpl::DestoryDevice()
{
	deptrum_device.DestoryDevice();
	return StellarErrors::OK;
}

StellarErrors StellarImpl::StellarFusion(const cv::Mat &input_depth_mat, const cv::Mat &input_rgb_mat)
{
	//step 2:convert 16bit image to 32bit image
	cv::Mat depth_image_32bit;
	input_depth_mat.convertTo(depth_image_32bit, CV_32FC1);
    //step :surface measurment
	surface_measurement.Run(global_frame_data, depth_image_32bit, input_rgb_mat);



	//
// 	cv::Mat color_image = cv::Mat::zeros(depth_camera_params_pyramid.camera_params_pyramid[0].image_height,
// 		                                 depth_camera_params_pyramid.camera_params_pyramid[0].image_width,
// 		                                 CV_8UC3);


	//cv::Mat color_image;
	//global_frame_data.depth_pyramid[0].download(color_image);
// 
// 	cv::imshow("color_image", color_image);

//	cv::normalize();
// 	cv::Mat depth_image = cv::Mat::zeros(depth_camera_params_pyramid.camera_params_pyramid[0].image_height,
// 		                                 depth_camera_params_pyramid.camera_params_pyramid[0].image_width,
// 		                                 CV_32FC1);
	cv::Mat depth_image;
	global_frame_data.depth_pyramid[0].download(depth_image);
	//cv::imshow("depth_image_pyramid_0", depth_image);



	return StellarErrors::OK;
}

void StellarImpl::Reset()
{
// 	const int pyramid_levels = stellar_params->pyramid_levels;
// 	for ()
// 	{
// 		global_frame_data.depth_pyramid
// 	}

}

       
