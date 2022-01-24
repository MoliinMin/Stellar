
#ifndef STELLAR_IMPL_H
#define STELLAR_IMPL_H
#include "stellar.h"
#include "deptrum_device.h"
#include "global.h"
#include "surface_measurement.h"
class StellarImpl:public Stellar
{

public:
	StellarImpl() = default;
	~StellarImpl() = default;

	StellarErrors Initialize(const StellarParams &stellar_params) override;

	StellarErrors StartDevice() override;

	StellarErrors GetFrames(cv::Mat &output_depth_frame, cv::Mat &output_rgb_frame) override;

	StellarErrors DestoryDevice() override;

	StellarErrors StellarFusion(const cv::Mat &input_depth_mat, const cv::Mat &input_rgb_mat) override;
private:
	void Reset();
private:
	CameraParamsPyramid depth_camera_params_pyramid;
	
	DeptrumDevice deptrum_device;

	FrameData global_frame_data;

	SurfaceMeasurement surface_measurement;

	std::shared_ptr<StellarParams> stellar_params;

};


#endif
