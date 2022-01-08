#include "deptrum_device.h"

DeptrumDevice::DeptrumDevice():global_device(nullptr), depth_stream(nullptr), rgb_stream(nullptr)
{

}

DeptrumDevice::~DeptrumDevice()
{

}

bool DeptrumDevice::CreateDevice()
{
	std::vector<DeviceInformation> device_list;
	int result = 0;
	result = Device::GetDeviceList(device_list);
	size_t device_conut = device_list.size();
	if (device_conut<1)
	{
		std::cout << "can not find any device" << std::endl;
		return false;
	}
    std::cout << "Device count: " << device_conut << std::endl;
	result = Device::Create(&global_device, device_list[DEFAULT_DEVICE_INDEX]);
	if (result != 0)
	{
		return false;
	}
	return true;
}

bool DeptrumDevice::OpenDevice()
{
	int result=global_device->Open();
	if (result!=0)
	{
		return false;
	}
	result = global_device->SetMode(deptrum::FrameMode::kInvalid,
		                            deptrum::FrameMode::kRes480x640RgbJpeg,
		                            deptrum::FrameMode::kRes400x640Depth16Bit);
	if (result != 0)
	{    
		return false;
	}
	return true;
}

bool DeptrumDevice::CreateStream()
{
	int result = global_device->CreateStream(&depth_stream, deptrum::kDepth);
	if (result != 0)
	{
		return false;
	}
	result = global_device->CreateStream(&rgb_stream,deptrum::kRgb);
	if (result != 0)
	{
		return false;
	}
	return true;
}

bool DeptrumDevice::AllocateMemery()
{
	int result = depth_stream->AllocateFrame(depth_frame);
	if (result != 0)
		return false;
	result = rgb_stream->AllocateFrame(rgb_frame);
	if (result != 0)
		return false;
	return true;
}

bool DeptrumDevice::StartCapture()
{
	rgb_stream->Start();
	depth_stream->Start();
	return true;
}

bool DeptrumDevice::GetFrame(cv::Mat &output_depth_frame, cv::Mat &output_rgb_frame)
{
	
	int result=rgb_stream->GetFrame(rgb_frame,2000);
	if (result!=0)
	{
		return false;
	}
	result=depth_stream->GetFrame(depth_frame,2000);

	if (result!=0)
	{
		return false;
	}
	const size_t  rgb_width = rgb_frame.cols;
	const size_t rgb_height = rgb_frame.rows;
	
	const size_t depth_width = depth_frame.cols;
	const size_t depth_height = depth_frame.rows;
	cv::Mat rgb_mat, depth_mat;
	rgb_mat = cv::Mat(rgb_height,rgb_width,CV_8UC3,(uint8_t*)rgb_frame.data);
	depth_mat = cv::Mat(depth_height, depth_width, CV_16UC1, (uint16_t*)depth_frame.data);
	
 	output_depth_frame = depth_mat.clone();
	output_rgb_frame = rgb_mat.clone();

	return true;
}

void DeptrumDevice::DestoryDevice()
{
	Stream::ReleaseFrame(rgb_frame);
	Stream::ReleaseFrame(depth_frame);

	rgb_stream->Stop();
	depth_stream->Stop();
	global_device->DestroyStream(&depth_stream);
	global_device->DestroyStream(&rgb_stream);
	global_device->Close();
	Device::Destroy(&global_device);
}

void DeptrumDevice::GetDeviceParams(cv::Mat &output_ir_camera_params, 
	                                cv::Mat &output_ir_distortion_params,
	                                cv::Mat &output_rgb_camera_params, 
	                                cv::Mat &output_rgb_distortion_params,
	                                cv::Mat &output_rotate_matrix, 
	                                cv::Mat &output_translate_matrix)
{
	Intrinsic ir_intrinsic, rgb_intrinsic;
	Extrinsic ir_rgb_extrinsic;
	global_device->GetCameraParameters(ir_intrinsic, rgb_intrinsic, ir_rgb_extrinsic);
	output_ir_camera_params = cv::Mat::eye(cv::Size(3,3),CV_32FC1);
	output_ir_distortion_params = cv::Mat::zeros(cv::Size(1,5),CV_32FC1);
	output_rgb_camera_params = cv::Mat::eye(cv::Size(3,3),CV_32FC1);
	output_rgb_distortion_params = cv::Mat::zeros(cv::Size(1, 5), CV_32FC1);
	output_rotate_matrix = cv::Mat::eye(cv::Size(3,3),CV_32FC1);
	output_translate_matrix = cv::Mat::zeros(cv::Size(1,3),CV_32FC1);
	// copy ir camera matrix
	output_ir_camera_params.at<float>(0, 0) = ir_intrinsic.focal_length[0];
	output_ir_camera_params.at<float>(1, 1) = ir_intrinsic.focal_length[1];
	output_ir_camera_params.at<float>(0, 2) = ir_intrinsic.principal_point[0];
	output_ir_camera_params.at<float>(1, 2) = ir_intrinsic.principal_point[1];

	output_ir_distortion_params.at<float>(0, 0) = ir_intrinsic.distortion_coeffs[0];
	output_ir_distortion_params.at<float>(1, 0) = ir_intrinsic.distortion_coeffs[1];
	output_ir_distortion_params.at<float>(2, 0) = ir_intrinsic.distortion_coeffs[2];
	output_ir_distortion_params.at<float>(3, 0) = ir_intrinsic.distortion_coeffs[3];
	output_ir_distortion_params.at<float>(4, 0) = ir_intrinsic.distortion_coeffs[4];

	output_rgb_camera_params.at<float>(0, 0) = rgb_intrinsic.focal_length[0];
	output_rgb_camera_params.at<float>(1, 1) = rgb_intrinsic.focal_length[1];
	output_rgb_camera_params.at<float>(0, 2) = rgb_intrinsic.principal_point[0];
	output_rgb_camera_params.at<float>(1, 2) = rgb_intrinsic.principal_point[1];

	output_rgb_distortion_params.at<float>(0, 0) = rgb_intrinsic.distortion_coeffs[0];
	output_rgb_distortion_params.at<float>(1, 0) = rgb_intrinsic.distortion_coeffs[1];
	output_rgb_distortion_params.at<float>(2, 0) = rgb_intrinsic.distortion_coeffs[2];
	output_rgb_distortion_params.at<float>(3, 0) = rgb_intrinsic.distortion_coeffs[3];
	output_rgb_distortion_params.at<float>(4, 0) = rgb_intrinsic.distortion_coeffs[4];
	
	output_rotate_matrix.at<float>(0, 0) = ir_rgb_extrinsic.rotation_matrix[0];
	output_rotate_matrix.at<float>(0, 1) = ir_rgb_extrinsic.rotation_matrix[1];
	output_rotate_matrix.at<float>(0, 2) = ir_rgb_extrinsic.rotation_matrix[2];

	output_rotate_matrix.at<float>(1, 0) = ir_rgb_extrinsic.rotation_matrix[3];
	output_rotate_matrix.at<float>(1, 1) = ir_rgb_extrinsic.rotation_matrix[4];
	output_rotate_matrix.at<float>(1, 2) = ir_rgb_extrinsic.rotation_matrix[5];

	output_rotate_matrix.at<float>(2, 0) = ir_rgb_extrinsic.rotation_matrix[6];
	output_rotate_matrix.at<float>(2, 1) = ir_rgb_extrinsic.rotation_matrix[7];
	output_rotate_matrix.at<float>(2, 2) = ir_rgb_extrinsic.rotation_matrix[8];

	output_translate_matrix.at<float>(0, 0) = ir_rgb_extrinsic.translation_vector[0];
	output_translate_matrix.at<float>(1, 0) = ir_rgb_extrinsic.translation_vector[1];
	output_translate_matrix.at<float>(2, 0) = ir_rgb_extrinsic.translation_vector[2];




}

